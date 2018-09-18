#include "interface.h"
#include "module.h"
#include "log.h"

stealth::interfacelist* stealth::interfacelist::get()
{
	static interfacelist g_interfacelist;
	return &g_interfacelist;
}

bool stealth::interfacelist::initialize_interfaces()
{
	for (auto m : stealth::module::get()->get_list())
	{
		void *create_interface = GetProcAddress(m.second, "CreateInterface");

		size_t jmp_instruction = (size_t)(create_interface) + 4;
		size_t jmp_target = jmp_instruction + *(size_t*)(jmp_instruction + 1) + 5;

		interface_list = **(interface_linked_list***)(jmp_target + 6);
		while (interface_list)
		{
			std::string name = interface_list->name;
			std::string msg = "found interface [" + name + "] in module [" + m.first + "]";
			stealth::log::get()->write(msg, INFO);
			interfaces.insert_or_assign(interface_list->name, interface_list->func);
			interface_list = interface_list->next;
		}
	}
	interface_size = interfaces.size();

	return interface_size > 0;
}

template <typename T>
T stealth::interfacelist::find_interface(std::string chInterface)
{
	static_assert(std::is_pointer<T>::value, "Type T must be a pointer type!");
	void* obj = nullptr;

	auto version_highest = -1;

	for (auto entry : interfaces)
	{
		/*
		> Copies the cleaned interface name into a buffer
		> ex. VClient001 -> VClient
		*/
		auto tmp(entry.first);
		tmp.resize(tmp.size() - 3);

		if (chInterface != tmp)
			continue;

		/*
		> Extracts the interface version number
		*/
		auto interface_version_buffer(entry.first.substr(entry.first.length() - 3));
		auto interface_version = atoi(interface_version_buffer.c_str());

		if (interface_version > version_highest)
		{
			obj = entry.second;
			version_highest = interface_version;
		}
	}

	//G::console.print("%s", chInterface.c_str());

	/*if (!obj)
	{
		G::console.print(" = ");
		G::console.print(eColour::RED, "nullptr\n");
	}
	else
	{
		G::console.print("%i = ", version_highest);
		G::console.print(eColour::GREEN, "0x%X\n", Object);
	}*/

	return static_cast<T>(obj);
}