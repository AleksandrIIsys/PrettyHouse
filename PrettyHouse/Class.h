#pragma once
#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <cstring>
#include <map>
#include <iterator>
using namespace std;
struct Login {
	string ID;
	string Pass;
	friend ifstream& operator>>(ifstream& stream, Login& login);
	friend ofstream& operator<<(ofstream&, Login&);

};
struct Patient 
{
	string login;
	int ID;
	string Name;
	string SecondName;
	string illness;
	string Cure;
	string IDdoctor;
	int IDward;
	int status;		// 0 - nothing 1 - request to oproom 2 - request maniproom 3 - in oproom 4 - in maniproom
	friend ifstream& operator>>(ifstream& stream, Patient& patient);
	friend ofstream& operator<<(ofstream&, Patient&);

	Patient();
	void SetId();
};
struct Doctor {
	string Name;
	string SecondName;
	string ID;
	friend ifstream& operator>>(ifstream& stream, Doctor& doctor);
	Doctor();
	friend ofstream& operator<<(ofstream&, Doctor&);
};
class Ward {
	list<Patient>* Patients;
	static int indexGEN;
	int index;
public:
	Ward();
	int getIndex();
	list<Patient> getPatients();
	void AddPatient(Patient);
	void EditIllnessPatient(int,string);
	void EditCurePatient(int, string);
	Patient getPatientById(int);
	void DeletePatient(int);
	void EditNamePatient(int, string);
	void EditSecondNamePatient(int, string);
	void EditStatusPatient(int, int );
};

struct OpRoom
{
	int idRoom;
	string request;
	string patient;
	friend ifstream& operator>>(ifstream& stream, OpRoom& oproom);
	friend ofstream& operator<<(ofstream&, OpRoom&);
};
struct  ManipRoom
{
	int idRoom;
	string request;
	string patient;
	friend ifstream& operator>>(ifstream& stream, ManipRoom& maniroom);
	friend ofstream& operator<<(ofstream&, ManipRoom&);

};