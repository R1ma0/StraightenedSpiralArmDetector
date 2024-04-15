#ifndef AZSM_MULTIPLE_PROCESSING_FRAME_CONTROLLER
#define AZSM_MULTIPLE_PROCESSING_FRAME_CONTROLLER

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <opencv2/opencv.hpp>
#include <vector>
#include <thread>
#include <mutex>
#include "i_controller.hpp"
#include "../model/adaptive_zhang_suen_method/adaptive_zhang_suen_types.hpp"
#include "../model/adaptive_zhang_suen_method/adaptive_zhang_suen.hpp"
#include "../model/src_files_handler.hpp"
#include "../model/constants.hpp"
#include "../model/thread_pool.hpp"
#include "../model/azs_mp_task.hpp"
#include "../view/azsm_multiple_processing_frame.hpp"
#include "../view/utils/proc_activity_indicator.hpp"

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
    wxActivityIndicator* activityIndicator;
    SrcFilesData* srcFiles;
    AZSTasks* thPoolTasks;
    std::thread* computeThread;
    std::mutex multiProcMtx;
    std::atomic<int> readyImgs;
    std::atomic<int> totalImgsCount;
    AZSParametersRanges GetRanges();
    void Compute(wxString, AZSParametersRanges, wxActivityIndicator*);
    void EnableDialogComponents(bool);
public:
    ~AZSMMPFC();
    void SetView(wxWindow*) override;
    void MakeProcessing();
    bool IsFolderHasFiles(wxString, std::vector<wxString>);
    wxString GetFileFormatsStr();
};

#endif
