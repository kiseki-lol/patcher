#include "Patcher.hpp"

LONG Patcher::Apply()
{
    DetourTransactionBegin();

    for (Patch patch : patchList)
    {
        DetourAttach(&(PVOID&)*patch.first, patch.second);
    }

    return DetourTransactionCommit();
}