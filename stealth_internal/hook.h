#pragma once
#include "include.h"
#include "renderer.h"
#include "vmt.h"

namespace hook
{
	extern hooking_method::vmt d3d_table;
	class init
	{
	private:

	public:
		static init* get();
		bool setup();
	};

	extern IDirect3DDevice9* g_device;
}