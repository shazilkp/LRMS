#include "OpeningFrame.h"
#include "MainFrame.h"
#include "ReportsFrame.h"
#include<wx/artprov.h>


OpeningFrame::OpeningFrame(const wxString& title):wxFrame(nullptr, wxID_ANY, title)
{
	createControls();
	bindEventHandlers();
}

void OpeningFrame::createControls() {
	menuBar = new wxMenuBar();
	formMenu = new wxMenu();
	newform = formMenu->Append(wxID_NEW, _("&New Form\tCtrl+N"));
	newform->SetBitmap(wxArtProvider::GetBitmap("wxART_LIST_VIEW"));
	
	
	reports = formMenu->Append(wxID_FILE1, _("&Reports\tCtrl+R"));
	reports->SetBitmap(wxArtProvider::GetBitmap("wxART_REPORT_VIEW"));
	
	exit = formMenu->Append(wxID_EXIT);

	MainFrame* mainFrame = new MainFrame("LRMS");
	mainFrame->SetClientSize(800, 600);
	mainFrame->Center();
	
	mainNote = new wxNotebook(this,wxID_ANY);
	mainNote->AddPage(mainFrame, "page1", true);

	
	

	menuBar->Append(formMenu,_("&File"));
	SetMenuBar(menuBar);
}

void OpeningFrame::bindEventHandlers()
{
	this->Bind(wxEVT_MENU, &OpeningFrame::onFormOpen, this, newform->GetId());

}

void OpeningFrame::onFormOpen(wxCommandEvent& evt)
{
	MainFrame* mainFrame = new MainFrame("LRMS");
	mainFrame->SetClientSize(800, 600);
	mainFrame->Center();
	mainFrame->Show();
}
