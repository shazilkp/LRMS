#include "MainFrame.h"
#include "OpeningFrame.h"
#include"ReportsFrame.h"
#include<wx/wx.h>
#include <wx/datectrl.h>
#include<filesystem>
#include <wx/timectrl.h>
#include<wx/gbsizer.h>
#include<vector>
#include<string>
#include <wx/notebook.h>
#include<map>
#include<fstream>
#include<wx/artprov.h>

#include"data.h"
#include"wx/image.h"


MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr,wxID_ANY,title)
{
	createControls();
	bindEventHandlers();
}


bool MainFrame::ifPageExist(wxWindow* page)
{
	int count = mainNotebook->GetPageCount();
	for (int i = 0; i < count; i++) {
		if (mainNotebook->GetPage(i) == page) {
			return true;
		}
	}
	return false;
}

size_t MainFrame::getPageIdFromPage(wxWindow* page)
{
	size_t i;
	for (i = 0; i < mainNotebook->GetPageCount(); i++) {
		if (mainNotebook->GetPage(i) == page) {
			return i;
		}
	}
	return 0;
}

void MainFrame::createControls()
{
	wxFont headingFont(wxFontInfo(wxSize(0, 40)).Bold());
	wxFont mainFont(wxFontInfo(FromDIP(wxSize(0, 22))).Weight(100));
	const auto margin = FromDIP(10);

	wxPNGHandler* handler = new wxPNGHandler();
	wxImage::AddHandler(handler);

	mainNotebook = new wxNotebook(this, wxID_ANY);
	reportpanel = new wxPanel(mainNotebook);
	formPanel = new wxPanel(mainNotebook);
	formPanel->SetFont(mainFont);
	formPanel->SetBackgroundColour(wxColour(RGB(250, 250, 253)));


	//mainNotebook->AddPage(formPanel, "Form", true);
	//mainNotebook->AddPage(reportpanel, "Reports");

	landingpanel = new wxPanel(this);
	landingpanel->SetBackgroundColour(wxColour(RGB(250, 250, 253)));
	wxStaticBitmap* image;
	image = new wxStaticBitmap(landingpanel, wxID_ANY, wxBitmap("C:/LRMS/bgImage.png", wxBITMAP_TYPE_PNG));

	auto landingpanelsizer = new wxBoxSizer(wxVERTICAL);
	landingpanelsizer->Add(image, 1, wxCENTER);
	landingpanel->SetSizer(landingpanelsizer);

	mainSizer = new wxBoxSizer(wxVERTICAL);

	createMenuControls();
	createFormControls();
	formPanel->Hide();

	createReportsControls();
	reportpanel->Hide();

	mainSizer->Add(landingpanel, 1, wxEXPAND | wxALL);
	mainSizer->Add(mainNotebook, 1, wxEXPAND | wxALL);

	mainNotebook->Hide();
	this->SetSizerAndFit(mainSizer);
}


