#ifndef GRID_EMPTY_CELL_H
#define GRID_EMPTY_CELL_H

#include <wx/window.h>
#include <wx/grid.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include "ui_utils.hpp"

void SSAD_UI_UTILS_API AddEmptyCells(wxWindow*, unsigned int, wxGridSizer&, wxSizerFlags&);

#endif