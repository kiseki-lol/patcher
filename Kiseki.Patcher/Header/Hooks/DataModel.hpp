#ifdef SERVER

#pragma once

#include "Hooks/CRoblox.hpp"

#include "Configuration.hpp"
#include "Helpers.hpp"

struct DataModel
{
	void* padding1[CLASSPADDING_DATAMODEL__JOBID];
	std::string jobId;
};

typedef INT(__thiscall* DataModel__getJobId_t)(DataModel* _this, int a2);
int __fastcall DataModel__getJobId_hook(DataModel* _this, void*, int a2);
extern DataModel__getJobId_t DataModel__getJobId;

#endif