#pragma once
#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<algorithm>
#include<vector>
#include<sstream>
#include<iomanip>
using namespace std;

struct Patient
{
    string firstName, lastName, SSN, status, type;

    Patient(string f, string l, string ss, string st, string t);
    Patient();
};

class Node
{
    public:
        Patient patient;
        Node * next;

        Node(Patient p);
        Node();
};

class Clinic
{
    private:
        int totalPatient;
        string name;
        Node * head ;
        Node * tail ;
        Node * txnHead ;
        Node * txnTail ;
    public:
        void addPatient();
        void addCriticalPatient();
        void listPatients();
        void printMenu();
        void cancelPatient();
        void operatePatient();
        void addPatientInQueue(Patient p);
        void addTransactionLog(Patient p);
        void printTransactionLog(ostream &output);
        void printTransactionType(string type, ostream &output);

        Clinic(string _name);

};

void readDataFile(Clinic * &heartClinic, Clinic * &lungClinic, Clinic * &plasticSurgery);
void printMenu(Clinic * &heartClinic, Clinic * &lungClinic, Clinic * &plasticSurgery);
void pressAnyKey();
