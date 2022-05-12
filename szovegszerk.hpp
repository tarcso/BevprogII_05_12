#ifndef SZOVEGSZERK_HPP_INCLUDED
#define SZOVEGSZERK_HPP_INCLUDED

#include "graphics.hpp"
#include "widgets.hpp"

class SzovegSzerk : public Widget
{
protected:
    std::string szov;
    bool selected = false;
    bool nagy = false;
    bool cursor = false;
    int ido = 0;

public:
    SzovegSzerk(Window* window, int x, int y, int sx, int sy);
    void draw() const;
    void handle(const genv::event& ev);
    std::string allapot() const;
};


#endif // SZOVEGSZERK_HPP_INCLUDED
