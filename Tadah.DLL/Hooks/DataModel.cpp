#include "pch.h"

#include "Hooks/DataModel.h"

#ifdef SERVER

bool setJobId = false;

DataModel__getJobId_t DataModel__getJobId = (DataModel__getJobId_t)ADDRESS_DATAMODEL__GETJOBID;

int __fastcall DataModel__getJobId_hook(DataModel* _this, void*, int a2)
{
	if (!setJobId && hasJobId && !jobId.empty())
	{
		_this->jobId = Helpers::ws2s(jobId);
		setJobId = true;
	}

	return DataModel__getJobId(_this, a2);
}

#endif
