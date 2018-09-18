#pragma once
#include "include.h"

#include "renderer.h"

namespace menu
{
	enum KEYS
	{
		MOUSE1 = 1,
		MOUSE2 = 2,
		ENTER = 13,
		UP = 38,
		DOWN = 40,
		INS = 45,
		DEL = 46,
		LSHIFT = VK_LSHIFT
	};

	class input
	{
		bool keys[254];
		bool old_keys[254];
	public:
		static input* get();

		void update();
		bool get_key_state(int key);
		bool get_key_click(int key);
		std::string get_key_name(int key);

		std::string to_upper(std::string in);
		std::string to_lower(std::string in);

		const char* keynames[254] = { nullptr, "Left Mouse", "Right Mouse", "Control+Break", "Middle Mouse", "Mouse 4", "Mouse 5",
			"u1", "Backspace", "TAB", "u2", "u3", "u4", "ENTER", nullptr, nullptr, "SHIFT", "CTRL", "ALT", "PAUSE",
			"CAPS LOCK", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, "ESC", nullptr, nullptr, nullptr, nullptr, "SPACEBAR",
			"PG UP", "PG DOWN", "END", "HOME", "Left", "Up", "Right", "Down", nullptr, "Print", nullptr, "Print Screen", "Insert",
			"Delete", nullptr, "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
			nullptr, "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X",
			"Y", "Z", "Left Windows", "Right Windows", nullptr, nullptr, nullptr, "NUM 0", "NUM 1", "NUM 2", "NUM 3", "NUM 4", "NUM 5", "NUM 6",
			"NUM 7", "NUM 8", "NUM 9", "*", "+", "_", "-", ".", "/", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12",
			"F13", "F14", "F15", "F16", "F17", "F18", "F19", "F20", "F21", "F22", "F23", "F24", nullptr, nullptr, nullptr, nullptr, nullptr,
			nullptr, nullptr, nullptr, "NUM LOCK", "SCROLL LOCK", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
			nullptr, nullptr, nullptr, nullptr, nullptr, "LSHIFT", "RSHIFT", "LCONTROL", "RCONTROL", "LMENU", "RMENU", nullptr, nullptr, nullptr,
			nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, "Next Track", "Previous Track", "Stop", "Play/Pause", nullptr, nullptr,
			nullptr, nullptr, nullptr, nullptr, ";", "+", ",", "-", ".", "/?", "~", nullptr, nullptr, nullptr, nullptr,
			nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
			nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, "[{", "\\|", "}]", "'\"", nullptr, nullptr, nullptr, nullptr,
			nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
			nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
	};
}

#define INPUTSYS menu::input::get()