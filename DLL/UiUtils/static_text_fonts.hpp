#ifndef STATIC_TEXT_FONTS_H
#define STATIC_TEXT_FONTS_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "ui_utils.hpp"

void SSAD_UI_UTILS_API SetBoldFont(wxStaticText*);
void SSAD_UI_UTILS_API SetItalicFont(wxStaticText*);
void SSAD_UI_UTILS_API SetUnderlinedFont(wxStaticText*);
void SSAD_UI_UTILS_API SetItalicUnderlinedFont(wxStaticText*);

#endif