void MainFrame::createFormControls()
{
	wxFont headingFont(wxFontInfo(wxSize(0, 40)).Bold());
	wxFont mainFont(wxFontInfo(FromDIP(wxSize(0, 22))).Weight(100));
	const auto margin = FromDIP(10);

	auto sizer = new wxGridBagSizer(margin, margin);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	std::vector<wxPanel*> panelvector;
	std::vector<std::pair<wxGBPosition, wxGBSpan>> items_sizer = {
		{{0,0}, {1,5}},
		{{1,1}, {1,1}},
		{{2,1}, {1,1}},
		{{3,0}, {1,5}},
		{{1,3} ,{1,1}},
		{{2,3} ,{1,1}},
		{{1,0} ,{1,1}},
		{{1,2} ,{1,1}},
		{{1,4} ,{1,1}},
		{{2,0} ,{1,1}},
		{{2,2} ,{1,1}},
		{{2,4} ,{1,1}},

	};
	int i = 0;
	for (auto& item : items_sizer) {
		auto panel_i = new wxPanel(formPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize);
		panelvector.push_back(panel_i);
		//panelvector[i]->SetBackgroundColour(wxColor(100, 51 * (i + 1), 120));
		if (i == 0 || i == 3) {
			sizer->Add(panelvector[i], item.first, item.second, wxEXPAND | wxALIGN_CENTER);
		}
		else {
			sizer->Add(panelvector[i], item.first, item.second, wxEXPAND);
		}
		panelvector[i]->SetFont(mainFont);
		i++;
	}




	//sizer->AddGrowableRow(0);
	sizer->AddGrowableRow(1);
	sizer->AddGrowableRow(2);
	//sizer->AddGrowableRow(3,1);

	//panelvector[0]->SetMinSize(FromDIP(wxSize(-1, 40)));
//	panelvector[3]->SetMinSize(FromDIP(wxSize(-1, 40)));

	sizer->AddGrowableCol(0, 2);
	sizer->AddGrowableCol(1, 3);
	sizer->AddGrowableCol(2, 2);
	sizer->AddGrowableCol(3, 3);
	sizer->AddGrowableCol(4, 2);
	//sizer->SetMinSize(FromDIP(wxSize(600, 400)));

	auto headSizer = new wxBoxSizer(wxVERTICAL);

	heading = new wxStaticText(panelvector[0], wxID_ANY, "LRMS");
	heading->SetFont(headingFont);
	//	heading->SetForegroundColour(wxColor(18, 52, 86));
	headSizer->Add(heading, 1, wxALIGN_CENTER);
	panelvector[0]->SetSizer(headSizer);


	auto panel1sizer = new wxGridBagSizer(margin, margin);
	std::vector<std::pair<wxGBPosition, wxGBSpan>> panel1_items = {
		{ { 0, 0 }, { 1,3 } },
		{ {1,0}, {1,1} },
		{ {1,1}, {1,1} },
		{ {1,2} ,{1,1} },
		{ {2,0}, {1,1} },
		{ {2,1} ,{1,2} }		//space
	};

	bloodChoice.Add("A+ve");
	bloodChoice.Add("A-ve");
	bloodChoice.Add("B+ve");
	bloodChoice.Add("B-ve");
	bloodChoice.Add("O+ve");
	bloodChoice.Add("O-ve");
	bloodChoice.Add("AB+ve");
	bloodChoice.Add("AB-ve");

	auto namelabel = new wxStaticText(panelvector[1], wxID_ANY, "Name");
	nameField = new wxTextCtrl(panelvector[1], wxID_ANY);
	nameField->SetBackgroundColour(*wxWHITE);

	auto agelabel = new wxStaticText(panelvector[1], wxID_ANY, "Age");
	ageField = new wxSpinCtrl(panelvector[1], wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, 20);
	ageField->SetBackgroundColour(*wxWHITE);

	auto iplabel = new wxStaticText(panelvector[1], wxID_ANY, "IPno");
	IPnoField = new wxTextCtrl(panelvector[1], wxID_ANY);
	IPnoField->SetBackgroundColour(*wxWHITE);

	auto oplabel = new wxStaticText(panelvector[1], wxID_ANY, "OPno");
	OPnoField = new wxTextCtrl(panelvector[1], wxID_ANY);
	OPnoField->SetBackgroundColour(*wxWHITE);

	auto hblabel = new wxStaticText(panelvector[1], wxID_ANY, "Hb");
	HbField = new wxTextCtrl(panelvector[1], wxID_ANY);
	HbField->SetBackgroundColour(*wxWHITE);

	auto bloodlabel = new wxStaticText(panelvector[1], wxID_ANY, "BloodGrp");
	bloodGrpField = new wxComboBox(panelvector[1], wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, bloodChoice);
	bloodGrpField->SetBackgroundColour(*wxWHITE);


	auto namesizer = new wxBoxSizer(wxVERTICAL);
	namesizer->Add(namelabel);
	namesizer->Add(nameField, 1, wxEXPAND | wxALL);				//wxEXPAND|wxALL

	auto ipsizer = new wxBoxSizer(wxVERTICAL);
	ipsizer->Add(iplabel);
	ipsizer->Add(IPnoField, 1, wxEXPAND | wxALL);

	auto opsizer = new wxBoxSizer(wxVERTICAL);
	opsizer->Add(oplabel);
	opsizer->Add(OPnoField, 1, wxEXPAND | wxALL);

	auto agesizer = new wxBoxSizer(wxVERTICAL);
	agesizer->Add(agelabel);
	agesizer->Add(ageField, 1, wxEXPAND | wxALL);

	auto bloodsizer = new wxBoxSizer(wxVERTICAL);
	bloodsizer->Add(bloodlabel);
	bloodsizer->Add(bloodGrpField, 1, wxEXPAND | wxALL);

	auto hbsizer = new wxBoxSizer(wxVERTICAL);
	hbsizer->Add(hblabel);
	hbsizer->Add(HbField, 1, wxEXPAND | wxALL);

	panel1sizer->Add(namesizer, panel1_items[0].first, panel1_items[0].second, wxEXPAND | wxBOTTOM, margin);
	panel1sizer->Add(ipsizer, panel1_items[1].first, panel1_items[1].second, wxEXPAND);
	panel1sizer->Add(opsizer, panel1_items[2].first, panel1_items[2].second, wxEXPAND);
	panel1sizer->Add(agesizer, panel1_items[3].first, panel1_items[3].second, wxEXPAND);
	panel1sizer->Add(hbsizer, panel1_items[4].first, panel1_items[4].second, wxEXPAND);
	panel1sizer->Add(bloodsizer, panel1_items[5].first, panel1_items[5].second, wxEXPAND);

	panelvector[1]->SetSizer(panel1sizer);

	//panel1sizer->AddGrowableRow(0);
	//panelsizer->AddGrowableRow(1);
	//panelsizer->AddGrowableRow(2);

	panel1sizer->AddGrowableCol(0);
	panel1sizer->AddGrowableCol(1);
	panel1sizer->AddGrowableCol(2);


	auto panel2sizer = new wxGridBagSizer(margin, margin);
	std::vector<std::pair<wxGBPosition, wxGBSpan>> panel2_items = {
		{ { 0, 0 }, { 1,1 } },
		{ {0,1}, {1,1} },
		{ {0,2}, {1,1} },
		{ {1,0}, {1,2} },
		{ {1,2}, {1,1} },
		{ {2,0}, {1,2} },
		{ {3,0} ,{1,2} },
		{{2,2} ,{2,1}}
	};


	auto gravilabel = new wxStaticText(panelvector[2], wxID_ANY, "Gravi");
	graviField = new wxSpinCtrl(panelvector[2], wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 12, 0);

	auto paralabel = new wxStaticText(panelvector[2], wxID_ANY, "Para");
	paraField = new wxSpinCtrl(panelvector[2], wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 12, 0);

	auto aliveChildlabel = new wxStaticText(panelvector[2], wxID_ANY, "Children Alive");
	aliveChildField = new wxSpinCtrl(panelvector[2], wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 12, 0);

	caseTypeChoice.Add("Reffered");
	caseTypeChoice.Add("Booking");

	auto gestWlabel = new wxStaticText(panelvector[2], wxID_ANY, "Gestational Week");
	gestAgeWeekField = new wxSpinCtrl(panelvector[2], wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 42, 38);

	auto gestDlabel = new wxStaticText(panelvector[2], wxID_ANY, "Day");
	gestAgeDayField = new wxSpinCtrl(panelvector[2], wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 6, 0);

	auto caseTypelabel = new wxStaticText(panelvector[2], wxID_ANY, "Case Type");
	caseTypeField = new wxChoice(panelvector[2], wxID_ANY, wxDefaultPosition, wxDefaultSize, caseTypeChoice);



	modeofDelichoice.Add("Vaginal delivery");
	modeofDelichoice.Add("Assisted vaginal delivery");
	modeofDelichoice.Add("Csection");
	modeofDelichoice.Add("VBAC");

	auto modeDelilabel = new wxStaticText(panelvector[2], wxID_ANY, "Mode of delivery");
	modeDelivField = new wxComboBox(panelvector[2], wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, modeofDelichoice);


	mesoChoice.Add("NIL");
	mesoChoice.Add("Meso 1");
	mesoChoice.Add("Meso 2");
	mesoChoice.Add("Meso 3");
	mesoChoice.Add("Meso 3+");

	inducedField = new wxCheckBox(panelvector[2], wxID_ANY, "Induced");
	//inductionMethod = new wxComboBox(panelvector[2], wxID_ANY, "induction method", wxDefaultPosition, wxDefaultSize, inductionChoice);
	foley = new wxCheckBox(panelvector[2], wxID_ANY, "Foley");
	meso = new wxRadioBox(panelvector[2], wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, mesoChoice, 1);
	pitocin = new wxCheckBox(panelvector[2], wxID_ANY, "Pitocin");

	//	inductionMethod->Show(true);
	//	inductionMethod->Show(false);

	auto gravisizer = new wxBoxSizer(wxVERTICAL);
	gravisizer->Add(gravilabel);
	gravisizer->Add(graviField, 1, wxEXPAND | wxALL);

	auto parasizer = new wxBoxSizer(wxVERTICAL);
	parasizer->Add(paralabel);
	parasizer->Add(paraField, 1, wxEXPAND | wxALL);

	auto aliveChildsizer = new wxBoxSizer(wxVERTICAL);
	aliveChildsizer->Add(aliveChildlabel);
	aliveChildsizer->Add(aliveChildField, 1, wxEXPAND | wxALL);

	auto gestWsizer = new wxBoxSizer(wxVERTICAL);
	gestWsizer->Add(gestWlabel);
	gestWsizer->Add(gestAgeWeekField, 1, wxEXPAND | wxALL);

	auto gestDsizer = new wxBoxSizer(wxVERTICAL);
	gestDsizer->Add(gestDlabel);
	gestDsizer->Add(gestAgeDayField, 1, wxEXPAND | wxALL);

	auto modeofDelisizer = new wxBoxSizer(wxVERTICAL);
	modeofDelisizer->Add(modeDelilabel);
	modeofDelisizer->Add(modeDelivField, 1, wxEXPAND | wxALL);

	auto caseTypesizer = new wxBoxSizer(wxVERTICAL);
	caseTypesizer->Add(caseTypelabel);
	caseTypesizer->Add(caseTypeField, 1, wxEXPAND | wxALL);

	auto inductionMethodsizer = new wxBoxSizer(wxHORIZONTAL);
	inductionMethodsizer->Add(foley, 0, wxALIGN_CENTER | wxALL);
	inductionMethodsizer->Add(meso, 0, wxALL);
	inductionMethodsizer->Add(pitocin, 0, wxALIGN_CENTER);

	auto inducedsizer = new wxBoxSizer(wxVERTICAL);
	inducedsizer->Add(inducedField, 1, wxEXPAND | wxALL);
	inducedsizer->Add(inductionMethodsizer, 0, wxALL);

	/*auto case_inducedsizer = new wxBoxSizer(wxHORIZONTAL);
	case_inducedsizer->Add(caseTypesizer, 1, wxEXPAND | wxALL, margin);
	case_inducedsizer->Add(inducedsizer, 1, wxEXPAND | wxALL, margin);*/

	panel2sizer->Add(gravisizer, panel2_items[0].first, panel2_items[0].second, wxEXPAND);
	panel2sizer->Add(parasizer, panel2_items[1].first, panel2_items[1].second, wxEXPAND);
	panel2sizer->Add(aliveChildsizer, panel2_items[2].first, panel2_items[2].second, wxEXPAND);
	panel2sizer->Add(gestWsizer, panel2_items[3].first, panel2_items[3].second, wxEXPAND);
	panel2sizer->Add(gestDsizer, panel2_items[4].first, panel2_items[4].second, wxEXPAND);
	panel2sizer->Add(modeofDelisizer, panel2_items[5].first, panel2_items[5].second, wxEXPAND);
	panel2sizer->Add(caseTypesizer, panel2_items[6].first, panel2_items[6].second, wxVERTICAL);
	panel2sizer->Add(inducedsizer, panel2_items[7].first, panel2_items[7].second, wxEXPAND);

	panelvector[2]->SetSizer(panel2sizer);

	panel2sizer->AddGrowableCol(0);
	panel2sizer->AddGrowableCol(1);
	panel2sizer->AddGrowableCol(2);


	auto panel4sizer = new wxGridBagSizer(margin, margin);
	std::vector<std::pair<wxGBPosition, wxGBSpan>> panel4_items = {
		{ {0,0}, {1,1} },
		{ {0,1}, {1,1} },
		{ {1,0}, {1,1} },
		{ {1,1}, {1,1} },
		{ {2,0}, {1,2} }		//space
	};


	babySex.Add("Male");
	babySex.Add("Female");

	babyAlive.Add("Alive");
	babyAlive.Add("Dead");

	babySexField = new wxRadioBox(panelvector[4], wxID_ANY, "baby sex", wxDefaultPosition, wxDefaultSize, babySex, 0);

	babyAliveField = new wxRadioBox(panelvector[4], wxID_ANY, "baby", wxDefaultPosition, wxDefaultSize, babyAlive, 0);

	auto babyWghtlabel = new wxStaticText(panelvector[4], wxID_ANY, "Baby Weight(KG)");
	babyWghtField = new wxTextCtrl(panelvector[4], wxID_ANY);

	auto apgarlabel = new wxStaticText(panelvector[4], wxID_ANY, "APGAR");
	apgarField = new wxTextCtrl(panelvector[4], wxID_ANY);

	auto dateTimeDelilabel = new wxStaticText(panelvector[4], wxID_ANY, "Delivery date-time");
	dateDeliField = new wxDatePickerCtrl(panelvector[4], wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DROPDOWN);
	timeDeliField = new wxTimePickerCtrl(panelvector[4], wxID_ANY, wxDefaultDateTime);


	auto babyWghtsizer = new wxBoxSizer(wxVERTICAL);
	babyWghtsizer->Add(babyWghtlabel);
	babyWghtsizer->Add(babyWghtField, 1, wxEXPAND | wxALL);

	auto apgarsizer = new wxBoxSizer(wxVERTICAL);
	apgarsizer->Add(apgarlabel);
	apgarsizer->Add(apgarField, 1, wxEXPAND | wxALL);

	auto datetimeDelisizer = new wxBoxSizer(wxHORIZONTAL);
	datetimeDelisizer->Add(dateDeliField, 1, wxEXPAND | wxALL);
	datetimeDelisizer->Add(timeDeliField, 1, wxEXPAND | wxALL);

	auto delisizer = new wxBoxSizer(wxVERTICAL);
	delisizer->Add(dateTimeDelilabel);
	delisizer->Add(datetimeDelisizer, 1, wxEXPAND | wxALL);

	panel4sizer->Add(babySexField, panel4_items[0].first, panel4_items[0].second, wxEXPAND);
	panel4sizer->Add(babyAliveField, panel4_items[1].first, panel4_items[1].second, wxEXPAND);
	panel4sizer->Add(babyWghtsizer, panel4_items[2].first, panel4_items[2].second, wxEXPAND);
	panel4sizer->Add(apgarsizer, panel4_items[3].first, panel4_items[3].second, wxEXPAND);
	panel4sizer->Add(delisizer, panel4_items[4].first, panel4_items[4].second, wxEXPAND);

	panelvector[4]->SetSizer(panel4sizer);

	panel4sizer->AddGrowableCol(0);
	panel4sizer->AddGrowableCol(1);

	auto panel5sizer = new wxGridBagSizer(margin * 2, margin * 2);
	std::vector<std::pair<wxGBPosition, wxGBSpan>> panel5_items = {
		{ {0,0}, {1,3} },
		{ {1,0}, {2,2} },
		{ {1,2}, {1,1} }		//space
	};

	comorbiditiesChoice.Add("GDM A1");
	comorbiditiesChoice.Add("GDM A2");
	comorbiditiesChoice.Add("HELLP");
	comorbiditiesChoice.Add("Pre-eclampsia");
	comorbiditiesChoice.Add("Severe pre-eclampsia");
	comorbiditiesChoice.Add("Eclampsia");
	comorbiditiesChoice.Add("Anemia-mild");
	comorbiditiesChoice.Add("Anemia-moderate");
	comorbiditiesChoice.Add("Anemia-severe");



	auto comorblabel = new wxStaticText(panelvector[5], wxID_ANY, "Co-Morbidities");
	//comorbiditiesField = new wxComboBox(panelvector[5], wxID_ANY, "Co-Morbidities", wxDefaultPosition, wxDefaultSize, comorbiditiesChoice);
	auto comorbCheckSizer = new wxBoxSizer(wxVERTICAL);
	for (auto& comorb : comorbiditiesChoice) {
		auto check = new wxCheckBox(panelvector[5], wxID_ANY, comorb);
		comorbCheckSizer->Add(check);
		comorbCheckBoxes.push_back(check);
	}

	auto drnamelabel = new wxStaticText(panelvector[5], wxID_ANY, "Dr Name");
	doctorField = new wxTextCtrl(panelvector[5], wxID_ANY, "Dr");

	auto remarkslabel = new wxStaticText(panelvector[5], wxID_ANY, "Remarks");
	remarksField = new wxTextCtrl(panelvector[5], wxID_ANY, "remarks", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);


	auto comorbsizer = new wxBoxSizer(wxVERTICAL);
	comorbsizer->Add(comorblabel);
	comorbsizer->Add(comorbCheckSizer, 1, wxEXPAND | wxALL);

	auto drnamesizer = new wxBoxSizer(wxVERTICAL);
	drnamesizer->Add(drnamelabel);
	drnamesizer->Add(doctorField, 1, wxEXPAND | wxALL);

	auto remarkssizer = new wxBoxSizer(wxVERTICAL);
	remarkssizer->Add(remarkslabel);
	remarkssizer->Add(remarksField, 1, wxEXPAND | wxALL);


	panel5sizer->Add(drnamesizer, panel5_items[0].first, panel5_items[0].second, wxEXPAND);
	panel5sizer->Add(remarkssizer, panel5_items[1].first, panel5_items[1].second, wxEXPAND);
	panel5sizer->Add(comorbsizer, panel5_items[2].first, panel5_items[2].second, wxEXPAND);

	panelvector[5]->SetSizer(panel5sizer);

	panel5sizer->AddGrowableCol(0);
	panel5sizer->AddGrowableCol(1);
	panel5sizer->AddGrowableCol(2);

	submitButton = new wxButton(panelvector[3], wxID_ANY, "Submit");
	clearAllButton = new wxButton(panelvector[3], wxID_ANY, "Clear");

	auto buttonsizer = new wxBoxSizer(wxHORIZONTAL);
	buttonsizer->Add(submitButton, 0, wxRIGHT | wxBOTTOM, margin);
	buttonsizer->Add(clearAllButton, 0, wxLEFT | wxBOTTOM, margin);

	panelvector[3]->SetSizer(buttonsizer);


	foley->Enable(false);
	meso->Enable(false);
	pitocin->Enable(false);

	formPanel->SetSizer(sizer);
}


