#ifndef AZSM_MULTIPLE_PROCESSING_FRAME_CONTROLLER
#define AZSM_MULTIPLE_PROCESSING_FRAME_CONTROLLER

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <opencv2/opencv.hpp>
#include <wx/filepicker.h>
#include <vector>
#include <filesystem>
#include "i_controller.hpp"
#include "../model/adaptive_zhang_suen_method/adaptive_zhang_suen_types.hpp"
#include "../model/adaptive_zhang_suen_method/adaptive_zhang_suen.hpp"
#include "../model/src_files_handler.hpp"
#include "../model/constants.hpp"
#include "../view/azsm_multiple_processing_frame.hpp"

#ifndef AZSMMPFC
#define AZSMMPFC AZSMMultipleProcessingFrameController
#endif
#ifndef CastAZSMMPF
#define CastAZSMMPF dynamic_cast<AZSMMultipleProcessingFrame*>(view)
#endif

class AZSMMPFC : public IController
{
private:
    wxWindow* view;
    AZSParametersRanges GetRanges();
    std::filesystem::path GetPathToSave(std::string, std::string);
public:
    ~AZSMMPFC();
    void SetView(wxWindow*) override;
    void MakeProcessing();
    void CheckDirExist(wxDirPickerCtrl*);
};

#endif
