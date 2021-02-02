# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: esp_local_ctrl.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf.internal import enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


import constants_pb2 as constants__pb2


DESCRIPTOR = _descriptor.FileDescriptor(
  name='esp_local_ctrl.proto',
  package='',
  syntax='proto3',
  serialized_options=None,
  serialized_pb=_b('\n\x14\x65sp_local_ctrl.proto\x1a\x0f\x63onstants.proto\"\x15\n\x13\x43mdGetPropertyCount\">\n\x14RespGetPropertyCount\x12\x17\n\x06status\x18\x01 \x01(\x0e\x32\x07.Status\x12\r\n\x05\x63ount\x18\x02 \x01(\r\"a\n\x0cPropertyInfo\x12\x17\n\x06status\x18\x01 \x01(\x0e\x32\x07.Status\x12\x0c\n\x04name\x18\x02 \x01(\t\x12\x0c\n\x04type\x18\x03 \x01(\r\x12\r\n\x05\x66lags\x18\x04 \x01(\r\x12\r\n\x05value\x18\x05 \x01(\x0c\"\'\n\x14\x43mdGetPropertyValues\x12\x0f\n\x07indices\x18\x01 \x03(\r\"N\n\x15RespGetPropertyValues\x12\x17\n\x06status\x18\x01 \x01(\x0e\x32\x07.Status\x12\x1c\n\x05props\x18\x02 \x03(\x0b\x32\r.PropertyInfo\"-\n\rPropertyValue\x12\r\n\x05index\x18\x01 \x01(\r\x12\r\n\x05value\x18\x02 \x01(\x0c\"5\n\x14\x43mdSetPropertyValues\x12\x1d\n\x05props\x18\x01 \x03(\x0b\x32\x0e.PropertyValue\"0\n\x15RespSetPropertyValues\x12\x17\n\x06status\x18\x01 \x01(\x0e\x32\x07.Status\"\xfb\x02\n\x10LocalCtrlMessage\x12\x1e\n\x03msg\x18\x01 \x01(\x0e\x32\x11.LocalCtrlMsgType\x12\x32\n\x12\x63md_get_prop_count\x18\n \x01(\x0b\x32\x14.CmdGetPropertyCountH\x00\x12\x34\n\x13resp_get_prop_count\x18\x0b \x01(\x0b\x32\x15.RespGetPropertyCountH\x00\x12\x32\n\x11\x63md_get_prop_vals\x18\x0c \x01(\x0b\x32\x15.CmdGetPropertyValuesH\x00\x12\x34\n\x12resp_get_prop_vals\x18\r \x01(\x0b\x32\x16.RespGetPropertyValuesH\x00\x12\x32\n\x11\x63md_set_prop_vals\x18\x0e \x01(\x0b\x32\x15.CmdSetPropertyValuesH\x00\x12\x34\n\x12resp_set_prop_vals\x18\x0f \x01(\x0b\x32\x16.RespSetPropertyValuesH\x00\x42\t\n\x07payload*\xc7\x01\n\x10LocalCtrlMsgType\x12\x1b\n\x17TypeCmdGetPropertyCount\x10\x00\x12\x1c\n\x18TypeRespGetPropertyCount\x10\x01\x12\x1c\n\x18TypeCmdGetPropertyValues\x10\x04\x12\x1d\n\x19TypeRespGetPropertyValues\x10\x05\x12\x1c\n\x18TypeCmdSetPropertyValues\x10\x06\x12\x1d\n\x19TypeRespSetPropertyValues\x10\x07\x62\x06proto3')
  ,
  dependencies=[constants__pb2.DESCRIPTOR,])

_LOCALCTRLMSGTYPE = _descriptor.EnumDescriptor(
  name='LocalCtrlMsgType',
  full_name='LocalCtrlMsgType',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='TypeCmdGetPropertyCount', index=0, number=0,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TypeRespGetPropertyCount', index=1, number=1,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TypeCmdGetPropertyValues', index=2, number=4,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TypeRespGetPropertyValues', index=3, number=5,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TypeCmdSetPropertyValues', index=4, number=6,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TypeRespSetPropertyValues', index=5, number=7,
      serialized_options=None,
      type=None),
  ],
  containing_type=None,
  serialized_options=None,
  serialized_start=883,
  serialized_end=1082,
)
_sym_db.RegisterEnumDescriptor(_LOCALCTRLMSGTYPE)

