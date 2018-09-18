#include "splashscreen.h"
#include "log.h"
#include "framework.h"

#include "console.h"

namespace menu
{
	stealth::cmd splashscreen_window_visibility("splashscreen.window.visibility", "change this and fuck the framework", true);
	menu::window* splash;

	void splsh_console()
	{
		console_window_visibility.set_value<bool>(!console_window_visibility.value<bool>());
	}

	splashscreen* splashscreen::get()
	{
		static splashscreen gsplashscreen;
		return &gsplashscreen;
	}

	void splashscreen::init()
	{
		splash = new window("splashscreen", 100, 100, 250, 200, &splashscreen_window_visibility);
		btn_console = new button("console", 10, 10, 230, 20, nullptr);
		btn_console->parent = splash;
		btn_console->set_callback(splsh_console);
		splash->add_child(btn_console);

		framework::get()->add_window(splash);
	}

	void splashscreen::add_cvar(stealth::cmd* var)
	{
		cvars.push_back(var);
	}
}