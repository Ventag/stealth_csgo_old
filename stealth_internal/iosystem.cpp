#include "iosystem.h"
#include "framework.h"
#include "control.h"
#include "textbox.h"

namespace hook
{
	iosys* iosys::get()
	{
		static iosys giosys;
		return &giosys;
	}

	LRESULT iosys::stealth_wnproc(HWND, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		memcpy(old_keys, keys, 256);
		switch (msg)
		{
		case WM_LBUTTONDOWN:
			mouse[0] = true;
			for (auto it = menu::framework::get()->windows.begin(); it != menu::framework::get()->windows.end(); ++it)
			{
				if (*it)
				{
					auto win = *it;
					if (win != menu::framework::get()->get_focus())
						win->update();
				}
			}

			if(menu::framework::get()->get_focused_control())
				menu::framework::get()->get_focused_control()->input(wParam);

			return true;
		case WM_LBUTTONUP:
			mouse[0] = false;
			return true;
		case WM_RBUTTONDOWN:
			mouse[1] = true;
			return true;
		case WM_RBUTTONUP:
			mouse[1] = false;
			return true;
		case WM_MBUTTONDOWN:
			mouse[2] = true;
			return true;
		case WM_MBUTTONUP:
			mouse[2] = false;
			return true;
		case WM_MOUSEWHEEL:
			mousewheel += GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? +1.0f : -1.0f;
			return true;
		case WM_MOUSEMOVE:
			mouse_x = (signed short)(lParam);
			mouse_y = (signed short)(lParam >> 16);
			return true;
		case WM_KEYDOWN:
			if (wParam < 256)
				keys[wParam] = 1;
			return true;
		case WM_KEYUP:
			if (wParam < 256)
				keys[wParam] = 0;

			//if (menu::framework::get()->get_focused_control())
			//	menu::framework::get()->get_focused_control()->input(wParam);

			return true;
		case WM_CHAR:
			//if (wParam > 0 && wParam < 0x10000)
			//	menu::framework::get()->buffer_add((unsigned short)wParam);

			if(wParam > 0 && wParam < 0x10000)
				if (menu::framework::get()->get_focused_control()->ctrl_type == menu::control_type::TEXTBOX)
				{
					menu::textbox* input_ptr = reinterpret_cast<menu::textbox*>(menu::framework::get()->get_focused_control());
					input_ptr->add_buffer((unsigned short)wParam);
				}
			return true;
		}

		return true;
	}
}