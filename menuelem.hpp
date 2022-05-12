#ifndef MENUELEM_HPP_INCLUDED
#define MENUELEM_HPP_INCLUDED

#include "graphics.hpp"
#include "gordmenu.hpp"

class MenuElem
{
private:
    int m_x, m_y, m_size_x, m_size_y;
    std::string m_szov;
    bool m_valasztott;

public:
    MenuElem(int x, int y, int sx, int sy, std::string szov);
    bool is_selected(int mouse_x, int mouse_y) const;
    void draw() const;
    bool kintvan(int YY) const;

friend class GordMenu;
};


#endif //MENUELEM_HPP_INCLUDED