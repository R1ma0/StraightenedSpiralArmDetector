#include "bitmap_control_panel.hpp"

#ifndef BCPC
#define BCPC BitmapControlPanelController 
#endif
#ifndef CastBCPC
#define CastBCPC dynamic_cast<BCPC *>(controller)
#endif

BitmapControlPanel::BitmapControlPanel
(
    wxWindow *parent,
    IController *controller
) : wxPanel(parent)
{
    this->controller = controller;
    this->parent = parent;

    CreateControls();
    BindEventHandlers();
}

void BitmapControlPanel::CreateControls()
{
    auto hSizer = new wxBoxSizer(wxHORIZONTAL);
    auto zoomInBtn = new wxButton(this, ID_ZOOM_IN, wxT("Zoom +"));
    auto zoomOutBtn = new wxButton(this, ID_ZOOM_OUT, wxT("Zoom -"));
    auto rotateScaleBtn = new wxButton(
        this, ID_ROTATE_SCALE, wxT("Rotate And Scale")
    );

    hSizer->Add(zoomInBtn, 0, wxALIGN_CENTER_VERTICAL);
    hSizer->Add(zoomOutBtn, 0, wxALIGN_CENTER_VERTICAL | wxLEFT, FromDIP(5));
    hSizer->Add(rotateScaleBtn, 0, wxALIGN_CENTER_VERTICAL | wxLEFT, FromDIP(15));

    this->SetSizerAndFit(hSizer);
}

void BitmapControlPanel::BindEventHandlers()
{
    Bind(wxEVT_BUTTON, &BitmapControlPanel::OnZoomIn, this, ID_ZOOM_IN);
    Bind(wxEVT_BUTTON, &BitmapControlPanel::OnZoomOut, this, ID_ZOOM_OUT);
    Bind(
        wxEVT_BUTTON, 
        &BitmapControlPanel::OnRotateScaleBtn, 
        this, 
        ID_ROTATE_SCALE
    );
}

void BitmapControlPanel::OnZoomIn(wxCommandEvent &WXUNUSED(event))
{
    CastBCPC->OnZoomInBitmap();
}

void BitmapControlPanel::OnZoomOut(wxCommandEvent &WXUNUSED(event))
{
    CastBCPC->OnZoomOutBitmap();
}

void BitmapControlPanel::OnRotateScaleBtn(wxCommandEvent &WXUNUSED(event))
{
    CastBCPC->OpenRotateScaleFrame();
}
