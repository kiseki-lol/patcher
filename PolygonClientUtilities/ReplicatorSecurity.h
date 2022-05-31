#pragma once

#include "Classes.h"

typedef void(__thiscall* ServerReplicator__sendTop_t)(ServerReplicator* _this, RakPeerInterface* peer);
typedef void(__thiscall* ServerReplicator__processTicket_t)(ServerReplicator* _this, Packet* packet);

void __fastcall ServerReplicator__sendTop_hook(ServerReplicator* _this, void*, RakPeerInterface* peer);
void __fastcall ServerReplicator__processTicket_hook(ServerReplicator* _this, void*, Packet* packet);

extern ServerReplicator__sendTop_t ServerReplicator__sendTop;
extern ServerReplicator__processTicket_t ServerReplicator__processTicket;