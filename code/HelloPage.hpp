#ifndef HELLOPAGE_HPP_INCLUDED
#define HELLOPAGE_HPP_INCLUDED

#include "Page.hpp"
#include "PageManager.hpp"
#include "AppState.hpp"

class HelloPage : public Page
{
    public:
    HelloPage();
    ~HelloPage();
    void init();
    void handle(const SDL_Event& event);
    void update();
    void draw();
    private:
};


#endif // HELLOPAGE_HPP_INCLUDED