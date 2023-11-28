#ifndef DETECTORATOR_CONTROL_PANEL_H
#define DETECTORATOR_CONTROL_PANEL_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <wx/spinctrl.h>
#include "ids_of_controls.hpp"
#include "buffered_bitmap.hpp"
#include "../model/processed_image.hpp"
#include "../controller/i_controller.hpp"
#include "../controller/detectorator_control_panel_controller.hpp"

#define DCPC DetectoratorControlPanelController

class DetectoratorControlPanel : public wxPanel
{
private:
    wxWindow *parent;
    IController *controller;
    void CreateControls();
    void BindEventHandlers();
    void OnRunDetectorator(wxCommandEvent &);
public:
    DetectoratorControlPanel(wxWindow *, IController *);
};

#endif
