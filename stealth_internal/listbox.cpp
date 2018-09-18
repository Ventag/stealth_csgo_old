#include "listbox.h"
#include "d3d_hook.h"
#include "font.h"
#include "iosystem.h"

#include "framework.h"

namespace menu
{
	void listbox::add_item(std::string item)
	{
		items.push_back(item);
	}

	void listbox::init()
	{

	}

	void listbox::update()
	{
		hook::iosys* io = hook::iosys::get();
		if (is_mouse_in_area())
		{
			if(io->get_mouse1())
				framework::get()->set_focused_control(this);
		}
	}

	void listbox::draw(RendererPtr renderer)
	{
		int x = get_x(), y = get_y();
		Vec4 control_rect = { (float)x, (float)y, (float)m_w, (float)m_h };
		renderer->draw_gradient_rect(control_rect, 0xff212121, 0xff0f0f0f); 
		renderer->draw_rect(control_rect, 1, 0xff000000);

		Vec2 fontextent = renderer->get_text_extent(hook::main_font, "a");
		int max_items = m_h / fontextent[1];

		if (items.size() == 0)
			return;

		int draw_index = 0;
		for (int i = min_items; i < min_items + max_items; i++)
		{
			if (i > items.size() - 1)
				return;

			renderer->draw_text(hook::main_font, { (float)x + 5.f, (float)y + (fontextent[1] * draw_index) }, items[i], 0xffffffff, TEXT_LEFT | TEXT_COLORTAGS);
			draw_index++;
		}
	}

	void listbox::input(WPARAM key)
	{
		if(key == KEYS::UP)
			if(min_items > 0)
				min_items--;

		if (key == KEYS::DOWN)
			if (min_items < items.size() - max_items)
				min_items++;
	}
}