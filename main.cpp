#include<iostream>
#include "functions.cpp"
using namespace std;

int main()
{
    Clinic* heartClinic = new Clinic("Heart Clinic");
    Clinic* lungClinic = new Clinic("Lung Clinic");
    Clinic* plasticSurgery = new Clinic("Plastic Surgery");

    readDataFile(heartClinic, lungClinic, plasticSurgery);

    printMenu(heartClinic, lungClinic, plasticSurgery);
}
