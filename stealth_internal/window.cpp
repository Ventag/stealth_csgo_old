#include "window.h"
#include "framework.h"
#include "stealth_input.h"
#include "iosystem.h"

namespace menu
{
	void window::add_child(control* child)
	{
		child->parent = this;
		children.push_back(child);
	}

	void window::init()
	{

	}

	void window::update()
	{
		static int d_x, d_y;
		hook::iosys* io = hook::iosys::get();
		if (!framework::get()->get_focus())
			framework::get()->set_focus(this);

		if (!cmd->value<bool>())
			return;

		if(io->get_mouse1() && dragging && framework::get()->get_focus() == this)
		{
			m_x = io->get_mouse_x() - d_x;//framework::get()->mouse_x - d_x;
			m_y = io->get_mouse_y() - d_y;//framework::get()->mouse_y - d_y;
			dragging = true;
		}
		else
		{
			dragging = false;
		}

		if (framework::get()->get_focus() != this && framework::get()->get_focus()->is_mouse_in_area())
			return;

		if (io->get_mouse1()/*input::get()->get_key_click(KEYS::MOUSE1)*/ 
			&& is_mouse_in_area(true))
		{
			d_x = io->get_mouse_x() - m_x;//framework::get()->mouse_x - m_x;
			d_y = io->get_mouse_y() - m_y;//framework::get()->mouse_y - m_y;
			framework::get()->set_focus(this);

			dragging = true;
		}

		if (!dragging)
		{
			for (auto child : children)
			{
				child->update();
			}
		}
	}

	void window::draw(RendererPtr renderer)
	{
		if (!cmd->value<bool>())
			return;

		const Vec4 outline_rect = { (float)m_x - 1.f, (float)m_y - 1.f, (float)m_w + 2.f, (float)m_h + 2.f };
		const Vec4 window_rect = { (float)m_x, (float)m_y, (float)m_w, (float)m_h };
		const Vec4 client_rect = { (float)m_x, (float)m_y + 30.f, (float)m_w, (float)m_h - 45.f };
		renderer->draw_filled_rect(outline_rect, 0xe0000000);
		renderer->draw_gradient_rect(window_rect, 0xffff0000, 0xffb20000);
		renderer->draw_gradient_rect(client_rect, 0xffbfbfbf, 0xffffffff);

		renderer->draw_text(hook::title_font, { m_x + 10.f, m_y + 2.f }, this->name, 0xffffffff, TextFlags::TEXT_LEFT | TextFlags::TEXT_SHADOW);
		renderer->draw_text(hook::main_font, { m_x + 10.f, m_y + m_h - 14.f }, "stealth framework v1.0", 0xffe0e0e0, TEXT_LEFT);
		for (auto child : children)
		{
			child->draw(renderer);
		}
	}

	void window::input(WPARAM key)
	{

	}
}