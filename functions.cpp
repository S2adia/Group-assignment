#include "functions.h"

Clinic :: Clinic (string _name)
{
    name = _name;
    totalPatient = 0;
    head = nullptr;
    tail = nullptr;
    txnHead = nullptr;
    txnTail = nullptr;
}

Node :: Node(Patient p)
{
    patient = p;
    next = nullptr;
}

Node :: Node()
{
    next = nullptr;
}

Patient :: Patient(string f, string l, string ss, string st, string t)
{
    firstName = f;
    lastName = l;
    SSN = ss;
    status = st;
    type = t;
}

Patient :: Patient()
{
}

//Add a regular patient
void Clinic:: addPatient()
{
    system("clear");
    string fName, lName, ssn;
    cout<<"Add Patient"<<endl;
    if(totalPatient == 10)
    {
        cout<<"Already 10 members in the queue. Please wait."<<endl;
        return;
    }
    cout<<"Enter first name: ";
    cin>>fName;
    cout<<"Enter last name: ";
    cin>>lName;
    cout<<"Enter social security number: ";
    getchar();
    getline(cin,ssn);
    if(ssn == "")
    {
        cout<<"Error: Social Security Number is empty."<<endl;
        return;
    }

    Patient p(fName,lName, ssn, "regular", "added");
    addPatientInQueue(p);
    cout<<"Patient added: "<<fName<<" "<<lName<<", "<<ssn<<endl;
}

// Add a critically ill patient
void Clinic:: addCriticalPatient()
{
    system("clear");
    string fName, lName, ssn;
    cout<<"Add Critically Ill Patient"<<endl;
    if(totalPatient == 10)
    {
        cout<<"Already 10 members in the queue. Please wait."<<endl;
        return;
    }
    cout<<"Enter first name: ";
    cin>>fName;
    cout<<"Enter last name: ";
    cin>>lName;
    cout<<"Enter social security number: ";
    getchar();
    getline(cin,ssn);
    if(ssn == "")
    {
        cout<<"Error: Social Security Number is empty."<<endl;
        return;
    }

    Patient p(fName,lName, ssn, "critical","added");
    addPatientInQueue(p);
    cout<<"Patient added: "<<fName<<" "<<lName<<", "<<ssn<<endl;
}

//Print clinic menu
void Clinic :: printMenu()
{
    menu2:
    system("clear");
    cout<<"Welcome to the "<<name<<endl;;

    cout<<"1: - Add Patient"<<endl;
    cout<<"2: - Add Critical Patient"<<endl;
    cout<<"3: - Take out Patient for Operation"<<endl;
    cout<<"4: - Cancel Patient"<<endl;
    cout<<"5: - List Patients in queue"<<endl;
    cout<<"6: - Change Department or exit"<<endl;
    cout<<"Enter your choice: ";
    int option;
    cin>>option;
    if(option==1)
    {
        addPatient();
        pressAnyKey();
        goto menu2;
    }
    else if(option==2)
    {
        addCriticalPatient();
        pressAnyKey();
        goto menu2;
    }
    else if(option==3)
    {
        operatePatient();
        cin.ignore();
        pressAnyKey();
        goto menu2;
    }
    else if(option==4)
    {
        cancelPatient();
        cin.ignore();
        pressAnyKey();
        goto menu2;
    }
    else if(option==5)
    {
        listPatients();
        cin.ignore();
        pressAnyKey();
        goto menu2;
    }
    else if(option==6)
    {
        system("clear");  // clear the console screen
        return;
    }
    else
    {
        cout<<"Invalid option. Please try again."<<endl; // showing a warning message for invalid option
        cin.ignore();
        pressAnyKey();
        goto menu2;
    }
}

