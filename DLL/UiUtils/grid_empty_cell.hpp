#ifndef GRID_EMPTY_CELL_H
#define GRID_EMPTY_CELL_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "ui_utils.hpp"

void SSAD_UI_UTILS_API AddEmptyCells(wxWindow*, unsigned int, wxGridSizer&, wxSizerFlags&);

#endif