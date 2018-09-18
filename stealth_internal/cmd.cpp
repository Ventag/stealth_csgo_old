#include "cmd.h"

namespace stealth
{
	cmd::cmd(const char* n, const char* d, int val)
	{
		strcpy(m_name, n);
		strcpy(m_desc, d);
		t = INT_T;
		ival = val;

		cmdlist::get()->add_cmd(this);
	}

	cmd::cmd(const char* n, const char* d, float val)
	{
		strcpy(m_name, n);
		strcpy(m_desc, d);
		t = FLT_T;
		fval = val;

		cmdlist::get()->add_cmd(this);
	}

	cmd::cmd(const char* n, const char* d, bool val)
	{
		strcpy(m_name, n);
		strcpy(m_desc, d);
		t = BL_T;
		bval = val;

		cmdlist::get()->add_cmd(this);
	}

	std::string cmd::handle_args(std::string args)
	{
		std::string ret = "";
		char buf[100];
		int _ival = 0;
		int _fval = 0;
		int _bval = 0;

		switch (t)
		{
		case INT_T:
			_ival = std::stoi(args, nullptr, 0);
			sprintf(buf, "%s changed from %i to %i", get_name().c_str(), ival, _ival);
			ival = _ival;
			break;
		case FLT_T:
			_fval = std::atof(args.c_str());
			sprintf(buf, "%s changed from %f to %f", get_name().c_str(), fval, _fval);
			fval = _fval;
			break;
		case BL_T:
			_bval = std::stoi(args, nullptr, 0);
			sprintf(buf, "%s changed from %i to %i", get_name().c_str(), bval, _bval);
			if (_bval == 0)
				bval = false;
			else
				_bval = true;
			break;
		default:
			ret = "unknown type";
		}
		ret = buf;
		return ret;
	}

	cmdlist* cmdlist::get()
	{
		static cmdlist g_cmdlist;
		return &g_cmdlist;
	}

	void cmdlist::add_cmd(cmd* cmd)
	{
		cmds.push_back(cmd);
	}

	cmd* cmdlist::get_cmd(std::string c)
	{
		for (int i = 0; i < cmds.size(); i++)
		{
			cmd* cmd = cmds.at(i);
			if (!cmd)
				continue;

			if (cmd->get_name() == c)
				return cmd;
		}

		return nullptr;
	}
}