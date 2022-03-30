#include "Class.h" 
#include "function.h"
#include <regex>
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
string USERNAME;
string PASSWORD;
map<int, Ward*> wards; // map палат
int ward; //номер палаты
int IdPatient; // Айди Пациента
vector<Patient> patients; // вектор пациентов
vector<Doctor> doctors; // вектор докторов
vector<Login> logins; // вектор логинова
vector<OpRoom> oprooms; //вектор операционных комнат
vector<ManipRoom> maniprooms; //вектор манипуляционных комнат
//Метод для поиска операционной по запросу в эту комнату
int FindOpRoomByRequest(string request) {
	for (int i = 0; i < oprooms.size(); i++)
		if (request == oprooms[i].request)
			return i;
}
//Метод для поиска манипуляционной по запросу в эту комнату
int FindManipRoomByRequest(string request) {
	for (int i = 0; i < oprooms.size(); i++)
		if (request == maniprooms[i].request)
			return i;
}
//Метод для поиска операционной по пациенту в этой комнате
int FindOpRoomByPatient(string patient) {
	for (int i = 0; i < oprooms.size(); i++)
		if (patient == oprooms[i].patient)
			return i;
}
//Метод для поиска манипуляционной по пациенту в этой комнате
int FindManipRoomByPatient(string patient) {
	for (int i = 0; i < oprooms.size(); i++)
		if (patient == maniprooms[i].patient)
			return i;
}
void clearTablet() {
	for (int i = 0; i < 19; i++) {
		SetConsoleCursorPosition(hStdOut, { 2,SHORT(5 + i) });
		cout << "                                  ";
	}
}
Patient FindPat() {
	for (Patient pat : patients) {
		if (USERNAME == ("P" + pat.login))
			return pat;
	}
}
Doctor FindDocById(string id) {
	for (Doctor doc : doctors) {
		if (id == doc.ID)
			return doc;
	}
}
enum COLOR
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};
void ColorOutput(string text, COLOR TextColor, COLOR BackColor)
{
	SetConsoleTextAttribute(hStdOut, (WORD)(BackColor << 4 | TextColor));
	cout << text;
	SetConsoleTextAttribute(hStdOut, (WORD)(COLOR::Black << 4 | COLOR::White));
}
void ReadAllFile() {
	ifstream Pinput("DATA/Patients.txt");
	ifstream Dinput("DATA/Doctors.txt");
	ifstream Linput("DATA/Login.txt");
	ifstream Opinput("DATA/OpRoom.txt");
	ifstream Manipinput("DATA/ManipRoom.txt");
	Patient* Ptemp = new Patient();
	Doctor Dtemp;
	Login Ltemp;
	OpRoom Optemp;
	ManipRoom Maniptemp;
	while (!Pinput.eof()) {
		Pinput >> (*Ptemp);
		patients.push_back(*Ptemp);
		if (!wards.count(Ptemp->IDward))
			wards[Ptemp->IDward] = new Ward();
		wards[Ptemp->IDward]->AddPatient(patients[patients.size() - 1]);
	}
	while (!Dinput.eof()) {
		Dinput >> Dtemp;
		doctors.push_back(Dtemp);
	}
	while (!Linput.eof()) {
		Linput >> Ltemp;
		logins.push_back(Ltemp);
	}
	while (!Opinput.eof()) {
		Opinput >> Optemp;
		oprooms.push_back(Optemp);
	}
	while (!Manipinput.eof()) {
		Manipinput >> Maniptemp;
		maniprooms.push_back(Maniptemp);
	}
	Pinput.close();
	Dinput.close();
	Linput.close();
	Opinput.close();
	Manipinput.close();
}
void WriteInAllFile() {
	ofstream Poutput("DATA/Patients.txt");
	ofstream Doutput("DATA/Doctors.txt");
	ofstream Loutput("DATA/Login.txt");
	ofstream Opoutput("DATA/OpRoom.txt");
	ofstream Manipoutput("DATA/ManipRoom.txt");
	for (int i = 0; i < patients.size(); i++) {
		Poutput << patients[i];
		if (i != patients.size() - 1)
			Poutput << endl;
	}
	for (int i = 0; i < doctors.size(); i++) {
		Doutput << doctors[i];
		if (i != doctors.size() - 1)
			Doutput << endl;
	}
	for (int i = 0; i < logins.size(); i++) {
		Loutput << logins[i];
		if (i != logins.size() - 1)
			Loutput << endl;
	}
	for (int i = 0; i < oprooms.size(); i++) {
		Opoutput << oprooms[i];
		if (i != oprooms.size() - 1)
			Opoutput << endl;
	}
	for (int i = 0; i < maniprooms.size(); i++) {
		Manipoutput << maniprooms[i];
		if (i != maniprooms.size() - 1)
			Manipoutput << endl;
	}
	Poutput.close();
	Doutput.close();
	Loutput.close();
	Opoutput.close();
	Manipoutput.close();
}
string Pass(string user) {
	for (Login log : logins) {
		if (log.ID == user)
			return log.Pass;
	}
	return "-1";


}
string DelD(string str) {
	string temp;
	for (int i = 1; i < str.size(); i++) {
		temp += str[i];
	}
	return temp;
}
void drawfunctionfortablet(int ward1, int inf) {
	SetConsoleCursorPosition(hStdOut, { 13,4 });
	ward = ward1;
	if (inf == 0) {
		ColorOutput("Ward:" + to_string(ward), Black, LightCyan);
		cout << "    ";
	}
	else
		cout << "Ward:" << ward << "      ";
	SetConsoleCursorPosition(hStdOut, { 4, 8 });
	if (inf == 1) {
		ColorOutput("--> Info", Black, LightCyan);
	}
	else
		cout << "Info      ";
	SetConsoleCursorPosition(hStdOut, { 4, 11 });
	if (inf == 2)
		ColorOutput("--> Enter to Ward", Black, LightCyan);
	else
		cout << "Enter to Ward        ";
	SetConsoleCursorPosition(hStdOut, { 4, 14 });
	if (inf == 3)
		ColorOutput("--> Exit", Black, LightCyan);
	else
		cout << "Exit        ";

	SetConsoleCursorPosition(hStdOut, { 0, 25 });
}
void InfoPanel(int ward1) {
	int space = 0;
	if (!wards.count(ward)) {
		SetConsoleCursorPosition(hStdOut, { 50, 7 });
		cout << "Ward is empty";
		return;
	}
	list<Patient> t = wards[ward]->getPatients();
	list<Patient>::iterator it = t.begin();
	for (; it != t.end(); it++, space += 2)
	{
		SetConsoleCursorPosition(hStdOut, { 50, SHORT(7 + space) });
		cout << (*it).ID << ". " << (*it).Name << " " << (*it).SecondName;
	}
}
void printPatientsInTablet() {
	int space = 0;
	clearTablet();
	SetConsoleCursorPosition(hStdOut, { 4, 8 });
	if (!wards.count(ward)) {
		cout << "Ward is empty";
		return;
	}
	list<Patient> t = wards[ward]->getPatients();
	list<Patient>::iterator it = t.begin();
	for (; it != t.end(); it++, space += 2)
	{
		SetConsoleCursorPosition(hStdOut, { 4, SHORT(8 + space) });
		cout << (*it).Name << " " << (*it).SecondName;
	}
	SetConsoleCursorPosition(hStdOut, { 4, SHORT(8 + space) });
	cout << "Back";
}
void PatientTablet() {
	drawTablet();
	SetConsoleCursorPosition(hStdOut, { 4, 6 });
	cout << "------------------------------";
	SetConsoleCursorPosition(hStdOut, { 4, 8 });
	cout << wards[ward]->getPatientById(IdPatient).Name << " " << wards[ward]->getPatientById(IdPatient).SecondName;
	SetConsoleCursorPosition(hStdOut, { 4, 10 });
	cout << "ILLNESS : " << wards[ward]->getPatientById(IdPatient).illness;
	SetConsoleCursorPosition(hStdOut, { 4, 12 });
	cout << "CURE : " << wards[ward]->getPatientById(IdPatient).Cure;
	SetConsoleCursorPosition(hStdOut, { 4, 14 });
	cout << "ATTENDING DOCTOR : Dr." << FindDocById(wards[ward]->getPatientById(IdPatient).IDdoctor).SecondName;
	SetConsoleCursorPosition(hStdOut, { 4, 20 });
	cout << "------------------------------";

}
void funcPatientTablet() {
	SetConsoleCursorPosition(hStdOut, { 4, 18 });
	ColorOutput("--> Back", Black, LightCyan);
	while (true) {
		if (_kbhit()) {
			if (_getch() == 13) {
				return;
			}
		}
	}
}
bool DoctorPatient(Patient pat) {
	return (("D" + (pat.IDdoctor)) == USERNAME) ? true : false;
}
void printPatientTabletIfDoctor(int pos) {
	PatientTablet();
	SetConsoleCursorPosition(hStdOut, { 4, 16 });
	cout << "Settings";
	SetConsoleCursorPosition(hStdOut, { 4, 18 });
	cout << "Back";
	if (pos == 0) {
		SetConsoleCursorPosition(hStdOut, { 4, 16 });
		ColorOutput("--> Settings", Black, LightCyan);
	}
	else {
		SetConsoleCursorPosition(hStdOut, { 4, 18 });
		ColorOutput("--> Back", Black, LightCyan);
	}
}
void PatientTabletIfDoctor() {
	int ikey;
	int pos = 0;
	printPatientTabletIfDoctor(pos);
	while (true)
	{
		if (_kbhit()) {

			ikey = _getch();
			if (ikey == 80) {
				pos = 1;
			}
			if (ikey == 72) {
				pos = 0;
			}
			printPatientTabletIfDoctor(pos);
			if (ikey == 13) {
				if (pos == 1)
					return;
				else {
					EditTablet();
					return;
				}
			}
		}
	}
}
void printEditTablet(int pos) {
	clearTablet();
	SetConsoleCursorPosition(hStdOut, { 4,8 });
	if (pos == 0)
		ColorOutput("--> EDIT ILLNESS", Black, LightCyan);
	else
		cout << "EDIT ILLNESS";
	SetConsoleCursorPosition(hStdOut, { 4,10 });
	if (pos == 1)
		ColorOutput("--> EDIT CURE", Black, LightCyan);
	else
		cout << "EDIT CURE";

	SetConsoleCursorPosition(hStdOut, { 4,12 });

	if (pos == 2)
		ColorOutput("--> DELETE", Black, LightCyan);
	else
		cout << "DELETE";

	SetConsoleCursorPosition(hStdOut, { 4,14 });
	if (pos == 3)
		ColorOutput("--> BACK", Black, LightCyan);
	else
		cout << "BACK";
	SetConsoleCursorPosition(hStdOut, { 4,16 });
	if (wards[ward]->getPatientById(IdPatient).status) {
		if (pos != 4)
			cout << "ROOM SETTINGS";
		else
			ColorOutput("--> ROOM SETTINGS", Black, LightCyan);

	}

}
void EditTablet() {
	int pos = 0, ikey;
	drawTablet();
	printEditTablet(pos);
	while (true) {
		if (_kbhit()) {
			ikey = _getch();
			if ((ikey == 80) && (wards[ward]->getPatientById(IdPatient).status) && (pos == 3))
				pos++;
			if ((ikey == 80) && (pos < 3)) {
				pos++;
			}
			if ((ikey == 72) && (pos > 0)) {
				pos--;
			}
			printEditTablet(pos);
			if (ikey == 13) {
				if (pos == 0) {
					funcEditTablet_Illness();
				}
				if (pos == 1) {
					funcEditTablet_Cure();
				}
				if (pos == 2) {
					funcEditTablet_delete();
				}
				if (pos == 3) {
					printPatientTabletIfDoctor(0);
				}
				if (pos == 4) {
					funcEditTablet_SettingsRoom();
				}
				WriteInAllFile();
				return;

			}
		}
	}

}
void funcEditTablet_SettingsRoom() {
	int ikey, pos = 0;
	printfuncEditTablet_SettingsRoom(pos);
	while (true) {
		if (_kbhit()) {
			ikey = _getch();
			if ((ikey == 72) && (pos > 0)) {
				pos--;
			}
			if ((ikey == 80) && (pos < 1)) {
				pos++;
			}
			printfuncEditTablet_SettingsRoom(pos);
			if (ikey == 13) {
				if (pos == 0) {
					if (funcEditTablet_SettingsRoom_Accepting())
					{
						if (wards[ward]->getPatientById(IdPatient).status == 1) {
							SetConsoleCursorPosition(hStdOut, { 4,12 });
							if (oprooms[FindOpRoomByRequest(wards[ward]->getPatientById(IdPatient).login)].patient != "0")
							{
								cout << "THE ROOM IS OCCUPIED";
								continue;
							}
							oprooms[FindOpRoomByRequest(wards[ward]->getPatientById(IdPatient).login)].patient = patients[IdPatient].login;
							oprooms[FindOpRoomByRequest(wards[ward]->getPatientById(IdPatient).login)].request = "0";
							patients[IdPatient].status = 3;
							wards[ward]->EditStatusPatient(IdPatient, 3);
							return;
						}
						if (wards[ward]->getPatientById(IdPatient).status == 2) {
							if (maniprooms[FindManipRoomByRequest(wards[ward]->getPatientById(IdPatient).login)].patient != "0")
							{
								SetConsoleCursorPosition(hStdOut, { 4,12 });
								cout << "THE ROOM IS OCCUPIED";
								continue;
							}
							maniprooms[FindManipRoomByRequest(wards[ward]->getPatientById(IdPatient).login)].patient = patients[IdPatient].login;
							maniprooms[FindManipRoomByRequest(wards[ward]->getPatientById(IdPatient).login)].request = "0";
							patients[IdPatient].status = 4;
							wards[ward]->EditStatusPatient(IdPatient, 4);
							return;
						}
						if (wards[ward]->getPatientById(IdPatient).status == 3) {
							oprooms[FindOpRoomByPatient(wards[ward]->getPatientById(IdPatient).login)].patient = "0";
							patients[IdPatient].status = 0;
							wards[ward]->EditStatusPatient(IdPatient, 0);
							return;
						}


						if (wards[ward]->getPatientById(IdPatient).status == 4) {
							maniprooms[FindManipRoomByPatient(wards[ward]->getPatientById(IdPatient).login)].patient = "0";
							patients[IdPatient].status = 0;
							wards[ward]->EditStatusPatient(IdPatient, 0);
							return;

						}
					}
				}
				if (pos == 1)
					return;
			}
		}
	}
}
bool funcEditTablet_SettingsRoom_Accepting() {
	int ikey, pos = 0;
	printfuncEditTablet_SettingsRoom_Accepting(pos);
	while (true) {
		if (_kbhit()) {
			ikey = _getch();
			if ((ikey == 72) && (pos > 0)) {
				pos--;
			}
			if ((ikey == 80) && (pos < 1)) {
				pos++;
			}
			printfuncEditTablet_SettingsRoom_Accepting(pos);
			if (ikey == 13) {
				if (pos == 0)
					return true;
				else
					return false;
			}
		}
	}
}
void printfuncEditTablet_SettingsRoom_Accepting(int pos) {
	SetConsoleCursorPosition(hStdOut, { 4,12 });
	if (pos != 0)
		cout << "ACCEPT";
	else
		ColorOutput("ACCEPT", Black, LightCyan);
	SetConsoleCursorPosition(hStdOut, { 4,14 });
	if (pos != 1)
		cout << "REFUSE";
	else
		ColorOutput("REFUSE", Black, LightCyan);

}
void printfuncEditTablet_SettingsRoom(int pos) {
	clearTablet();
	SetConsoleCursorPosition(hStdOut, { 4,8 });
	if (wards[ward]->getPatientById(IdPatient).status == 1)
		if (pos != 0)
			cout << "ACCEPT REQUEST TO OPERATION";
		else
			ColorOutput("--> ACCEPT REQUEST TO OPERATION", Black, LightCyan);

	if (wards[ward]->getPatientById(IdPatient).status == 2)
		if (pos != 0)
			cout << "ACCEPT REQUEST TO MANIPUL.";
		else
			ColorOutput("--> ACCEPT REQUEST TO MANIPUL.", Black, LightCyan);
	if (wards[ward]->getPatientById(IdPatient).status == 3)
		if (pos != 0)
			cout << "DELETE FROM OPERATION ROOM";
		else
			ColorOutput("--> DELETE FROM OPERATION ROOM", Black, LightCyan);
	if (wards[ward]->getPatientById(IdPatient).status == 4)
		if (pos != 0)
			cout << "DELETE FROM MANIPULATIVE ROOM";
		else
			ColorOutput("--> DELETE FROM MANIPULATIVE ROOM", Black, LightCyan);
	SetConsoleCursorPosition(hStdOut, { 4,10 });
	if (pos != 1)
		cout << "BACK";
	else
		ColorOutput("--> BACK", Black, LightCyan);
}
void funcEditTablet_Cure() {
	regex rx{ "[A-Za-z]{0,24}" };
	PatientTablet();
	SetConsoleCursorPosition(hStdOut, { 11,12 });
	cout << "            ";
	SetConsoleCursorPosition(hStdOut, { 11,12 });
	vector<char> newCure;
	string str;
	int ikey;
	while (true) {
		if (_kbhit()) {

			ikey = _getch();
			if (ikey == 13) {
				str = CreatStringByVectChar(newCure);
				patients[IdPatient].Cure = str;
				wards[ward]->EditCurePatient(IdPatient, str);
				return;
			}
			if (ikey == 8) {
				if (newCure.size() == 0)
					continue;
				newCure.pop_back();
				SetConsoleCursorPosition(hStdOut, { 11 + SHORT(newCure.size()), 10 });
				cout << " ";
				SetConsoleCursorPosition(hStdOut, { 11 + SHORT(newCure.size()), 10 });
			}
			newCure.push_back(ikey);
			str = CreatStringByVectChar(newCure);
			if (regex_match(str, rx)) {
				cout << char(ikey);
			}
			else {
				newCure.pop_back();
			}
		}
	}
}
void funcEditTablet_delete() {
	wards[ward]->DeletePatient(IdPatient);
	for (int i = IdPatient; i < patients.size(); i++)
		patients[i].ID--;
	for (int i = 0; i < logins.size(); i++) {
		if (logins[i].ID == ("P" + patients[IdPatient].login))
		{
			logins.erase(logins.begin() + i);
			break;
		}
	}
	if (patients[IdPatient].status == 1) {
		oprooms[FindOpRoomByRequest(patients[IdPatient].login)].request = "0";
	}
	if (patients[IdPatient].status == 2) {
		oprooms[FindManipRoomByRequest(patients[IdPatient].login)].request = "0";

	}
	if (patients[IdPatient].status == 3) {
		oprooms[FindOpRoomByPatient(patients[IdPatient].login)].patient = "0";

	}
	if (patients[IdPatient].status == 4) {
		oprooms[FindOpRoomByPatient(patients[IdPatient].login)].patient = "0";

	}
	patients.erase(patients.begin() + IdPatient);
	if (!wards[ward]->getPatients().size())
		wards.erase(ward);
	IdPatient = -1;
	WriteInAllFile();
}
void funcEditTablet_Illness() {
	regex rx{ "[A-Za-z]{0,20}" };
	PatientTablet();
	SetConsoleCursorPosition(hStdOut, { 14,10 });
	cout << "            ";
	SetConsoleCursorPosition(hStdOut, { 14,10 });
	vector<char> newIll;
	string str;
	int ikey;
	while (true) {
		if (_kbhit()) {

			ikey = _getch();
			if (ikey == 13) {
				str = CreatStringByVectChar(newIll);
				patients[IdPatient].illness = str;
				wards[ward]->EditIllnessPatient(IdPatient, str);
				return;
			}
			if (ikey == 8) {
				if (newIll.size() == 0)
					continue;
				newIll.pop_back();
				SetConsoleCursorPosition(hStdOut, { 14 + SHORT(newIll.size()), 10 });
				cout << " ";
				SetConsoleCursorPosition(hStdOut, { 14 + SHORT(newIll.size()), 10 });
			}
			newIll.push_back(ikey);
			str = CreatStringByVectChar(newIll);
			if (regex_match(str, rx)) {
				cout << char(ikey);
			}
			else {
				newIll.pop_back();
			}
		}
	}
}
void EnterPanel(int ward1) {
	if (!wards.count(ward)) {
		SetConsoleCursorPosition(hStdOut, { 50, 7 });
		cout << "Ward is empty";
		return;
	}
	drawTablet();
	SetConsoleCursorPosition(hStdOut, { 13,4 });
	cout << "Ward:" << ward << "    ";
	printPatientsInTablet();
	int space = 0;
	int ikey = 0;
	list<Patient> t = wards[ward]->getPatients();
	list<Patient>::iterator it = t.begin();
	SetConsoleCursorPosition(hStdOut, { 4, SHORT(8 + space) });
	ColorOutput("--> " + (*it).Name + " " + (*it).SecondName, Black, LightCyan);
	SetConsoleCursorPosition(hStdOut, { 0,27 });
	IdPatient = (*it).ID;
	while (true) {
		if (_kbhit())
		{
			ikey = _getch();

			if (ikey == 13) {
				if (it == t.end()) {
					clearTablet();
					return;
				}

				if (IdPatient == -1) {
					space = 0;
					t = wards[ward]->getPatients();
					it = t.begin();
				}
				if (DoctorPatient(*it)) {
					PatientTabletIfDoctor();
					it = t.begin();
					clearTablet();
						return;
				}
				else {
					PatientTablet();
					funcPatientTablet();
					clearTablet();
				}
			}
			if (ikey == 72) {
				if (it == t.begin()) {
					continue;
				}
				else {
					it--;
					space -= 2;
				}
			}
			if ((ikey == 80)) {
				if (it != t.end()) {
					it++;
					space += 2;
				}

			}
			if (it == t.end())
			{
				printPatientsInTablet();
				SetConsoleCursorPosition(hStdOut, { 4, SHORT(8 + space) });
				ColorOutput("--> Back", Black, LightCyan);
				continue;
			}
			printPatientsInTablet();
			IdPatient = (*it).ID;
			SetConsoleCursorPosition(hStdOut, { 4, SHORT(8 + space) });
			ColorOutput("--> " + (*it).Name + " " + (*it).SecondName, Black, LightCyan);
			SetConsoleCursorPosition(hStdOut, { 0,27 });
		}


	}
	SetConsoleCursorPosition(hStdOut, { 0,27 });
}
void drawHospital() {
	ReadAllFile();
	cout << "										 " << endl;
	cout << "                ########				 " << endl;
	cout << "               ####";
	SetConsoleTextAttribute(hStdOut, BACKGROUND_RED | BACKGROUND_INTENSITY);
	cout << "  ";
	SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "####				 " << endl;
	cout << "               #";
	SetConsoleTextAttribute(hStdOut, BACKGROUND_RED | BACKGROUND_INTENSITY);
	cout << "        ";
	SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "#				 " << endl;
	cout << "               ####";
	SetConsoleTextAttribute(hStdOut, BACKGROUND_RED | BACKGROUND_INTENSITY);
	cout << "  ";
	SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "####				 " << endl;
	cout << "           ##################           " << endl;
	cout << "           #      ####      #       	 " << endl;
	cout << "           #    ##    ##    #			 " << endl;
	cout << "   ######  ##################  ######   " << endl;
	cout << "   #  # #  # #  ##    ##  # #  # #  #   " << endl;
	cout << "   #  # #  # #  ##    ##  # #  # #  #   " << endl;
	cout << "   ######  ##################  ######   " << endl;
	cout << "   #    #  #    ##    ##    #  #    #   " << endl;
	cout << "   #  # #  # #  ##    ##  # #  # #  #   " << endl;
	cout << "   #  # #  # #  ##    ##  # #  # #  #   " << endl;
	cout << "   ######  ##################  ######   " << endl;
	cout << "   #  # #  # #  #      #  # #  # #  #   " << endl;
	cout << "   #    #  #    # #### #    #  #    #   " << endl;
	cout << "   ######  ###### #### ######  ######   " << endl;
	cout << "										 " << endl;
	cout << "   WELCOME TO HOSPITAL \"PRETTY HOUSE\" " << endl;
	cout << "										 " << endl;
	cout << "           Press key to Enter           " << endl;
	while (true) {
		if (_kbhit()) {
			_getch();
			return;
		}
	}

}
string CreatStringByVectChar(vector<char> str) {
	string built = "";
	for (int i = 0; i < str.size(); i++)
		built += str[i];
	return built;
}
void drowAuthoWindow() {
	system("cls");
	cout << "#####################################################" << endl;
	cout << "###########|        authorization        |###########" << endl;
	cout << "#####################################################" << endl;
	cout << "##|username|                             |###########" << endl;
	cout << "#####################################################" << endl;
	cout << "##|password|                             |###########" << endl;
	cout << "#####################################################" << endl;

}
int AuthoWindow() {
	drowAuthoWindow();
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO scbi;
	GetConsoleScreenBufferInfo(hStdOut, &scbi);
	int ikey, a = 0;
	vector<char> user;
	vector<char> pass;
	ikey = 0;
	while (true) {
		if (ikey == 13)
			break;
		ikey = 0;
		switch (a)
		{
		case 0:
			SetConsoleCursorPosition(hStdOut, { 12 + SHORT(user.size()),3 });
			while (ikey != 13) {
				if (_kbhit()) {
					ikey = _getch();
					if (ikey == 61) {
						a = 1;
						break;
					}
					if (((ikey >= 'a') && (ikey <= 'z')) || ((ikey >= 'A') && (ikey <= 'Z')) || ((ikey >= '0') && (ikey <= '9'))) {
						if (user.size() == 28)
							continue;
						user.push_back(ikey);
						cout << char(ikey);
					}
					if (ikey == 8) {
						if (user.size() == 0)
							continue;
						user.pop_back();
						SetConsoleCursorPosition(hStdOut, { 12 + SHORT(user.size()), 3 });
						cout << " ";
						SetConsoleCursorPosition(hStdOut, { 12 + SHORT(user.size()), 3 });
					}
				}
			}
			break;
		case 1:
			SetConsoleCursorPosition(hStdOut, { 12 + SHORT(pass.size()),5 });
			while (ikey != 13) {
				if (_kbhit()) {
					ikey = _getch();
					if (ikey == 45) {
						a = 0;
						break;
					}
					if (((ikey >= 'a') && (ikey <= 'z')) || ((ikey >= 'A') && (ikey <= 'Z')) || ((ikey >= '0') && (ikey <= '9'))) {
						if (pass.size() == 26)
							continue;
						pass.push_back(ikey);
						cout << char(ikey);
					}
					if (ikey == 8) {
						if (pass.size() == 0)
							continue;
						pass.pop_back();
						SetConsoleCursorPosition(hStdOut, { 12 + SHORT(pass.size()), 5 });
						cout << " ";
						SetConsoleCursorPosition(hStdOut, { 12 + SHORT(pass.size()), 5 });
					}
				}
			}
			break;
		}
	}
	SetConsoleCursorPosition(hStdOut, { 0, 8 });
	USERNAME = CreatStringByVectChar(user);
	PASSWORD = CreatStringByVectChar(pass);
	if (USERNAME == "admin")
		if (PASSWORD == "admin")
			return 3;
	if (Pass(USERNAME) == PASSWORD) {
		if (USERNAME[0] == 'P') {
			system("cls");
			return 1;
		}
		if (USERNAME[0] == 'D') {
			system("cls");
			return 2;
		}
	}
}
void adminPanel() {
	int ikey, pos = 0;
	printadminPanel(pos);
	while (true) {
		if (_kbhit()) {
			ikey = _getch();
			if ((ikey == 72) && (pos != 0))
				pos--;
			if ((ikey == 80) && (pos != 2))
				pos++;
			printadminPanel(pos);
			if (ikey == 13) {
				if (pos == 0) {
					adminPanel_CreatPatient();
					printadminPanel(pos);
				}
				if (pos == 1) {
					adminPanel_CreateDoctor();
					printadminPanel(pos);

				}
				if (pos == 2) {
					return;
				}
			}
		}
	}

}
void printadminPanel(int pos) {
	system("cls");
	if (pos == 0)
		ColorOutput("--> CREAT PATIENT", Black, LightCyan);
	else
		cout << "CREAT PATIENT";
	cout << endl;
	if (pos == 1)
		ColorOutput("--> CREAT DOCTOR", Black, LightCyan);
	else
		cout << "CREAT DOCTOR";
	cout << endl;
	if (pos == 2)
		ColorOutput("--> EXIT", Black, LightCyan);
	else
		cout << "EXIT";
}
void adminPanel_CreateDoctor() {
	Doctor* creatDoc = new Doctor();
	int pos = 0, ikey;
	printadminPanel_CreateDoctor(creatDoc, pos);
	while (true) {
		if (_kbhit())
		{
			ikey = _getch();
			if ((ikey == 80) && (pos != 4))
				pos++;
			if ((ikey == 72) && (pos != 0)) {
				pos--;
			}
			printadminPanel_CreateDoctor(creatDoc, pos);
			if (ikey == 13) {
				creatDoc = funcadminPanel_CreateDoctor(creatDoc, pos);
				if (pos == 3) {
					if (!EnoughtFields(*creatDoc)) {
						SetConsoleCursorPosition(hStdOut, { 15, 13 });
						cout << "NOT ENOUGHT INFORMATION !";
						continue;
					}
					doctors.push_back(*creatDoc);
					adminPanel_CreatLogin("Doctor", creatDoc->ID);
					WriteInAllFile();
					return;
				}
				if (pos == 4)
					return;

			}
			printadminPanel_CreateDoctor(creatDoc, pos);
		}
	}
}
bool EnoughtFields(Doctor creatDoc) {
	if (creatDoc.ID == "")
		return false;
	if (creatDoc.Name == "")
		return false;
	if (creatDoc.SecondName == "")
		return false;
	return true;
}
Doctor* funcadminPanel_CreateDoctor(Doctor* creatDoc, int pos) {
	if (pos == 0)
		creatDoc->Name = KeyBoardPrint(11, 4);
	if (pos == 1)
		creatDoc->SecondName = KeyBoardPrint(18, 6);
	if (pos == 2) {
		creatDoc->ID = KeyBoardPrint(12, 8);
	}
	return creatDoc;
}
void printadminPanel_CreateDoctor(Doctor* creatDoc, int pos) {
	system("cls");
	SetConsoleCursorPosition(hStdOut, { 4, 1 });
	cout << "------------------------------";
	SetConsoleCursorPosition(hStdOut, { 4, 4 });
	cout << "NAME : ";
	if (pos != 0)
		cout << ((creatDoc->Name != "") ? creatDoc->Name : "  ???   ");
	else
		ColorOutput((creatDoc->Name != "") ? creatDoc->Name : "  ???   ", Black, LightCyan);
	SetConsoleCursorPosition(hStdOut, { 4, 6 });
	cout << "SECOND NAME : ";
	if (pos != 1)
		cout << ((creatDoc->SecondName != "") ? creatDoc->SecondName : "  ???   ");
	else
		ColorOutput((creatDoc->SecondName != "") ? creatDoc->SecondName : "  ???   ", Black, LightCyan);

	SetConsoleCursorPosition(hStdOut, { 4, 8 });
	cout << "Login : ";
	if (pos != 2)
		cout << ((creatDoc->ID != "") ? creatDoc->ID : "  ???   ");
	else
		ColorOutput((creatDoc->ID != "") ? creatDoc->ID : "  ???   ", Black, LightCyan);
	SetConsoleCursorPosition(hStdOut, { 4, 10 });
	cout << "------------------------------";
	SetConsoleCursorPosition(hStdOut, { 4, 13 });
	if (pos != 3)
		cout << "ACCEPT";
	else
		ColorOutput("ACCEPT", Black, LightCyan);
	SetConsoleCursorPosition(hStdOut, { 4,15 });
	if (pos != 4)
		cout << "BACK";
	else
		ColorOutput("BACK", Black, LightCyan);
}
void adminPanel_CreatLogin(string who, string id) {
	system("cls");
	Login login;
	SetConsoleCursorPosition(hStdOut, { 4, 1 });
	cout << "------------------------------";
	SetConsoleCursorPosition(hStdOut, { 4 ,4 });
	if (who == "Doctor") {
		login.ID = "D" + id;
	}
	if (who == "Patient") {
		login.ID = "P" + id;
	}
	cout << "LOGIN : " << login.ID;
	SetConsoleCursorPosition(hStdOut, { 4 , 6 });
	cout << "PASSWORD : ";
	SetConsoleCursorPosition(hStdOut, { 4 , 8 });
	cout << "------------------------------";
	login.Pass = KeyBoardPrint(15, 6);

	logins.push_back(login);

}
void adminPanel_CreatPatient() {
	Patient* creatPat = new Patient();
	int pos = 0, ikey;
	printadminPanel_CreatePatient(creatPat, pos);
	while (true) {
		if (_kbhit())
		{
			ikey = _getch();
			if ((ikey == 80) && (pos != 8))
				pos++;
			if ((ikey == 72) && (pos != 0)) {
				pos--;
			}
			printadminPanel_CreatePatient(creatPat, pos);
			if (ikey == 13) {
				if (pos == 8)
					return;
				if (pos == 7) {
					if (!EnoughtFields(*creatPat)) {
						SetConsoleCursorPosition(hStdOut, { 15, 23 });
						cout << "NOT ENOUGHT INFORMATION !";
						continue;
					}
					if (!wards.count(creatPat->IDward))
						wards[creatPat->IDward] = new Ward();
					creatPat->SetId();
					wards[creatPat->IDward]->AddPatient(*creatPat);
					patients.push_back(*creatPat);
					adminPanel_CreatLogin("Patient", creatPat->login);
					WriteInAllFile();
					return;
				}
				creatPat = funcadminPanel_CreatePatient(creatPat, pos);
			}
			printadminPanel_CreatePatient(creatPat, pos);
		}
	}
}
bool EnoughtFields(Patient creatPat) {
	if (creatPat.IDdoctor == "")
		return false;
	if (creatPat.IDward == (-1))
		return false;
	if (creatPat.Name == "")
		return false;
	if (creatPat.illness == "")
		return false;
	if (creatPat.login == "")
		return false;
	return true;
}
Patient* funcadminPanel_CreatePatient(Patient* creatPat, int pos) {
	if (pos == 0)
		creatPat->Name = KeyBoardPrint(11, 4);
	if (pos == 1)
		creatPat->SecondName = KeyBoardPrint(18, 6);
	if (pos == 2) {
		int ikey, i = creatPat->IDward;
		while (true) {
			if (_kbhit()) {
				ikey = _getch();
				if ((ikey == 75) && (i != -1))
					i--;
				if (ikey == 77)
					i++;
				SetConsoleCursorPosition(hStdOut, { 11, 8 });
				cout << i << "   ";
				SetConsoleCursorPosition(hStdOut, { 0,0 });
				if (ikey == 13) {
					if (wards[i] != NULL)
						if (wards[i]->getPatients().size() == 6) {
							SetConsoleCursorPosition(hStdOut, { 20,8 });
							cout << "WARD IS FULL";
							continue;
						}
					if (wards[i] == NULL)
						wards[i] = new Ward();
					creatPat->IDward = i;
					break;
				}
			}
		}
	}
	if (pos == 3)
		creatPat->illness = KeyBoardPrint(14, 10);
	if (pos == 4)
		creatPat->Cure = KeyBoardPrint(11, 12);
	if (pos == 5)
		creatPat->IDdoctor = ChooseDoctor().ID;
	if (pos == 6)
		creatPat->login = KeyBoardPrint(12, 18);
	return creatPat;
}
Doctor ChooseDoctor() {
	int i = 0, ikey, space = 0;
	printChooseDoctor();
	SetConsoleCursorPosition(hStdOut, { 35,SHORT(4 + space) });
	ColorOutput(doctors[i].Name + " " + doctors[i].SecondName, Black, LightCyan);
	while (true) {
		if (_kbhit()) {
			ikey = _getch();
			if ((i != (doctors.size() - 1)) && (ikey == 80)) {
				i++;
				space += 2;
			}
			if ((i != 0) && (ikey == 72)) {
				i--;
				space -= 2;
			}
			if (ikey == 13) {
				return doctors[i];
			}
			printChooseDoctor();
			SetConsoleCursorPosition(hStdOut, { 35,SHORT(4 + space) });
			ColorOutput(doctors[i].Name + " " + doctors[i].SecondName, Black, LightCyan);
		}
	}
}
void printChooseDoctor() {
	int space = 0;
	for (int i = 0; i < doctors.size(); i++, space += 2) {
		SetConsoleCursorPosition(hStdOut, { 35, SHORT(4 + space) });
		cout << doctors[i].Name << " " << doctors[i].SecondName;
	}
}
string KeyBoardPrint(int x, int y) {
	regex rx{ "[A-Za-z0-9]{0,20}" };
	SetConsoleCursorPosition(hStdOut, { SHORT(x),SHORT(y) });
	cout << "            ";
	SetConsoleCursorPosition(hStdOut, { SHORT(x),SHORT(y) });
	vector<char> temp;
	string str;
	int ikey;
	while (true) {
		if (_kbhit()) {

			ikey = _getch();
			if (ikey == 13) {
				str = CreatStringByVectChar(temp);
				return str;
			}
			if (ikey == 8) {
				if (temp.size() == 0)
					continue;
				temp.pop_back();
				SetConsoleCursorPosition(hStdOut, { SHORT(x) + SHORT(temp.size()), SHORT(y) });
				cout << " ";
				SetConsoleCursorPosition(hStdOut, { SHORT(x) + SHORT(temp.size()), SHORT(y) });
			}
			temp.push_back(ikey);
			str = CreatStringByVectChar(temp);
			if (regex_match(str, rx)) {
				cout << char(ikey);
			}
			else {
				temp.pop_back();
			}
		}
	}
}
void printadminPanel_CreatePatient(Patient* creatPat, int pos) {
	system("cls");
	SetConsoleCursorPosition(hStdOut, { 4, 1 });
	cout << "------------------------------";
	SetConsoleCursorPosition(hStdOut, { 4, 4 });
	cout << "NAME : ";
	if (pos != 0)
		cout << ((creatPat->Name != "") ? creatPat->Name : "  ???   ");
	else
		ColorOutput((creatPat->Name != "") ? creatPat->Name : "  ???   ", Black, LightCyan);
	SetConsoleCursorPosition(hStdOut, { 4, 6 });
	cout << "SECOND NAME : ";
	if (pos != 1)
		cout << ((creatPat->SecondName != "") ? creatPat->SecondName : "  ???   ");
	else
		ColorOutput((creatPat->SecondName != "") ? creatPat->SecondName : "  ???   ", Black, LightCyan);

	SetConsoleCursorPosition(hStdOut, { 4, 8 });
	cout << "WARD : ";
	if (pos != 2)
		cout << ((creatPat->IDward != -1) ? creatPat->IDward : -1);
	else
		ColorOutput((creatPat->IDward != -1) ? to_string(creatPat->IDward) : "-1", Black, LightCyan);
	SetConsoleCursorPosition(hStdOut, { 4, 10 });
	cout << "ILLNESS : ";
	if (pos != 3)
		cout << ((creatPat->illness != "") ? creatPat->illness : "  ???   ");
	else
		ColorOutput((creatPat->illness != "") ? creatPat->illness : "  ???   ", Black, LightCyan);
	SetConsoleCursorPosition(hStdOut, { 4, 12 });
	cout << "CURE : ";
	if (pos != 4)
		cout << ((creatPat->Cure != "") ? creatPat->Cure : "  ???   ");
	else
		ColorOutput((creatPat->Cure != "") ? creatPat->Cure : "  ???   ", Black, LightCyan);
	SetConsoleCursorPosition(hStdOut, { 4, 14 });
	cout << "ATTENDING DOCTOR : ";
	if (creatPat->IDdoctor == "")
		if (pos != 5)
			cout << "Choose";
		else
			ColorOutput("Choose", Black, LightCyan);
	else {
		SetConsoleCursorPosition(hStdOut, { 4 , 16 });
		if (pos != 5) {
			cout << "Dr. " << FindDocById(creatPat->IDdoctor).SecondName;
		}
		else {
			ColorOutput("Dr. " + FindDocById(creatPat->IDdoctor).SecondName, Black, LightCyan);
		}
	}
	SetConsoleCursorPosition(hStdOut, { 4, 18 });
	cout << "Login : ";
	if (pos != 6) {
		cout << ((creatPat->login != "") ? creatPat->login : "  ???   ");
	}
	else {
		ColorOutput(((creatPat->login != "") ? creatPat->login : "  ???   "), Black, LightCyan);
	}
	SetConsoleCursorPosition(hStdOut, { 4,20 });
	cout << "------------------------------";
	SetConsoleCursorPosition(hStdOut, { 4, 23 });
	if (pos != 7)
		cout << "ACCEPT";
	else
		ColorOutput("ACCEPT", Black, LightCyan);
	SetConsoleCursorPosition(hStdOut, { 4, 25 });
	if (pos != 8)
		cout << "BACK";
	else
		ColorOutput("BACK", Black, LightCyan);
}
void MenuPatient() {
	int ikey, pos = 0;
	printMenuPatientTablet();
	while (true) {
		if (_kbhit()) {
			ikey = _getch();
			if (ikey == 80)
				pos = 1;
			if (ikey == 72) {
				pos = 0;
			}
			printMenuPatient(pos);
			if (ikey == 13)
			{
				if (pos == 0) {
					functionMenuPatient();
					printMenuPatientTablet();
				}
				if (pos == 1)
					return;
			}
		}
	}
}
void printMenuPatientTablet() {
	system("cls");
	cout << "******************||********************" << endl;
	cout << "*|      Name      ||                  |*" << endl;
	cout << "******************||********************" << endl;
	cout << "*|   SecondName   ||                  |*" << endl;
	cout << "******************||********************" << endl;
	cout << "*|    illness     ||                  |*" << endl;
	cout << "******************||********************" << endl;
	cout << "*|     Doctor     || Dr.              |*" << endl;
	cout << "******************||********************" << endl;
	cout << "*|      Cure      ||                  |*" << endl;
	cout << "******************||********************" << endl;
	cout << "*|      Ward      ||                  |*" << endl;
	cout << "******************||********************" << endl;
	cout << "*|     Status     ||                  |*" << endl;
	cout << "******************||********************" << endl;
	printMenuPatient(0);
}
void functionMenuPatient() {
	int ikey, pos = 0;
	Patient patient = FindPat();
	printfunctionMenuPatient(pos);
	while (true) {
		if (_kbhit()) {
			ikey = _getch();
			if ((ikey == 80) && (pos != 4))
				pos++;
			if ((ikey == 72) && (pos != 0)) {
				pos--;
			}
			printfunctionMenuPatient(pos);
			if (ikey == 13) {
				if (pos == 0) {
					patient.Name = KeyBoardPrint(21, 1);
					patients[patient.ID].Name = patient.Name;
					wards[patient.IDward]->EditNamePatient(patient.ID, patient.Name);
				}
				if (pos == 1) {
					patient.SecondName = KeyBoardPrint(21, 3);
					patients[patient.ID].SecondName = patient.SecondName;
					wards[patient.IDward]->EditSecondNamePatient(patient.ID, patient.SecondName);
				}
				if (pos == 4)
					return;
				if (pos == 2)
				{
					for (int i = 0; i < oprooms.size(); i++) {
						SetConsoleCursorPosition(hStdOut, { 12,26 });
						cout << "                                     ";
						SetConsoleCursorPosition(hStdOut, { 12,26 });
						if (oprooms[i].request == "0")
						{
							if (patient.status)
							{
								ColorOutput("ACTION NOT AVAIBLE", Black, Red);
								continue;
							}
							ColorOutput("SUCCESS", Black, Green);
							oprooms[i].request = patient.login;
							patient.status = 1;
							patients[patient.ID].status = 1;
							wards[patient.IDward]->EditStatusPatient(patient.ID, patient.status);
							break;
						}
						ColorOutput("THERE ARE NO AVAIBLE ROOMS", Black, Red);

					}
				}
				if (pos == 3)
				{

					for (int i = 0; i < maniprooms.size(); i++) {
						SetConsoleCursorPosition(hStdOut, { 12,26 });
						cout << "                                     ";
						SetConsoleCursorPosition(hStdOut, { 12,26 });
						if (maniprooms[i].request == "0")
						{
							if (patient.status)
							{
								ColorOutput("ACTION NOT AVAIBLE", Black, Red);
								continue;

							}
							ColorOutput("SUCCESS", Black, Green);
							maniprooms[i].request = patient.login;
							patient.status = 2;
							patients[patient.ID].status = 2;
							wards[patient.IDward]->EditStatusPatient(patient.ID, patient.status);
							break;
						}
						ColorOutput("THERE ARE NO AVAIBLE ROOMS", Black, Red);

					}
				}
				WriteInAllFile();

			}
		}

	}
}
void printfunctionMenuPatient(int pos) {
	SetConsoleCursorPosition(hStdOut, { 12,16 });
	if (pos != 0)
		cout << "EDIT NAME";
	else
		ColorOutput("EDIT NAME", Black, LightCyan);
	SetConsoleCursorPosition(hStdOut, { 12,18 });
	if (pos != 1)
		cout << "EDIT SECOND NAME";
	else
		ColorOutput("EDIT SECOND NAME", Black, LightCyan);
	SetConsoleCursorPosition(hStdOut, { 12,20 });
	if (pos != 2)
		cout << "REQUEST IN OPERATION ROOM";
	else
		ColorOutput("REQUEST IN OPERATION ROOM", Black, LightCyan);
	SetConsoleCursorPosition(hStdOut, { 12,22 });
	if (pos != 3)
		cout << "REQUEST IN MANIPULATIVE ROOM";
	else
		ColorOutput("REQUEST IN MANIPULATIVE ROOM", Black, LightCyan);
	SetConsoleCursorPosition(hStdOut, { 12,24 });
	if (pos != 4)
		cout << "BACK";
	else
		ColorOutput("BACK", Black, LightCyan);
	SetConsoleCursorPosition(hStdOut, { 12,26 });
	cout << "                                     ";


}
void printMenuPatient(int pos) {
	Patient patient = FindPat();
	SetConsoleCursorPosition(hStdOut, { 21,1 });
	cout << patient.Name;
	SetConsoleCursorPosition(hStdOut, { 21,3 });
	cout << patient.SecondName;
	SetConsoleCursorPosition(hStdOut, { 21,5 });
	cout << patient.illness;
	SetConsoleCursorPosition(hStdOut, { 24,7 });
	cout << FindDocById(patient.IDdoctor).SecondName;
	SetConsoleCursorPosition(hStdOut, { 21,9 });
	cout << patient.Cure;
	SetConsoleCursorPosition(hStdOut, { 21,11 });
	cout << patient.IDward;
	SetConsoleCursorPosition(hStdOut, { 21,13 });
	if (patient.status == 0)
		cout << "----";
	if (patient.status == 1)
		cout << "Waiting Request";
	if (patient.status == 2)
		cout << "Waiting Request";
	if (patient.status == 3)
		cout << "In Operation Room";
	if (patient.status == 4)
		cout << "In Manipulation";
	SetConsoleCursorPosition(hStdOut, { 0,16 });
	if (pos != 0)
		cout << "Settings";
	else
		ColorOutput("Settings", Black, LightCyan);
	SetConsoleCursorPosition(hStdOut, { 0,18 });
	if (pos != 1)
		cout << "Exit";
	else
		ColorOutput("Exit", Black, LightCyan);

}
void drawTablet() {
	system("cls");
	cout << "               ########                 " << endl;
	cout << "              ##      ##				 " << endl;
	cout << "              ##########                " << endl;
	cout << "     ############################		 " << endl;
	cout << " ###########               ########## 	 " << endl;
	cout << "##                                  ##	 " << endl;
	cout << "##                                  ##	 " << endl;
	cout << "##                                  ##	 " << endl;
	cout << "##                                  ##	 " << endl;
	cout << "##                                  ##	 " << endl;
	cout << "##                                  ##	 " << endl;
	cout << "##                                  ##	 " << endl;
	cout << "##                                  ##	 " << endl;
	cout << "##                                  ##	 " << endl;
	cout << "##                                  ##	 " << endl;
	cout << "##                                  ##	 " << endl;
	cout << "##                                  ##	 " << endl;
	cout << "##                                  ##	 " << endl;
	cout << "##                                  ##	 " << endl;
	cout << "##                                  ##	 " << endl;
	cout << "##                                  ##	 " << endl;
	cout << "##                                  ##	 " << endl;
	cout << "##                                  ##	 " << endl;
	cout << "##                                  ##	 " << endl;
	cout << " ####################################	 " << endl;
	SetConsoleCursorPosition(hStdOut, { 4,22 });
	cout << "Dr." << FindDocById(DelD(USERNAME)).SecondName;
}