//Print all patients in the queue
void Clinic :: listPatients()
{
    system("clear");  // clear the console screen
    cout<<"Patient in the "<<name<<":"<<endl;
    if(totalPatient == 0)
    {
        cout<<"No patient found."<<endl;
        return;
    }
    cout<<setw(15)<<left<<"First Name"<<setw(15)<<left<<"Last Name"<<setw(8)<<left<<"SSN"<<"Status"<<endl;
    Node * cur = head;
    while(cur!= nullptr)
    {
        cout<<setw(15)<<left<<cur->patient.firstName<<setw(15)<<left<<cur->patient.lastName<<setw(8)<<left<<cur->patient.SSN<<cur->patient.status<<endl;
        cur = cur->next;
    }
}

//Cancel a patient
void Clinic :: cancelPatient()
{
    system("clear");  // clear the console screen
    cout<<"Enter the SSN number of patient: ";
    string ssn;
    cin>>ssn;

    if(totalPatient == 0)
    {
        cout<<"Patient Does Not Exist."<<endl;
        return;
    }

    Node * cur = head;
    Node * prev;
    if(head->patient.SSN== ssn)
    {
        head = cur->next;
        cout<<"Patient: "<<cur->patient.firstName<<" "<<cur->patient.lastName<<" has been canceled."<<endl;
        cur->patient.type = "canceled";
        addTransactionLog(cur->patient);
        delete(cur);
        totalPatient--;
        return;
    }
    while(cur!= nullptr)
    {
        if(cur->patient.SSN == ssn)
        {
            break;
        }
        prev = cur;
        cur = cur-> next;
    }
    if(cur == nullptr)
    {
        cout<<"Patient Does Not Exist."<<endl;
    }
    else
    {
        prev-> next = cur->next;
        cout<<"Patient "<<cur->patient.firstName<<" "<<cur->patient.lastName<<" has been canceled."<<endl;
        cur->patient.type = "canceled";
        addTransactionLog(cur->patient);
        delete(cur);
        totalPatient--;
    }
}

//Take a patient to operation
void Clinic:: operatePatient()
{
    system("clear");  // clear the console screen
    if(totalPatient == 0)
    {
        cout<<"No more patients."<<endl;
    }
    else
    {
        Node * cur = head;
        head = cur->next;
        cout<<"Patient: "<<cur->patient.firstName<<" "<<cur->patient.lastName<<" taken for operation."<<endl;
        cur->patient.type = "operation";
        addTransactionLog(cur->patient);
        delete(cur);
        totalPatient--;
    }
}


//a common function to add any type of patient in queue
void Clinic :: addPatientInQueue(Patient p)
{
    Node * node  = new Node(p);
    if(head == nullptr)
    {
        head = node;
        tail = node;
    }
    else
    {
        if(p.status == "regular")
        {
            tail->next = node;
            tail = node;
        }
        else if(p.status == "critical")
        {
            if(head->patient.status == "regular")
            {
                node->next = head;
                head = node;
            }
            else if(tail->patient.status == "critical")
            {
                tail->next = node;
                tail = node;
            }
            else
            {
                Node * cur = head;
                Node * prev = nullptr;
                while(cur->patient.status == "critical")
                {
                    prev = cur;
                    cur= cur->next;
                }
                prev->next = node;
                node->next = cur;
            }
        }
    }
    totalPatient++;
    addTransactionLog(p);
}

// a common function to add transaction log
void Clinic :: addTransactionLog(Patient p)
{
    Node * cur = new Node(p);
    if(txnHead == nullptr)
    {
        txnHead = cur;
        txnTail = cur;
    }
    else
    {
        txnTail->next = cur;
        txnTail = cur;
    }
}

//print transaction log patient list
void Clinic :: printTransactionType(string type, ostream &output)
{
    output<<setw(15)<<left<<"First Name"<<setw(15)<<left<<"Last Name"<<setw(8)<<left<<"SSN"<<"Status"<<endl;
    Node * cur = txnHead;
    while(cur!= nullptr)
    {
        if(cur->patient.type == type)
            output<<setw(15)<<left<<cur->patient.firstName<<setw(15)<<left<<cur->patient.lastName<<setw(8)<<left<<cur->patient.SSN<<cur->patient.status<<endl;
        cur = cur->next;
    }
}

