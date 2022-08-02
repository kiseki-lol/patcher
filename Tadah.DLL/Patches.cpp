#include "pch.h"

#include "Patches.h"

LONG Patches::Apply()
{
    DetourTransactionBegin();

    for (Patch patch : patchList)
    {
        DetourAttach(&(PVOID&)*patch.first, patch.second);
    }

    return DetourTransactionCommit();
}