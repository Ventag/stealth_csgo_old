#pragma once
#include "include.h"
#include "control.h"
#include "window.h"
#include "renderer.h"

namespace menu
{
	class framework
	{
	private:
		window* focused_window = nullptr;

		control* focused_control = nullptr;

		std::string buffer;

	public:
		std::vector<window*> windows;
		int mouse_x, mouse_y;
		bool active;
		
		static framework* get();

		void add_window(window* win);

		void set_focus(window* win);

		window* get_focus();

		void set_focused_control(control* control);

		control* get_focused_control();

		void run_frame(RendererPtr renderer);

		std::string buffer_get();

		void buffer_add(char c);

		void buffer_popback();

		void buffer_reset();
	};
}