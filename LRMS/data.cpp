#include "data.h"
#include<string>
#include<vector>
#include<filesystem>
#include<fstream>
#include<ctime>
#include<sstream>
#include<iostream>
#include<algorithm>

#define noOfColumn 24



//a csv row(in string format) tokeniser that breaks the string into tokens based on ','
std::vector<std::string> tokeniser(std::string line)
{
	std::vector <std::string> tokens;
	std::string intermediate;
	std::stringstream str(line);
	while (std::getline(str, intermediate, ',')) {
		tokens.push_back(intermediate);
	}
	return tokens;
}



//converts a vector of strings in the order from the csv file into the data structure of our prgrm
data stringVectorToData(std::vector<std::string> tokens)
{
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

	struct data data;
	/*
	if (tokens.size() != noOfColumn) {
		return data;
	}*/
	data.IPno = stol(tokens[0]);
	data.OPno = stol(tokens[1]);
	data.deliveryTimeDate.tm_year = stoi(tokens[2]);
	data.deliveryTimeDate.tm_mon= stoi(tokens[3]);
	data.deliveryTimeDate.tm_mday = stoi(tokens[4]);
	data.deliveryTimeDate.tm_hour = stoi(tokens[5]);
	data.deliveryTimeDate.tm_min = stoi(tokens[6]);
	data.name = tokens[7];
	data.bloodGrp = tokens[8];
	data.Hb = stof(tokens[9]);
	data.caseType = tokens[10][0];
	data.age = stoi(tokens[11]);
	data.gravida = stoi(tokens[12]);
	data.para = stoi(tokens[13]);
	data.childrenAlive = stoi(tokens[14]);
	data.gestationalAge.week = stoi(tokens[15]);
	data.gestationalAge.day = stoi(tokens[16]);
	data.modeOfDelivery = tokens[17];
	data.babyDetail.sex = tokens[18][0];
	data.babyDetail.weight = stof(tokens[19]);
	data.babyDetail.Alive = stoi(tokens[20]);
	data.babyDetail.apgar = stof(tokens[21]);
	int i;
	for (i = 0; i < comorbChoice.size(); i++) {
		data.comorbidities.push_back(stoi(tokens[22 + i]));
	}
	int j = 22 + i;
	data.induced = stoi(tokens[j++]);
	data.foley = stoi(tokens[j++]);
	data.meso = stoi(tokens[j++]);
	data.pitocin = stoi(tokens[j++]);
	data.doctor = tokens[j++];
	data.remark = tokens[j++];
	
	return data;
}

//reads line by line from the file and tokenises each row and convert and store as vector of data
std::vector<data> readfromMonthFile(std::string fileName)
{
	if (!std::filesystem::exists(fileName)) {
		return std::vector<data>();
	}

	std::vector<data>dataVector;
	std::ifstream fileStream;							//unable to open file /file deleted
	fileStream.open(fileName);
	
	


	std::string line;
	struct data dataInter;
	std::vector <std::string> tokens;

	std::getline(fileStream, line);//heading row

	while (std::getline(fileStream, line)) {
		tokens = tokeniser(line);
		dataInter = stringVectorToData(tokens);
		dataVector.push_back(dataInter);
		
	}
	
	return dataVector;
		
}

//writing into file in a fixed order
void inputToFile(data data, const std::string& fileName)
{	
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

	if (!std::filesystem::exists(fileName)) {
		std::cout << "hello";
		std::ofstream fileStream;
		fileStream.open(fileName);
		fileStream << "IPno" << "," << "OPno" << ",";
		fileStream << "delivery year" << "," << "delivery month" << "," << "delivery day" << "," << "delivery hour" << "," << "delivery minute" << ",";
		fileStream << "name" << "," << "bloodGrp" << "," << "Hb" << "," << "caseType" << "," << "age" << "," << "gravida" << "," << "para" << "," << "childrenAlive" << "," << "gestationalAge.week" << "," << "gestationalAge.day" << "," << "modeOfDelivery" << ",";
		fileStream << "babySex" << "," << "babyWeight" << ", " << "babyAlive" << "," << "babyApgar" << ",";
		for (auto const& comorb : comorbChoice ) {
			fileStream << comorb << ",";
		}
		fileStream << "induced" << "," << "foley" << "," << "meso" << "," << "pitocin" << "," << "doctor" << "," << "remark" << "\n";
	}

	std::ofstream fileStream;
	fileStream.open(fileName,std::ios::app);
	fileStream << data.IPno << "," << data.OPno << ",";
	fileStream << data.deliveryTimeDate.tm_year << "," << data.deliveryTimeDate.tm_mon << "," << data.deliveryTimeDate.tm_mday << "," << data.deliveryTimeDate.tm_hour << "," << data.deliveryTimeDate.tm_min<<",";
	fileStream << data.name << "," << data.bloodGrp << "," << data.Hb << "," << data.caseType << "," << data.age << "," << data.gravida << "," << data.para << "," << data.childrenAlive << "," << data.gestationalAge.week << "," << data.gestationalAge.day << "," << data.modeOfDelivery << ",";
	fileStream << data.babyDetail.sex << "," << data.babyDetail.weight << "," << data.babyDetail.Alive << "," << data.babyDetail.apgar << ",";
	for (auto const& comorb : data.comorbidities) {
		fileStream << comorb << ",";
	}
	fileStream << data.induced << "," << data.foley << "," << data.meso << "," << data.pitocin << "," << data.doctor << "," << data.remark << "\n";
}

//creates the year folder of our data does nothing when it already exists
std::string makeDirectory(data data)
{
	std::string projectFolder = "C:\\LRMS\\database\\";
	std::filesystem::create_directories(projectFolder);

	int year = data.deliveryTimeDate.tm_year + 1900;

	std::string yearFolder = projectFolder + std::to_string(year) + "\\";
	std::filesystem::create_directories(yearFolder);

	return yearFolder;
}

//top level fn to store data into csv file on drive
void storeData(data data)
{
	std::string yearFolder = makeDirectory(data);
	int month = data.deliveryTimeDate.tm_mon + 1;
	std::string fileName = yearFolder + std::to_string(month) + ".csv";
	inputToFile(data, fileName);
}



/*
int main() {
	struct gestationalAge G_age {
		37, 3
	};

	struct baby b {
		'M',2.990,true,5.8
	};

	struct tm time;
	time.tm_year = 123;
	time.tm_mon = 2;
	time.tm_mday = 16;
	time.tm_hour = 10;
	time.tm_min = 23;
	struct data data = {
		"Ashika",25,546,1524141,'B',2,1,1,G_age,11.5,"O+ve",'E',b,time,"Dr.Seenu","Elective cs"
	};

	//storeData(data);
	std::string path = "C:\\LRMS\\database\\2024\\5.csv";

	std::ifstream fileStream;
	fileStream.open(path);

	std::string line;
	struct data trialData;
	std::vector <std::string> tokens;
	std::getline(fileStream, line);//heading row
	while (std::getline(fileStream, line)) {
		tokens = tokeniser(line);
	}
//	for (int i = 0; i < tokens.size(); i++) {
//		std::cout << tokens[i]<<"\n";
//	}
	
//	trialData.IPno = stoi(tokens[0]);
//	std::cout << trialData.IPno;
	storeData(data);
	trialData = stringVectorToData(tokens);
	trialData.deliveryTimeDate.tm_mon = 8;
	storeData(trialData);
	

	return 0;
}
*/