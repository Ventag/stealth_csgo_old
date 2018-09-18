#include "stealth_input.h"
#include "log.h"
#include <cctype>

namespace menu
{
	input* input::get()
	{
		static input ginput;
		return &ginput;
	}

	void input::update()
	{
		for (int i = 0; i < 256; i++)
		{
			old_keys[i] = keys[i];
			keys[i] = GetAsyncKeyState(i);
		}
	}

	bool input::get_key_state(int key)
	{
		return keys[key];
	}

	bool input::get_key_click(int key)
	{
		return (!old_keys[key] && keys[key]);
	}

	std::string input::get_key_name(int key)
	{
		std::string keyname = keynames[key];

		std::transform(keyname.begin(), keyname.end(), keyname.begin(), [this](unsigned char c) { return get_key_state(KEYS::LSHIFT) ? std::toupper(c) : std::tolower(c); });

		return keyname;
	}

	std::string input::to_lower(std::string in)
	{
		std::string copy = in;
		std::transform(copy.begin(), copy.end(), copy.begin(), [](unsigned char c) { return std::tolower(c); });
		return copy;
	}

	std::string input::to_upper(std::string in)
	{
		std::string copy = in;
		std::transform(copy.begin(), copy.end(), copy.begin(), [](unsigned char c) { return std::toupper(c); });
		return copy;
	}
}