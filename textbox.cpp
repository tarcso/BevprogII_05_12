#include "textbox.hpp"
#include <iostream>

using namespace genv;

textBox::textBox(Window* window, int x, int y, int sx, int sy, std::string s) : Widget(window, x, y, sx, sy), m_szov(s)
{}

void textBox::handle(const genv::event& ev)
{}

void textBox::draw() const
{
    gout << move_to(m_x, m_y) << color(255, 255, 255) << box(m_size_x, m_size_y);
    gout << move_to(m_x + 1, m_y + 1) << color(0, 0, 0) << box(m_size_x-2, m_size_y-2);
    gout << move_to(m_x + 5, m_y + m_size_y/2 - (gout.cascent()+ gout.cdescent())/2) << color(255,255,255) << text(m_szov);
}

void textBox::setText(std::string s)
{
    m_szov = s;
}