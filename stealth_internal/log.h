#pragma once
#include "include.h"

enum logtype
{
	INFO,
	SUCCESS,
	WARNING
};

namespace stealth
{
	class log
	{
	private:
		std::ofstream logfile;

		std::string get_type(logtype t);
	public:
		static log* get();

		bool initialize(std::string file);

		void write(std::string msg, logtype t, ...);
		void print(std::string msg, ...);
		void log_to_console(std::string msg, logtype t, ...);
	};
}