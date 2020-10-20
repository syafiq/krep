#include <arpa/inet.h>
#include <linux/bpf.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/udp.h>
#include <string.h>
#include <bpf/bpf_helpers.h>
#include <stdlib.h>

#include "../common/xdp_stats_kern_user.h" /* common structure for both userspace and kernel code */
#include "../common/xdp_stats_kern.h"

SEC("xdp_prog")
int xdp_program(struct xdp_md *ctx)
{
	void *data_end = (void *)(long)ctx->data_end;
	void *data = (void *)(long)ctx->data;
	struct ethhdr *eth = data;
	struct iphdr *ip;
	struct udphdr *udp;
	unsigned char *payload, *msg;
	unsigned char dest_inside[9]; // FIXME: both 9 and 5 here are magic
	unsigned char msg_inside[5];
	unsigned int payload_size;
	unsigned int msg_n, dest_n;
	struct key_addr ka, key;
	struct mapval mv;
	__u64 get_ns;
	__u64 *t_now;
	__u64 TT1 = 1000000000;
	__u64 TT2 = 1000000000;
	__u64 TT3 = 1000000000;
	__u64 TF1 = 2000000;
	__u64 TF2 = 1000000;
	int a;
    __u64 dropvalinit = 0;
    __u32 drop = 1;
    __u64 passvalinit = 0;
    __u32 pass = 2;

    // sanity check
	ip = data + sizeof(*eth);
	udp = (void *)ip + sizeof(*ip);
	if ((void *)udp + sizeof(*udp) > data_end) {
		return XDP_PASS;
	}

	// if UDP
	if (ip->protocol == IPPROTO_UDP) {

		payload_size = ntohs(udp->len) - sizeof(*udp);
		payload = (unsigned char *)udp + sizeof(*udp);
		if ((void *)payload + payload_size > data_end)
			return XDP_PASS;

		if (htons(udp->dest) == 5683) { // if CoAP
			dest_n = bpf_probe_read_kernel_str(dest_inside, sizeof(dest_inside), payload);
			msg = (unsigned char *)payload + 9; // FIXME: and also here
			msg_n = bpf_probe_read_kernel_str(msg_inside, sizeof(msg_inside), msg);
			if ((dest_n > 0) && (msg_n > 0)) { 
				// bpf_printk("dest %s \n", dest_inside);
				// bpf_printk("msg %s \n", msg_inside);
				ka.saddr = ip->saddr;
				// FIXME: should be dest_inside, but strtoul conversion in bpf is kind of weird
				ka.daddr = 2893719744; 
				//bpf_printk("ka.saddr %lu ka.daddr %lu \n", ka.saddr, ka.daddr);
				__u64 *mv_get = bpf_map_lookup_elem(&mapall, &ka);
				get_ns = bpf_ktime_get_ns();
				t_now = &get_ns;

                __u32 tdiff_num = 1;
                __u32 *tdk = &tdiff_num;
                __u64 *td = bpf_map_lookup_elem(&tdiff, tdk);
                
                if (td) {
				    if (mv_get && t_now) {
				    	
				    	mv.ts1 = *((__u64 *)mv_get);
				    	mv.ts2 = *((__u64 *)mv_get +1);
				    	mv.c = *((__u64 *)mv_get +2);
				    	mv.dc = *((__u64 *)mv_get +3);
				    	mv.mark = *((__u64 *)mv_get +4);
				    	
				    	if(((*t_now)+(*td)-mv.ts2) > TT1) {
				    		mv.ts1 = (*t_now) + (*td);
				    		mv.c = 0;
				    		mv.dc = 0;
				    		mv.mark = 1;
				    	}
				    } else {
				    	mv.ts1 = (*t_now) + (*td);
				    	mv.ts2 = (*t_now) + (*td);
                        mv.c = 0;
				    	mv.dc = 0;
				    	mv.mark = 0;
				    }
				    mv.c = mv.c + 1;
				    mv.dc = mv.dc + 1;
			        mv.ts2 = (*t_now) + (*td);

				    __u64 mv_arr[5] = {mv.ts1, mv.ts2, mv.c, mv.dc, mv.mark};
				    void *vp = mv_arr;

				    bpf_map_update_elem(&mapall, &ka, vp, BPF_ANY);

				    if ((mv.ts2-mv.ts1) > TT2 ) { 
				    	if (((mv.c*1000000000)/(mv.ts2-mv.ts1)) > TF1) {
                            __u64 *dstat = bpf_map_lookup_elem(&stats, &drop);
                            if (dstat) {
                                __sync_fetch_and_add(dstat, 1);
                                bpf_map_update_elem(&stats, &drop, dstat, BPF_ANY);

                                __u64 *pstat2 = bpf_map_lookup_elem(&stats, &pass);
                                if (pstat2) {
                                    //bpf_printk("pstat %llu dstat %llu \n", *pstat2, *dstat);
                                } 

                            } else {
                                bpf_map_update_elem(&stats, &drop, &dropvalinit, BPF_ANY);
                            }
				    		return XDP_DROP;
				    	}
				    }

				    // LOW RATE attack
				    // =======================================================				
				    __u64 *look;
				    struct mapval mvl;
				    __u64 curr_ts1 = 0;
				    __u64 curr_ts2 = 0;
				    __u64 curr_cdc = 0;

				    // this loop might be optimized, it's a hack after all
				    for(a=101; a<106; a++) { // optim HERE! server: 192.168.101-105.5
				    	__u32 sa = (__u32) 16777216*5 + 65536*a + 256*168 + 192;
				    	__u32 da = (__u32) 16777216*172 + 65536*122 + 256*168 + 192;
				    	key.saddr = sa;
				    	key.daddr = da;
				    	look = bpf_map_lookup_elem(&mapall, &key);
				    	if (look) {
				    		mvl.ts1 = *((__u64 *)look);
				    		if ((mvl.ts1 < curr_ts1) || (curr_ts1 == 0)) {
				    			curr_ts1 = mvl.ts1;
				    		}
				    		mvl.ts2 = *((__u64 *)look+1);
				    		if (mvl.ts2 > curr_ts2) {
				    			curr_ts2 = mvl.ts2;
				    		}
				    		mvl.c = *((__u64 *)look+2);
				    		mvl.dc = *((__u64 *)look+3);
				    		curr_cdc = curr_cdc+mv.c+mv.dc;
                            bpf_printk("curr_cdc %llu \n", curr_cdc);
				    	}
				    }

				    if ((curr_ts2-curr_ts1 > TT3) && ((curr_cdc*1000000000/(curr_ts2-curr_ts1)) >= TF2) ) {
				    	return XDP_DROP;
				    }
                }
			}

            __u64 *pstat = bpf_map_lookup_elem(&stats, &pass);
            if (pstat) {
                __sync_fetch_and_add(pstat, 1);
                bpf_map_update_elem(&stats, &pass, pstat, BPF_ANY);
                //bpf_printk("pstat %llu \n", *pstat);
            } else {
                bpf_map_update_elem(&stats, &pass, &passvalinit, BPF_ANY);
            }

		}
	}

    return XDP_PASS;
}

char _license[] SEC("license") = "GPL";
