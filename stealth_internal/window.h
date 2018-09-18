#pragma once
#include "control.h"

namespace menu
{
	class window : public control
	{
	private:
		std::vector<control*> children;

		bool dragging = false;

	public:
		window(const char* name, int x, int y, int w, int h, stealth::cmd* cmd)
		{
			this->name = name;
			this->m_x = x;
			this->m_y = y;
			this->m_w = w;
			this->m_h = h;
			this->cmd = cmd;
			this->ctrl_type = control_type::WINDOW;
		}

		void add_child(control* child);

		void init();
		void update();
		void draw(RendererPtr renderer);
		void input(WPARAM key);

		control* focus_control;
	};
}