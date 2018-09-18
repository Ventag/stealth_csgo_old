#pragma once
#include "include.h"

namespace stealth
{
	class init
	{
	public:
		static init* get();
		bool modules();
		bool interfaces();

		bool setup(HMODULE mod);

		HMODULE mod;
	};
}