#include "pch.h"
#include "DebugDatamodel.h"

DataModel__createDataModel_t DataModel__createDataModel = (DataModel__createDataModel_t)0; // ADDRESS_DATAMODEL__CREATEDATAMODEL;

int  __fastcall DataModel__createDataModel_hook(int, int, int, bool startHeartbeat)
{
	printf("DataModel::createDataModel called\n");

	printf("Value of startHeartbeat: %#010x\n", startHeartbeat);

	return DataModel__createDataModel(startHeartbeat);
}

/* DataModel__createDataModel_t DataModel__createDataModel = (DataModel__createDataModel_t)ADDRESS_GAME__CONSTRUCT;

int __fastcall DataModel__createDataModel_hook(int _this)
{
	printf("Game::Game called\n");
	printf("Value of _this: %#010X\n", _this);
	return DataModel__createDataModel(_this);
} */