void MainFrame::createMenuControls()
{
	menuBar = new wxMenuBar();
	formMenu = new wxMenu();
	newform = formMenu->Append(wxID_NEW, _("&New Form\tCtrl+N"));
	newform->SetBitmap(wxArtProvider::GetBitmap("wxART_LIST_VIEW"));


	reports = formMenu->Append(wxID_FILE1, _("&Reports\tCtrl+R"));
	reports->SetBitmap(wxArtProvider::GetBitmap("wxART_REPORT_VIEW"));
	formMenu->AppendSeparator();
	exit = formMenu->Append(wxID_EXIT);

	menuBar->Append(formMenu, _("&File"));
	SetMenuBar(menuBar);
}

void MainFrame::createReportsControls()
{
	wxFont headingFont(wxFontInfo(wxSize(0, 40)).Bold());
	wxFont mainFont(wxFontInfo(FromDIP(wxSize(0, 22))).Weight(100));
	const auto margin = FromDIP(10);

	reportpanelcenter = new wxPanel(reportpanel);
	///////////////////////////////////////////////////////////
	displayReportsPanel = new wxPanel(reportpanel);
	listView = new wxListView(displayReportsPanel);
	listView->AppendColumn("Category");
	listView->AppendColumn("Number");

	auto listsizer = new wxBoxSizer(wxVERTICAL);
	listsizer->Add(listView, 1, wxALL | wxEXPAND);
	displayReportsPanel->SetSizerAndFit(listsizer);
	
	reportpanelcenter->SetBackgroundColour(wxColour(RGB(254, 254, 255)));
	reportpanel->SetBackgroundColour(wxColour(RGB(254, 254, 255)));

	//const auto margin = FromDIP(10);
	auto mlabel = new wxStaticText(reportpanelcenter, wxID_ANY, "Month");
	auto ylabel = new wxStaticText(reportpanelcenter, wxID_ANY, "Year");

	mlabel->SetFont(headingFont);
	ylabel->SetFont(headingFont);

	reportMonth = new wxSpinCtrl(reportpanelcenter, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 12, 1);
	ReportYear = new wxSpinCtrl(reportpanelcenter, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 2012, 2050, 2024);
	search = new wxButton(reportpanelcenter, wxID_ANY, "Search");
	reportClear = new wxButton(reportpanelcenter, wxID_ANY, "Clear");

	//auto mainsizer = new wxGridSizer(wxVERTICAL);
	auto reportsizer = new wxGridSizer(3, 2, margin, margin);
	reportsizer->Add(mlabel, 0, wxALIGN_BOTTOM | wxALIGN_CENTER_HORIZONTAL);
	reportsizer->Add(ylabel, 0, wxALIGN_BOTTOM | wxALIGN_CENTER_HORIZONTAL);
	reportsizer->Add(reportMonth, 0, wxALIGN_TOP | wxALIGN_CENTER_HORIZONTAL);
	reportsizer->Add(ReportYear, 0, wxALIGN_TOP | wxALIGN_CENTER_HORIZONTAL);
	reportsizer->Add(search, 0, wxALIGN_TOP | wxALIGN_CENTER_HORIZONTAL);
	reportsizer->Add(reportClear, 0, wxALIGN_TOP | wxALIGN_CENTER_HORIZONTAL);

	reportpanelcenter->SetSizer(reportsizer);
	
	auto reportPageSizer = new wxBoxSizer(wxHORIZONTAL);
	reportPageSizer->Add(reportpanelcenter, 0, wxALL, margin);
	reportPageSizer->Add(displayReportsPanel, 1, wxEXPAND | wxALL, margin);

	reportpanel->SetSizer(reportPageSizer);
}

