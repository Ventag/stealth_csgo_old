#pragma once
#include "include.h"
namespace stealth
{
	class cmdlist;

	class cmd
	{
	private:
		enum TYPE
		{
			INT_T,
			FLT_T,
			BL_T
		};

		float fval;
		int ival;
		bool bval;
		TYPE t;

		char m_name[64];
		char m_desc[64];
	public:
		cmd() {};
		cmd(const char* n, const char* d, float val);
		cmd(const char* n, const char* d, int val);
		cmd(const char* n, const char* d, bool val);

		std::string handle_args(std::string args);

		std::string get_name()
		{
			return m_name;
		}

		std::string get_desc()
		{
			return m_desc;
		}

		template <typename T>
		T value()
		{
			switch (t)
			{
			case INT_T:
				return (int)ival;
			case FLT_T:
				return (float)fval;
			case BL_T:
				return (bool)bval;
			default:
				return 0;
			}
		}

		template <typename T>
		void set_value(T val)
		{
			switch (t)
			{
			case INT_T:
				ival = val;
				break;
			case FLT_T:
				fval = val;
				break;
			case BL_T:
				bval = val;
				break;
			default:
				break;
			}
		}
	};

	class cmdlist
	{
		std::vector<cmd*> cmds;
	public:
		static cmdlist* get();

		void add_cmd(cmd* cmd);

		cmd* get_cmd(std::string cmd);
	};
}