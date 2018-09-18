#pragma once
#include "include.h"
#include "renderer.h"
#include "cmd.h"
#include "log.h"
#include "d3d_hook.h"
#include "hook.h"
#include "iosystem.h"

#define HEADER_HEIGHT 30
namespace menu
{
	enum control_type
	{
		WINDOW,
		BUTTON,
		LISTBOX,
		TEXTBOX
	};

	typedef void(*callbackfn)(void);
	class control
	{
	public:
		float m_x, m_y;
		float m_w, m_h;
		std::string name;
		stealth::cmd* cmd = nullptr;
		bool focus = false;
		Color color;

		callbackfn callback = nullptr;
		control* parent = nullptr;

		std::vector<control*> children;

		control_type ctrl_type;
	public:
		control() { stealth::log::get()->write("tried null initializing control", logtype::WARNING); }
		control(const char* name, int x, int y, int w, int h, stealth::cmd* cmd)
		{
			this->name = name;
			this->m_x = x;
			this->m_y = y;
			this->m_w = w;
			this->m_h = h;
			this->cmd = cmd;
		}

		virtual void init() = 0;
		virtual void update() = 0;
		virtual void draw(RendererPtr renderer) = 0;
		virtual void input(WPARAM key) = 0;

		void set_color(Color color);
		void add_child(control* child);
		bool is_mouse_in_area();
		bool is_mouse_in_area(bool header);

		int get_x()
		{
			if (parent)
				return parent->m_x + m_x;
			return m_x;
		}

		int get_y()
		{
			if (parent)
				return parent->m_y + HEADER_HEIGHT + m_y;
			return m_y;
		}
	};
}