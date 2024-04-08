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
    delete controller;
    delete srcFolderLabel;
    delete dstFolderLabel;
    delete srcDirPicker;
    delete dstDirPicker;
    delete startProcessing;
    delete binaryThreshValueLabel;
    delete gaussConstLabel;
    delete imgCompressPercentageLabel;
    delete gaussBlockSizeLabel;
    delete parameterLabel;
    delete parameterMinLabel;
    delete parameterMaxLabel;
    delete parameterStepLabel;
    delete binaryThreshMinSpin;
    delete binaryThreshMaxSpin;
    delete binaryThreshStepSpin;
    delete gaussConstMinSpin;
    delete gaussConstMaxSpin;
    delete gaussConstStepSpin;
    delete imgCompressMinSpin;
    delete imgCompressMaxSpin;
    delete imgCompressStepSpin;
    delete gaussBlockMinSpin;
    delete gaussBlockMaxSpin;
    delete gaussBlockStepSpin;
}

void AZSMMPF::CreateControls()
{
    auto gridSizer = new wxGridSizer(0, 4, wxSize(1, 1));
    auto& gridSizerFlags = wxSizerFlags().Expand().Border(
        wxALL, 10
    ).CenterVertical();

    // Folder pickers

    srcFolderLabel = new wxStaticText(
        this, 
        -1, 
        _("Tate the original images from..."),
        wxDefaultPosition,
        wxDefaultSize,
        wxALIGN_RIGHT
    );
    gridSizer->Add(srcFolderLabel, gridSizerFlags);
    srcDirPicker = new wxDirPickerCtrl(
        this, 
        wxID_ANY,
        DIR_DEFAULT_PATH,
        wxDirSelectorPromptStr,
        wxDefaultPosition,
        wxDefaultSize,
        wxDIRP_DEFAULT_STYLE | wxDIRP_SMALL
    );
    srcDirPicker->SetInitialDirectory(DIR_DEFAULT_PATH);
    gridSizer->Add(srcDirPicker, gridSizerFlags);
    dstFolderLabel = new wxStaticText(
        this, 
        -1, 
        _("Save the processed images to..."),
        wxDefaultPosition,
        wxDefaultSize,
        wxALIGN_RIGHT
    );
    gridSizer->Add(dstFolderLabel, gridSizerFlags);
    dstDirPicker = new wxDirPickerCtrl(
        this, 
        wxID_ANY,
        DIR_DEFAULT_PATH,
        wxDirSelectorPromptStr,
        wxDefaultPosition,
        wxDefaultSize,
        wxDIRP_DEFAULT_STYLE | wxDIRP_SMALL
    );
    dstDirPicker->SetInitialDirectory(DIR_DEFAULT_PATH);
    gridSizer->Add(dstDirPicker, gridSizerFlags);

    // Parameters labels

    parameterLabel = new wxStaticText(
        this, 
        -1, 
        _("Parameter"),
        wxDefaultPosition,
        wxDefaultSize,
        wxALIGN_CENTER
    );
    SetItalicUnderlinedFont(parameterLabel);
    gridSizer->Add(parameterLabel, gridSizerFlags);
    parameterMinLabel = new wxStaticText(
        this, 
        -1, 
        _("Min"),
        wxDefaultPosition,
        wxDefaultSize,
        wxALIGN_CENTER
    );
    SetItalicUnderlinedFont(parameterMinLabel);
    gridSizer->Add(parameterMinLabel, gridSizerFlags);
    parameterMaxLabel = new wxStaticText(
        this, 
        -1, 
        _("Max"),
        wxDefaultPosition,
        wxDefaultSize,
        wxALIGN_CENTER
    );
    SetItalicUnderlinedFont(parameterMaxLabel);
    gridSizer->Add(parameterMaxLabel, gridSizerFlags);
    parameterStepLabel = new wxStaticText(
        this, 
        -1, 
        _("Step"),
        wxDefaultPosition,
        wxDefaultSize,
        wxALIGN_CENTER
    );
    SetItalicUnderlinedFont(parameterStepLabel);
    gridSizer->Add(parameterStepLabel, gridSizerFlags);

    // Binary thresh value

    binaryThreshValueLabel = new wxStaticText(
        this,
        -1,
        _("Binary threshold parameters:"),
        wxDefaultPosition,
        wxDefaultSize,
        wxALIGN_RIGHT
    );
    gridSizer->Add(binaryThreshValueLabel, gridSizerFlags);
    binaryThreshMinSpin = new wxSpinCtrl(this);
    gridSizer->Add(binaryThreshMinSpin, gridSizerFlags);
    binaryThreshMaxSpin = new wxSpinCtrl(this);
    gridSizer->Add(binaryThreshMaxSpin, gridSizerFlags);
    binaryThreshStepSpin = new wxSpinCtrl(this);
    gridSizer->Add(binaryThreshStepSpin, gridSizerFlags);

    // Gauss constant value

    gaussConstLabel = new wxStaticText(
        this,
        -1,
        _("Gaussian constant parameters:"),
        wxDefaultPosition,
        wxDefaultSize,
        wxALIGN_RIGHT
    );
    gridSizer->Add(gaussConstLabel, gridSizerFlags);
    gaussConstMinSpin = new wxSpinCtrl(this);
    gridSizer->Add(gaussConstMinSpin, gridSizerFlags);
    gaussConstMaxSpin = new wxSpinCtrl(this);
    gridSizer->Add(gaussConstMaxSpin, gridSizerFlags);
    gaussConstStepSpin = new wxSpinCtrl(this);
    gridSizer->Add(gaussConstStepSpin, gridSizerFlags);

    // Image compress percentage value

    imgCompressPercentageLabel = new wxStaticText(
        this,
        -1,
        _("Image compress percentage parameters:"),
        wxDefaultPosition,
        wxDefaultSize,
        wxALIGN_RIGHT
    );
    gridSizer->Add(imgCompressPercentageLabel, gridSizerFlags);
    imgCompressMinSpin = new wxSpinCtrl(this);
    gridSizer->Add(imgCompressMinSpin, gridSizerFlags);
    imgCompressMaxSpin = new wxSpinCtrl(this);
    gridSizer->Add(imgCompressMaxSpin, gridSizerFlags);
    imgCompressStepSpin = new wxSpinCtrl(this);
    gridSizer->Add(imgCompressStepSpin, gridSizerFlags);

    // Gauss block size value

    gaussBlockSizeLabel = new wxStaticText(
        this, 
        -1,
        _("Gauss block size parameters:"),
        wxDefaultPosition,
        wxDefaultSize,
        wxALIGN_RIGHT
    );
    gridSizer->Add(gaussBlockSizeLabel, gridSizerFlags);

    gaussBlockMinSpin = new wxSpinCtrl(this);
    gridSizer->Add(gaussBlockMinSpin, gridSizerFlags);
    gaussBlockMaxSpin = new wxSpinCtrl(this);
    gridSizer->Add(gaussBlockMaxSpin, gridSizerFlags);
    gaussBlockStepSpin = new wxSpinCtrl(this);
    gridSizer->Add(gaussBlockStepSpin, gridSizerFlags);

    //

    AddEmptyCells(this, 3, *gridSizer, gridSizerFlags);

    startProcessing = new wxButton(this, ID_START_MP, _("Process"));
    gridSizer->Add(startProcessing, gridSizerFlags);

    this->SetSizer(gridSizer);
    gridSizer->SetSizeHints(this);
}

void AZSMMPF::BindEventHandlers()
{
    Bind(wxEVT_BUTTON, &AZSMMPF::OnStartProcess, this, ID_START_MP);
}

void AZSMMPF::OnStartProcess(wxCommandEvent& WXUNUSED(event))
{

}
