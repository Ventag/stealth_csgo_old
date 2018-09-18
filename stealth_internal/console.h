#pragma once
#include "include.h"
#include "renderer.h"
#include "cmd.h"

#include "listbox.h"
#include "textbox.h"

namespace menu
{
	class console
	{
	public:
		static console* get();

		void init();

		bool initialized;

		listbox* history;
		textbox* input;
	};

	extern stealth::cmd console_window_visibility;
};