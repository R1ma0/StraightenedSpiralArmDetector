#include "detectorator_control_panel.hpp"

DetectoratorControlPanel::DetectoratorControlPanel
(
    wxFrame *parentWindow, 
    BufferedBitmap *bitmap,
    ProcessedImage *procImage
) : wxPanel(parentWindow)
{
    this->bitmap = bitmap;
    this->procImage = procImage;
    
    auto sizer = new wxBoxSizer(wxVERTICAL);

    auto btn1 = new wxButton(this, wxID_ANY, wxT("Hello"));

    sizer->Add(btn1, 0, wxALIGN_CENTER | wxTOP | wxRIGHT | wxBOTTOM, FromDIP(10));

    this->SetSizerAndFit(sizer);
}

//void DetectoratorControlPanel::OnBtnClick([[maybe_unused]] wxCommandEvent &event)
//{
//    AppMainWindow *parentWin = (AppMainWindow *) parentPanel->GetParent();
//}
