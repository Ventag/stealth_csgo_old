#pragma once
#include "include.h"
#include "renderer.h"
#include "cmd.h"

#include "button.h"
#include "listbox.h"
#include "textbox.h"
namespace menu
{
	class splashscreen
	{
	private:
		std::vector<stealth::cmd*> cvars;

		menu::button* btn_console;
	public:
		static splashscreen* get();

		void init();

		void add_cvar(stealth::cmd* var);
	};
}