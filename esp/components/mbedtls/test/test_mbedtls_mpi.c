/* mbedTLS bignum (MPI) self-tests as unit tests
*/
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <esp_system.h>
#include "mbedtls/bignum.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "unity.h"
#include "sdkconfig.h"

#define MBEDTLS_OK 0

/* Debugging function to print an MPI number to stdout. Happens to
   print output that can be copy-pasted directly into a Python shell.
*/
void mbedtls_mpi_printf(const char *name, const mbedtls_mpi *X)
{
    static char buf[2048];
    size_t n;
    memset(buf, 0, sizeof(buf));
    mbedtls_mpi_write_string(X, 16, buf, sizeof(buf)-1, &n);
    if(n) {
        printf("%s = 0x%s\n", name, buf);
    } else {
        printf("%s = TOOLONG\n", name);
    }
}

/* 
    Assert E == X, X=A*B if res_operands_overlap==0
    Assert E == A, A=A*B if res_operands_overlap==1
    Assert E == B, B=A*B if res_operands_overlap==2
*/
static void test_bignum_mult_variant(const char *a_str, const char *b_str, const char *e_str, size_t mod_bits, int res_operands_overlap)
{
    mbedtls_mpi A, B, X, E, M;
    char x_buf[2048] = {0};
    size_t x_buf_len = 0;

    mbedtls_mpi_init(&A);
    mbedtls_mpi_init(&B);
    mbedtls_mpi_init(&X);
    mbedtls_mpi_init(&E);

    TEST_ASSERT_FALSE(mbedtls_mpi_read_string(&A, 16, a_str));
    TEST_ASSERT_FALSE(mbedtls_mpi_read_string(&B, 16, b_str));

    /* calulate X = A * B variant */
    TEST_ASSERT_FALSE(mbedtls_mpi_read_string(&E, 16, e_str));
    if (res_operands_overlap == 0) {
        TEST_ASSERT_FALSE(mbedtls_mpi_mul_mpi(&X, &A, &B));
    } else if (res_operands_overlap == 1) {
        mbedtls_mpi_copy( &X, &A );
        TEST_ASSERT_FALSE(mbedtls_mpi_mul_mpi(&X, &X, &B));
    } else if (res_operands_overlap == 2) {
        mbedtls_mpi_copy( &X, &B );
        TEST_ASSERT_FALSE(mbedtls_mpi_mul_mpi(&X, &A, &X));
    }

    mbedtls_mpi_write_string(&X, 16, x_buf, sizeof(x_buf)-1, &x_buf_len);
    TEST_ASSERT_EQUAL_STRING_MESSAGE(e_str, x_buf, "mbedtls_mpi_mul_mpi result wrong");

    /* if mod_bits arg is set, also do a esp_mpi_mul_mod() call */
    if (mod_bits > 0) {
        mbedtls_mpi_init(&M);
        for(int i = 0; i < mod_bits; i++) {
            mbedtls_mpi_set_bit(&M, i, 1);
        }

        TEST_ASSERT_FALSE(esp_mpi_mul_mpi_mod(&X, &A, &B, &M));

        mbedtls_mpi_write_string(&X, 16, x_buf, sizeof(x_buf)-1, &x_buf_len);
        TEST_ASSERT_EQUAL_STRING_MESSAGE(e_str, x_buf, "esp_mpi_mul_mpi_mod result wrong");

        mbedtls_mpi_free(&M);
    }


    mbedtls_mpi_free(&A);
    mbedtls_mpi_free(&B);
    mbedtls_mpi_free(&X);
    mbedtls_mpi_free(&E);
}

/* Assert E = A * B, including 3 variants: X=A*B A*=B, B*=A */
static void test_bignum_mult(const char *a_str, const char *b_str, const char *e_str, size_t mod_bits)
{
    for (int overlap_operands=0; overlap_operands < 3; ++overlap_operands) {
        test_bignum_mult_variant(a_str, b_str, e_str, mod_bits, overlap_operands);
    }
}


