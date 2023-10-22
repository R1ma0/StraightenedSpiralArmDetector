#ifndef DETECTORATOR_CONTROL_PANEL_H
#define DETECTORATOR_CONTROL_PANEL_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include "app_main_window.hpp"

class DetectoratorControlPanel : public wxPanel
{
private:
    wxPanel *parentPanel; 
public:
    DetectoratorControlPanel(wxFrame *, wxPanel *);
    ~DetectoratorControlPanel();
};

#endif
