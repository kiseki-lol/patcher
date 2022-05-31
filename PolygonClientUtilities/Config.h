#pragma once

#define MFC2010
#define PLAYERBUILD
#define ARBITERBUILD

// #define DEBUG_SERVERREPLICATOR__PROCESSPACKET

// when PLAYERBUILD is defined, the following changes occur for 2010 and 2012 only:
// the -jobId arg is parsed

// when ARBITERBUILD is defined, the following changes occur:
// DataModel::getJobId is hooked
// DataModel::~DataModel is hooked
// StandardOut::print is hooked
// Network::RakNetAddressToString is hooked
// -jobId arg becomes available
// HTTP requests and output messages are logged to a file

// RobloxApp (2010)
#ifdef MFC2010
#define CLASSPADDING_DATAMODEL__JOBID              729 // when compiled as debug, this must be 728

#define ADDRESS_DATAMODEL__GETJOBID                0x005CACC0
#define ADDRESS_STANDARDOUT__PRINT                 0x0059F340
#define ADDRESS_NETWORK__RAKNETADDRESSTOSTRING     0x004FC1A0
#define ADDRESS_HTTP__TRUSTCHECK                   0x005A2680
#define ADDRESS_CRYPT__VERIFYSIGNATUREBASE64       0x0079ECF0
#define ADDRESS_SERVERREPLICATOR__SENDTOP          0x00506910
#define ADDRESS_SERVERREPLICATOR__PROCESSPACKET    0x00507420
#define ADDRESS_SERVERREPLICATOR__PROCESSTICKET    0x0

// MFC specific definitions
#define CLASSLOCATION_CROBLOXAPP                   0x00BFF898
#define CLASSLOCATION_CAPP                         0x00405D20

#define CLASSPADDING_CROBLOXDOC__WORKSPACE         40

#define ADDRESS_CAPP__CREATEGAME                   0x00405D20
#define ADDRESS_CAPP__ROBLOXAUTHENTICATE           0x00408060
#define ADDRESS_CROBLOXAPP__INITINSTANCE           0x00452900
#define ADDRESS_CROBLOXAPP__CREATEDOCUMENT         0x0044F6E0
#define ADDRESS_CWORKSPACE__EXECURLSCRIPT          0x0047EC10
#define ADDRESS_CROBLOXCOMMANDLINEINFO__PARSEPARAM 0x00450AC0
#define ADDRESS_CCOMMANDLINEINFO__PARSELAST        0x007A80A0

// Player specific definitions
#define ADDRESS_APPLICATION__PARSEARGUMENTS        0x0

// RakNet packet definitions
#define ID_TIMESTAMP                               25
#define ID_SET_GLOBALS                             95
#define ID_REQUEST_CHARACTER                       96
#define ID_DATA                                    98
#define ID_SUBMIT_TICKET                           104
#endif

// RobloxApp (2011)
#ifdef MFC2011
#define CLASSPADDING_DATAMODEL__JOBID              740 // when compiled as debug, this must be 739

#define ADDRESS_DATAMODEL__GETJOBID                0x005E70C0
#define ADDRESS_DATAMODEL__DESTRUCT                0x006002A0
#define ADDRESS_STANDARDOUT__PRINT                 0x005B25E0
#define ADDRESS_NETWORK__RAKNETADDRESSTOSTRING     0x0
#define ADDRESS_HTTP__TRUSTCHECK                   0x005B7050
#define ADDRESS_CRYPT__VERIFYSIGNATUREBASE64       0x00809EC0
#define ADDRESS_SERVERREPLICATOR__SENDTOP          0x00513E80
#define ADDRESS_SERVERREPLICATOR__PROCESSTICKET    0x00514B60

// MFC specific definitions
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

// RakNet definitions
#define ID_SET_GLOBALS                             127
#define ID_DATA                                    129
#define ID_REQUEST_MARKER                          130
#define ID_PHYSICS                                 131
#define ID_CHAT_ALL                                132
#define ID_CHAT_TEAM                               133
#define ID_REPORT_ABUSE                            134
#define ID_SUBMIT_TICKET                           135
#define ID_CHAT_GAME                               136
#endif

// RobloxApp/RobloxPlayer (2012)
#ifdef MFC2012
#define ADDRESS_HTTP__TRUSTCHECK                   0x006D5D20
#define ADDRESS_CRYPT__VERIFYSIGNATUREBASE64       0x009B1D20
#endif

// RobloxPlayerBeta (2012)
#ifdef PLAYER2012
// so 2012's a bit different
// VMProtect likes to offset the memory locations randomly on startup
// so defining the addresses here are a bit weird
	
// say the beginning of the program is located at 0x00BF1000
// and you have a trust check hook that's, for example, located at 0x00DF20A0

// VMProtect is offsetting the memory location from 0x00000000 - 0x00FF0000
// so the 0x00BF0000 in 0x00BF1000 is actually an offset

// with that offset, the address you'd have to put for your trust check hook will be 0x00DF20A0 - 0x00BF0000 = 0x002020A0
// and you just put that address into the function

#define CLASSPADDING_DATAMODEL__JOBID              763 // when compiled as debug, this must be 762

#define ADDRESS_DATAMODEL__GETJOBID                Patches::GetAddressByOffset(0x002079A0)
#define ADDRESS_STANDARDOUT__PRINT                 Patches::GetAddressByOffset(0x0023A8C0)
#define ADDRESS_NETWORK__RAKNETADDRESSTOSTRING     0x0
#define ADDRESS_HTTP__TRUSTCHECK                   Patches::GetAddressByOffset(0x002020A0)
#define ADDRESS_CRYPT__VERIFYSIGNATUREBASE64       Patches::GetAddressByOffset(0x00526330)

// Player specific definitions
#define ADDRESS_APPLICATION__PARSEARGUMENTS        Patches::GetAddressByOffset(0x00004E60)
#endif

// RobloxStudioBeta (2012)
#ifdef STUDIO2012
#define ADDRESS_HTTP__TRUSTCHECK                   Patches::GetAddressByOffset(0x001931A0)
#define ADDRESS_CRYPT__VERIFYSIGNATUREBASE64       Patches::GetAddressByOffset(0x004CD250)
#endif

#define RR_STOP_PROCESSING_AND_DEALLOCATE 0
#define RR_CONTINUE_PROCESSING 1
#define RR_STOP_PROCESSING 2