//print transaction log
void Clinic :: printTransactionLog(ostream &output)
{
    output<<endl<<endl<<"----------"<<name<<"----------"<<endl;

    output<<endl<<endl<<"The following patients are added at the beginning of the day:"<<endl;
    printTransactionType("beginning",output);

    output<<endl<<endl<<"The following patients are added throughout the day:"<<endl;
    printTransactionType("added",output);

    output<<endl<<endl<<"The following patients are canceled throughout the day:"<<endl;
    printTransactionType("canceled",output);

    output<<endl<<endl<<"The following patients are taken for operation throughout the day:"<<endl;
    printTransactionType("operation",output);

    if(totalPatient > 0)
    {
        output<<endl<<endl<<"The following patients must be rescheduled:"<<endl;
        output<<setw(15)<<left<<"First Name"<<setw(15)<<left<<"Last Name"<<setw(8)<<left<<"SSN"<<"Status"<<endl;
        Node * cur = head;
        while(cur!= nullptr)
        {
            output<<setw(15)<<left<<cur->patient.firstName<<setw(15)<<left<<cur->patient.lastName<<setw(8)<<left<<cur->patient.SSN<<cur->patient.status<<endl;
            cur = cur->next;
        }
    }
}

//Read data from patient.csv file at the beginning of the day
void readDataFile(Clinic * &heartClinic, Clinic * &lungClinic, Clinic * &plasticSurgery)
{
    try
    {
        ifstream file;
        file.open("patient.csv");
        if(!file.is_open())
        {
            char msg[]="Patient.csv file doesn't exist....";
            throw msg;
        }
        string line;
        while(file>>line)
        {
            line.erase( std::remove(line.begin(), line.end(), '\r'), line.end() );
            stringstream ss(line);
            vector<string> row;

            while(ss.good() )
            {
                string str;
                getline(ss, str, ',');
                row.push_back(str);
            }

            Patient p(row[1],row[2],row[3],"regular","beginning");
            if(row[0] == "HC")
            {
                heartClinic->addPatientInQueue(p);
            }
            else if(row[0] == "LC")
            {
                lungClinic->addPatientInQueue(p);
            }
            else if(row[0] == "PS")
            {
                plasticSurgery->addPatientInQueue(p);
            }
        }
    }
    catch(char * msg)
    {
        cout<<msg<<endl;
    }
    catch(...)
    {
        ;
    }
}

//print hospital menu
void printMenu(Clinic * &heartClinic, Clinic * &lungClinic, Clinic * &plasticSurgery)
{
    ofstream output;
    output.open("output.txt");
    menu1:
    cout<<"   WELCOME TO RESEARCH HOSPITAL"<<endl;
    cout<<"1:  Heart Clinic"<<endl;
    cout<<"2:  Lung Clinic"<<endl;
    cout<<"3:  Plastic Surgery"<<endl;
    cout<<"4:  Quit"<<endl;
    cout<<"Please enter the clinic of interest: ";
    int option;
    cin>>option;
    if(option == 1)
    {
        heartClinic->printMenu();
        goto menu1;
    }
    else if(option==2)
    {
        lungClinic->printMenu();
        goto menu1;
    }
    else if(option==3)
    {
        plasticSurgery->printMenu();
        goto menu1;
    }
    else if(option==4)
    {
        output<<"###############Transaction Logs###############"<<endl;
        heartClinic->printTransactionLog(output);
        lungClinic->printTransactionLog(output);
        plasticSurgery->printTransactionLog(output);
    }
    else
    {
        system("clear");  // clear the console screen
        cout<<"Invalid option. Please try again."<<endl; // showing a warning message for invalid option
        goto menu1;
    }
}

//a common function to back to menu again
void pressAnyKey()
{
    cout<<"Press enter key to return menu."<<endl;
    string ch;
    getline(cin,ch);
}


