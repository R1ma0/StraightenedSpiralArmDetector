#include "options_frame.hpp"

OptionsFrame::OptionsFrame(
	IController*
) : wxDialog (
	NULL, wxID_ANY, _("Options")
)
{
	this->controller = controller;

	CreateControls();
}

void OptionsFrame::CreateControls()
{
	auto gridSizer = new wxGridSizer(1, 1, wxSize(1, 1));
	auto& gridSizerFlags = wxSizerFlags().Expand();

	propertyGrid = new wxPropertyGrid(
		this,
		wxID_ANY,
		wxDefaultPosition,
		wxDefaultSize,
		wxPG_SPLITTER_AUTO_CENTER | wxPG_BOLD_MODIFIED
	);

	AppendOptions();

	gridSizer->Add(propertyGrid, gridSizerFlags);
	this->SetSizer(gridSizer);
	gridSizer->SetSizeHints(this);
}

void OptionsFrame::AppendOptions()
{
	propertyGrid->Append(new wxPropertyCategory(_("Localisation")));
	propertyGrid->Append(new wxEnumProperty(
		_("Language"), wxPG_LABEL, CastOFC->GetLanguagesList()
	));

	propertyGrid->Append(new wxPropertyCategory(_("Window")));
	propertyGrid->Append(new wxIntProperty(
		_("Width"), wxPG_LABEL, CastOFC->GetWinWidth()
	));
	propertyGrid->Append(new wxIntProperty(
		_("Height"), wxPG_LABEL, CastOFC->GetWinHeight()
	));
}