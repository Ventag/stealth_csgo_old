#pragma once
#include "include.h"
namespace stealth
{
	class interfacelist
	{
	private:
		std::map<std::string, void*> interfaces;
	private:
		int module_size;
		int interface_size;

		/*struct interface_registry
		{
			using interface_fn = void*(*)();
			interface_fn m_create_fn;
			const char* m_name;
			interface_registry* m_next;
		}*interface_first = nullptr;*/

		struct interface_linked_list 
		{
			void*(*func)();
			const char *name;
			interface_linked_list *next;
		};

		interface_linked_list *interface_list;

	public:
		interfacelist(const std::map<std::string, void*>& pairs, int i_interfaces, int i_modules, interface_linked_list* interface_first)
			: interfaces(pairs),
			interface_size(i_interfaces),
			module_size(i_modules)
		{
		}

		interfacelist() : module_size(0), interface_size(0)
		{
		}
	public:
		static interfacelist* get();
		bool initialize_interfaces();

		template <typename T>
		T find_interface(std::string chInterface);
	};
}