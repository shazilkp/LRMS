#include "ReportsFrame.h"
#include "MainFrame.h"
#include<filesystem>
#include<fstream>
#include"data.h"
#include<wx/wx.h>
#include<wx/spinctrl.h>
#include<vector>
#include<string>
#include<map>

ReportsFrame::ReportsFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	createControls();
	bindEventHandlers();
}

void ReportsFrame::createControls()
{
	//auto mainsizer = new wxGridSizer(wxVERTICAL);
	reportpanelcenter = new wxPanel(this, wxID_ANY);
	reportpanelcenter->SetBackgroundColour(wxColour(RGB(254, 254, 255)));

	const auto margin = FromDIP(10);
	auto mlabel = new wxStaticText(reportpanelcenter, wxID_ANY, "Month");
	auto ylabel = new wxStaticText(reportpanelcenter, wxID_ANY, "Year");

	wxFont headingFont(wxFontInfo(wxSize(0, 20)).Bold());
	mlabel->SetFont(headingFont);
	ylabel->SetFont(headingFont);

	month = new wxSpinCtrl(reportpanelcenter, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 12, 1);
	reportYear = new wxSpinCtrl(reportpanelcenter, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 2012, 2050, 2024);
	search = new wxButton(reportpanelcenter, wxID_ANY, "Search");
	cancel = new wxButton(reportpanelcenter, wxID_ANY, "Cancel");

	//auto mainsizer = new wxGridSizer(wxVERTICAL);
	auto sizer = new wxGridSizer(3, 2, margin, margin);
	sizer->Add(mlabel, 1, wxALIGN_BOTTOM | wxALIGN_CENTER_HORIZONTAL);
	sizer->Add(ylabel, 0, wxALIGN_BOTTOM | wxALIGN_CENTER_HORIZONTAL);
	sizer->Add(month, 0, wxALIGN_TOP | wxALIGN_CENTER_HORIZONTAL);
	sizer->Add(reportYear, 1, wxALIGN_TOP | wxALIGN_CENTER_HORIZONTAL);
	sizer->Add(search, 0, wxALIGN_TOP | wxALIGN_CENTER_HORIZONTAL);
	sizer->Add(cancel, 1, wxALIGN_TOP | wxALIGN_CENTER_HORIZONTAL);

	reportpanelcenter->SetSizer(sizer);
}

void ReportsFrame::bindEventHandlers()
{
	search->Bind(wxEVT_BUTTON, &ReportsFrame::generateReport, this);
}

void ReportsFrame::generateReport(wxCommandEvent& evt)
{

	auto year_i = reportYear->GetValue();
	auto month_i = month->GetValue();
	
	std::string fileName = "C:\\LRMS\\database\\" + std::to_string(year_i) + "\\" + std::to_string(month_i) + ".csv";
	if (!std::filesystem::exists(fileName)) {
		wxMessageBox("File doesnt Exist!!!", "caption",wxOK, this);
		evt.Skip();
		return;
	}
	std::vector<data> dataVector = readfromMonthFile(fileName);
	
	
	int totalDeliv = dataVector.size();    

	std::vector < std::tuple<std::string, int>> valueTuple;
	int bookedCase = 0, refferedCase = 0, cSec = 0, VBAC = 0, aVag = 0, nVag = 0, FTND = 0, PTVD = 0, gest_37_39 = 0, gest_34_36 = 0, gest_32_33 = 0, gest_28_31 = 0;
	int l18 = 0, age_18_29=0 ,age_30_34 =0, age_35_40=0,g40=0,primi = 0,multi=0,rhneg = 0, rhpos =0,totPreterm=0, gestg40=0,gestl28=0;
	int birthwght[8] = {0,0,0,0,0,0,0,0}, babyMale = 0, babyFemale = 0, inducedVag = 0, inducedCsec =0 ,foley =0;
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
		comorbidsCount.push_back(std::make_pair(i,0));
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
	vMap["nVag"] =nVag;
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
	float j = 0,k=0.5,m=1.0;
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

}
