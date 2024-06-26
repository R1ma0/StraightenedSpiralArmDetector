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
    wxDELETE(controller);
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
        _("Take the source images from..."),
        wxDefaultPosition,
        wxDefaultSize,
        wxALIGN_RIGHT
    );
    gridSizer->Add(srcFolderLabel, gridSizerFlags);
    srcDirPicker = new wxDirPickerCtrl(
        this, 
        ID_SRC_DIR_PICKER,
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
        ID_DST_DIR_PICKER,
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
        _("Binary threshold:"),
        wxDefaultPosition,
        wxDefaultSize,
        wxALIGN_RIGHT
    );
    gridSizer->Add(binaryThreshValueLabel, gridSizerFlags);
    binaryThreshMinSpin = new wxSpinCtrl(this, ID_AZSMMP_BTV_MIN_SPIN);
    SetSpinRangeAndValue(binaryThreshMinSpin, 0, 255, 125);
    gridSizer->Add(binaryThreshMinSpin, gridSizerFlags);
    binaryThreshMaxSpin = new wxSpinCtrl(this);
    SetSpinRangeAndValue(binaryThreshMaxSpin, 0, 255, 125);
    gridSizer->Add(binaryThreshMaxSpin, gridSizerFlags);
    binaryThreshStepSpin = new wxSpinCtrl(this);
    SetSpinRangeAndValue(binaryThreshStepSpin, 1, 255, 1);
    gridSizer->Add(binaryThreshStepSpin, gridSizerFlags);

    // Gauss constant value

    gaussConstLabel = new wxStaticText(
        this,
        -1,
        _("Gaussian constant:"),
        wxDefaultPosition,
        wxDefaultSize,
        wxALIGN_RIGHT
    );
    gridSizer->Add(gaussConstLabel, gridSizerFlags);
    gaussConstMinSpin = new wxSpinCtrl(this, ID_AZSMMP_GC_MIN_SPIN);
    SetSpinRangeAndValue(gaussConstMinSpin, -50, 50, 0);
    gridSizer->Add(gaussConstMinSpin, gridSizerFlags);
    gaussConstMaxSpin = new wxSpinCtrl(this);
    SetSpinRangeAndValue(gaussConstMaxSpin, -50, 50, 0);
    gridSizer->Add(gaussConstMaxSpin, gridSizerFlags);
    gaussConstStepSpin = new wxSpinCtrl(this);
    SetSpinRangeAndValue(gaussConstStepSpin, 1, 100, 1);
    gridSizer->Add(gaussConstStepSpin, gridSizerFlags);

    // Image compress percentage value

    imgCompressPercentageLabel = new wxStaticText(
        this,
        -1,
        _("Image compress percentage:"),
        wxDefaultPosition,
        wxDefaultSize,
        wxALIGN_RIGHT
    );
    gridSizer->Add(imgCompressPercentageLabel, gridSizerFlags);
    imgCompressMinSpin = new wxSpinCtrl(this, ID_AZSMMP_ICP_MIN_SPIN);
    SetSpinRangeAndValue(imgCompressMinSpin, 1, 99, 20);
    gridSizer->Add(imgCompressMinSpin, gridSizerFlags);
    imgCompressMaxSpin = new wxSpinCtrl(this);
    SetSpinRangeAndValue(imgCompressMaxSpin, 1, 99, 20);
    gridSizer->Add(imgCompressMaxSpin, gridSizerFlags);
    imgCompressStepSpin = new wxSpinCtrl(this);
    SetSpinRangeAndValue(imgCompressStepSpin, 1, 99, 1);
    gridSizer->Add(imgCompressStepSpin, gridSizerFlags);

    // Gauss block size value

    gaussBlockSizeLabel = new wxStaticText(
        this, 
        -1,
        _("Gauss block size:"),
        wxDefaultPosition,
        wxDefaultSize,
        wxALIGN_RIGHT
    );
    gridSizer->Add(gaussBlockSizeLabel, gridSizerFlags);

    gaussBlockMinSpin = new wxSpinCtrl(this, ID_AZSMMP_GBS_MIN_SPIN);
    SetSpinRangeAndValue(gaussBlockMinSpin, 3, 1001, 3);
    gridSizer->Add(gaussBlockMinSpin, gridSizerFlags);
    gaussBlockMaxSpin = new wxSpinCtrl(this, ID_AZSMMP_GBS_MAX_SPIN);
    SetSpinRangeAndValue(gaussBlockMaxSpin, 3, 1001, 3);
    gridSizer->Add(gaussBlockMaxSpin, gridSizerFlags);
    gaussBlockStepSpin = new wxSpinCtrl(this, ID_AZSMMP_GBS_STEP_SPIN);
    SetSpinRangeAndValue(gaussBlockStepSpin, 2, 1001, 2);
    gridSizer->Add(gaussBlockStepSpin, gridSizerFlags);

    //

    procImgsBar = new wxGauge(this, wxID_ANY, 1);
    procImgsBar->SetValue(0);
    procImgsBar->Hide();
    gridSizer->Add(procImgsBar, gridSizerFlags);

    multiProcImgsLabel = new wxStaticText(
        this,
        -1,
        multProcLabelPP
    );
    SetBoldFont(multiProcImgsLabel);
    multiProcImgsLabel->Hide();
    gridSizer->Add(multiProcImgsLabel, gridSizerFlags);

    stopProcessing = new wxButton(this, ID_STOP_MP, _("Stop"));
    stopProcessing->Hide();
    gridSizer->Add(stopProcessing, gridSizerFlags);

    startProcessing = new wxButton(this, ID_START_MP, _("Process"));
    startProcessing->Enable(false);
    gridSizer->Add(startProcessing, gridSizerFlags);

    this->SetSizer(gridSizer);
    gridSizer->SetSizeHints(this);
}

