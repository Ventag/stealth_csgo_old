#include "init.h"
#include "module.h"
#include "interface.h"
#include "log.h"
#include "hook.h"
#include "console.h"
stealth::init* stealth::init::get()
{
	static init g_init;
	return &g_init;
}

bool stealth::init::modules()
{
	if (stealth::module::get()->create_list())
		return true;

	return false;
}

bool stealth::init::interfaces()
{
	if(stealth::interfacelist::get()->initialize_interfaces())
		return true;

	return false;
}

bool stealth::init::setup(HMODULE mod)
{
	if (!log::get()->initialize("stealth.log"))
		return false;

	if (!mod)
	{
		log::get()->write("failed to acquire local module", logtype::WARNING);
		return false;
	}

	this->mod = mod;

	if (!this->modules())
		return false;

	log::get()->write("acquired modules", SUCCESS);

	if (!this->interfaces())
		return false;

	log::get()->write("acquired interfaces", SUCCESS);

	if (!hook::init::get()->setup())
		return false;

	while (true);

	return true;
}