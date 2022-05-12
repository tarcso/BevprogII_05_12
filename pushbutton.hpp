#ifndef PUSHBUTTON_HPP_INCLUDED
#define PUSHBUTTON_HPP_INCLUDED

#include "gordmenu.hpp"
#include <functional>

class PushButton : public Widget
{
    private:
        bool m_pushed;
        std::string m_szov;
        std::function<void()> m_func;
    
    public:
        PushButton(Window* window, int x, int y, int sx, int sy, std::string s, std::function<void()> f);
        void handle(const genv::event& ev);
        void draw() const;
};

#endif // PUSHBUTTON_HPP_INCLUDED