#pragma once
#include "include.h"

namespace stealth
{
	class module
	{
		std::map<std::string, HMODULE> module_list;

	public:
		static module* get();
		bool create_list();

		HMODULE get_module(std::string name);
		std::map<std::string, HMODULE> get_list();
	};
}