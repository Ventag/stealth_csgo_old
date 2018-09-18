#pragma once
#include "control.h"

namespace menu
{
	class listbox : public control
	{
	private:
		std::vector<std::string> items;
		int min_items = 0;
		int max_items = 1;
		int item_index = 0;
	public:
		listbox(const char* name, int x, int y, int w, int h, stealth::cmd* cmd)
		{
			this->name = name;
			this->m_x = x;
			this->m_y = y;
			this->m_w = w;
			this->m_h = h;
			this->cmd = cmd;
			this->ctrl_type = control_type::LISTBOX;
		}

		void add_item(std::string item);

		void init();
		void update();
		void draw(RendererPtr renderer);
		void input(WPARAM key);
	};
}