void MainFrame::bindEventHandlers()
{
	submitButton->Bind(wxEVT_BUTTON, &MainFrame::onSubmitButtonClicked, this);
	clearAllButton->Bind(wxEVT_BUTTON, &MainFrame::onClearButtonClicked, this);
	formMenu->Bind(wxEVT_MENU, &MainFrame::onFormMenuClick, this);
	inducedField->Bind(wxEVT_CHECKBOX, &MainFrame::onCheckBoxTick, this);

	////////////////////////////////////////////////////////////////////////////
	graviField->Bind(wxEVT_SPINCTRL, &MainFrame::onGraviSpinChange, this);
	ageField->Bind(wxEVT_SPINCTRL, &MainFrame::onAgeSpinChange, this);
	paraField->Bind(wxEVT_SPINCTRL, &MainFrame::onParaSpinChange, this);
	aliveChildField->Bind(wxEVT_SPINCTRL, &MainFrame::onChildSpinChange, this);
	gestAgeWeekField->Bind(wxEVT_SPINCTRL, &MainFrame::onGestWSpinChange, this);
	gestAgeDayField->Bind(wxEVT_SPINCTRL, &MainFrame::onGestDSpinChange, this);

	graviField->Bind(wxEVT_TEXT, &MainFrame::onGraviSpinTextChange, this);
	ageField->Bind(wxEVT_TEXT, &MainFrame::onAgeSpinTextChange, this);
	paraField->Bind(wxEVT_TEXT, &MainFrame::onParaSpinTextChange, this);
	aliveChildField->Bind(wxEVT_TEXT, &MainFrame::onChildSpinTextChange, this);
	gestAgeWeekField->Bind(wxEVT_TEXT, &MainFrame::onGestWSpinTextChange, this);
	gestAgeDayField->Bind(wxEVT_TEXT, &MainFrame::onGestDSpinTextChange, this);
	////////////////////////////////////////////////////////////////////////////

	///////////////////////////reports////////////////////////////////////////////
	search->Bind(wxEVT_BUTTON, &MainFrame::onReportSearchClick, this);
	reportClear->Bind(wxEVT_BUTTON, &MainFrame::onReportClearButtonClicked, this);
}

