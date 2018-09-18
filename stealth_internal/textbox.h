#pragma once
#include "control.h"


namespace menu
{
	class textbox : public control
	{
	private:
		std::string buffer;
		bool active = false;

		bool is_key_blacklisted(int key);
	public:
		textbox(const char* name, int x, int y, int w, int h, stealth::cmd* cmd)
		{
			this->name = name;
			this->m_x = x;
			this->m_y = y;
			this->m_w = w;
			this->m_h = h;
			this->cmd = cmd;
			this->ctrl_type = control_type::TEXTBOX;
		}

		void set_callback(callbackfn fn);
		std::string get_buffer();
		void add_buffer(WPARAM key);
		void reset_buffer();

		void init();
		void update();
		void draw(RendererPtr renderer);
		void input(WPARAM key);
	};
}