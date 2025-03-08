#include "App.h"
#include "MainFrame.h"
#include "OpeningFrame.h"

wxIMPLEMENT_APP(App);
bool App::OnInit()
{

    /*
    OpeningFrame* openingFrame = new OpeningFrame("OpenPage");
    openingFrame->SetClientSize(800,600);
    openingFrame->Center();
    openingFrame->Show();

    */

    MainFrame* mainFrame = new MainFrame("LRMS");
    mainFrame->SetClientSize(wxSize(800,600));
    mainFrame->SetWindowStyle(wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER));
    mainFrame->Center();
    mainFrame->Show();



    return true;
}