void MainFrame::onClearButtonClicked(wxCommandEvent& evt)
{
	wxMessageDialog dialog(this, "Are you sure you want to clear all inputs?", "Clear", wxYES_NO | wxCANCEL);
	int result = dialog.ShowModal();

	if (result == wxID_YES) {
		nameField->Clear();
		IPnoField->Clear();
		OPnoField->Clear();
		HbField->Clear();
		apgarField->Clear();
		babyWghtField->Clear();
		doctorField->Clear();
		remarksField->Clear();
		ageField->SetValue(0);
		graviField->SetValue(0);
		paraField->SetValue(0);
		aliveChildField->SetValue(0);
		gestAgeWeekField->SetValue(0);
		gestAgeDayField->SetValue(0);
		bloodGrpField->SetSelection(wxNOT_FOUND);
		modeDelivField->SetSelection(wxNOT_FOUND);
		caseTypeField->SetSelection(wxNOT_FOUND);

		inducedField->SetValue(false);
		foley->SetValue(false);
		foley->Enable(false);
		meso->SetSelection(0);
		meso->Enable(false);
		pitocin->SetValue(false);
		pitocin->Enable(false);

		for (auto check : comorbCheckBoxes) {
			check->SetValue(false);
		}
	}
}

void MainFrame::onReportSearchClick(wxCommandEvent& evt)
{
	auto year_i = ReportYear->GetValue();
	auto month_i = reportMonth->GetValue();

	std::string fileName = "C:\\LRMS\\database\\" + std::to_string(year_i) + "\\" + std::to_string(month_i) + ".csv";
	if (!std::filesystem::exists(fileName)) {
		wxMessageBox("File doesnt Exist!!!", "caption", wxOK, this);
		evt.Skip();
		return;
	}

	std::string outputfile;
	outputfile = generateReport(fileName);

	int noOfColumnInReport = 2;
	displayreport(noOfColumnInReport,outputfile);
}

