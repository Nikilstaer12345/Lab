#include <iostream>
#include "cstdlib"
#include <string>
#include <fstream>
#include <vector>
using namespace std;
struct LIVE{
	int id = 0;
	bool survival = 0;
	int pclass = 0;
	string name = "";
	string sex = "";
	double age = 0;
	int sibsp = 0;
	int parch = 0;
	string ticket = "";
	double fare = 0;
	string cabin = "";
	string Embarked = "";
};

LIVE help(string str){
	LIVE people;
	string temp[13];
	int i = 0;
	for (int j = 0; j < 13; j++){
		while (str[i] != ',' && str[i] != '\0'){
			temp[j] += str[i];
			i++;
		}
		i++;
	}
	people.id = atoi(temp[0].c_str());
	people.survival = atoi(temp[1].c_str());
	people.pclass = atoi(temp[2].c_str());
	people.name = temp[3] + " " + temp[4];
	people.sex = temp[5];
	people.age = atoi(temp[6].c_str());
	people.sibsp = atoi(temp[7].c_str());
	people.parch = atoi(temp[8].c_str());
	people.ticket = temp[9];
	people.fare = atof(temp[10].c_str());
	people.cabin = temp[11];
	people.Embarked = temp[12];
	return people;

}

int main(){
	ifstream fin("train.csv");
	vector <string> temp;
	string str;
	while (getline(fin, str, '\r'))
	{
		if (str.size() > 0)
			temp.push_back(str);
	}
	fin.close();
	int all_surv = 0, surv_1 = 0, surv_2 = 0, surv_3 = 0, surv_wom = 0, surv_man = 0, all_wom = 0, all_man = 0;
	double count_wom = 0.0, count_man = 0.0, all_age = 0.0;
	int C = 0, Q = 0, S = 0;
	vector<int> vec;
	for (int i = 1; i < temp.size(); i++){
		LIVE a = help(temp[i]);
		if (a.survival == 1){
			all_surv++;
			if (a.sex == "female"){
				surv_wom++;
			}
			else surv_man++;

			switch (a.pclass){
			case 1:
				surv_1++;
				break;
			case 2:
				surv_2++;
				break;
			case 3:
				surv_3++;
				break;
			}
		}

		if (a.age <= 17){
			vec.push_back(a.id);
		}

		if (a.Embarked == "C") {
			C++;
		}
		if (a.Embarked == "S") {
			S++;
		}
		if (a.Embarked == "Q") {
			Q++;
		}
		
		if (a.sex == "male"){
			all_man++;
			count_man += a.age;
		}
		else {
			all_wom++;
			count_wom += a.age;
		}
		all_age += a.age;
	}

	string Embarked;
	if (S > Q) {
		if (S > C) {
			Embarked = "Southampton"; 
		}
		else Embarked = "Cherbourgh";
	}
	else {
		if (Q > C) {
			Embarked = "Qeenstown";
		}
		else Embarked = "Cherbourgh";
	}

	ofstream fout("Результат.txt");
	fout << "Общее число выживших:" << all_surv << endl;
	fout << "Число выживших из 1 класса: " << surv_1 << endl;
	fout << "Число выживших из 2 класса: " << surv_2 << endl;
	fout << "Число выживших из 3 класса: " << surv_3 << endl;
	fout << "Количество выживших женщин: " << surv_wom << endl;
	fout << "Количество выживших мужчин:  " << surv_man << endl;
	fout << "Средний возраст пассажира / женский / мужской: " << all_age / temp.size() << "/ "<< count_wom / all_wom << "/ "<< count_man / all_man << endl;
	fout << "Штат, в котором село больше всего пассажиров: " << Embarked << endl;
	fout << "Список идентификаторов несовершеннолетних (младше 18) пассажиров: ";
	for (int i = 0; i < vec.size(); i++){
		if (i == vec.size() - 1){
			fout << vec[i] << ".";
			fout.close();
			return 0;
		}
		fout << vec[i] << ",";
	}
}
