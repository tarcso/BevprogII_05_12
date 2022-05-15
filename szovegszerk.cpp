#include "graphics.hpp"
#include "szovegszerk.hpp"
#include <string>

using namespace genv;

SzovegSzerk::SzovegSzerk(Window* window, int x, int y, int sx, int sy) : Widget(window, x, y, sx, sy){}

void SzovegSzerk::handle(const event& ev)
{
    if(is_selected(ev.pos_x, ev.pos_y) && ev.button == btn_left)
    {
        selected = true;
    }
    else if(!is_selected(ev.pos_x, ev.pos_y) && ev.button == btn_left)
    {
        selected = false;
    }

    if(selected)
    {
        if(ev.keycode == key_lshift || ev.keycode == key_rshift) nagy  = true;
        if(ev.keycode == -key_lshift || ev.keycode == -key_rshift) nagy = false;
        if(ev.keycode == key_capsl) nagy = abs(nagy-1);
        if(ev.type == ev_key && ev.keycode >= 0 && ev.keycode != key_backspace && gout.twidth(szov) <= m_size_x - 22)
        {
            if(ev.keycode != key_rshift && ev.keycode != key_lshift && ev.keycode != key_capsl)
            {
                if(nagy) szov += toupper(ev.keycode);
                else szov += ev.keycode;
            }
        }
        else if(ev.keycode == key_backspace && szov.length() != 0 && ev.keycode >= 0)
        {
            std::string ujszov;
            for(size_t i = 0; i < szov.length()-1; i++)
            {
                ujszov += szov[i];
            }
            szov = ujszov;
        }
        if(ev.type == ev_timer)
        {
            ido++;
            if(ido >= 30 && ido <= 40)
            {
                cursor = true;
                if(ido == 40) ido = 0;
            }
            else cursor = false;
        }
    }
}

void SzovegSzerk::draw() const
{
    gout << move_to(m_x, m_y) << color(255, 255, 255) << box(m_size_x, m_size_y) << move_to(m_x+3, m_y+3) << color(0, 0, 0) << box(m_size_x - 6, m_size_y - 6) << color(255, 255, 255) << move_to(m_x+10, m_y + m_size_y/2 - (gout.cascent()+ gout.cdescent())/2) << text(szov);
    if (cursor)
    gout << move_to(m_x + 10 + gout.twidth(szov), m_y + 15) << line_to(m_x + 10 + gout.twidth(szov), m_y + 30);
}

std::string SzovegSzerk::allapot() const
{
    return szov;
}

void SzovegSzerk::clear()
{
    szov = "";
}