std::string MainFrame::generateReport(std::string fileName)
{
	auto year_i = ReportYear->GetValue();
	auto month_i = reportMonth->GetValue();

	std::vector<data> dataVector = readfromMonthFile(fileName);



	int totalDeliv = dataVector.size();

	std::vector < std::tuple<std::string, int>> valueTuple;
	int bookedCase = 0, refferedCase = 0, cSec = 0, VBAC = 0, aVag = 0, nVag = 0, FTND = 0, PTVD = 0, gest_37_39 = 0, gest_34_36 = 0, gest_32_33 = 0, gest_28_31 = 0;
	int l18 = 0, age_18_29 = 0, age_30_34 = 0, age_35_40 = 0, g40 = 0, primi = 0, multi = 0, rhneg = 0, rhpos = 0, totPreterm = 0, gestg40 = 0, gestl28 = 0;
	int birthwght[8] = { 0,0,0,0,0,0,0,0 }, babyMale = 0, babyFemale = 0, inducedVag = 0, inducedCsec = 0, foley = 0;
	int induction[19] = { 0 };

	std::map<std::string, int> vMap;
	std::vector<std::string> outputDataValues;

	vMap["bookedCase"] = 0;
	vMap["refferedCase"] = 0;
	vMap["cSec"] = 0;
	vMap["VBAC"] = 0;
	vMap["aVAg"] = 0;
	vMap["nVag"] = 0;
	vMap["FTND"] = 0;
	vMap["PTVD"] = 0;
	vMap["gest_37_39"] = 0;
	vMap["gest_34_36"] = 0;
	vMap["gest_32_33"] = 0;
	vMap["gest_28_31"] = 0;
	vMap["l18"] = 0;
	vMap["age_18_29"] = 0;
	vMap["age_30_34"] = 0;
	vMap["age_35_40"] = 0;
	vMap["g40"] = 0;
	vMap["primi"] = 0;
	vMap["multi"] = 0;
	vMap["rhneg"] = 0;
	vMap["rhpos"] = 0;
	vMap["totPreterm"] = 0;
	vMap["gestg40"] = 0;
	vMap["gestl28"] = 0;
	vMap["babyMale"] = 0;
	vMap["babyFemale"] = 0;
	vMap["inducedVag"] = 0;
	vMap["inducedCsec"] = 0;
	vMap["foley"] = 0;
	vMap["total_delivery"] = totalDeliv;

	outputDataValues.push_back("total_delivery");
	outputDataValues.push_back("bookedCase");
	outputDataValues.push_back("refferedCase");
	outputDataValues.push_back("cSec");
	outputDataValues.push_back("VBAC");
	outputDataValues.push_back("aVAg");
	outputDataValues.push_back("nVag");
	outputDataValues.push_back("FTND");
	outputDataValues.push_back("PTVD");
	outputDataValues.push_back("gestg40");
	outputDataValues.push_back("gest_37_39");
	outputDataValues.push_back("gest_34_36");
	outputDataValues.push_back("gest_32_33");
	outputDataValues.push_back("gest_28_31");
	outputDataValues.push_back("gestl28");
	outputDataValues.push_back("l18");
	outputDataValues.push_back("age_18_29");
	outputDataValues.push_back("age_30_34");
	outputDataValues.push_back("age_35_40");
	outputDataValues.push_back("g40");
	outputDataValues.push_back("primi");
	outputDataValues.push_back("multi");
	outputDataValues.push_back("rhneg");
	outputDataValues.push_back("rhpos");
	outputDataValues.push_back("totPreterm");
	outputDataValues.push_back("babyMale");
	outputDataValues.push_back("babyFemale");
	outputDataValues.push_back("inducedVag");
	outputDataValues.push_back("inducedCsec");
	outputDataValues.push_back("foley");

	std::vector<std::string> comorbChoice;

	comorbChoice.push_back("GDM A1");
	comorbChoice.push_back("GDM A2");
	comorbChoice.push_back("HELLP");
	comorbChoice.push_back("Pre-eclampsia");
	comorbChoice.push_back("Severe pre-eclampsia");
	comorbChoice.push_back("Eclampsia");
	comorbChoice.push_back("Anemia-mild");
	comorbChoice.push_back("Anemia-moderate");
	comorbChoice.push_back("Anemia-severe");

	std::vector<std::pair<std::string, int>> comorbidsCount;

	for (auto& i : comorbChoice) {
		comorbidsCount.push_back(std::make_pair(i, 0));
		outputDataValues.push_back(i);
	}

	//0foley
	//1       + 1meso
	//2       + 2meso
	//3       + 3meso
	//4       + 3+meso
	//5       +       + p
	//6foley + 1meso
	//7foley + 2meso
	//8foley + 3meso
	//9foley + 3+meso
	//10foley + 1meso + p
	//11foley + 2meso + p
	//12foley + 3meso + p
	//13foley + 3+meso + p
	//14foley +        + p
	//15foley
	//16     + 1meso  + p
	//17     + 2meso  + p
	//18     + 3meso  + p
	//19     + 3+meso + p




	for (const auto& d : dataVector) {
		switch (d.caseType) {
		case 'R': {
			refferedCase++;
			break;
		}
		case 'B': {
			bookedCase++;
			break;
		}
		}

		if (d.modeOfDelivery == "VBAC") {
			VBAC++;
		}
		if (d.modeOfDelivery == "Csection") {
			cSec++;
		}
		if (d.modeOfDelivery == "Assisted vaginal delivery") {
			aVag++;
		}
		if (d.modeOfDelivery == "Vaginal delivery") {
			nVag++;
		}

		if ((d.modeOfDelivery == "Vaginal delivery") || (d.modeOfDelivery == "Assisted vaginal delivery") || (d.modeOfDelivery == "VBAC")) {
			if (d.gestationalAge.week >= 36) {
				FTND++;
			}
			else {
				PTVD++;
			}
		}

		if (d.age < 18) {
			l18++;
		}
		else if (d.age <= 29) {
			age_18_29++;
		}
		else if (d.age <= 34) {
			age_30_34++;
		}
		else if (d.age <= 40) {
			age_35_40++;
		}
		else {
			g40++;
		}


		if (d.para == 0) {
			primi++;
		}
		else {
			multi++;
		}


		if ((d.bloodGrp == "A-ve") || (d.bloodGrp == "B-ve") || (d.bloodGrp == "AB-ve") || (d.bloodGrp == "O-ve")) {
			rhneg++;
		}


		if (d.gestationalAge.week < 28) {
			gestl28++;
		}
		else if (d.gestationalAge.week < 32) {
			gest_28_31++;
		}
		else if (d.gestationalAge.week < 34) {
			gest_32_33++;
		}
		else if (d.gestationalAge.week < 37) {
			gest_34_36++;
		}
		else if (d.gestationalAge.week < 40) {
			gest_37_39++;
		}
		else {
			gestg40++;
		}


		if (d.babyDetail.weight > 0.5 && d.babyDetail.weight <= 1) {
			birthwght[0]++;
		}
		if (d.babyDetail.weight > 1 && d.babyDetail.weight <= 1.5) {
			birthwght[1]++;
		}
		if (d.babyDetail.weight > 1.5 && d.babyDetail.weight <= 2) {
			birthwght[2]++;
		}
		if (d.babyDetail.weight > 2 && d.babyDetail.weight <= 2.5) {
			birthwght[3]++;
		}
		if (d.babyDetail.weight > 2.5 && d.babyDetail.weight <= 3) {
			birthwght[4]++;
		}
		if (d.babyDetail.weight > 3 && d.babyDetail.weight <= 3.5) {
			birthwght[5]++;
		}
		if (d.babyDetail.weight > 3.5 && d.babyDetail.weight <= 4) {
			birthwght[6]++;
		}
		if (d.babyDetail.weight > 4) {
			birthwght[7]++;
		}

		if (d.babyDetail.sex == 'M') {
			babyMale++;
		}
		if (d.babyDetail.sex == 'F') {
			babyFemale++;
		}

		if (((d.modeOfDelivery == "Vaginal delivery") || (d.modeOfDelivery == "Assisted vaginal delivery") || (d.modeOfDelivery == "VBAC")) && d.induced == true) {
			inducedVag++;
		}

		if (d.modeOfDelivery == "Csection" && d.induced == true) {
			inducedCsec++;
		}



		//0foley
		//1       + 1meso
		//2       + 2meso
		//3       + 3meso
		//4       + 3+meso
		//5       +       + p
		//6foley + 1meso
		//7foley + 2meso
		//8foley + 3meso
		//9foley + 3+meso
		//10foley + 1meso + p
		//11foley + 2meso + p
		//12foley + 3meso + p
		//13foley + 3+meso + p
		//14foley +        + p
		//15     + 1meso  + p
		//16     + 2meso  + p
		//17     + 3meso  + p
		//18     + 3+meso + p

		if (d.induced) {
			switch (d.meso) {
			case 0: {
				d.foley ? (d.pitocin ? induction[14]++ : induction[0]++) : (d.pitocin ? induction[5]++ : false);
				break;
			}
			case 1: {
				d.foley ? (d.pitocin ? induction[10]++ : induction[6]++) : (d.pitocin ? induction[15]++ : induction[1]++);
				break;
			}
			case 2: {
				d.foley ? (d.pitocin ? induction[11]++ : induction[7]++) : (d.pitocin ? induction[16]++ : induction[2]++);
				break;
			}
			case 3: {
				d.foley ? (d.pitocin ? induction[12]++ : induction[8]++) : (d.pitocin ? induction[17]++ : induction[3]++);
				break;
			}
			case 4: {
				d.foley ? (d.pitocin ? induction[13]++ : induction[9]++) : (d.pitocin ? induction[18]++ : induction[4]++);
				break;
			}
			}
		}

		for (int i = 0; i < d.comorbidities.size(); i++) {
			if (d.comorbidities[i]) {
				comorbidsCount[i].second++;
			}
		}


	}

	vMap["bookedCase"] = bookedCase;
	vMap["refferedCase"] = refferedCase;
	vMap["cSec"] = cSec;
	vMap["VBAC"] = VBAC;
	vMap["aVAg"] = aVag;
	vMap["nVag"] = nVag;
	vMap["FTND"] = FTND;
	vMap["PTVD"] = PTVD;
	vMap["gest_37_39"] = gest_37_39;
	vMap["gest_34_36"] = gest_34_36;
	vMap["gest_32_33"] = gest_32_33;
	vMap["gest_28_31"] = gest_28_31;
	vMap["l18"] = l18;
	vMap["age_18_29"] = age_18_29;
	vMap["age_30_34"] = age_30_34;
	vMap["age_35_40"] = age_35_40;
	vMap["g40"] = g40;
	vMap["primi"] = primi;
	vMap["multi"] = multi;
	vMap["rhneg"] = rhneg;
	vMap["rhpos"] = rhpos;
	vMap["totPreterm"] = totPreterm;
	vMap["gestg40"] = gestg40;
	vMap["gestl28"] = gestl28;
	vMap["babyMale"] = babyMale;
	vMap["babyFemale"] = babyFemale;
	vMap["inducedVag"] = inducedVag;
	vMap["inducedCsec"] = inducedCsec;
	vMap["foley"] = foley;
	for (auto const& comorb : comorbidsCount) {
		vMap.insert(comorb);
	}

	std::string title = "babywght";
	float j = 0, k = 0.5, m = 1.0;
	for (auto const& wght : birthwght) {
		if (j == 3.5) {
			break;
		}
		vMap[title + std::to_string(k + j) + "-" + std::to_string(m + j)] = wght;
		outputDataValues.push_back(title + std::to_string(k + j) + "-" + std::to_string(m + j));
		j = j + 0.5;
	}
	vMap["babywght4+"] = birthwght[7];
	outputDataValues.push_back("babywght4+");

	//0foley
		//1       + 1meso
		//2       + 2meso
		//3       + 3meso
		//4       + 3+meso
		//5       +       + p
		//6foley + 1meso
		//7foley + 2meso
		//8foley + 3meso
		//9foley + 3+meso
		//10foley + 1meso + p
		//11foley + 2meso + p
		//12foley + 3meso + p
		//13foley + 3+meso + p
		//14foley +        + p
		//15     + 1meso  + p
		//16     + 2meso  + p
		//17     + 3meso  + p
		//18     + 3+meso + p

	vMap["foley_only"] = induction[0];
	vMap["1meso_only"] = induction[1];
	vMap["2meso_only"] = induction[2];
	vMap["3meso_only"] = induction[3];
	vMap["3+meso_only"] = induction[4];
	vMap["piocin_only"] = induction[5];
	vMap["foley-1meso"] = induction[6];
	vMap["foley-2meso"] = induction[7];
	vMap["foley-3meso"] = induction[8];
	vMap["foley-3+meso"] = induction[9];
	vMap["foley-1meso-pito"] = induction[10];
	vMap["foley-2meso-pito"] = induction[11];
	vMap["foley-3meso-pito"] = induction[12];
	vMap["foley-3+meso-pito"] = induction[13];
	vMap["foley-pito"] = induction[14];
	vMap["1meso-pito"] = induction[15];
	vMap["2meso-pito"] = induction[16];
	vMap["3meso-pito"] = induction[17];
	vMap["3+meso-pito"] = induction[18];

	outputDataValues.push_back("foley_only");
	outputDataValues.push_back("1meso_only");
	outputDataValues.push_back("2meso_only");
	outputDataValues.push_back("3meso_only");
	outputDataValues.push_back("3+meso_only");
	outputDataValues.push_back("piocin_only");
	outputDataValues.push_back("foley-1meso");
	outputDataValues.push_back("foley-2meso");
	outputDataValues.push_back("foley-3meso");
	outputDataValues.push_back("foley-3+meso");
	outputDataValues.push_back("foley-1meso-pito");
	outputDataValues.push_back("foley-2meso-pito");
	outputDataValues.push_back("foley-3meso-pito");
	outputDataValues.push_back("foley-3+meso-pito");
	outputDataValues.push_back("foley-pito");
	outputDataValues.push_back("1meso-pito");
	outputDataValues.push_back("2meso-pito");
	outputDataValues.push_back("3meso-pito");
	outputDataValues.push_back("3+meso-pito");


	std::string reportsYearFolder = "C:\\LRMS\\reports\\" + std::to_string(year_i) + "\\";
	std::filesystem::create_directories(reportsYearFolder);
	std::ofstream fileStream;
	std::string outputFile = reportsYearFolder + std::to_string(month_i) + ".csv";
	fileStream.open(outputFile);


	for (auto const& items : outputDataValues) {
		fileStream << items << "," << vMap.at(items) << "\n";
	}

	return outputFile;

}

