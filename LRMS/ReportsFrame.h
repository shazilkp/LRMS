#pragma once
#include"MainFrame.h"
#include<wx/wx.h>
#include<wx/spinctrl.h>
#include"data.h"

class ReportsFrame:public wxFrame
{
public:
	ReportsFrame(const wxString& title);
private:
	void createControls();
	void bindEventHandlers();

	void generateReport(wxCommandEvent& evt);

	wxPanel* reportpanelcenter;
	wxSpinCtrl* month;
	wxSpinCtrl* reportYear;
	wxButton* cancel;
	wxButton* search;

	
};

