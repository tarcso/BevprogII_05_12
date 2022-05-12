#include "szambeall.hpp"
#include <iostream>

using namespace genv;

Szambeall::Szambeall(Window* window, int x, int y, int sx, int sy, int min, int max) : Widget(window, x, y, sx, sy), m_max(max), m_min(min)
{
    if(min >= max) throw "lol";
    m_novo = false;
    m_csokken = false;
    m_nyomott = false;
    m_numb = (m_min + m_max) / 2.0;
}

int Szambeall::m_mx;
int Szambeall::m_my;

void Szambeall::handle(const event& ev)
{
    m_novo = false;
    m_csokken = false;
    if(ev.type == ev_mouse)
    {
        m_mx = ev.pos_x;
        m_my = ev.pos_y;
    }

    if(is_selected(m_mx, m_my) && ev.type == ev_mouse && ev.button == btn_left)
        m_nyomott = true;
    else if(!is_selected(m_mx, m_my) && ev.type == ev_mouse && ev.button == btn_left)
        m_nyomott = false;



    if(m_nyomott)
    {
        if(is_selected(m_mx, m_my))
        {
            if(m_mx >= m_x + m_size_x * 9.0/10.0 && ev.button == btn_left)
            {
                if(m_my >= Widget::m_y + m_size_y/2.0)
                {
                    m_numb--;
                    m_csokken = true;
                    m_novo = false;
                }
                else 
                {
                    m_numb++;
                    m_novo = true;
                    m_csokken = false;
                }
            }
        }
        if(ev.type == ev_key)
        {
            if(ev.keycode == key_down)
            {
                m_numb--;
                m_csokken = true;
                m_novo = false;
            }
            else if(ev.keycode == key_up)
            {
                m_numb++;
                m_novo = true;
                m_csokken = false;
            }
            else if(ev.keycode == key_pgdn)
            {
                m_numb -= 10;
                m_csokken = true;
                m_novo = false;
            }
            else if(ev.keycode == key_pgup)
            {
                m_numb += 10;
                m_novo = true;
                m_csokken = false;
            }
        }
    }
    if(m_numb > m_max) m_numb = m_max;
    if(m_numb < m_min) m_numb = m_min;
}

void Szambeall::draw() const
{
    std::string numb = std::to_string(m_numb);
    gout << color(255, 255, 255) << move_to(m_x, m_y) << box(m_size_x, m_size_y);
    gout << color(100, 100, 90) << move_to(m_x+2, m_y+2) << box(m_size_x-4, m_size_y-4) << color(255, 255, 255) << move_to(m_x + 4, m_y + 4) << text(numb);
    if(m_novo) gout << move_to(m_x + m_size_x*9.0/10.0, m_y+2) << color(50, 50, 50) << box(m_size_x/10.0-2, m_size_y/2.0-2);
    else if(m_csokken) gout << move_to(m_x + m_size_x*9.0/10.0, m_y + m_size_y/2.0) << color(50, 50, 50) << box(m_size_x/10.0-2, m_size_y/2.0-2);
    gout << color(255, 255, 255) << move_to(m_x + m_size_x * 9.0/10.0,m_y) << line(0, m_size_y);
    gout << move(0, -m_size_y/2.0) << line(m_size_x*1.0/10.0, 0);
    haromszog(m_x + m_size_x*9.0/10.0 + (m_size_x*1.0/10.0)/2.0, m_y + m_size_y*2.0/3.0, (m_size_x*1.0/10.0)*1.0/4.0 ,m_size_y/6.0, 1);
    haromszog(m_x + m_size_x*9.0/10.0 + (m_size_x*1.0/10.0)/2.0, m_y + m_size_y/3.0, (m_size_x*1.0/10.0)*1.0/4.0 ,m_size_y/6.0, -1);
}

const int Szambeall::allapot() const
{
    return m_numb;
}