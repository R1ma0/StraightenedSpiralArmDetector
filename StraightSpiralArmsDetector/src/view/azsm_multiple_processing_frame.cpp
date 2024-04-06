#include "azsm_multiple_processing_frame.hpp"

AZSMMPF::AZSMMPF(
    IController* controller
) : wxDialog(
    NULL, wxID_ANY, _("Multiple processing: Adaptive Zhang-Suen method")
)
{
    this->controller = controller;

    CreateControls();
    BindEventHandlers();
}

AZSMMPF::~AZSMMPF()
{

}

void AZSMMPF::CreateControls()
{
    auto gridSizer = new wxGridSizer(0, 2, wxSize(1, 1));
    auto& gridSizerFlags = wxSizerFlags().Expand().Border(
        wxALL, 10
    ).CenterVertical();

    auto label = new wxStaticText(this, -1, wxT("Hello world!"));
    gridSizer->Add(label, gridSizerFlags);

    this->SetSizer(gridSizer);
    gridSizer->SetSizeHints(this);
}

void AZSMMPF::BindEventHandlers()
{
}
