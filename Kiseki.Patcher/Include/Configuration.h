#pragma once

/*
 * This is commented out since our CI defines this automatically.
 * Uncomment this if you want to test locally, but please do not push with these uncommented!
 */

// #define SERVER
// #define PLAYER

#define BASE_URL "https://kiseki.lol"
#define DISCORD_APP_ID 0

#define ALLOWED_WILDCARD_DOMAINS "kiseki.lol", "rbxcdn.com", "roblox.com"
#define ALLOWED_DOMAINS
#define ALLOWED_SCHEMES "http", "https"
#define ALLOWED_EMBEDDED_SCHEMES "javascript", "jscript", "res"

#ifdef _DEBUG
#define PUBLIC_KEY ""
#else
#define PUBLIC_KEY 0x00
#endif

// TODO: Verify this
#define CLASSPADDING_DATAMODEL__JOBID              739

#define ADDRESS_HTTP__HTTPGETPOSTWININET           0x0
#define ADDRESS_HTTP__TRUSTCHECK                   0x005B7050
#define ADDRESS_CRYPT__VERIFYSIGNATUREBASE64       0x00809EC0
#define ADDRESS_CONTEXT__REQUIREPERMISSION         0x0
#define ADDRESS_CONTEXT__ISINROLE                  0x0
#define ADDRESS_DATAMODEL__GETJOBID                0x005E70C0
#define ADDRESS_STANDARDOUT__PRINT                 0x005B25E0
#define ADDRESS_SERVERREPLICATOR__SENDTOP          0x00513E80
#define ADDRESS_SERVERREPLICATOR__PROCESSTICKET    0x00514B60
#define ADDRESS_SERVERREPLICATOR__PROCESSPACKET    0x00514B60

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

#define RBX__MESSAGE_INFO 0
#define RBX__MESSAGE_OUTPUT 1
#define RBX__MESSAGE_WARNING 2
#define RBX__MESSAGE_ERROR 3