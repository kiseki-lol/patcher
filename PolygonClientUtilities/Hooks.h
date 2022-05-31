#pragma once

#include "Classes.h"

// Type Definitions //

#ifdef ARBITERBUILD
typedef INT(__thiscall* DataModel__getJobId_t)(DataModel* _this, int a2);
// typedef std::string(__thiscall* Network__RakNetAddressToString_t)(const int raknetAddress, char portDelineator);
#ifdef MFC2011

#endif
#ifdef PLAYER2012
#endif
#endif
#if defined(MFC2010) || defined(MFC2011)
// typedef INT(__thiscall* CApp__CreateGame_t)(CApp* _this, int *a2, LPCWSTR a3);
#endif
#ifdef DEBUG_SERVERREPLICATOR__PROCESSPACKET
typedef int(__thiscall* ServerReplicator__processPacket_t)(int _this, Packet* packet);
#endif

// Hook Declarations //

#ifdef ARBITERBUILD
INT  __fastcall DataModel__getJobId_hook(DataModel* _this, void*, int a2);
// std::string  __fastcall Network__RakNetAddressToString_hook(const int raknetAddress, char portDelineator);
#ifdef MFC2011

#endif
#ifdef PLAYER2012
#endif
#endif
#if defined(MFC2010) || defined(MFC2011)
// INT  __fastcall CApp__CreateGame_hook(CApp* _this, void*, int *a2, LPCWSTR a3);
#endif
#ifdef DEBUG_SERVERREPLICATOR__PROCESSPACKET
INT  __fastcall ServerReplicator__processPacket_hook(int _this, void*, Packet* packet);
#endif

// Externals //

#ifdef ARBITERBUILD
extern DataModel__getJobId_t DataModel__getJobId;
// extern Network__RakNetAddressToString_t Network__RakNetAddressToString;
#ifdef MFC2011

#endif
#ifdef PLAYER2012
#endif
#endif
#if defined(MFC2010) || defined(MFC2011)
// extern CApp__CreateGame_t CApp__CreateGame;
#endif
#ifdef DEBUG_SERVERREPLICATOR__PROCESSPACKET
extern ServerReplicator__processPacket_t ServerReplicator__processPacket;
#endif