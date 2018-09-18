#pragma once
#include "control.h"

namespace menu
{
	class button : public control
	{
	private:
		callbackfn callback;
	public:
		button(const char* name, int x, int y, int w, int h, stealth::cmd* cmd)
		{
			this->name = name;
			this->m_x = x;
			this->m_y = y;
			this->m_w = w;
			this->m_h = h;
			this->cmd = cmd;
			this->ctrl_type = control_type::BUTTON;
		}

		void set_callback(callbackfn callback);

		void init();
		void update();
		void draw(RendererPtr renderer);
		void input(WPARAM key);
	};
}