TEST_CASE("test MPI multiplication", "[bignum]")
{
    /* Run some trivial numbers tests w/ various high modulo bit counts,
     should make no difference to the result
    */
    for(int i = 512; i <= 4096; i+= 512) {
        test_bignum_mult("10", "100", "1000",
                         i);
    }

    test_bignum_mult("60006FA8D3E3BD746BE39B860FFAADB4F108E15CF2ED8F685FB0E86CC4CB107A488720B41C3F1E18550F00619CD3CA8442296ECB54D2F52ECEE5346D310195700000000",
                     "BF474CA7",
                     "047BB102CAF58A48D3D97E4231BC0B753051D8232B9B939A2A4E310F88E65FEFD7762FC2DE0E2BAD6AA51A391DFFABD120653A312E4998F42E2C03AA404EE63B67275BC100000000",
                     1024);

    test_bignum_mult("49493AC229831EC01EEB01EAF3BBEBC44768EADF9ABC30C87D1791F5E04245756ED4965361EC0599626884DF079B6B5738985CE76BD66FAA67E3AAAD60775D5C9D44C09FDF9E27C033696C007BE1C540D718CA148BA01FFA4A358541E9E9F02F72BE37AFAB037DAEA5E3669A770400D2F4A5DBBD83A83919D05E3DD64787BC80000000",
                     "B878CC29",
                     "34CF37013066D5BDA2C86CF1FE7BDA66604E0D55DAFF9864B6E727BFF5871012B0AB73D28D4E100BA1E4607AA2A247C912FDBC435C6BF7C5F8E00278AE1381B1E5F6E3D52D2CBE819F0D65CB37370666D156E7A7B1FD4698D8C9D3165FC8A83F9293C839521993619CCF8180E521300C4306206C9121D629754F1FCC7839BF6DFAF33080000000",
                     3072);

    test_bignum_mult("24BF6185468786FDD303083D25E64EFC66CA472BC44D253102F8B4A9D3BFA75091386C0077937FE33FA3252D28855837AE1B484A8A9A45F7EE8C0C634F9E8CDDF79C5CE07EE72C7F123142198164234CABB724CF78B8173B9F880FC86322407AF1FEDFDDE2BEB674CA15F3E81A1521E071513A1E85B5DFA031F21ECAE9A34D",
                     "010001",
                     "24BF8644A80CCD855A00DB402E2374E2B5C6ADF60B78E97E2829B7A288697B103888FD38E393F776BF8664D04DB280BD0652F665D2E4D0923483FAEF5C01DC7C847A547CDBC7AB663EB0544AC37DA4B0CF03D0869D878FF3B6C3AF5072EAA39D3279D1DCC29C9933808ABDFE0DFD3BF59331AB6FBFD46556119250BD086E36A34D",
        1536);

    test_bignum_mult("-5D88B669C417EDD02213723546A906B7E9DA7683780E9B54856A2147467ADA316F8819D69486FC8056FE1E8EA7DEC5D5EF12340B95C4FC966F4B348D35893620",
                     "9AE7FBC99546432DF71896FC239EADAEF38D18D2B2F0E2DD275AA977E2BF4411F5A3B2A5D33605AEBBCCBA7FEB9F2D2FA74206CEC169D74BF5A8C50D6F48EA08",
                     "-38990016EB21810E3B5E6AEE339AEE72BB7CD629C4C9270A3D832701A2949BC82B2BE5A7F900C0C9937464699862821976095187D646884E8FBF01DE8C3442F3BC97B670AF573EFB74A9BBEBE4432EE74B0A83BBCDF59485D332B1FF49EB461A3A8B12C38FD72C7772D75EC6EBA5633199540C47678BD2F4ADEEA40830C2F100",
        2048);


    /* 1 << 2050 * 0X1234 */
    test_bignum_mult("400000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                     "1234",
                     "48D000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                     3072);

    /* multiply a 1178 bit number by a 2050 bit number */
    test_bignum_mult("AAAAAAAAAA75124938ABBECD0EEEEE333333333333333333333FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFAAAAAAABBBBBBBBBBBBBBBBBBBB000000000000000000000000000000000004988A5293848932948872398400000000000FFFFFFFFFFF0000000000000EDFABC0204048975876873487387478327482374871327482347328742837483247283748234723874238",
                     "390587293875124938ABBECD0EEEEE3333333333333333333333333333333399999888000AAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBB00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000EDFABC0204048975876873487387478327482374871327482347328742837483247283748234723874238478327400000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000003012111111111111111100000000000000000000000111111111111111111111111",
                     "02603AF70D0421C1AD82CE623F28F70B128118D06D00C27D433EC25BA86E6105C3890A0B1973B8BE068CA68E159A21078785DDB37F94216FBF4AEC939958AF4B8CEA2A48895CECA87562FC846EAAE0C866AF9D41EEABFB1D579F5828E9666A15E2AF946F16A189B5C645872FDCA247D309AB0BCAFB0D112881186FCFFEDC87061B4AE4A375E9BBCF579A7BC87A8EAC8C6F66E107986FC603F920F5E1A0FD8C619D88D90066FFFC8F4DB77437EBD7E3BD7E398C4C01F93426E347E039DCA7B0A73C0C90A9C4271BB761ADFF88971D190CE5DA98EFC5D7390D33BC034908AF81D784A4D7F32D0902E0C5DABC706635D5A28FC0E3A364EDEB21E8E117041D0E4B51CA6F9684F434057E7FCF2AF6BD050334B1D11E043B0967154E57354B681161D3C618974D5A7E0385755B80B931AE9B59DD4402BAEC206F04B8440741B3C4CA6D9F7DAF0AE6B3BF1B24B76C2F12B9E9A7C50D32E2093608FC9A30CBD852329E64A9AE0BC3F513899EBFA28629C1DF38081FB8C6630408F70D7B9A37701ABA4176C8B7DCB8CC78BD7783B861A7FC50862E75191DB8",
                     4096);

    /* multiply two very large numbers (4080 bits x 4088 bits) with and without overlapping multipliers/multiplicant */
    test_bignum_mult("B96BF707C8CD3CA5AE8247C5CA2AF98140EFAE60179BE3F5BEAD7DA3C6D17404C529239DD1EFE6CADAE1AAFB4FE936B0107839C28A7861E4364EB093CB4698E4BBF6BD8BEF85D9B35781D14AEE1BE86E57B49DF98896CF037CCBD8C622603D84891FD6AC48BE4728E564E64FB715C149C243BAA289569D0FF2E0C9E183D38C8A669CEFF542737E35F3E484D39FF7A3727EF8DB733DAB3E359E1456C0AE33C358EFEC8079EDDD5D58E09B37744EE1DBDF567742CFC0CE98BCC9AD90242ECCF7F6FA696C8C1B32A4D7285C56AB3658DB1AD89A7331F69DEFE212DE8EEEE5B377EC7A4112A27A0FD02EFABB9D3025F6563B65DC214A38A6E7BF8C78B6A3D2A8BA12D75BFBF26ACA655EF13A145AC18D2A6C9B535AAF8290314A2512451B3BD6DA19C42F1FD1B958E1F49303EDEC0392A8CD8450FBC177B26FD2D6CC23F051655565B42FEDE9685A9E708CFC8EA766B94D7B9B627BFA98945BB8EF88E9E7FB696BC4729240F1C25F7085E8C8A9DE2241BBC388FFC65E0058B4327D554FD2D8AA872614052C38BE177F9EC0E705DFDD5F82DD5ED49DAF3582CA64E7F14CE97FD6F25B53FD888D1593450EDC5E79A947F18D0917E01F66ACE99FF4A249C14957A9860B839CEE5096F78FE02C7610E558FC0FCA803A6EF0FBA64AB94893E61080BC5D2AC5DA548E9E0D8E2B63BAB6B82247DF22007D925711E0FE45EB14B92665B6",
                        "C15B96BF707C8CD3CA5AE8247C5CA2AF98140EFAE60179BE3F5BEAD7DA3C6D17404C529239DD1EFE6CADAE1AAFB4FE936B0107839C28A7861E4364EB093CB4698E4BBF6BD8BEF85D9B35781D14AEE1BE86E57B49DF98896CF037CCBD8C622603D84891FD6AC48BE4728E564E64FB715C149C243BAA289569D0FF2E0C9E183D38C8A669CEFF542737E35F3E484D39FF7A3727EF8DB733DAB3E359E1456C0AE33C358EFEC8079EDDD5D58E09B37744EE1DBDF567742CFC0CE98BCC9AD90242ECCF7F6FA696C8C1B32A4D7285C56AB3658DB1AD89A7331F69DEFE212DE8EEEE5B377EC7A4112A27A0FD02EFABB9D3025F6563B65DC214A38A6E7BF8C78B6A3D2A8BA12D75BFBF26ACA655EF13A145AC18D2A6C9B535AAF8290314A2512451B3BD6DA19C42F1FD1B958E1F49303EDEC0392A8CD8450FBC177B26FD2D6CC23F051655565B42FEDE9685A9E708CFC8EA766B94D7B9B627BFA98945BB8EF88E9E7FB696BC4729240F1C25F7085E8C8A9DE2241BBC388FFC65E0058B4327D554FD2D8AA872614052C38BE177F9EC0E705DFDD5F82DD5ED49DAF3582CA64E7F14CE97FD6F25B53FD888D1593450EDC5E79A947F18D0917E01F66ACE99FF4A249C14957A9860B839CEE5096F78FE02C7610E558FC0FCA803A6EF0FBA64AB94893E61080BC5D2AC5DA548E9E0D8E2B63BAB6B82247DF22007D925711E0FE45EB14B92665B6",
                        "08C0CBBCD99EC6C840B63887B07378C45DF268C118061B2AFFD9D0C854EE0F7DE5F548FF5BA7F155CCA81EF086F9760FCD86722167AC88E504723CB19A772D9EFF4EC75DD29F6187D34535B2A801C82DF9B1D0F08B64373A5AE5BD31346EE06EDB032B0A306A871E4FDB576F3E8D8F32ED4E054D9292719E77A1C5500FBEC23C59F5CC49A4E0B49D15F92D426FEF36376CB674AACDABF68A731746CA74440C71534D30CBF0252DE4EC38EA53E5821C9868F636239923C460CB813C4F05DD5EC36987A390FDBB7EE345F9D2687D1EF9A26A1FF84BF38049E995E1A5F2D5318A7BEFC9AA15528F7A2253299D30718459CF7958694AA58D91CA28F22718D07105C3FBFA4FEA970A810DD52BFC6AB4D44E3253347A3C5F42C1E723588343B210581F3B8A97C616A26C9C99C1376E169B8C8ED5DE6FA2272D24FB05BA6351B687A27C5CA1CF3FC1BA2BF06DD7598DED3F89080A2AB6DD694000698A7488274396E55EA78104584A5A0523C4744D018DCBFD3E411DA8CA679199FE818C59E08B126356028E3B6AAEA61ACE679D6EF2587CCAE513AB99EB161A405A8AA6FB36BB308BB7CBC21E2117B7CE4B4D1A1FE7EE0386DD229220BFD892A293FD7B8F6617743612736CC2F6200C736FD49C6A4AC9565E4B4EFD841C5FC3F6883621FD4319A11319EF462B549A12DA699612F2E8CE08525559C3487AAD57DFDBF1CAB847174C2FF8BA8D5232E33E5D8F60E5BE4CD8BE5857A860B615EFCFFF38DC0EE6A40F725D5275892419D3915EDB534166AC402B5849EB16AF1E8ADA68EF8C2E6AC8BE254DAEDAC135DA0ECA0E5A3CCF5332CFAB4C2249A92EF96A7DD6F69B4B0F9379CDA164FB1CB1934F27F42C0CEF9AFBA6A0B1716A4A1092E6CC7081AC74503A22F3C2071BB4D3A6842772C02CE78BD1FB4E0D39EB19E2425D3DC77777A8E8254F86A69950C75C1D8CF98C512ECEAF2FF15DC8A6D373A20045F63166BFDB8899C6095D91FC282D49DB9154E74DC64C41A98EFABDB207FF31A88718FF5410EA5A15E76F9591E5BE3B26035FD8567117588D9B94708B98FD764529B43B09EC6A2CDF79E2C05D3A799484516369795E103C7FCB78F1B1CADA47C3092695220FF2DB05136A9401897DE182EDB89022E4E7419B43172808C0A9F3ED80A8DF0A9E5F8E59E57994053050E709E63A4809AAECC3DEABDF5E2B9ED3F8FDA6297811A666E81BB0914B1F9D5D558EE40DBD89BE8B9D7F58575CE66C5A5EC2939463D1CECDD760B2C0584535FEEB2125CB675A1AB09CEDC81F27FA6830423B1F8D426E361EB1B9AD203C33176ACAB28C618714E068DA294C9338EF92FF4ED9F67F438E33E53797C1C31F8FF8D5466887E5610EA41C0CABC07ED90894BA73ECF84F5F3C5443EFAC61F9826C54D176D482CB5174D08A7EA3C3933FEE4986DB38A1EEC08D3366711D64",
                        0);

}

static bool test_bignum_modexp(const char *z_str, const char *x_str, const char *y_str, const char *m_str, int ret_error)
{
    mbedtls_mpi Z, X, Y, M;
    char z_buf[400] = { 0 };
    size_t z_buf_len = 0;
    bool fail = false;

    printf("%s = (%s ^ %s) mod %s  ret=%d ... ", z_str, x_str, y_str, m_str, ret_error);

    mbedtls_mpi_init(&Z);
    mbedtls_mpi_init(&X);
    mbedtls_mpi_init(&Y);
    mbedtls_mpi_init(&M);

    TEST_ASSERT_FALSE(mbedtls_mpi_read_string(&X, 16, x_str));
    TEST_ASSERT_FALSE(mbedtls_mpi_read_string(&Y, 16, y_str));
    TEST_ASSERT_FALSE(mbedtls_mpi_read_string(&M, 16, m_str));

    //mbedtls_mpi_printf("X", &X);
    //mbedtls_mpi_printf("X", &Y);
    //mbedtls_mpi_printf("M", &M);

    /* Z = (X ^ Y) mod M */
    if (ret_error != mbedtls_mpi_exp_mod(&Z, &X, &Y, &M, NULL)) {
        fail = true;
    }

    if (ret_error == MBEDTLS_OK) {
        mbedtls_mpi_write_string(&Z, 16, z_buf, sizeof(z_buf)-1, &z_buf_len);
        if (memcmp(z_str, z_buf, strlen(z_str)) != 0) {
            printf("\n Expected '%s' Was '%s' \n", z_str, z_buf);
            fail = true;
        }
    }

    mbedtls_mpi_free(&Z);
    mbedtls_mpi_free(&X);
    mbedtls_mpi_free(&Y);
    mbedtls_mpi_free(&M);

    if (fail == true) {
        printf(" FAIL\n");
    } else {
        printf(" PASS\n");
    }
    return fail;
}

TEST_CASE("test MPI modexp", "[bignum]")
{
    bool test_error = false;
    printf("Z = (X ^ Y) mod M \n");
    // test_bignum_modexp(Z, X, Y, M, ret_error);
    test_error |= test_bignum_modexp("01000000", "1000", "2", "FFFFFFFF", MBEDTLS_OK);
    test_error |= test_bignum_modexp("014B5A90", "1234", "2", "FFFFFFF", MBEDTLS_OK);
    test_error |= test_bignum_modexp("01234321", "1111", "2", "FFFFFFFF", MBEDTLS_OK);
    test_error |= test_bignum_modexp("02", "5", "1", "3", MBEDTLS_OK);
    test_error |= test_bignum_modexp("22", "55", "1", "33", MBEDTLS_OK);
    test_error |= test_bignum_modexp("0222", "555", "1", "333", MBEDTLS_OK);
    test_error |= test_bignum_modexp("2222", "5555", "1", "3333", MBEDTLS_OK);
    test_error |= test_bignum_modexp("11", "5555", "1", "33", MBEDTLS_OK);
    test_error |= test_bignum_modexp("55", "1111", "1", "77", MBEDTLS_OK);
    test_error |= test_bignum_modexp("88", "1111", "2", "BB", MBEDTLS_OK);
    test_error |= test_bignum_modexp("01000000", "2", "128", "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", MBEDTLS_OK);
    test_error |= test_bignum_modexp("0ABCDEF12345", "ABCDEF12345", "1", "FFFFFFFFFFFF", MBEDTLS_OK);
    test_error |= test_bignum_modexp("0ABCDE", "ABCDE", "1", "FFFFF", MBEDTLS_OK);

    test_error |= test_bignum_modexp("04",  "2",  "2",  "9",  MBEDTLS_OK);
    test_error |= test_bignum_modexp("04",  "2", "-2",  "9",  MBEDTLS_ERR_MPI_BAD_INPUT_DATA);
    test_error |= test_bignum_modexp("04",  "2",  "2", "-9",  MBEDTLS_ERR_MPI_BAD_INPUT_DATA);
    test_error |= test_bignum_modexp("04",  "2", "-2", "-9",  MBEDTLS_ERR_MPI_BAD_INPUT_DATA);

    test_error |= test_bignum_modexp("01",  "2",  "0",  "9",  MBEDTLS_OK);
    test_error |= test_bignum_modexp("04",  "2",  "0",  "0",  MBEDTLS_ERR_MPI_BAD_INPUT_DATA);
    test_error |= test_bignum_modexp("04",  "2",  "2",  "0",  MBEDTLS_ERR_MPI_BAD_INPUT_DATA);
    test_error |= test_bignum_modexp("00",  "0",  "2",  "9",  MBEDTLS_OK);
    test_error |= test_bignum_modexp("01",  "0",  "0",  "9",  MBEDTLS_OK);

    test_error |= test_bignum_modexp("04", "-2",  "2",  "9",  MBEDTLS_OK);
    test_error |= test_bignum_modexp("01", "-2",  "0",  "9",  MBEDTLS_OK);
    test_error |= test_bignum_modexp("07", "-2",  "7",  "9",  MBEDTLS_OK);
    test_error |= test_bignum_modexp("07", "-2",  "1",  "9",  MBEDTLS_OK);
    test_error |= test_bignum_modexp("02",  "2",  "1",  "9",  MBEDTLS_OK);
    test_error |= test_bignum_modexp("01",  "2",  "0",  "9",  MBEDTLS_OK);

    test_error |= test_bignum_modexp("05",  "5",  "7",  "7",  MBEDTLS_OK);
    test_error |= test_bignum_modexp("02", "-5",  "7",  "7",  MBEDTLS_OK);
    test_error |= test_bignum_modexp("01", "-5",  "7",  "3",  MBEDTLS_OK);

    TEST_ASSERT_FALSE_MESSAGE(test_error, "mbedtls_mpi_exp_mod incorrect for some tests\n");
}

