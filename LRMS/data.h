#pragma once
#include<string>
#include<ctime>
#include<vector>

struct baby {
	char sex;
	float weight;
	bool Alive;
	float apgar;
};

struct gestationalAge {
	int week;
	int day;
};
/*
enum class casetype {
	Vaginal_delivery,
	Assisted_vaginal_delivery,
	Csection,
	VBAC
};*/

struct data
{
	std::string name;
	int age;
	long int OPno;
	long int IPno;
	char caseType;
	int gravida;
	int para;
	int childrenAlive;
	struct gestationalAge gestationalAge;
	float Hb;
	std::string bloodGrp;
	std::string modeOfDelivery;
	struct baby babyDetail;
	tm deliveryTimeDate;
	std::string doctor;
	std::string remark;
	std::vector<bool>comorbidities;
	bool induced;
	bool foley;
	int meso;
	bool pitocin;
};


void inputToFile(struct data data, const std::string& fileName); // member of storedata
std::string makeDirectory(struct data data); //member of storedata


std::vector<std::string> tokeniser(std::string line);//member of read
struct data stringVectorToData(std::vector<std::string> tokens);//member of read

void storeData(struct data data);					//high level store
std::vector<data> readfromMonthFile(std::string fileName);//high level read a whole month file