LocalCtrlMsgType = enum_type_wrapper.EnumTypeWrapper(_LOCALCTRLMSGTYPE)
TypeCmdGetPropertyCount = 0
TypeRespGetPropertyCount = 1
TypeCmdGetPropertyValues = 4
TypeRespGetPropertyValues = 5
TypeCmdSetPropertyValues = 6
TypeRespSetPropertyValues = 7



_CMDGETPROPERTYCOUNT = _descriptor.Descriptor(
  name='CmdGetPropertyCount',
  full_name='CmdGetPropertyCount',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=41,
  serialized_end=62,
)


_RESPGETPROPERTYCOUNT = _descriptor.Descriptor(
  name='RespGetPropertyCount',
  full_name='RespGetPropertyCount',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='status', full_name='RespGetPropertyCount.status', index=0,
      number=1, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='count', full_name='RespGetPropertyCount.count', index=1,
      number=2, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=64,
  serialized_end=126,
)


_PROPERTYINFO = _descriptor.Descriptor(
  name='PropertyInfo',
  full_name='PropertyInfo',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='status', full_name='PropertyInfo.status', index=0,
      number=1, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='name', full_name='PropertyInfo.name', index=1,
      number=2, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='type', full_name='PropertyInfo.type', index=2,
      number=3, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='flags', full_name='PropertyInfo.flags', index=3,
      number=4, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='value', full_name='PropertyInfo.value', index=4,
      number=5, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value=_b(""),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=128,
  serialized_end=225,
)


_CMDGETPROPERTYVALUES = _descriptor.Descriptor(
  name='CmdGetPropertyValues',
  full_name='CmdGetPropertyValues',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='indices', full_name='CmdGetPropertyValues.indices', index=0,
      number=1, type=13, cpp_type=3, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=227,
  serialized_end=266,
)


_RESPGETPROPERTYVALUES = _descriptor.Descriptor(
  name='RespGetPropertyValues',
  full_name='RespGetPropertyValues',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='status', full_name='RespGetPropertyValues.status', index=0,
      number=1, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='props', full_name='RespGetPropertyValues.props', index=1,
      number=2, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=268,
  serialized_end=346,
)


_PROPERTYVALUE = _descriptor.Descriptor(
  name='PropertyValue',
  full_name='PropertyValue',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='index', full_name='PropertyValue.index', index=0,
      number=1, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='value', full_name='PropertyValue.value', index=1,
      number=2, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value=_b(""),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=348,
  serialized_end=393,
)


_CMDSETPROPERTYVALUES = _descriptor.Descriptor(
  name='CmdSetPropertyValues',
  full_name='CmdSetPropertyValues',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='props', full_name='CmdSetPropertyValues.props', index=0,
      number=1, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=395,
  serialized_end=448,
)


_RESPSETPROPERTYVALUES = _descriptor.Descriptor(
  name='RespSetPropertyValues',
  full_name='RespSetPropertyValues',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='status', full_name='RespSetPropertyValues.status', index=0,
      number=1, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=450,
  serialized_end=498,
)


_LOCALCTRLMESSAGE = _descriptor.Descriptor(
  name='LocalCtrlMessage',
  full_name='LocalCtrlMessage',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='msg', full_name='LocalCtrlMessage.msg', index=0,
      number=1, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='cmd_get_prop_count', full_name='LocalCtrlMessage.cmd_get_prop_count', index=1,
      number=10, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='resp_get_prop_count', full_name='LocalCtrlMessage.resp_get_prop_count', index=2,
      number=11, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='cmd_get_prop_vals', full_name='LocalCtrlMessage.cmd_get_prop_vals', index=3,
      number=12, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='resp_get_prop_vals', full_name='LocalCtrlMessage.resp_get_prop_vals', index=4,
      number=13, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='cmd_set_prop_vals', full_name='LocalCtrlMessage.cmd_set_prop_vals', index=5,
      number=14, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='resp_set_prop_vals', full_name='LocalCtrlMessage.resp_set_prop_vals', index=6,
      number=15, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
    _descriptor.OneofDescriptor(
      name='payload', full_name='LocalCtrlMessage.payload',
      index=0, containing_type=None, fields=[]),
  ],
  serialized_start=501,
  serialized_end=880,
)

