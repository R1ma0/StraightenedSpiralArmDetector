#include "options_frame_controller.hpp"

OptionsFrameController::OptionsFrameController(Configurator* configurator)
{
	this->configurator = configurator;
}

void OptionsFrameController::SetView(wxWindow* view)
{
	this->view = view;
}

wxArrayString OptionsFrameController::GetLanguagesList()
{
	wxArrayString langs;
	
	for (const auto& [code, value] : cts::LANGUAGES)
	{
		langs.Add(code);
	}

	return langs;
}

int OptionsFrameController::GetWinWidth() const
{
	return 0;// configurator->GetWindowSize().GetWidth();
}

int OptionsFrameController::GetWinHeight() const
{
	return 0;// configurator->GetWindowSize().GetHeight();
}