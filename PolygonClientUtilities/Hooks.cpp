#include "pch.h"
#include "Hooks.h"
#include "Patches.h"
#include "Config.h"
#include "Util.h"
#include "LUrlParser.h"
#ifdef ARBITERBUILD
// #include "Logger.h"
#endif

static bool hasJobId = false;
static bool setJobId = false;

static std::string jobId;

// Functions //

#ifdef ARBITERBUILD
DataModel__getJobId_t DataModel__getJobId = (DataModel__getJobId_t)ADDRESS_DATAMODEL__GETJOBID;
// Network__RakNetAddressToString_t Network__RakNetAddressToString = (Network__RakNetAddressToString_t)ADDRESS_NETWORK__RAKNETADDRESSTOSTRING;
#ifdef MFC2011

#endif
#endif
#if defined(MFC2010) || defined(MFC2011)
// CApp__CreateGame_t CApp__CreateGame = (CApp__CreateGame_t)ADDRESS_CAPP__CREATEGAME;
#endif
#ifdef DEBUG_SERVERREPLICATOR__PROCESSPACKET
ServerReplicator__processPacket_t ServerReplicator__processPacket = (ServerReplicator__processPacket_t)ADDRESS_SERVERREPLICATOR__PROCESSPACKET;
#endif

// Hook Definitions //

#ifdef ARBITERBUILD
int __fastcall DataModel__getJobId_hook(DataModel* _this, void*, int a2)
{
    // the actual function signature is (DataModel* _this)
    // this only sets the job id when game.jobId is called by lua
    // so the gameserver script must call game.jobId at the beginning for this to take effect
    // also, this only applies to the first datamodel that is created

    if (!setJobId && hasJobId && !jobId.empty())
    {
        _this->jobId = jobId;
        setJobId = true;
    }

    return DataModel__getJobId(_this, a2);
}

// std::string __fastcall Network__RakNetAddressToString_hook(const int raknetAddress, char portDelineator)
// {
//     return Network__RakNetAddressToString(raknetAddress, portDelineator);
// }
#endif

#if defined(MFC2010) || defined(MFC2011)
/* INT __fastcall CApp__CreateGame_hook(CApp* _this, void*, int* a2, LPCWSTR a3)
{
    printf("CApp::CreateGame called\n");
    // printf("Location of _this: %p\n", _this);
    // printf("Location of a2: %p\n", a2);
    // printf("Location of a3: %p\n", a3);

    // int result = (int)CApp__CreateGame(_this, a2, a3);
    // int result = (int)CApp__CreateGame(_this, a2, L"44340105256");
    int result = (int)CApp__CreateGame(_this, a2, L"44340105256");

    return result;
} */
#endif

#ifdef DEBUG_SERVERREPLICATOR__PROCESSPACKET
INT __fastcall ServerReplicator__processPacket_hook(int _this, void*, Packet* packet)
{    
    switch ((unsigned char)packet->data[0])
    {
    case ID_TIMESTAMP:
        printf("ServerReplicator::processPacket received ID_TIMESTAMP with length %d\n", packet->length);
        break;

    case ID_REQUEST_CHARACTER:
        printf("ServerReplicator::processPacket received ID_REQUEST_CHARACTER with length %d\n", packet->length);
        break;

    case ID_DATA:
        printf("ServerReplicator::processPacket received ID_DATA with length %d\n", packet->length);
        break;

    case ID_SUBMIT_TICKET:
        printf("ServerReplicator::processPacket received ID_SUBMIT_TICKET with length %d\n", packet->length);
        break;

    default:
        printf("ServerReplicator::processPacket received packet %d with length %d\n", packet->data[0], packet->length);
        break;
    }

    /* if ((unsigned char)packet->data[0] == ID_SUBMIT_TICKET)
    {
        printf("ServerReplicator::processPacket received ID_SUBMIT_TICKET with length %d\n", packet->length);
    }
    else
    {
        printf("ServerReplicator::processPacket received packet %d with length %d\n", packet->data[0], packet->length);
    } */

    /* switch ((unsigned char)packet->data[0])
    {
    case ID_SUBMIT_TICKET:
        // printf("ServerReplicator::processPacket called: ID_SUBMIT_TICKET\n");
        return ServerReplicator__processPacket(_this, packet);

    default:
        if (true)
        {
            Logger::Print(2, "Player not authenticated s");
            return RR_STOP_PROCESSING_AND_DEALLOCATE;
        }
        return ServerReplicator__processPacket(_this, packet);
    } */

    return ServerReplicator__processPacket(_this, packet);
}
#endif
