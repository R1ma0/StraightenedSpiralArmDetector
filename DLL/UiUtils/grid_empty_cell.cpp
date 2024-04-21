#include "pch.h"
#include "grid_empty_cell.hpp"

void AddEmptyCells
(
    wxWindow* parent, unsigned int num_cells, wxGridSizer& grid, wxSizerFlags& flags
)
{
    for (unsigned int i = 0; i < num_cells; i++)
    {
        grid.Add(new wxStaticText(parent, -1, ""), flags);
    }
}