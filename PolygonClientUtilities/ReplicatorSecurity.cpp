#include "pch.h"
#include "ReplicatorSecurity.h"

static std::map<ServerReplicator*, RakPeerInterface*> rakPeers;

ServerReplicator__sendTop_t ServerReplicator__sendTop = (ServerReplicator__sendTop_t)ADDRESS_SERVERREPLICATOR__SENDTOP;
ServerReplicator__processTicket_t ServerReplicator__processTicket = (ServerReplicator__processTicket_t)ADDRESS_SERVERREPLICATOR__PROCESSTICKET;

void __fastcall ServerReplicator__sendTop_hook(ServerReplicator* _this, void*, RakPeerInterface* peer)
{
    if (_this->isAuthenticated)
    {
        // printf("ServerReplicator::sendTop called: player is authenticated\n");
        ServerReplicator__sendTop(_this, peer);
    }
    else if (rakPeers.find(_this) == rakPeers.end())
    {
        // printf("ServerReplicator::sendTop called: player is not authenticated\n");
        rakPeers.insert(std::pair<ServerReplicator*, RakPeerInterface*>(_this, peer));
    }
}

void __fastcall ServerReplicator__processTicket_hook(ServerReplicator* _this, void*, Packet* packet)
{
    ServerReplicator__processTicket(_this, packet);

    // THIS IS TEMPORARY
    // i literally cant find a way to obtain rakpeerinterface from _this, like it's really damn hard
    // so i'm cheating on doing that by getting rakpeerinterface from the first sendtop call,
    // throwing that into a lookup table and then using that here

    auto pos = rakPeers.find(_this);
    if (pos == rakPeers.end())
    {
        // printf("ServerReplicator::sendTop called: could not find rakpeer for %08X\n", (int)_this);
    }
    else if (_this->isAuthenticated)
    {
        // printf("ServerReplicator::sendTop called: Value of peer: %08X - associated with %08X\n", (int)pos->second, (int)_this);
        ServerReplicator__sendTop_hook(_this, nullptr, pos->second);
    }
    else
    {
        // printf("ServerReplicator::sendTop called: player is not authenticated\n");
    }
}