void MainFrame::populateList(int noOfColumn,std::vector < std::vector <std::string>> csvFileAsVector)
{	
	int i = 0;
	for (auto& line : csvFileAsVector) {
		listView->InsertItem(i, line[0]);
		for (int j = 1; j < noOfColumn; j++) {
			listView->SetItem(i, j, line[j]);
		}
	}
	for (int j = 0; j < noOfColumn; j++) {
		listView->SetColumnWidth(j, wxLIST_AUTOSIZE);
	}
}

void MainFrame::displayreport(int noOfColumn,std::string fileName)
{
	displayReportsPanel->Show();
	std::ifstream fileStream;							//unable to open file /file deleted
	fileStream.open(fileName);

	std::string line;
	std::vector <std::string> tokens;
	std::vector < std::vector <std::string>> csvFileAsVector;

	while (std::getline(fileStream, line)) {
		tokens = tokeniser(line);
		csvFileAsVector.push_back(tokens);
	}

	populateList(noOfColumn, csvFileAsVector);	
}

void MainFrame::onReportsButtonClicked(wxCommandEvent& evt)
{
	ReportsFrame* secondFrame = new ReportsFrame("Reports");
	secondFrame->SetWindowStyle(wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX));
	secondFrame->Center();
	secondFrame->Show(true);
	//secondFrame->SetBackgroundColour(wxColor(RGB(227, 252, 247)));
	//this->Show(false);
}

void MainFrame::onCheckBoxTick(wxCommandEvent& evt)
{
	foley->Enable(inducedField->GetValue());
	meso->Enable(inducedField->GetValue());
	pitocin->Enable(inducedField->GetValue());
}

void MainFrame::onReportClearButtonClicked(wxCommandEvent& evt)
{
	listView->DeleteAllItems();
}

bool MainFrame::anyFieldEmpty()
{

	return (anyTextEmpty());
}

bool MainFrame::anyTextEmpty()
{
	bool textEmpty = (babyWghtField->GetValue().IsEmpty() || apgarField->GetValue().IsEmpty() || doctorField->GetValue().IsEmpty() || remarksField->GetValue().IsEmpty());
	textEmpty = (textEmpty || IPnoField->GetValue().IsEmpty() || OPnoField->GetValue().IsEmpty() || nameField->GetValue().IsEmpty() || HbField->GetValue().IsEmpty());
	textEmpty = (textEmpty || modeDelivField->GetValue().IsEmpty() || bloodGrpField->GetValue().IsEmpty());

	return textEmpty;
}

void MainFrame::onNewMenuClick(wxCommandEvent& evt)
{
	int initialPageCount = mainNotebook->GetPageCount();
	
	if (evt.GetId() == wxID_NEW)  { 
		if (!ifPageExist(formPanel)) {
			formPanel->Show();
			mainNotebook->AddPage(formPanel, "Form", true);
		}
		mainNotebook->SetSelection(getPageIdFromPage(formPanel));
	 }

	if (evt.GetId() == wxID_FILE1){
		if (!ifPageExist(reportpanel)) {
			reportpanel->Show();
			mainNotebook->AddPage(reportpanel, "Reports");
		}
		mainNotebook->SetSelection(getPageIdFromPage(reportpanel));
	}

	if (initialPageCount == 0) {
		mainNotebook->Show();
		landingpanel->Hide();
		this->GetSizer()->Layout();
	}
}

