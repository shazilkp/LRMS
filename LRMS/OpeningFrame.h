#pragma once
#include<wx/wx.h>
#include <wx/notebook.h>

class OpeningFrame: public wxFrame
{
public:
	OpeningFrame(const wxString& title);
	
	
private:
	wxMenuBar* menuBar;
	wxMenu* formMenu;
	wxMenuItem* newform;
	wxMenuItem* reports;
	wxMenuItem* exit;
	wxNotebook* mainNote;

	


	void createControls();
	void bindEventHandlers();
	void onFormOpen(wxCommandEvent& evt);
};

