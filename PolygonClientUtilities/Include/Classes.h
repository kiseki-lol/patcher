#pragma once

#include <oaidl.h>

#include "Config.h"

// TODO: These need a place

struct DataModel
{
    void* padding1[CLASSPADDING_DATAMODEL__JOBID + PADDING_STRUCT];
    std::string jobId;
};

struct Game
{
    // 2010 has a class size of 104 bytes
    void* padding1[8];
    std::shared_ptr<DataModel> dataModel;
    void* padding2[9];
};

const auto Game__initializeClass = (Game * (__thiscall*)(Game* _this, int a2))0x455D40;
const auto Game__construct = (int(__thiscall*)(Game* _this))0x47DBF0;

const auto ServiceProvider__createScriptContext = (void * (__thiscall*)(void* _this))0x4282E0;
const auto ScriptContext__execute = (void (__thiscall*)(void* _this, int identity, const char* script, const char* name))0x617C80;

// const auto DataModel__createDataModel = (std::shared_ptr<void>(__thiscall*)(bool startHeartbeat))ADDRESS_DATAMODEL__CREATEDATAMODEL;