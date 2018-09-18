#include "control.h"
#include "framework.h"


namespace menu
{
	void control::set_color(Color color)
	{
		this->color = color;
	}

	void control::add_child(control* child)
	{
		if (child)
			this->children.push_back(child);
		else
			stealth::log::get()->write("tried writing child nullptr", logtype::WARNING);
	}

	bool control::is_mouse_in_area()
	{
		/*if(parent)
			return (framework::get()->mouse_x > parent->m_x + m_x		// is the mouse inside the area?
				&& framework::get()->mouse_x < parent->m_x + m_x + m_w
				&& framework::get()->mouse_y > parent->m_y + m_y
				&& framework::get()->mouse_y < parent->m_y + m_y + m_h);*/
			
		/*return (framework::get()->mouse_x > get_x()		// is the mouse inside the area?
			&& framework::get()->mouse_x < get_x() + m_w
			&& framework::get()->mouse_y > get_y()
			&& framework::get()->mouse_y < get_y() + m_h);*/

		hook::iosys* io = hook::iosys::get();
		if(parent)
			return (io->get_mouse_x() > get_x()		// is the mouse inside the area?
				&& io->get_mouse_x() < get_x() + m_w
				&& io->get_mouse_y() > get_y()
				&& io->get_mouse_y() < get_y() + m_h);
		else
			return(io->get_mouse_x() > m_x		// is the mouse inside the area?
			&& io->get_mouse_x() < m_x + m_w
			&& io->get_mouse_y() > m_y
			&& io->get_mouse_y() < m_y + m_h);
	}

	bool control::is_mouse_in_area(bool header)
	{
		hook::iosys* io = hook::iosys::get();
		if(parent)
			return (io->get_mouse_x() > get_x()		// is the mouse inside the area?
				&& io->get_mouse_x() < get_x() + m_w
				&& io->get_mouse_y() > get_y()
				&& io->get_mouse_y() < get_y() + 30); 
		else
			return(io->get_mouse_x() > m_x		// is the mouse inside the area?
				&& io->get_mouse_x() < m_x + m_w
				&& io->get_mouse_y() > m_y
				&& io->get_mouse_y() < m_y + 30);
	}
}