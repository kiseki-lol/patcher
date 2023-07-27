#pragma once

#include <vector>
#include <utility>

#include <detours/detours.h>

namespace Patcher
{
    typedef std::pair<void**, void*> Patch;

    extern std::vector<Patch> patchList;

    LONG Apply();
}

#define START_PATCH_LIST() std::vector<Patcher::Patch> Patcher::patchList = {
#define ADD_PATCH(a, b) { (void**)&(a), (b) }, 
#define END_PATCH_LIST() };