_RESPGETPROPERTYCOUNT.fields_by_name['status'].enum_type = constants__pb2._STATUS
_PROPERTYINFO.fields_by_name['status'].enum_type = constants__pb2._STATUS
_RESPGETPROPERTYVALUES.fields_by_name['status'].enum_type = constants__pb2._STATUS
_RESPGETPROPERTYVALUES.fields_by_name['props'].message_type = _PROPERTYINFO
_CMDSETPROPERTYVALUES.fields_by_name['props'].message_type = _PROPERTYVALUE
_RESPSETPROPERTYVALUES.fields_by_name['status'].enum_type = constants__pb2._STATUS
_LOCALCTRLMESSAGE.fields_by_name['msg'].enum_type = _LOCALCTRLMSGTYPE
_LOCALCTRLMESSAGE.fields_by_name['cmd_get_prop_count'].message_type = _CMDGETPROPERTYCOUNT
_LOCALCTRLMESSAGE.fields_by_name['resp_get_prop_count'].message_type = _RESPGETPROPERTYCOUNT
_LOCALCTRLMESSAGE.fields_by_name['cmd_get_prop_vals'].message_type = _CMDGETPROPERTYVALUES
_LOCALCTRLMESSAGE.fields_by_name['resp_get_prop_vals'].message_type = _RESPGETPROPERTYVALUES
_LOCALCTRLMESSAGE.fields_by_name['cmd_set_prop_vals'].message_type = _CMDSETPROPERTYVALUES
_LOCALCTRLMESSAGE.fields_by_name['resp_set_prop_vals'].message_type = _RESPSETPROPERTYVALUES
_LOCALCTRLMESSAGE.oneofs_by_name['payload'].fields.append(
  _LOCALCTRLMESSAGE.fields_by_name['cmd_get_prop_count'])
_LOCALCTRLMESSAGE.fields_by_name['cmd_get_prop_count'].containing_oneof = _LOCALCTRLMESSAGE.oneofs_by_name['payload']
_LOCALCTRLMESSAGE.oneofs_by_name['payload'].fields.append(
  _LOCALCTRLMESSAGE.fields_by_name['resp_get_prop_count'])
_LOCALCTRLMESSAGE.fields_by_name['resp_get_prop_count'].containing_oneof = _LOCALCTRLMESSAGE.oneofs_by_name['payload']
_LOCALCTRLMESSAGE.oneofs_by_name['payload'].fields.append(
  _LOCALCTRLMESSAGE.fields_by_name['cmd_get_prop_vals'])
_LOCALCTRLMESSAGE.fields_by_name['cmd_get_prop_vals'].containing_oneof = _LOCALCTRLMESSAGE.oneofs_by_name['payload']
_LOCALCTRLMESSAGE.oneofs_by_name['payload'].fields.append(
  _LOCALCTRLMESSAGE.fields_by_name['resp_get_prop_vals'])
_LOCALCTRLMESSAGE.fields_by_name['resp_get_prop_vals'].containing_oneof = _LOCALCTRLMESSAGE.oneofs_by_name['payload']
_LOCALCTRLMESSAGE.oneofs_by_name['payload'].fields.append(
  _LOCALCTRLMESSAGE.fields_by_name['cmd_set_prop_vals'])
_LOCALCTRLMESSAGE.fields_by_name['cmd_set_prop_vals'].containing_oneof = _LOCALCTRLMESSAGE.oneofs_by_name['payload']
_LOCALCTRLMESSAGE.oneofs_by_name['payload'].fields.append(
  _LOCALCTRLMESSAGE.fields_by_name['resp_set_prop_vals'])
_LOCALCTRLMESSAGE.fields_by_name['resp_set_prop_vals'].containing_oneof = _LOCALCTRLMESSAGE.oneofs_by_name['payload']
DESCRIPTOR.message_types_by_name['CmdGetPropertyCount'] = _CMDGETPROPERTYCOUNT
DESCRIPTOR.message_types_by_name['RespGetPropertyCount'] = _RESPGETPROPERTYCOUNT
DESCRIPTOR.message_types_by_name['PropertyInfo'] = _PROPERTYINFO
DESCRIPTOR.message_types_by_name['CmdGetPropertyValues'] = _CMDGETPROPERTYVALUES
DESCRIPTOR.message_types_by_name['RespGetPropertyValues'] = _RESPGETPROPERTYVALUES
DESCRIPTOR.message_types_by_name['PropertyValue'] = _PROPERTYVALUE
DESCRIPTOR.message_types_by_name['CmdSetPropertyValues'] = _CMDSETPROPERTYVALUES
DESCRIPTOR.message_types_by_name['RespSetPropertyValues'] = _RESPSETPROPERTYVALUES
DESCRIPTOR.message_types_by_name['LocalCtrlMessage'] = _LOCALCTRLMESSAGE
DESCRIPTOR.enum_types_by_name['LocalCtrlMsgType'] = _LOCALCTRLMSGTYPE
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

