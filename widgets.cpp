#include "widgets.hpp"
#include "Window.hpp"

using namespace genv;

Widget::Widget(Window* window, int x, int y, int sx, int sy)
: m_x(x), m_y(y), m_size_x(sx), m_size_y(sy)
{
    m_screensize = window->screensize();
    window->registerwidget(this);
}

bool Widget::is_selected(int mx, int my) const
{
    return mx >= m_x && mx <= m_x + m_size_x && my >= m_y && my <= m_y + m_size_y;
}

void haromszog(int x, int y, int felalap, int magassag, int elojel)
{
    gout << move_to(x, y);
    for (int i = 0; i < magassag; i++)
    {
        gout << line_to(x + felalap, y);
        gout << move_to(x, y + elojel * i);
        gout << line_to(x - felalap, y);
        gout << move_to(x, y + elojel * i);
    }
}