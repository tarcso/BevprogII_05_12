#include "menuelem.hpp"

using namespace genv;

MenuElem::MenuElem(int x, int y, int sx, int sy, std::string szov)
{
    m_x = x;
    m_y = y;
    m_size_x = sx;
    m_size_y = sy;
    m_szov = szov;
    m_valasztott = false;
}

bool MenuElem::is_selected(int mouse_x, int mouse_y) const
{
    return mouse_x>m_x && mouse_x<m_x+m_size_x && mouse_y>m_y && mouse_y<m_y+m_size_y;
}

void MenuElem::draw() const
{
    gout << move_to(m_x, m_y) << color(255, 255, 255) << box(m_size_x, m_size_y) << move_to(m_x + 2, m_y + 4);
    if(m_valasztott) gout << move_to(m_x + 2, m_y + 2) << color(150, 150, 150) << box(m_size_x - 4, m_size_y - 4);
    gout << move_to(m_x + 4, m_y + 4) << color(10, 10, 10) << text(m_szov);
}

bool MenuElem::kintvan(int hatar) const
{
    return m_y >= hatar;
}