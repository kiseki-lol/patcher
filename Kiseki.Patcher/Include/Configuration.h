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

#define CLASSPADDING_DATAMODEL__JOBID              0

#define ADDRESS_HTTP__HTTPGETPOSTWININET           0x0
#define ADDRESS_HTTP__TRUSTCHECK                   0x0
#define ADDRESS_CRYPT__VERIFYSIGNATUREBASE64       0x0
#define ADDRESS_CONTEXT__REQUIREPERMISSION         0x0
#define ADDRESS_CONTEXT__ISINROLE                  0x0
#define ADDRESS_DATAMODEL__GETJOBID                0x0
#define ADDRESS_STANDARDOUT__PRINT                 0x0
#define ADDRESS_SERVERREPLICATOR__SENDTOP          0x0
#define ADDRESS_SERVERREPLICATOR__PROCESSTICKET    0x0
#define ADDRESS_SERVERREPLICATOR__PROCESSPACKET    0x0

#define CLASSLOCATION_CROBLOXAPP                   0x0
#define CLASSLOCATION_CAPP                         0x0

#define CLASSPADDING_CROBLOXDOC__WORKSPACE         45

#define ADDRESS_CAPP__CREATEGAME                   0x0
#define ADDRESS_CAPP__ROBLOXAUTHENTICATE           0x0
#define ADDRESS_CROBLOXAPP__INITINSTANCE           0x0
#define ADDRESS_CROBLOXAPP__CREATEDOCUMENT         0x0
#define ADDRESS_CWORKSPACE__EXECURLSCRIPT          0x0
#define ADDRESS_CROBLOXCOMMANDLINEINFO__PARSEPARAM 0x0
#define ADDRESS_CCOMMANDLINEINFO__PARSELAST        0x0

#ifndef _DEBUG
#define PADDING_STRUCT 1
#else
#define PADDING_STRUCT 0
#endif

#define RBX__MESSAGE_INFO 0
#define RBX__MESSAGE_OUTPUT 1
#define RBX__MESSAGE_WARNING 2
#define RBX__MESSAGE_ERROR 3