void AZSMMPF::BindEventHandlers()
{
    Bind(wxEVT_BUTTON, &AZSMMPF::OnStartProcess, this, ID_START_MP);
    Bind(wxEVT_BUTTON, &AZSMMPF::OnStopProcess, this, ID_STOP_MP);
    Bind(
        wxEVT_SPINCTRL, 
        &AZSMMPF::OnSetGaussBlockSizeMin, 
        this, 
        ID_AZSMMP_GBS_MIN_SPIN
    );
    Bind(
        wxEVT_SPINCTRL, 
        &AZSMMPF::OnSetGaussBlockSizeMax, 
        this, 
        ID_AZSMMP_GBS_MAX_SPIN
    );
    Bind(
        wxEVT_SPINCTRL, 
        &AZSMMPF::OnSetGaussBlockSizeStep,
        this, 
        ID_AZSMMP_GBS_STEP_SPIN
    );
    Bind(
        wxEVT_SPINCTRL, 
        &AZSMMPF::OnSetBinaryThreshMinSpin, 
        this, 
        ID_AZSMMP_BTV_MIN_SPIN
    );
    Bind(
        wxEVT_SPINCTRL, 
        &AZSMMPF::OnSetGaussConstMinSpin,
        this, 
        ID_AZSMMP_GC_MIN_SPIN
    );
    Bind(
        wxEVT_SPINCTRL, 
        &AZSMMPF::OnSetImgCompressPercentageMinSpin, 
        this, 
        ID_AZSMMP_ICP_MIN_SPIN
    );
    Bind(
        wxEVT_DIRPICKER_CHANGED, 
        &AZSMMPF::OnDirPickerChanged, 
        this, 
        ID_SRC_DIR_PICKER
    );
    Bind(
        wxEVT_DIRPICKER_CHANGED,
        &AZSMMPF::OnDirPickerChanged,
        this,
        ID_DST_DIR_PICKER
    );
}

void AZSMMPF::OnDirPickerChanged(wxCommandEvent& WXUNUSED(event))
{
    bool isSrcDirValid = wxDirExists(srcDirPicker->GetPath());;
    bool isDstDirValid = wxDirExists(dstDirPicker->GetPath());;
    bool btnState = (isSrcDirValid && isDstDirValid) ? true : false;

    SetStartProcessingBtnEnable(btnState);
}

void AZSMMPF::OnSetBinaryThreshMinSpin(wxCommandEvent& WXUNUSED(event))
{
    binaryThreshMaxSpin->SetRange(binaryThreshMinSpin->GetValue(), 255);
}

void AZSMMPF::OnSetGaussConstMinSpin(wxCommandEvent& WXUNUSED(event))
{
    gaussConstMaxSpin->SetRange(gaussConstMinSpin->GetValue(), 50);
}

void AZSMMPF::OnSetImgCompressPercentageMinSpin(wxCommandEvent& WXUNUSED(event))
{
    imgCompressMaxSpin->SetRange(imgCompressMinSpin->GetValue(), 99);
}

void AZSMMPF::OnSetGaussBlockSizeMin(wxCommandEvent& WXUNUSED(event))
{
    gaussBlockMinSpin->SetValue(
        CheckOddValue(gaussBlockMinSpin->GetValue(), &gbsMinOldValue)
    );

    gaussBlockMaxSpin->SetRange(gaussBlockMinSpin->GetValue(), 1001);
}
    
