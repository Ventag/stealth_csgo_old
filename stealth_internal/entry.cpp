#include "include.h"
#include "init.h"

/*unsigned __stdcall*/void entry(HINSTANCE mod)
{
	if (stealth::init::get()->setup(mod))
		Beep(0x200, 10);
	//return 0x0;
}
int __stdcall DllMain(HINSTANCE mod, DWORD reason, void*)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
	{
		entry(mod);
		break;
	}
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	default:
		break;
	}
}