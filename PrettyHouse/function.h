#pragma once
#include <conio.h>
#include <Windows.h>
#include <vector>
void drawTablet();
void drawfunctionfortablet(int, int);
void drawHospital();
string DelD(string);
int FindManipRoomByPatient(string);
int FindOpRoomByPatient(string);
int FindManipRoomByRequest(string);
int FindOpRoomByRequest(string);
void drowAuthoWindow();
int AuthoWindow();
void clearTablet();
Doctor FineDocById(string);
Patient FinedPat();
void EnterPanel(int);
void printPatientTabletIfDoctor(int);
void PatientTablet();
void funcEditTablet_Illness();
void funcEditTablet_Cure();
void funcEditTablet_delete();
void PatientTabletIfDoctor();
void printPatientsInTablet();
void EditTablet();
void InfoPanel(int);
void ReadAllFile();
void MenuPatient();
void adminPanel();
void WriteInAllFile();
void adminPanel_CreatPatient();
Patient* funcadminPanel_CreatePatient(Patient*, int);
string KeyBoardPrint(int x, int y);
Doctor ChooseDoctor();
void printChooseDoctor();
bool EnoughtFields(Patient);
bool EnoughtFields(Doctor);
void printadminPanel(int);
void printadminPanel_CreatePatient(Patient*, int);
void adminPanel_CreateDoctor();
void adminPanel_CreatLogin(string, string);
void printfunctionMenuPatient(int);
void printMenuPatient(int);
void functionMenuPatient();
void printMenuPatientTablet();
void funcEditTablet_SettingsRoom();
bool funcEditTablet_SettingsRoom_Accepting();
void printfuncEditTablet_SettingsRoom_Accepting(int);
void printfuncEditTablet_SettingsRoom(int);
void printadminPanel_CreateDoctor(Doctor*, int);
Doctor* funcadminPanel_CreateDoctor(Doctor*, int);
string Pass(string);
string CreatStringByVectChar(vector<char>);