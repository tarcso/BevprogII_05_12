#ifndef WINDOW_HPP_INCLUDED
#define WINDOW_HPP_INCLUDED

#include "widgets.hpp"
#include <vector>

class Window
{
protected:
    std::vector<Widget*> widgets;
    int screenx, screeny;

public:
    Window();
    void event_loop();
    void registerwidget(Widget* widget) {widgets.push_back(widget);}
    virtual void esemeny(const std::string& ki_mondta) = 0;
    std::pair<int, int> screensize() {return std::make_pair(screenx, screeny);}
    void torolWidget(Widget* w);
};


#endif // OSABLAK_HPP_INCLUDED