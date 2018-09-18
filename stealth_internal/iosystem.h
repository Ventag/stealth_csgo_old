#pragma once
#include "include.h"

namespace hook
{
	class iosys
	{
	private:
		bool keys[256];
		bool old_keys[256];
		bool older_keys[256];

		bool mouse[5];

		float mousewheel = 0.f;

		int mouse_x, mouse_y;
	public:
		static iosys* get();

		LRESULT stealth_wnproc(HWND, UINT msg, WPARAM wParam, LPARAM lParam);

		int get_mouse_x()
		{
			return mouse_x;
		}

		int get_mouse_y()
		{
			return mouse_y;
		}

		bool get_mouse1()
		{
			return mouse[0] & 1;
		}

		bool get_mouse2()
		{
			return mouse[1];
		}

		bool get_key_status(int key)
		{
			return keys[key] & 1;
		}

		bool get_key_click(int key)
		{
			return keys[key] && !old_keys[key];
		}
	};
}