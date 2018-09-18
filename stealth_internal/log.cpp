#include "log.h"
#include <vadefs.h>
#include "console.h"

HANDLE _out = NULL, _old_out = NULL;
HANDLE _err = NULL, _old_err = NULL;
HANDLE _in = NULL, _old_in = NULL;

stealth::log* stealth::log::get()
{
	static log g_log;
	return &g_log;
}

bool stealth::log::initialize(std::string file)
{
	_old_out = GetStdHandle(STD_OUTPUT_HANDLE);
	_old_err = GetStdHandle(STD_ERROR_HANDLE);
	_old_in = GetStdHandle(STD_INPUT_HANDLE);

	::AllocConsole() && ::AttachConsole(GetCurrentProcessId());

	_out = GetStdHandle(STD_OUTPUT_HANDLE);
	_err = GetStdHandle(STD_ERROR_HANDLE);
	_in = GetStdHandle(STD_INPUT_HANDLE);

	SetConsoleMode(_out,
		ENABLE_PROCESSED_OUTPUT | ENABLE_WRAP_AT_EOL_OUTPUT);

	SetConsoleMode(_in,
		ENABLE_INSERT_MODE | ENABLE_EXTENDED_FLAGS |
		ENABLE_PROCESSED_INPUT | ENABLE_QUICK_EDIT_MODE);

	logfile.open(file.c_str(), std::ios::out | std::ios::app);

	if (!logfile.is_open())
		return false;

	write("\n===============================\nnew session - initialized logger\n===============================", SUCCESS);

	return true;
}

std::string stealth::log::get_type(logtype t)
{
	switch (t)
	{
	case INFO:
		return "INFO";
	case WARNING:
		return "WARNING";
	case SUCCESS:
		return "SUCCESS";
	default:
		return "UNKNOWN";
	}
}

void stealth::log::write(std::string msg, logtype t, ...)
{
	//print("[%s] %s", get_type(t), msg);
	print(msg);
	try
	{
		// get the current time
		std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
		time_t tt = std::chrono::system_clock::to_time_t(now);

		// strip the newline passed back by ctime
		auto tt_stripped = std::strtok(ctime(&tt), "\n");
		logfile << "[ " << get_type(t) << " ] " << "[" << tt_stripped << "] " << msg << std::endl;
		log_to_console(msg, t);
	}
	catch (std::exception& e)
	{
		std::cerr << "Error while trying to log a message:\n" << e.what() << std::endl;
	}
}

void stealth::log::print(std::string msg, ...)
{
	int len = strlen(msg.c_str());
	if (msg.at(len - 2) != '\'' && msg.at(len - 1) != 'n')
		msg += "\n";

	const char* string = msg.c_str();

	char buf[1024] = { 0 };
	va_list va;

	va_start(va, string);
	_vsnprintf_s(buf, 1024, string, va);
	va_end(va);

	std::string outRes = buf;

	WriteConsoleA(_out, buf, static_cast<DWORD>(strlen(buf)), nullptr, nullptr);
}

void stealth::log::log_to_console(std::string msg, logtype t, ...)
{
	if (!menu::console::get()->initialized)
		return;

	std::string prequel = "";
	switch (t)
	{
	case logtype::INFO:
		prequel = "[{#ff008080}INFO{#ffffffff}] ";
		break;
	case logtype::SUCCESS:
		prequel = "[{#ff228B22} OK {#ffffffff}] ";
		break;
	case logtype::WARNING:
		prequel = "[{#ffff2400}FAIL{#ffffffff}] ";
	}

	prequel += msg;
	menu::console::get()->history->add_item(prequel);
}