#pragma once

#define MFC2010
#define ARBITERBUILD

// RobloxApp (2010)
#ifdef MFC2010
#define CLASSLOCATION_CROBLOXAPP                   0x00BFF898
#define CLASSLOCATION_CAPP                         0x00405D20

#define STRUCTOFFSET_DATAMODEL__JOBID              2912      

#define ADDRESS_DATAMODEL__GETJOBID                0x005CACC0
#define ADDRESS_STANDARDOUT__PRINT                 0x0059F340
#define ADDRESS_NETWORK__RAKNETADDRESSTOSTRING     0x004FC1A0
#define ADDRESS_HTTP__TRUSTCHECK                   0x005A2680
#define ADDRESS_CRYPT__VERIFYSIGNATUREBASE64       0x0079ECF0
#define ADDRESS_CAPP__CREATEGAME                   0x00405D20
#define ADDRESS_CAPP__ROBLOXAUTHENTICATE           0x00408060
#define ADDRESS_CROBLOXAPP__INITINSTANCE           0x00452900
#define ADDRESS_CROBLOXAPP__CREATEDOCUMENT         0x0044F6E0
#define ADDRESS_CWORKSPACE__EXECURLSCRIPT          0x0047EC10
#define ADDRESS_CROBLOXCOMMANDLINEINFO__PARSEPARAM 0x00450AC0
#define ADDRESS_CCOMMANDLINEINFO__PARSELAST        0x007A80A0
#endif

// RobloxApp (2011)
#ifdef MFC2011
#define CLASSLOCATION_CROBLOXAPP                   0x00CBA8A0
#define CLASSLOCATION_CAPP                         0x00406D80

#define STRUCTOFFSET_DATAMODEL__JOBID              2956      

#define ADDRESS_DATAMODEL__GETJOBID                0x005E70C0
#define ADDRESS_STANDARDOUT__PRINT                 0x005B25E0
#define ADDRESS_NETWORK__RAKNETADDRESSTOSTRING     0x0
#define ADDRESS_HTTP__TRUSTCHECK                   0x005B7050
#define ADDRESS_CRYPT__VERIFYSIGNATUREBASE64       0x00809EC0
#define ADDRESS_CAPP__CREATEGAME                   0x00406D80
#define ADDRESS_CAPP__ROBLOXAUTHENTICATE           0x00409050
#define ADDRESS_CROBLOXAPP__INITINSTANCE           0x004613C0
#define ADDRESS_CROBLOXAPP__CREATEDOCUMENT         0x0045D030
#define ADDRESS_CWORKSPACE__EXECURLSCRIPT          0x0049FC90
#define ADDRESS_CROBLOXCOMMANDLINEINFO__PARSEPARAM 0x0045EE50
#define ADDRESS_CCOMMANDLINEINFO__PARSELAST        0x0081354A
#endif