void AZSMMPF::OnSetGaussBlockSizeMax(wxCommandEvent& WXUNUSED(event))
{
    gaussBlockMaxSpin->SetValue(
        CheckOddValue(gaussBlockMaxSpin->GetValue(), &gbsMaxOldValue)
    );
}

void AZSMMPF::OnSetGaussBlockSizeStep(wxCommandEvent& WXUNUSED(event))
{
    gaussBlockStepSpin->SetValue(
        CheckEvenValue(gaussBlockStepSpin->GetValue(), &gbsStepOldValue)
    );
}

void AZSMMPF::OnStartProcess(wxCommandEvent& WXUNUSED(event))
{
    wxString folder = srcDirPicker->GetPath();
    folder.erase(std::remove_if(folder.begin(), folder.end(), isspace), folder.end());
    bool isFolderHasFiles = CastAZSMMPFC->IsFolderHasFiles(
        folder,
        cts::IN_FILE_FORMATS
    );

    if (isFolderHasFiles)
    {
        CastAZSMMPFC->MakeProcessing();
    }
    else
    {
        wxString formats = CastAZSMMPFC->GetFileFormatsStr();

        wxMessageBox(
            folder + _(" folder does not contain ") + formats + _(" files."),
            _("File search error")
        );
    }
}

void AZSMMPF::OnStopProcess(wxCommandEvent& WXUNUSED(event))
{
    CastAZSMMPFC->StopProcessing();
}

void AZSMMPF::SetSpinRangeAndValue(wxSpinCtrl* spin, int min, int max, int value)
{
    spin->SetRange(min, max);
    spin->SetValue(value);
}

void AZSMMPF::SetStartProcessingBtnEnable(bool state)
{
    startProcessing->Enable(state);
}

void AZSMMPF::SetEnableComponents(bool state)
{
    startProcessing->Enable(state);
    srcFolderLabel->Enable(state);
    dstFolderLabel->Enable(state);
    srcDirPicker->Enable(state);
    dstDirPicker->Enable(state);
    binaryThreshValueLabel->Enable(state);
    gaussConstLabel->Enable(state);
    imgCompressPercentageLabel->Enable(state);
    gaussBlockSizeLabel->Enable(state);
    parameterLabel->Enable(state);
    parameterMinLabel->Enable(state);
    parameterMaxLabel->Enable(state);
    parameterStepLabel->Enable(state);
    binaryThreshMinSpin->Enable(state);
    binaryThreshMaxSpin->Enable(state);
    binaryThreshStepSpin->Enable(state);
    gaussConstMinSpin->Enable(state);
    gaussConstMaxSpin->Enable(state);
    gaussConstStepSpin->Enable(state);
    imgCompressMinSpin->Enable(state);
    imgCompressMaxSpin->Enable(state);
    imgCompressStepSpin->Enable(state);
    gaussBlockMinSpin->Enable(state);
    gaussBlockMaxSpin->Enable(state);
    gaussBlockStepSpin->Enable(state);
}

void AZSMMPF::SetHideProcessingInfoComponents(bool state)
{
    if (state)
    {
        multiProcImgsLabel->Hide();
        procImgsBar->Hide();
        stopProcessing->Hide();
    }
    else
    {
        multiProcImgsLabel->Show();
        procImgsBar->Show();
        stopProcessing->Show();
    }
}

void AZSMMPF::SetProcessingBarRange(int range)
{
    procImgsBar->SetRange(range);
}

void AZSMMPF::UpdateProcessingBarComponents(int barValue, int totalValue)
{
    procImgsBar->SetValue(barValue);

    wxString ready = std::to_string(barValue);
    wxString total = std::to_string(totalValue);

    SetMultiProcImgsLabel(multiProcImgsLabel, ready, total, multProcLabelRT);
}

void AZSMMPF::ResetProcessingBarComponents()
{
    procImgsBar->SetValue(0);
    procImgsBar->SetRange(1);
    SetMultiProcImgsLabel(multiProcImgsLabel);
}

void AZSMMPF::SetMultiProcImgsLabel(
    wxStaticText* st,
    wxString ready,
    wxString total,
    wxString label
)
{
    if (label == wxEmptyString)
    {
        st->SetLabelText(multProcLabelPP);
    }
    else
    {
        st->SetLabelText(label + " : " + ready + "/" + total);
    }
}

void AZSMMPF::SetProcessingBarPulse()
{
    procImgsBar->Pulse();
}