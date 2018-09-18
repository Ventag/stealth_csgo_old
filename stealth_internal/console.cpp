#include "framework.h"
#include "console.h"
#include "d3d_hook.h"
#include "cmd.h"
#include "util_funcs.h"


namespace menu
{
	stealth::cmd console_window_visibility("console.window.visibility", "determines visibility of the console", true);
	stealth::cmd console_history_length("console.history.length", "determines the length of the console log", 100);
	stealth::cmd test("test", "testing variable", 100);
	menu::window* win;

	void clbk()
	{
		std::string cmd_string = console::get()->input->get_buffer();//framework::get()->buffer_get();//console::get()->input->get_buffer();

		std::transform(cmd_string.begin(), cmd_string.end(), cmd_string.begin(), [](unsigned char c) { return std::tolower(c); });
		std::string delimiter = " ";
		
		stealth::cmd* cmd = nullptr;
		if (cmd_string.size())
		{
			std::string output = "] " + cmd_string.substr(0, cmd_string.find(delimiter));
			console::get()->history->add_item(cmd_string);
			if (cmd = stealth::cmdlist::get()->get_cmd(cmd_string.substr(0, cmd_string.find(delimiter))))
			{
				std::vector<std::string> args;
				std::stringstream stream(cmd_string);
				std::string item;
				while (std::getline(stream, item, ' '))
					args.push_back(item);
				
				if (args.size() > 1)
				{
					if (!utility::is_number(args.at(1)))
						console::get()->history->add_item("argument must be a numeric value");
					else
						console::get()->history->add_item(cmd->handle_args(args.at(1)));
				}
				else
				{
					cmd_string = cmd->get_name() + " " + std::to_string(cmd->value<int>()) + " " + cmd->get_desc();
					console::get()->history->add_item(cmd_string);
				}
			}
			else
			{
				console::get()->history->add_item("cmd does not exist");
			}

			console::get()->input->reset_buffer();
			//framework::get()->buffer_reset();
		}
	}

	console* console::get()
	{
		static console g_console;
		return &g_console;
	}

	void console::init()
	{
		win = new menu::window("console", 200, 200, 450, 390, &console_window_visibility);

		history = new menu::listbox("history", 10, 10, 430, 300, &console_history_length);
		history->add_item("] {#ff00e910}stealth_internal{#ffffffff} v. 1 - ventag.cc");
		win->add_child(history);

		input = new menu::textbox("input", 10, 315, 430, 20, nullptr);
		input->set_callback(clbk);
		win->add_child(input);

		framework::get()->add_window(win);

		initialized = true;
	}
}