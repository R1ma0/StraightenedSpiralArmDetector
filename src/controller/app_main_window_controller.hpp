#ifndef APP_MAIN_WINDOW_CONTROLLER_H
#define APP_MAIN_WINDOW_CONTROLLER_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include "i_controller.hpp"
#include "../view/app_main_window.hpp"
#include <iostream>

class AppMainWindowController : public IController
{
private:
    wxFrame *uncastedView;
public:
    AppMainWindowController();
    void SetView(wxFrame *);
    void Display();
};

#endif
