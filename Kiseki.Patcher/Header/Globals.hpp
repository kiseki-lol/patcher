#pragma once

#define ALLOWED_WILDCARD_DOMAINS "kiseki.lol", "rbxcdn.com", "roblox.com"
#define ALLOWED_DOMAINS
#define ALLOWED_SCHEMES "http", "https"
#define ALLOWED_EMBEDDED_SCHEMES "javascript", "jscript", "res"

#define PUBLIC_KEY 0x06, 0x02, 0x00, 0x00, 0x00, 0xA4, 0x00, 0x00, 0x52, 0x53, 0x41, 0x31, 0x00, 0x04, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0xA5, 0x11, 0xD0, 0x9F, 0xAB, 0x9B, 0x3A, 0x96, 0xC5, 0xBE, 0x50, 0xBB, 0xCA, 0x0C, 0xBB, 0xC8, 0x1A, 0x9C, 0xC1, 0x2F, 0x22, 0x7A, 0x80, 0x2C, 0x31, 0x01, 0xE1, 0x21, 0xC2, 0x7F, 0xE0, 0x10, 0xA1, 0x2D, 0x09, 0xED, 0x10, 0x3E, 0x28, 0xB9, 0xBD, 0x0F, 0x38, 0xDB, 0x52, 0x78, 0xC0, 0xEC, 0x04, 0xD4, 0x00, 0xAD, 0x45, 0xD3, 0xC7, 0x78, 0xF2, 0x83, 0xB5, 0x5B, 0x16, 0x0C, 0x32, 0x5D, 0xB3, 0x3B, 0xDA, 0xA2, 0x9C, 0x73, 0xB2, 0x0C, 0x09, 0x93, 0xD8, 0xF8, 0xD9, 0xC5, 0x75, 0xAB, 0x33, 0x19, 0xD3, 0x6A, 0xAF, 0x20, 0x21, 0x6C, 0x78, 0x31, 0x41, 0xD1, 0xCD, 0x6D, 0x4D, 0xA1, 0x6D, 0x49, 0x3A, 0x6A, 0x33, 0x10, 0x6D, 0x52, 0x33, 0x4A, 0x10, 0x32, 0x3D, 0x42, 0xE6, 0xEC, 0x38, 0x97, 0x2F, 0x05, 0x41, 0xDD, 0xD6, 0xB6, 0xAC, 0x17, 0x4B, 0x7E, 0xFA, 0xFE, 0xA4, 0xD2

#define RBX__MESSAGE_INFO 0
#define RBX__MESSAGE_OUTPUT 1
#define RBX__MESSAGE_WARNING 2
#define RBX__MESSAGE_ERROR 3

#define CLASSPADDING_DATAMODEL__JOBID              739

#define ADDRESS_HTTP__HTTPGETPOSTWININET           0x006F03B0
#define ADDRESS_HTTP__HTTPGETPOSTWINHTTP           0x006EEE70
#define ADDRESS_HTTP__TRUSTCHECK                   0x005B7050
#define ADDRESS_CRYPT__VERIFYSIGNATUREBASE64       0x00809EC0
#define ADDRESS_DATAMODEL__GETJOBID                0x005E70C0
#define ADDRESS_STANDARDOUT__PRINT                 0x005B25E0
#define ADDRESS_SERVERREPLICATOR__SENDTOP          0x00513E80
#define ADDRESS_SERVERREPLICATOR__PROCESSTICKET    0x00514B60
#define ADDRESS_SCRIPTCONTEXT__OPENSTATE           0x006245E0
#define ADDRESS_LUA_PUSHCFUNCTION                  0x0076B8E0
#define ADDRESS_LUA_SETGLOBAL                      0x0076B810

#define CLASSLOCATION_CROBLOXAPP                   0x00CBA8A0
#define CLASSLOCATION_CAPP                         0x00406D80

#define CLASSPADDING_CROBLOXDOC__WORKSPACE         45

#define ADDRESS_CAPP__CREATEGAME                   0x00406D80
#define ADDRESS_CAPP__ROBLOXAUTHENTICATE           0x00409050
#define ADDRESS_CROBLOXAPP__INITINSTANCE           0x004613C0
#define ADDRESS_CROBLOXAPP__CREATEDOCUMENT         0x0045D030
#define ADDRESS_CWORKSPACE__EXECURLSCRIPT          0x0049FC90
#define ADDRESS_CROBLOXCOMMANDLINEINFO__PARSEPARAM 0x0045EE50
#define ADDRESS_CCOMMANDLINEINFO__PARSELAST        0x0081354A

#ifdef _DEBUG
#define PADDING_STRUCT 0
#else
#define PADDING_STRUCT 1
#endif