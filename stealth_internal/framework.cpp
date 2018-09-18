#include "framework.h"
#include "iosystem.h"
#include "log.h"

#include "console.h"

namespace menu
{
	framework* framework::get()
	{
		static framework gframework;
		return &gframework;
	}

	void framework::add_window(window* win)
	{
		if (!win)
		{
			stealth::log::get()->write("framework received null window", logtype::WARNING);
			return;
		}

		windows.push_back(win);
		if (!focused_window)
			focused_window = win;
	}

	void framework::set_focus(window* win)
	{
		if (win)
		{
			focused_window = win;
			/*for (auto it = windows.begin(); it != windows.end(); ++it)
			{
				if (*it == focused_window)
				{
					windows.erase(it);
					windows.push_back(focused_window);
				}
			}*/
		}
	}

	window* framework::get_focus()
	{
		if (focused_window)
			return focused_window;
		else
			return nullptr;
	}

	void framework::set_focused_control(control* control)
	{
		focused_control = control;
	}

	control* framework::get_focused_control()
	{
		return focused_control;
	}

	void framework::run_frame(RendererPtr renderer)
	{
		hook::iosys* io = hook::iosys::get();

		//if (io->get_key_click(VK_INSERT))
		if(GetAsyncKeyState(VK_INSERT) & 1)
			active = !active;

		if (!active)
			return;

		if (!windows.size())
			return;

		for (auto it = windows.begin(); it != windows.end(); ++it)
		{
			if (*it)
			{
				auto win = *it;
				if (win != get_focus())
				{
					//win->update();
					win->draw(renderer);
				}
			}
		}

		get_focus()->update();
		get_focus()->draw(renderer);

		renderer->draw_circle({ (float)io->get_mouse_x() - 1, (float)io->get_mouse_y() - 1 }, 3, 0xffffffff);

		/*if (io->get_mouse1())
			renderer->draw_filled_rect({ 5,5,40,40 }, 0xff00ff00);
		else
			renderer->draw_filled_rect({ 5,5,40,40 }, 0xffff0000);

		if (buffer.size())
			renderer->draw_text(hook::main_font, { 5,70 }, "buf: " + buffer, 0xffffffff, TEXT_LEFT);*/
	}

	std::string framework::buffer_get()
	{
		return buffer;
	}

	void framework::buffer_add(char c)
	{
		if (c == '\b' && buffer.size())
			buffer.pop_back();
		else if (c == '\r' && get_focused_control() && get_focused_control()->callback)
			get_focused_control()->callback();
		else
			buffer += c;
	}

	void framework::buffer_popback()
	{
		if(buffer.size())
			buffer.pop_back();
	}

	void framework::buffer_reset()
	{
		buffer.clear();
	}
}