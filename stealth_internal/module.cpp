#include "module.h"
#include "log.h"

#include "TlHelp32.h"

stealth::module* stealth::module::get()
{
	static stealth::module g_module;
	return &g_module;
}

bool stealth::module::create_list()
{
	/*MODULEENTRY32 me32;

	auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetCurrentProcessId());
	if (snapshot == INVALID_HANDLE_VALUE)
	{
		MessageBoxA(0, "invalid handle", "", 0);
		return false;
	}

	me32.dwSize = sizeof(MODULEENTRY32);

	if (!Module32First(snapshot, &me32))
	{
		MessageBoxA(0, "invalid me32", "", 0);
		CloseHandle(snapshot);
		return false;
	}

	while(Module32Next(snapshot, &me32))
	{
		HINSTANCE* p_module = nullptr;

		while (!p_module)
			*p_module = GetModuleHandle(me32.szModule);

		log::get()->write(me32.szModule, INFO);

		module_list.insert_or_assign(me32.szModule, p_module);
	}

	CloseHandle(snapshot);
	return true;*/
	const int module_num = 3;

	//std::array<std::string, module_num> module_names = {"engine.dll", "client.dll", "shaderapidx9.dll"};
	//std::map<std::string> modules = {};
	std::vector<std::string> module_names = {"engine.dll", "client_panorama.dll", "shaderapidx9.dll"};
	for (int i = 0; i < module_names.size(); i++)
	{
		HMODULE p_module = nullptr;
		while (!p_module)
			p_module = GetModuleHandleA(module_names[i].c_str());

		log::get()->write(module_names[i], SUCCESS);
		module_list.insert_or_assign(module_names[i], p_module);
	}

	return true;
}

HMODULE stealth::module::get_module(std::string name)
{
	for (auto m : module_list)
	{
		if (m.first == name)
			return m.second;
	}

	return nullptr;
}

std::map<std::string, HINSTANCE> stealth::module::get_list()
{
	return module_list;
}