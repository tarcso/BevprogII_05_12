#include "pushbutton.hpp"
#include <iostream>

using namespace genv;

PushButton::PushButton(Window* window, int x, int y, int sx, int sy, std::string s, std::function<void()> f)
                       : Widget(window, x, y, sx, sy), m_szov(s), m_func(f)
{}

void PushButton::handle(const event& ev)
{
    if(ev.type == ev_mouse && ev.button == btn_left && is_selected(ev.pos_x, ev.pos_y))
    {
        m_pushed = true;
        m_func();
    }
}

void PushButton::draw() const
{
    gout << color(255, 255, 255) << move_to(m_x, m_y) << box(m_size_x, m_size_y);
    gout << color(0,0,0) << move_to(m_x + 1, m_y + 1) << box(m_size_x-2, m_size_y-2);
    gout << move_to(m_x + m_size_x/2.0-gout.twidth(m_szov)/2.0, m_y + m_size_y/2 - (gout.cascent()+ gout.cdescent())/2) << color(255,255,255) << text(m_szov);
}