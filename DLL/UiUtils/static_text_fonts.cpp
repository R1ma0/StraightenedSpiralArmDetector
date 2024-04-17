#include "pch.h"
#include "static_text_fonts.hpp"

void SetBoldFont(wxStaticText* text)
{
    wxFont font = text->GetFont();
    font.SetWeight(wxFONTWEIGHT_BOLD);
    text->SetFont(font);
}

void SetItalicFont(wxStaticText* text)
{
    wxFont font = text->GetFont();
    font = font.Italic();
    text->SetFont(font);
}

void SetUnderlinedFont(wxStaticText* text)
{
    wxFont font = text->GetFont();
    font = font.Underlined();
    text->SetFont(font);
}

void SetItalicUnderlinedFont(wxStaticText* text)
{
    SetItalicFont(text);
    SetUnderlinedFont(text);
}