CmdGetPropertyCount = _reflection.GeneratedProtocolMessageType('CmdGetPropertyCount', (_message.Message,), dict(
  DESCRIPTOR = _CMDGETPROPERTYCOUNT,
  __module__ = 'esp_local_ctrl_pb2'
  # @@protoc_insertion_point(class_scope:CmdGetPropertyCount)
  ))
_sym_db.RegisterMessage(CmdGetPropertyCount)

RespGetPropertyCount = _reflection.GeneratedProtocolMessageType('RespGetPropertyCount', (_message.Message,), dict(
  DESCRIPTOR = _RESPGETPROPERTYCOUNT,
  __module__ = 'esp_local_ctrl_pb2'
  # @@protoc_insertion_point(class_scope:RespGetPropertyCount)
  ))
_sym_db.RegisterMessage(RespGetPropertyCount)

PropertyInfo = _reflection.GeneratedProtocolMessageType('PropertyInfo', (_message.Message,), dict(
  DESCRIPTOR = _PROPERTYINFO,
  __module__ = 'esp_local_ctrl_pb2'
  # @@protoc_insertion_point(class_scope:PropertyInfo)
  ))
_sym_db.RegisterMessage(PropertyInfo)

CmdGetPropertyValues = _reflection.GeneratedProtocolMessageType('CmdGetPropertyValues', (_message.Message,), dict(
  DESCRIPTOR = _CMDGETPROPERTYVALUES,
  __module__ = 'esp_local_ctrl_pb2'
  # @@protoc_insertion_point(class_scope:CmdGetPropertyValues)
  ))
_sym_db.RegisterMessage(CmdGetPropertyValues)

RespGetPropertyValues = _reflection.GeneratedProtocolMessageType('RespGetPropertyValues', (_message.Message,), dict(
  DESCRIPTOR = _RESPGETPROPERTYVALUES,
  __module__ = 'esp_local_ctrl_pb2'
  # @@protoc_insertion_point(class_scope:RespGetPropertyValues)
  ))
_sym_db.RegisterMessage(RespGetPropertyValues)

PropertyValue = _reflection.GeneratedProtocolMessageType('PropertyValue', (_message.Message,), dict(
  DESCRIPTOR = _PROPERTYVALUE,
  __module__ = 'esp_local_ctrl_pb2'
  # @@protoc_insertion_point(class_scope:PropertyValue)
  ))
_sym_db.RegisterMessage(PropertyValue)

CmdSetPropertyValues = _reflection.GeneratedProtocolMessageType('CmdSetPropertyValues', (_message.Message,), dict(
  DESCRIPTOR = _CMDSETPROPERTYVALUES,
  __module__ = 'esp_local_ctrl_pb2'
  # @@protoc_insertion_point(class_scope:CmdSetPropertyValues)
  ))
_sym_db.RegisterMessage(CmdSetPropertyValues)

RespSetPropertyValues = _reflection.GeneratedProtocolMessageType('RespSetPropertyValues', (_message.Message,), dict(
  DESCRIPTOR = _RESPSETPROPERTYVALUES,
  __module__ = 'esp_local_ctrl_pb2'
  # @@protoc_insertion_point(class_scope:RespSetPropertyValues)
  ))
_sym_db.RegisterMessage(RespSetPropertyValues)

LocalCtrlMessage = _reflection.GeneratedProtocolMessageType('LocalCtrlMessage', (_message.Message,), dict(
  DESCRIPTOR = _LOCALCTRLMESSAGE,
  __module__ = 'esp_local_ctrl_pb2'
  # @@protoc_insertion_point(class_scope:LocalCtrlMessage)
  ))
_sym_db.RegisterMessage(LocalCtrlMessage)


# @@protoc_insertion_point(module_scope)
