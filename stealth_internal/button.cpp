#include "button.h"
#include "iosystem.h"
#include "framework.h"

namespace menu
{
	void button::set_callback(callbackfn callback)
	{
		this->callback = callback;
	}

	void button::init()
	{

	}

	void button::update()
	{
		hook::iosys* io = hook::iosys::get();

		if (is_mouse_in_area())// && io->get_mouse1())
			framework::get()->set_focused_control(this);
	}

	void button::draw(RendererPtr renderer)
	{
		float x = get_x(), y = get_y();
		Vec4 control_rect = { (float)x, (float)y, (float)m_w, (float)m_h };

		renderer->draw_filled_rect(control_rect, 0xff101010);

		control_rect = { (float)x + 1, (float)y + 1, (float)m_w - 2, (float)m_h - 2 };
		if(is_mouse_in_area(false))
			renderer->draw_gradient_rect(control_rect, 0xffbfbfbf, 0xffffffff);
		else
			renderer->draw_gradient_rect(control_rect, 0xffffffff, 0xffbfbfbf);

		renderer->draw_text(hook::main_font, { x + (m_w / 2), y + (m_h / 2.f) - 7.f }, this->name, 0xff000000, TEXT_CENTERED_X);
	}

	void button::input(WPARAM key)
	{
		// nyi

		if (is_mouse_in_area())
		{
			hook::iosys* io = hook::iosys::get();
			if(key == KEYS::MOUSE1)
				callback();
		}
		else
		{
			framework::get()->set_focused_control(nullptr);
		}
	}
}