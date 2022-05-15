#include "gordmenu.hpp"
#include "menuelem.hpp"
#include <cmath>
#include <vector>

using namespace genv;

GordMenu::GordMenu(Window* window, int x, int y, int sx, int sy, std::string szov, std::vector<std::string> v, int darab)
                : Widget(window, x, y, sx, sy), m_nyomott(false), m_szov(szov),
                  m_gorgsz(0), m_gorg(false), m_hatardb(darab)
{
    for (size_t i = 0; i < v.size(); i++)
    {
        m_elemek.push_back(new MenuElem(x, y + (i+1) * sy, sx, sy, v[i]));
    }

    m_eredetihatar = darab;

    if(m_hatardb>m_elemek.size()) 
    {
        m_hatardb = m_elemek.size();
    }
    else
    {
        for (size_t i = 0; i < m_hatardb; i++)
        {
            if(m_elemek[i]->kintvan(m_screensize.second))
            {
                m_hatardb = i;
                break;
            }
        }
    }

    if(m_elemek.size()-m_hatardb > 0)
    {
        m_gorg = true;
        m_gordmax = m_elemek.size()-m_hatardb;
    }
}

void GordMenu::reset()
{
    for (size_t i = 0; i < m_elemek.size(); i++)
    {
        if(m_elemek[0]->m_y != m_y + m_size_y)
        {
            for(MenuElem* m : m_elemek)
            {
                m->m_y += m->m_size_y;
            }
        }
    }
    m_gorgsz = 0;
}


void GordMenu::hozzaadElem(std::string s)
{
    if(s == "") return;

    for(MenuElem* p : m_elemek)
    {
        if(p->m_szov == s) return;
    }

    reset();

    m_elemek.push_back(new MenuElem(m_x, m_y + m_size_y*(m_elemek.size() + 1), m_size_x, m_size_y, s));
}

void GordMenu::torolElem(std::string s)
{
    if(m_elemek.size() == 0) return;
    std::vector<MenuElem*> marad;
    int ittvan = m_elemek.size();
    for (size_t i = 0; i < m_elemek.size(); i++)
    {
        if(m_elemek[i]->m_szov == m_szov)
        {
            delete m_elemek[i];
            ittvan = i;
        }
        else if(i > ittvan)
        {
            m_elemek[i]->m_y -= m_size_y;
            marad.push_back(m_elemek[i]);
        }
        else marad.push_back(m_elemek[i]);
    }
    m_elemek = marad;
    if(m_elemek.size() <= m_hatardb) m_gorg = false;

    if(m_elemek.size()-m_hatardb > 0)
        m_gordmax = m_elemek.size()-m_hatardb;
    if(s == m_szov && ittvan != m_elemek.size())
    {
        m_szov = m_elemek[ittvan]->m_szov;
        m_index = ittvan;
    }
    else if(s == m_szov)
    {
        m_szov = m_elemek[ittvan-1]->m_szov;
        m_index = ittvan-1;
    }
}

bool GordMenu::is_selected(int mx, int my) const 
{
    if(m_nyomott && !m_elemek.empty()) return mx >= m_x && mx <= m_x + m_size_x && my >= m_y && my <= m_elemek[m_elemek.size()-1]->m_y + m_elemek[m_elemek.size()-1]->m_size_y;
    else return mx >= m_x && mx <= m_x + m_size_x && my >= m_y && my <= m_y + m_size_y;
}

void GordMenu::handle(const event& ev)
{
    
    if(Widget::is_selected(ev.pos_x, ev.pos_y) &&  ev.type == ev_mouse &&  ev.button == btn_left && ev.button != -btn_left)
    {
        m_nyomott = true;
    }

    if(m_nyomott && m_gorg && ev.type == ev_mouse && ev.button == btn_wheeldown && m_elemek[m_elemek.size()-1]->kintvan(m_y + m_size_y + m_hatardb * m_size_y))
    {
        for(MenuElem* m : m_elemek)
        {
            m->m_y -= m->m_size_y;
        }
        m_gorgsz++;
    }

    if(m_nyomott && m_gorg && ev.type == ev_mouse && ev.button == btn_wheelup && m_elemek[0]->m_y != m_y + m_size_y)
    {
        for(MenuElem* m : m_elemek)
        {
            m->m_y += m->m_size_y;
        }
        m_gorgsz--;
    }

    for(size_t i = 0; i < m_elemek.size(); i++)
    {
        if(m_elemek[i]->is_selected(ev.pos_x, ev.pos_y) && m_nyomott && !m_elemek[i]->kintvan(m_y + m_size_y + m_hatardb * m_size_y) && m_elemek[i]->m_y >= m_y + m_size_y)
        {
            m_elemek[i]->m_valasztott = true;
            if(ev.button == btn_left)
            {
                m_nyomott = false;
                m_szov = m_elemek[i]->m_szov;
                m_index = i;
                reset();
            }
        }
        else m_elemek[i]->m_valasztott = false;
    }

    if(!Widget::is_selected(ev.pos_x, ev.pos_y) && ev.type == ev_mouse && ev.button == btn_left)
    {
        m_nyomott = false;
    }
}

void GordMenu::draw() const
{
    gout << move_to(m_x, m_y) << color(255, 255, 255) << box(m_size_x, m_size_y);
    gout << move_to(m_x + 4, m_y + 4) << color(10, 10, 10) << text(m_szov);
    if(!m_nyomott)
    {
        haromszog(m_x + m_size_x*9.0/10.0 + (m_size_x*1.0/10.0)/2.0, m_y + m_size_y/3.0, (m_size_x*1.0/10.0)*1.0/4.0, m_size_y/3.0, 1);
    }
    else if(m_elemek.size() >= 0)
    {
        haromszog(m_x + m_size_x*9.0/10.0 + (m_size_x*1.0/10.0)/2.0, m_y + m_size_y*2.0/3.0, (m_size_x*1.0/10.0)*1.0/4.0 ,m_size_y/3.0, -1);
        for(const MenuElem* const m : m_elemek)
        {
            if(!m->kintvan(m_y + m_size_y + m_hatardb * m_size_y) && m->m_y >= m_y + m_size_y) m->draw();
        }
        if(m_gorg)
        {
            gout << move_to(m_x + m_size_x - 4, m_y + m_size_y + m_gorgsz * m_hatardb * m_size_y/(m_gordmax+1)) << color(0, 0, 0) << box(4,m_hatardb * m_size_y/(m_gordmax+1));
        }
    }
}

void GordMenu::replaceVec(std::vector<std::string> vec)
{
    for (size_t i = 0; i < m_elemek.size(); i++)
    {
        delete m_elemek[i];
    }
    while(!m_elemek.empty())
    {
        m_elemek.pop_back();
    }
    
    for (size_t i = 0; i < vec.size(); i++)
    {
        m_elemek.push_back(new MenuElem(m_x, m_y + (i+1) * m_size_y, m_size_x, m_size_y, vec[i]));
    }

    if(m_elemek.size() >= m_eredetihatar) m_hatardb = m_eredetihatar;
    else m_hatardb = m_elemek.size();

    if(m_elemek.size() > m_hatardb) m_gorg = true;
    else m_gorg = false;

    reset();

    if(m_elemek.size()-m_hatardb > 0)
    {
        m_gorg = true;
        m_gordmax = m_elemek.size()-m_hatardb;
    }

    if(m_elemek.size() > 0) 
    {
        m_szov = m_elemek[0]->m_szov;
        m_index = 0;
    }
    else m_szov = "";
}

int GordMenu::allapot() const
{
    return m_index;
}
