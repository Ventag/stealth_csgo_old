#include "d3d_hook.h"
#include "hook.h"
#include "log.h"

#include "framework.h"

#include "console.h"
#include "splashscreen.h"

RendererPtr renderer;
FontHandle hook::main_font;
FontHandle hook::title_font;
long __stdcall hook::hook_endscene(IDirect3DDevice9* device)
{
	auto original = d3d_table.get_original<endscene>(42);

	static bool endscene_init = false;
	if (!endscene_init)
	{
		renderer = std::make_shared<Renderer>(device, 1536);
		main_font = renderer->create_font("Verdana", 4, FONT_DEFAULT);
		title_font = renderer->create_font("Verdana", 8, FontFlags::FONT_BOLD);

		menu::splashscreen::get()->init();
		menu::console::get()->init();
		stealth::log::get()->write("hooked endscene", SUCCESS);
		endscene_init = true;
	}

	if (device && renderer)
	{
		//INPUTSYS->update();

		renderer->begin();

		menu::framework::get()->run_frame(renderer);

		renderer->draw();
		renderer->end();
	}

	return original(device);
}

long __stdcall hook::hook_reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	auto original = d3d_table.get_original<reset>(16);

	return original(device, pPresentationParameters);
}