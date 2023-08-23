#ifndef APP_MAIN_WINDOW_H
#define APP_MAIN_WINDOW_H

#include <wx/frame.h>
#include <wx/menu.h>

class AppMainWindow : public wxFrame
{
public:
    AppMainWindow();
private:
    void OnExit(wxCommandEvent &event);
};

#endif