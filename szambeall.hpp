#ifndef SZAMBEALL_HPP_INCLUDED
#define SZAMBEALL_HPP_INCLUDED

#include "widgets.hpp"

class Szambeall : public Widget
{
private:
    int m_numb, m_max, m_min;
    bool m_novo, m_csokken, m_nyomott;
    static int m_mx;
    static int m_my;

public:
    Szambeall(Window* window, int x, int y, int sx, int sy, int min, int max);
    void novocsokken(const genv::event& ev);
    void draw() const;
    void handle(const genv::event& ev);
    const int allapot() const;
};


#endif // SZAMBEALL_HPP_INCLUDED