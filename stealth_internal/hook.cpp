#include "hook.h"
#include "pattern.h"
#include "module.h"
#include "log.h"
#include "d3d_hook.h"
#include "iosystem.h"
#include "framework.h"

#include "console.h"

IDirect3DDevice9* hook::g_device = nullptr;

hooking_method::vmt hook::d3d_table;

hook::init* hook::init::get()
{
	static init g_init;
	return &g_init;
}

WNDPROC game_wndproc = nullptr;
LRESULT __stdcall hkWndProc(HWND window, UINT message_type, WPARAM w_param, LPARAM l_param) 
{
	// Let the renderer decide whether we should pass this input message to the game.
	//	return hook::iosys::get()->stealth_wnproc(window, message_type, w_param, l_param);//CallWindowProc(hook::iosys::get()->stealth_wnproc(), window, message_type, w_param, l_param);
	//if (w_param == VK_INSERT)
	//	menu::framework::get()->active = !menu::framework::get()->active;
	
	if (menu::framework::get()->active)
		return hook::iosys::get()->stealth_wnproc(window, message_type, w_param, l_param);
	//if (renderer.HandleInputMessage(message_type, w_param, l_param))

	// The GUI is inactive so pass the input to the game.
	return CallWindowProc(game_wndproc, window, message_type, w_param, l_param);
};

bool hook::init::setup()
{
	while(!g_device)
		g_device = **(IDirect3DDevice9***)(utility::pattern_scan(stealth::module::get()->get_module("shaderapidx9.dll"), "A1 ? ? ? ? 50 8B 08 FF 51 0C") + 1);
	
	stealth::log::get()->write("acquired d3d9 device from shaderapidx9.dll", SUCCESS);

	stealth::log::get()->write("initializing d3d hooks", SUCCESS);
	d3d_table.setup(g_device);
	d3d_table.hook_index(42, hook_endscene);
	//d3d_table.hook_index(16, &d3d_hook::get()->hook_reset);

	game_wndproc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(FindWindowA("Valve001", NULL), GWLP_WNDPROC, LONG_PTR(hkWndProc)));
	return true;
}