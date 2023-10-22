#include "detectorator_control_panel.hpp"

DetectoratorControlPanel::DetectoratorControlPanel(
    wxFrame *parentWindow, wxPanel *parentWinPanel
) : wxPanel(parentWindow)
{
    parentPanel = parentWinPanel;
    
    auto sizer = new wxBoxSizer(wxVERTICAL);

    auto btn1 = new wxButton(this, wxID_ANY, wxT("Hello"));

    sizer->Add(btn1, 0, wxALIGN_CENTER | wxALL, FromDIP(10));

    this->SetSizerAndFit(sizer);
}

DetectoratorControlPanel::~DetectoratorControlPanel() {}

//void DetectoratorControlPanel::OnBtnClick([[maybe_unused]] wxCommandEvent &event)
//{
//    AppMainWindow *parentWin = (AppMainWindow *) parentPanel->GetParent();
//}
