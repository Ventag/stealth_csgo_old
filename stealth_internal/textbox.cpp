#include "textbox.h"
#include "framework.h"
#include "iosystem.h"

const char* keynames[254] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, "bkspc", "	", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, "SHIFT", nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, " ",
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X",
"Y", "Z", nullptr, nullptr, nullptr, nullptr, nullptr, "0", "1", "2", "3", "4", "5", "6",
"7", "8", "9", "*", "+", "_", "-", ".", "/", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, ";", "+", ",", "-", ".", "/?", "~", nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, "[{", "\\|", "}]", "'\"", nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };

namespace menu
{
	void textbox::set_callback(callbackfn fn)
	{
		callback = fn;
	}

	std::string textbox::get_buffer()
	{
		return buffer;
	}

	void textbox::add_buffer(WPARAM key)
	{
		if (key > 0 && key < 0x10000)
		{
			if (key == '\r')
				callback();
			else if (key == '\b' && buffer.size() > 0)
				buffer.pop_back();
			else
				buffer += (unsigned short)key;
		}
	}

	void textbox::reset_buffer()
	{
		buffer.clear();
	}

	bool textbox::is_key_blacklisted(int key)
	{
		return key < 32 || key > 100;
	}

	void textbox::init()
	{

	}

	void textbox::update()
	{
		hook::iosys* io = hook::iosys::get();

		if (is_mouse_in_area())
		{
			if (io->get_mouse1())
			{
				framework::get()->set_focused_control(this);
				//framework::get()->buffer_reset();
				buffer.clear();
			}
		}
	}

	void textbox::draw(RendererPtr renderer)
	{
		int x = get_x(), y = get_y();
		Vec4 control_rect = { (float)x, (float)y, (float)m_w, (float)m_h };
		renderer->draw_gradient_rect(control_rect, 0xff212121, 0xff0f0f0f);
		renderer->draw_rect(control_rect, 1, 0xff000000);
		renderer->draw_text(hook::main_font, { (float)x + 5.f, (float)y + 2.f }, buffer, 0xffffffff, TEXT_LEFT);
	}

	void textbox::input(WPARAM key)
	{
		if (key > 0 && key < 0x10000)
		{
			if (key == '\r')
				callback();

			buffer += (unsigned short)key;
		}
	}
}