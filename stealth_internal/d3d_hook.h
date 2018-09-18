#pragma once
#include "renderer.h"
#include "include.h"
#include "stealth_input.h"

namespace hook
{
	using endscene = long(__stdcall *)(IDirect3DDevice9*);
	using reset = long(__stdcall *)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);

	long __stdcall hook_endscene(IDirect3DDevice9* device);
	long __stdcall hook_reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* pPresentationParameters);

	extern FontHandle main_font;
	extern FontHandle title_font;
}