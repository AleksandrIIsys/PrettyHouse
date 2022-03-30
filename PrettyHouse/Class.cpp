#include "Class.h"
int Ward::indexGEN = 1;
int IDX = 0;
list<Patient> temp;
ifstream& operator>>(ifstream& stream, Login& login) {
	stream >> login.ID >> login.Pass;
	return stream;
}
ifstream& operator>>(ifstream& stream, Patient& patient) {
	stream >> patient.login >> patient.IDward >> patient.Name >> patient.SecondName >> patient.illness >> patient.Cure >> patient.IDdoctor >> patient.status;
	patient.ID = IDX++;
	return stream;
}
ifstream& operator>>(ifstream& stream, Doctor& doctor) {
	stream >> doctor.Name >> doctor.SecondName >> doctor.ID;
	return stream;
}
ifstream& operator>>(ifstream& stream, ManipRoom& maniproom) {
	stream >> maniproom.idRoom >> maniproom.request >> maniproom.patient;
	return stream;
}
ifstream& operator>>(ifstream& stream, OpRoom& oproom) {
	stream >> oproom.idRoom >> oproom.request >> oproom.patient;
	return stream;
}
ofstream& operator<<(ofstream& stream, OpRoom& oproom) {
	stream << oproom.idRoom << " " << oproom.request << " " << oproom.patient;
	return stream;
}
ofstream& operator<<(ofstream& stream, ManipRoom& maniproom) {
	stream << maniproom.idRoom << " " << maniproom.request << " " << maniproom.patient;
	return stream;
}
ofstream& operator<<(ofstream& stream, Login& login) {
	stream << login.ID << " " << login.Pass;
	return stream;
}
ofstream& operator<<(ofstream& stream, Patient& patient) {
	stream << patient.login << " " << patient.IDward << " " << patient.Name << " " << patient.SecondName << " " << patient.illness << " " << patient.Cure << " " << patient.IDdoctor << " " << patient.status;
	return stream;
}
ofstream& operator<<(ofstream& stream, Doctor& doctor) {
	stream << doctor.Name << " " << doctor.SecondName << " " << doctor.ID;
	return stream;
}


Ward::Ward() {
	this->index = indexGEN++;
	this->Patients = new list<Patient>;
}
int Ward::getIndex() {
	return this->index;
}
Doctor::Doctor() {
	this->ID = "";
	this->Name = "";
	this->SecondName = "";
}
Patient::Patient() {
	this->status = 0;
	this->login = "";
	this->Name = "";
	this->SecondName = "";
	this->illness = "";
	this->Cure = "";
	this->IDward = -1;
	this->IDdoctor = "";
}
list<Patient> Ward::getPatients() {
	return *Patients;
}
void Ward::AddPatient(Patient patient) {
	Patients->push_back(patient);
}
Patient Ward::getPatientById(int id) {
	list<Patient>::iterator it = Patients->begin();
	for (; it != Patients->end(); it++) {
		if ((*it).ID == id) {
			return (*it);
		}
	}
}
void Patient::SetId() {
	this->ID = IDX++;
}
void Ward::EditNamePatient(int id, string name) {
	list<Patient>::iterator it = Patients->begin();
	for (; it != Patients->end(); it++) {
		if ((*it).ID == id) {
			(*it).Name = name;
		}
	}
}
void Ward::EditStatusPatient(int id, int status) {
	list<Patient>::iterator it = Patients->begin();
	for (; it != Patients->end(); it++) {
		if ((*it).ID == id) {
			(*it).status = status;
		}
	}
}
void Ward::EditSecondNamePatient(int id, string secondname) {
	list<Patient>::iterator it = Patients->begin();
	for (; it != Patients->end(); it++) {
		if ((*it).ID == id) {
			(*it).SecondName = secondname;
		}
	}
}
void Ward::EditIllnessPatient(int id, string illness) {
	list<Patient>::iterator it = Patients->begin();
	for (; it != Patients->end(); it++) {
		if ((*it).ID == id) {
			(*it).illness = illness;
		}
	}
}
void Ward::EditCurePatient(int id, string cure) {
	list<Patient>::iterator it = Patients->begin();
	for (; it != Patients->end(); it++) {
		if ((*it).ID == id) {
			(*it).Cure = cure;
		}
	}
}
void Ward::DeletePatient(int id) {
	list<Patient>::iterator it = Patients->begin();
	for (; it != Patients->end(); it++) {
		if ((*it).ID == id) {
			Patients->erase(it);
			IDX--;
			break;
		}
	}
}