void MainFrame::onFormMenuClick(wxCommandEvent& evt)
{
	int eventID = evt.GetId();
	if (eventID == wxID_NEW || eventID == wxID_FILE1) {
		onNewMenuClick(evt);
	}

	if (eventID == wxID_EXIT) {
		this->Close();
	}
}

void MainFrame::onSubmitButtonClicked(wxCommandEvent& evt)
{ 
	if (anyFieldEmpty()) {
		wxMessageBox("CANT BE EMPTY");
		evt.Skip();
	}
	else {
		wxMessageDialog dialog(this, "Confirm Submission!!", "submit", wxYES_NO);
		int subResult = dialog.ShowModal();

		if (subResult == wxID_YES) {
			struct data inputData = createDataFromInput();
			storeData(inputData);
		}
		if (subResult == wxID_NO) {
			evt.Skip();
		}
		wxMessageDialog dialog2(this,"Submitted Successfully!!All fields will be cleared. Press cancel to keep values","submitted", wxOK | wxCANCEL);
		dialog2.SetOKLabel("Proceed");
		int result2 = dialog2.ShowModal();

		if (result2 == wxID_OK) {
			nameField->Clear();
			IPnoField->Clear();
			OPnoField->Clear();
			HbField->Clear();
			apgarField->Clear();
			babyWghtField->Clear();
			doctorField->Clear();
			remarksField->Clear();
			ageField->SetValue(0);
			graviField->SetValue(0);
			paraField->SetValue(0);
			aliveChildField->SetValue(0);
			gestAgeWeekField->SetValue(0);
			gestAgeDayField->SetValue(0);
			bloodGrpField->SetSelection(wxNOT_FOUND);
			modeDelivField->SetSelection(wxNOT_FOUND);
			caseTypeField->SetSelection(wxNOT_FOUND);
		}
	}
}
//------------------------------//--------------------------//-----------------------------------------//-------------------
void MainFrame::onGraviSpinChange(wxSpinEvent& evt)
{
	graviEmpty = false;
}

void MainFrame::onGraviSpinTextChange(wxCommandEvent& evt)
{
	graviEmpty = false;
}

void MainFrame::onAgeSpinChange(wxSpinEvent& evt)
{
	ageEmpty = false;
}

void MainFrame::onAgeSpinTextChange(wxCommandEvent& evt)
{
	ageEmpty = false;
}

void MainFrame::onParaSpinChange(wxSpinEvent& evt)
{
	paraEmpty = false;
}

void MainFrame::onParaSpinTextChange(wxCommandEvent& evt)
{
	paraEmpty = false;
}

void MainFrame::onChildSpinChange(wxSpinEvent& evt)
{
	childAliveEmpty = false;
}

void MainFrame::onChildSpinTextChange(wxCommandEvent& evt)
{
	childAliveEmpty = false;
}

void MainFrame::onGestWSpinChange(wxSpinEvent& evt)
{
	gestWEmpty = false;
}

void MainFrame::onGestWSpinTextChange(wxCommandEvent& evt)
{
	gestWEmpty = false;
}
void MainFrame::onGestDSpinChange(wxSpinEvent& evt)
{
	gestDEmpty = false;
}

void MainFrame::onGestDSpinTextChange(wxCommandEvent& evt)
{
	gestDEmpty = false;
}
//--------------------------------//----------------------------//--------------------------//--------------------------------------//


data MainFrame::createDataFromInput()
{
    //-------------------------------------------reading from gui-----------------------------------------------------//
	data inputData;
	wxString IPno_s = IPnoField->GetValue();
	wxString OPno_s = OPnoField->GetValue();
	wxString name_s = nameField->GetValue();
	wxString Hb_s = HbField->GetValue();
	wxString modeDeliv_s = modeDelivField->GetValue();
	wxString bloodGrp_s = bloodGrpField->GetValue();
	int caseType_i = caseTypeField->GetSelection();
	int age_i = ageField->GetValue();
	int gravi_i = graviField->GetValue();
	int para_i = paraField->GetValue();
	int aliveChild_i = aliveChildField->GetValue();
	int gestWeek_i = gestAgeWeekField->GetValue();
	int gestDay_i = gestAgeDayField->GetValue();
	int babySex_i = babySexField->GetSelection();
	int babyAlive_i = babyAliveField->GetSelection();
	wxString babyWght_s = babyWghtField->GetValue();
	wxString apgar_s = apgarField->GetValue();
	wxDateTime dateDeli_wx = dateDeliField->GetValue();
	wxDateTime timeDeli_wx = timeDeliField->GetValue();
	wxString doctor_s = doctorField->GetValue();
	wxString remarks_s = remarksField->GetValue();
	//wxString comorbidities_s = comorbiditiesField->GetValue();
	int induced_i = inducedField->GetValue();
	//wxString inductionMethod_s = inductionMethod->GetValue();
	
	///implement the bool array comorbidity thingy
	
	tm deliveryTimeDate;
	wxDateTime::Tm dateDeli_wxTm = dateDeli_wx.GetTm();
	wxDateTime::Tm timeDeli_wxTm = timeDeli_wx.GetTm();
	deliveryTimeDate.tm_year = dateDeli_wxTm.year - 1900;
	deliveryTimeDate.tm_mon = dateDeli_wxTm.mon;
	deliveryTimeDate.tm_mday = dateDeli_wxTm.mday;
	deliveryTimeDate.tm_hour = timeDeli_wxTm.hour;
	deliveryTimeDate.tm_min = timeDeli_wxTm.min;
    //---------------------------------------assigning to data struct-----------------------------------------------------------------//
	inputData.IPno = wxAtol(IPno_s);
	inputData.OPno = wxAtol(OPno_s);
	inputData.name = name_s;
	inputData.Hb = wxAtol(Hb_s);
	inputData.age = age_i;
	inputData.modeOfDelivery = modeDeliv_s;
	inputData.bloodGrp = bloodGrp_s;
	inputData.gravida = gravi_i;
	inputData.para = para_i;
	inputData.childrenAlive = aliveChild_i;
	inputData.gestationalAge.week = gestWeek_i;
	inputData.gestationalAge.day = gestDay_i;

	switch (babySex_i) {
	case 0: {
		inputData.babyDetail.sex = 'M';
		break;
	}
	case 1: {
		inputData.babyDetail.sex = 'F';
		break;
	}
	}

	switch (caseType_i) {
	case 0: {
		inputData.caseType = 'R';
		break;
	}
	case 1: {
		inputData.caseType = 'B';
		break;
	}
	}

	inputData.babyDetail.Alive = !babyAlive_i;
	inputData.babyDetail.weight = wxAtof(babyWght_s);
	inputData.babyDetail.apgar = wxAtof(apgar_s);
	inputData.deliveryTimeDate = deliveryTimeDate;
	inputData.doctor = doctor_s;
	inputData.remark = remarks_s;
	inputData.induced = induced_i;

	for (auto& comorbCheck : comorbCheckBoxes) {
		inputData.comorbidities.push_back(comorbCheck->GetValue());
	}

	inputData.foley = foley->GetValue();
	inputData.meso = meso->GetSelection();
	inputData.pitocin = pitocin->GetValue();
	return inputData;
}

