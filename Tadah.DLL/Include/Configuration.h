#pragma once

#define BASE_URL "https://tadah.rocks"
#define DISCORD_APP_ID 923705431543668736

#define ALLOWED_WILDCARD_DOMAINS "tadah.rocks", "rbxcdn.com", "roblox.com"
#define ALLOWED_DOMAINS
#define ALLOWED_SCHEMES "http", "https"
#define ALLOWED_EMBEDDED_SCHEMES "javascript", "jscript", "res"

#ifdef _DEBUG
#define PUBLIC_KEY "BgIAAACkAABSU0ExABAAAAEAAQAVZ+t4ywGMLfMmCbtQv8HNKsSGERgVq+giTsaTbovzYYsX4LRxqQWk81MDX3VlwdpHqcKlZJgsB9xQMt6jSy79f89UZybasguwuljUsFoUCkMinjnnJZuGKJouqq5+OL86q/PafC8xhDIU2GnP/ALcLsk9letXLUR/OFHnD32MkEzbMax89d263LO1T2sjGLQCVM438ATF2GNdqJIEWVLDGqv+4UkN+2otAfOToJ/y+e1L4fFi9xonV0vc8RhOQ8U6WzdKVK+0KpmAncFw/MUYAXtBO37CCVRX4cHQ+9XCFMO9XLBkC9F6GKe1RlhM/YsOqKVBvaiPpWlQFgQQk2VaPO37qjKiAHHAB9Dp3TJbF+5nUgsCHP1Z9f1nwdl1e/XrDSHjktF/r5dCOnwBGwZHsjxL526HdkH+z0OaBvpF+N72iJtIgimueMakpuAZLF5k++QRqsdJf6qgQPHSkXClA0arKM4OUsZt7lHnCnVxHdX/zWqGPhzZvo143OPLgpGvgVextlpJ3E3wFCItSSv85J6wyRd1bh68i9JOOHI08d/EQoa0/b2VqqKMv8XmULwRU7+h/INZbrFnNXT4k9UE3M4WmAfuKqm6/Aej8LAArZJycoCJSPfddUaFICIUlEw6qCayI/EcXxI+zu5ipJHL3FpsjTcnB873+DNWQHCD5g=="
#else
#define PUBLIC_KEY 0x06, 0x02, 0x00, 0x00, 0x00, 0xa4, 0x00, 0x00, 0x52, 0x53, 0x41, 0x31, 0x00, 0x10, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x15, 0x67, 0xeb, 0x78, 0xcb, 0x01, 0x8c, 0x2d, 0xf3, 0x26, 0x09, 0xbb, 0x50, 0xbf, 0xc1, 0xcd, 0x2a, 0xc4, 0x86, 0x11, 0x18, 0x15, 0xab, 0xe8, 0x22, 0x4e, 0xc6, 0x93, 0x6e, 0x8b, 0xf3, 0x61, 0x8b, 0x17, 0xe0, 0xb4, 0x71, 0xa9, 0x05, 0xa4, 0xf3, 0x53, 0x03, 0x5f, 0x75, 0x65, 0xc1, 0xda, 0x47, 0xa9, 0xc2, 0xa5, 0x64, 0x98, 0x2c, 0x07, 0xdc, 0x50, 0x32, 0xde, 0xa3, 0x4b, 0x2e, 0xfd, 0x7f, 0xcf, 0x54, 0x67, 0x26, 0xda, 0xb2, 0x0b, 0xb0, 0xba, 0x58, 0xd4, 0xb0, 0x5a, 0x14, 0x0a, 0x43, 0x22, 0x9e, 0x39, 0xe7, 0x25, 0x9b, 0x86, 0x28, 0x9a, 0x2e, 0xaa, 0xae, 0x7e, 0x38, 0xbf, 0x3a, 0xab, 0xf3, 0xda, 0x7c, 0x2f, 0x31, 0x84, 0x32, 0x14, 0xd8, 0x69, 0xcf, 0xfc, 0x02, 0xdc, 0x2e, 0xc9, 0x3d, 0x95, 0xeb, 0x57, 0x2d, 0x44, 0x7f, 0x38, 0x51, 0xe7, 0x0f, 0x7d, 0x8c, 0x90, 0x4c, 0xdb, 0x31, 0xac, 0x7c, 0xf5, 0xdd, 0xba, 0xdc, 0xb3, 0xb5, 0x4f, 0x6b, 0x23, 0x18, 0xb4, 0x02, 0x54, 0xce, 0x37, 0xf0, 0x04, 0xc5, 0xd8, 0x63, 0x5d, 0xa8, 0x92, 0x04, 0x59, 0x52, 0xc3, 0x1a, 0xab, 0xfe, 0xe1, 0x49, 0x0d, 0xfb, 0x6a, 0x2d, 0x01, 0xf3, 0x93, 0xa0, 0x9f, 0xf2, 0xf9, 0xed, 0x4b, 0xe1, 0xf1, 0x62, 0xf7, 0x1a, 0x27, 0x57, 0x4b, 0xdc, 0xf1, 0x18, 0x4e, 0x43, 0xc5, 0x3a, 0x5b, 0x37, 0x4a, 0x54, 0xaf, 0xb4, 0x2a, 0x99, 0x80, 0x9d, 0xc1, 0x70, 0xfc, 0xc5, 0x18, 0x01, 0x7b, 0x41, 0x3b, 0x7e, 0xc2, 0x09, 0x54, 0x57, 0xe1, 0xc1, 0xd0, 0xfb, 0xd5, 0xc2, 0x14, 0xc3, 0xbd, 0x5c, 0xb0, 0x64, 0x0b, 0xd1, 0x7a, 0x18, 0xa7, 0xb5, 0x46, 0x58, 0x4c, 0xfd, 0x8b, 0x0e, 0xa8, 0xa5, 0x41, 0xbd, 0xa8, 0x8f, 0xa5, 0x69, 0x50, 0x16, 0x04, 0x10, 0x93, 0x65, 0x5a, 0x3c, 0xed, 0xfb, 0xaa, 0x32, 0xa2, 0x00, 0x71, 0xc0, 0x07, 0xd0, 0xe9, 0xdd, 0x32, 0x5b, 0x17, 0xee, 0x67, 0x52, 0x0b, 0x02, 0x1c, 0xfd, 0x59, 0xf5, 0xfd, 0x67, 0xc1, 0xd9, 0x75, 0x7b, 0xf5, 0xeb, 0x0d, 0x21, 0xe3, 0x92, 0xd1, 0x7f, 0xaf, 0x97, 0x42, 0x3a, 0x7c, 0x01, 0x1b, 0x06, 0x47, 0xb2, 0x3c, 0x4b, 0xe7, 0x6e, 0x87, 0x76, 0x41, 0xfe, 0xcf, 0x43, 0x9a, 0x06, 0xfa, 0x45, 0xf8, 0xde, 0xf6, 0x88, 0x9b, 0x48, 0x82, 0x29, 0xae, 0x78, 0xc6, 0xa4, 0xa6, 0xe0, 0x19, 0x2c, 0x5e, 0x64, 0xfb, 0xe4, 0x11, 0xaa, 0xc7, 0x49, 0x7f, 0xaa, 0xa0, 0x40, 0xf1, 0xd2, 0x91, 0x70, 0xa5, 0x03, 0x46, 0xab, 0x28, 0xce, 0x0e, 0x52, 0xc6, 0x6d, 0xee, 0x51, 0xe7, 0x0a, 0x75, 0x71, 0x1d, 0xd5, 0xff, 0xcd, 0x6a, 0x86, 0x3e, 0x1c, 0xd9, 0xbe, 0x8d, 0x78, 0xdc, 0xe3, 0xcb, 0x82, 0x91, 0xaf, 0x81, 0x57, 0xb1, 0xb6, 0x5a, 0x49, 0xdc, 0x4d, 0xf0, 0x14, 0x22, 0x2d, 0x49, 0x2b, 0xfc, 0xe4, 0x9e, 0xb0, 0xc9, 0x17, 0x75, 0x6e, 0x1e, 0xbc, 0x8b, 0xd2, 0x4e, 0x38, 0x72, 0x34, 0xf1, 0xdf, 0xc4, 0x42, 0x86, 0xb4, 0xfd, 0xbd, 0x95, 0xaa, 0xa2, 0x8c, 0xbf, 0xc5, 0xe6, 0x50, 0xbc, 0x11, 0x53, 0xbf, 0xa1, 0xfc, 0x83, 0x59, 0x6e, 0xb1, 0x67, 0x35, 0x74, 0xf8, 0x93, 0xd5, 0x04, 0xdc, 0xce, 0x16, 0x98, 0x07, 0xee, 0x2a, 0xa9, 0xba, 0xfc, 0x07, 0xa3, 0xf0, 0xb0, 0x00, 0xad, 0x92, 0x72, 0x72, 0x80, 0x89, 0x48, 0xf7, 0xdd, 0x75, 0x46, 0x85, 0x20, 0x22, 0x14, 0x94, 0x4c, 0x3a, 0xa8, 0x26, 0xb2, 0x23, 0xf1, 0x1c, 0x5f, 0x12, 0x3e, 0xce, 0xee, 0x62, 0xa4, 0x91, 0xcb, 0xdc, 0x5a, 0x6c, 0x8d, 0x37, 0x27, 0x07, 0xce, 0xf7, 0xf8, 0x33, 0x56, 0x40, 0x70, 0x83, 0xe6
#endif

// #define ARBITER

#define CLASSPADDING_DATAMODEL__JOBID              739

#define ADDRESS_STANDARDOUT__PRINT                 0x005B25E0
#define ADDRESS_CRYPT__VERIFYSIGNATUREBASE64       0x00809EC0
#define ADDRESS_SERVERREPLICATOR__SENDTOP          0x00513E80
#define ADDRESS_SERVERREPLICATOR__PROCESSTICKET    0x00514B60
#define ADDRESS_SERVERREPLICATOR__PROCESSPACKET    0x0
#define ADDRESS_GAME__CONSTRUCT                    0x0
#define ADDRESS_HTTP__HTTPGETPOSTWININET           0x0
#define ADDRESS_HTTP__TRUSTCHECK                   0x005B7050
#define ADDRESS_CONTEXT__REQUIREPERMISSION         0x0
#define ADDRESS_CONTEXT__ISINROLE                  0x0

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

#ifndef _DEBUG
#define PADDING_STRUCT 1
#else
#define PADDING_STRUCT 0
#endif