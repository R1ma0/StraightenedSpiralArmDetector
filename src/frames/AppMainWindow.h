#ifndef APP_MAIN_WINDOW_H
#define APP_MAIN_WINDOW_H

#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/filedlg.h>
#include <wx/wfstream.h>

enum 
{
    ID_LOAD_IMG = 1
};

class AppMainWindow : public wxFrame
{
public:
    AppMainWindow();
private:
    void OnExit(wxCommandEvent &event);
    void OnLoadImg(wxCommandEvent &event);
};

#endif