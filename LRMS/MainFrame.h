#pragma once
#include<wx/wx.h>
#include<wx/spinctrl.h>
#include <wx/calctrl.h>
#include <wx/datectrl.h>
#include <wx/timectrl.h>
#include"data.h"
#include<cstdlib>
#include <wx/notebook.h>
#include<wx/listctrl.h>

#define noOfSpin 6

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);
private:

	///////////////////////////////////////reports/////////////////////////////////////////////
	void onReportSearchClick(wxCommandEvent& evt);
	std::string generateReport(std::string fileName);
	void displayreport(int noOfColumn, std::string fileName);

	void populateList(int noOfColumn,std::vector < std::vector <std::string>> csvFileAsVector);

	wxPanel* landingpanel;
	wxPanel* reportpanelcenter;
	wxPanel* reportpanel;
	wxSpinCtrl* reportMonth;
	wxSpinCtrl* ReportYear;
	wxButton* reportClear;
	wxButton* search;

	////////////////////////////////////end-reports////////////////////////////////////////////

	wxPanel* displayReportsPanel;
	wxListView* listView;

	wxMenuBar* menuBar;
	wxMenu* formMenu;
	wxMenuItem* newform;
	wxMenuItem* reports;
	wxMenuItem* exit;

	wxNotebook* mainNotebook;
	wxBoxSizer* mainSizer;
	
	bool ageEmpty = true;
	bool graviEmpty = true;
	bool paraEmpty = true;
	bool childAliveEmpty = true;
	bool gestWEmpty = true;
	bool gestDEmpty = true;

	
	
	bool ifPageExist(wxWindow* page);
	size_t getPageIdFromPage(wxWindow* page);
	void createControls();
	void createFormControls();
	void createMenuControls();
	void createReportsControls();
	void bindEventHandlers();

	bool anyFieldEmpty();
	bool anySpinEmpty();
	bool anyTextEmpty();

	void onNewMenuClick(wxCommandEvent& evt);
	void onFormMenuClick(wxCommandEvent& evt);

	void onSubmitButtonClicked(wxCommandEvent& evt);
	void onClearButtonClicked(wxCommandEvent& evt);
	void onReportsButtonClicked(wxCommandEvent& evt);
	void onCheckBoxTick(wxCommandEvent& evt);
	void onReportClearButtonClicked(wxCommandEvent& evt);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void onGraviSpinChange(wxSpinEvent& evt);
	void onGraviSpinTextChange(wxCommandEvent& evt);
	void onAgeSpinChange(wxSpinEvent& evt);
	void onAgeSpinTextChange(wxCommandEvent& evt);
	void onParaSpinChange(wxSpinEvent& evt);
	void onParaSpinTextChange(wxCommandEvent& evt);
	void onChildSpinChange(wxSpinEvent& evt);
	void onChildSpinTextChange(wxCommandEvent& evt);
	void onGestWSpinChange(wxSpinEvent& evt);
	void onGestWSpinTextChange(wxCommandEvent& evt);
	void onGestDSpinChange(wxSpinEvent& evt);
	void onGestDSpinTextChange(wxCommandEvent& evt);

	struct data createDataFromInput();

	wxArrayString bloodChoice;
	wxArrayString modeofDelichoice;
	wxArrayString babySex;
	wxArrayString babyAlive;
	wxArrayString caseTypeChoice;
	wxArrayString comorbiditiesChoice;
	wxArrayString mesoChoice;

	wxPanel* formPanel;
	wxStaticText* heading;
	wxTextCtrl* nameField;
	wxSpinCtrl* ageField;
	wxTextCtrl* IPnoField;
	wxTextCtrl* OPnoField;
	wxSpinCtrl* graviField;
	wxSpinCtrl* paraField;
	wxSpinCtrl* aliveChildField;
	wxSpinCtrl* gestAgeWeekField;
	wxSpinCtrl* gestAgeDayField;
	wxTextCtrl* HbField;
	wxComboBox* bloodGrpField;
	wxChoice* caseTypeField;
	wxComboBox* modeDelivField;
	wxRadioBox* babySexField;
	wxRadioBox* babyAliveField;
	wxTextCtrl* babyWghtField;
	wxTextCtrl* apgarField;					//verify data type!!!
	wxDatePickerCtrl* dateDeliField;
	wxTimePickerCtrl* timeDeliField;
	wxTextCtrl* doctorField;
	wxTextCtrl* remarksField;
	wxButton* submitButton;
	wxButton* clearAllButton;
	wxButton* reportsButton;
	
	wxCheckBox* inducedField;

	wxCheckBox* foley;
	wxRadioBox* meso;
	wxCheckBox* pitocin;
	std::vector<wxCheckBox*> comorbCheckBoxes;
};

