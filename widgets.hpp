#ifndef WIDGETS_HPP_INCLUDED
#define WIDGETS_HPP_INCLUDED

#include "graphics.hpp"

class Window;

class Widget
{
protected:
    int m_x, m_y, m_size_x, m_size_y;
    std::pair<int, int> m_screensize;

public:
    Widget(Window* window, int x, int y, int sx, int sy);
    virtual bool is_selected(int mx, int my) const;
    virtual void handle(const genv::event& ev) = 0;
    virtual void draw() const = 0;
};

void haromszog(int x, int y, int felalap, int magassag, int elojel);

#endif // WIDGETS_HPP_INCLUDED