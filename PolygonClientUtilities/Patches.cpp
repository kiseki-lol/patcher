#include "pch.h"
#include "Patches.h"

#include <detours/detours.h>

int addressOffset;

LONG Patches::Apply()
{
    DetourTransactionBegin();

    for (Patch patch : patchList)
        DetourAttach(&(PVOID&)*patch.first, patch.second);

    return DetourTransactionCommit();
}

VOID Patches::ResolveOffset()
{
    // the only surviving fragment of PolygonUtil.dll
    // RIP 05/08/2021 - 20/01/2022

    MEMORY_BASIC_INFORMATION mbi;
    DWORD ProcID = GetCurrentProcessId();
    HANDLE Handle = OpenProcess(PROCESS_ALL_ACCESS, TRUE, ProcID);

    unsigned int Opcode = 0xC7F18B56;
    int BaseAddress = 0x00001000;

    int Offset = 0x00010000;
    int Searches = 0xFFF;

    for (int i = 1; i <= Searches; i++)
    {
        int SearchAddress = Offset * i;
        int Address = SearchAddress + BaseAddress;
        if (VirtualQuery((LPVOID)Address, &mbi, sizeof(mbi)) == 0) continue;

        std::vector<int> buffer(mbi.RegionSize);

        if (!ReadProcessMemory(Handle, (LPCVOID)Address, &buffer[0], buffer.size(), NULL)) continue;

        if (buffer[0] == Opcode)
        {
            addressOffset = SearchAddress;
            break;
        }

        if (SearchAddress == Offset * Searches)
        {
            ExitProcess(EXIT_FAILURE);
        }
    }
}

INT Patches::GetAddressByOffset(int address)
{
    if (!addressOffset) ResolveOffset();
    return address + addressOffset;
}