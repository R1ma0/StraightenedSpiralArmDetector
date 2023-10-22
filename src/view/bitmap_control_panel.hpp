#ifndef BITMAP_CONTROL_PANEL_H
#define BITMAP_CONTROL_PANEL_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include "app_main_window.hpp"

class BitmapControlPanel : public wxPanel
{
private:
    wxPanel *parentPanel;
    void CreateControls();
    void BindEventHandlers();
    void OnZoomIn(wxCommandEvent &);
    void OnZoomOut(wxCommandEvent &);
    void OnAngleChangeBtn(wxCommandEvent &);
    void OnAngleChangeSlider(wxCommandEvent &);
public:
    BitmapControlPanel(wxFrame *, wxPanel *);
    ~BitmapControlPanel();
};

#endif
