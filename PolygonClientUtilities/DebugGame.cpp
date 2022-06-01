#include "pch.h"
#include "DebugGame.h"

Game__construct_t Game__construct = (Game__construct_t)0x47DBF0;

int __fastcall Game__construct_hook(Game* _this)
{
	printf("Game::Game called\n");
	printf("Value of _this: %p\n", _this);
	return Game__construct(_this);
}