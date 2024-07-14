#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;



// Function to find the index of a given Car ID in a vector of rented cars
int FindIndex(vector<int> RentedCars, int CarID){
    vector<int>::iterator it;
    it = find(RentedCars.begin(), RentedCars.end(), CarID);
    if (it != RentedCars.end()) {
        return distance(RentedCars.begin(), it);
    }
    else{
        return -1;
    }
}


// Class definition for Car
class Car{
    public:
        int CarID;
        string Company;
        string Model;
        string PlateNo;
        int Condition;
        int Rent;
        int Availibility;
        string DueDate;

    public:
 

        Car(int CID=-1, string PNo="XX00XX0000", string comp="ABC", string mod="123", int cond=100, float r=2000, int avail=1, string due="00/00/0000"){
            CarID=CID;
            Company= comp;
            PlateNo=PNo;
            Model=mod;
            Condition=cond;
            Rent=r;
            Availibility=avail;
            DueDate=due;
           
        }

     
    float getRent(){
        return Rent;
        }
    string showDueDate(){
        return DueDate;
        }

};

// Function to append car details to the car database file
    void appendToCarDatabase(Car car) {

            ofstream carFile("car_database.txt", ios::app);//Append the existing one
 
        if (carFile.is_open()) {
        carFile << car.CarID << "," << car.PlateNo << "," << car.Company << "," << car.Model << "," << car.Condition << "," << car.Rent << "," << car.Availibility << "," << car.DueDate << "\n";

        carFile.close();
        }
        else {
            cout << "Unable to open car database file.\n";
        }
    } 
    
// Function to change car details to the car database file
    void ChangeCarDatabase(Car car) {

            ofstream carFile("car_database.txt");//Append the existing one
 
        if (carFile.is_open()) {
        carFile << car.CarID << "," << car.PlateNo << "," << car.Company << "," << car.Model << "," << car.Condition << "," << car.Rent << "," << car.Availibility << "," << car.DueDate << "\n";

        carFile.close();

        }
        else {
            cout << "Unable to open car database file.\n";
        }
    } 
    



// Function to read car details from the car database file
std::vector<Car> readCarDatabase() {
    std::vector<Car> cars;
    std::ifstream carFile("car_database.txt"); // Open the file in read mode
    if (carFile.is_open()) {
        std::string line;
        while (getline(carFile, line)) { // Read the file line by line
                if (line.empty()) {
                continue;
            }
            std::stringstream s(line);
            Car car;

            // Read each field from the line
            std::string field;
            getline(s, field, ',');
            car.CarID = std::stoi(field);
            getline(s, car.PlateNo, ',');
            getline(s, car.Company, ',');
            getline(s, car.Model, ',');
            getline(s, field, ',');
            car.Condition = std::stoi(field);
            getline(s, field, ',');
            car.Rent = std::stoi(field);
            getline(s, field, ',');
            car.Availibility = std::stoi(field);
            getline(s, car.DueDate, ',');

            cars.push_back(car); // Add the car to the vector
        }
        carFile.close();
    } else {
        std::cout << "Unable to open car database file.\n";
    }
    return cars;
} 

    
// Class definition for Customer
class Customer{
    public:
    string CustID;
    string Password;
    string Name;
    string PhoneNO;
    string address;
    vector<int> RentedCars;
    float RentDues;
    float FineDue;
    int CustomerRecord;

        // Constructor for Customer class
    public:


    Customer(string Id="NoID",string Pwd="NOTSET", string name="NULL", string phoneNO="NA", string addr="NA") {
        CustID = Id;
        Password=Pwd;
        Name = name;
        PhoneNO = phoneNO;
        address = addr;
        RentedCars = {};
        FineDue = 0;
        RentDues=0;
        CustomerRecord = 20;
    }

    void clearFineDues(){
        FineDue = 0;
    }
    void clearRentDues(){
        RentDues = 0;
    }
    void RentCar(Car& car  ){ //NEED TO CUSTOMISE IT ACCORDING TO CUSTOMER RECORD
        if(car.Availibility && 3*RentedCars.size()<=CustomerRecord){//check using vector size and customer record
            RentedCars.push_back(car.CarID);
            cout<<"Rent of the car- "<<car.Rent<<endl;
            cout<<"Final Dues of the car- "<<(car.Rent)<<endl;
            RentDues+=car.Rent;
            car.Availibility=0;
            cout<< "Successfully rented the Car."<<endl;
        }
        else if(!car.Availibility) {
            cout<<"Car is unavailable!"<<endl;
        }
        else   cout<<"Your customer record is not eligible for renting a car.\nPlease contact our office."<<endl;
    }

    void returnCar(Car& car, int delay, int newCondition){//update cutomer record too
        int damages=car.Condition-newCondition;
        cout<<"damages= "<<damages<<endl;
        car.Condition=newCondition;
        FineDue+= delay*2 + damages*4;
        cout<<"Total Fine Amount- "<<FineDue<<endl;
        car.Availibility=true;
        int index=FindIndex(RentedCars,car.CarID);
        RentedCars.erase(RentedCars.begin()+index);
        car.DueDate="00/00/0000";
    }

};
// Class definition for Employee
class Employee{
    public:
    string EmpID;
    string Password;
    string Name;
    string PhoneNO;
    string address;
    vector<int> RentedCars;
    float FineDue;
    int EmployeeRecord;

        // Constructor for Customer class
    public:
    Employee(string Id="NoID",string Pwd="NOTSET", string name="NULL", string phoneNO="NA", string addr="NA") {
        EmpID = Id;
        Password=Pwd;
        Name = name;
        PhoneNO = phoneNO;
        address = addr;
        RentedCars = {};
        FineDue = 0;
        EmployeeRecord = 20;
    }

    void RentCar(Car& car){//NEED TO CUSTOMISE IT ACCORDING TO Employee RECORD
        if(car.Availibility && 2*RentedCars.size()<=EmployeeRecord){//check using vector size and customer record
            RentedCars.push_back(car.CarID);
            cout<<"Rent of the car- "<<car.Rent<<endl;
            cout<<"Since you are an employee, you get 15 percent discount"<<endl;
            cout<<"Final Dues- "<<(0.85*car.Rent)<<endl;
            FineDue+=(0.85*car.Rent);
            car.Availibility=0;
            cout<< "Successfully rented the Car."<<endl;
        }
        else if(!car.Availibility) {
            cout<<"Car is unavailable!"<<endl;
        }
        else   cout<<"Your employee record is not eligible for renting a car.\nPlease contact our office."<<endl;
    }

    void returnCar(Car& car, int delay, int newCondition){
        int damages=car.Condition-newCondition;
        cout<<"damages= "<<damages<<endl;
        car.Condition=newCondition;
        FineDue+= delay*2 + damages*4;
        cout<<"Total Fine Amount- "<<FineDue<<endl;
        car.Availibility=1;
        int index=FindIndex(RentedCars,car.CarID);
        RentedCars.erase(RentedCars.begin()+index);
        car.DueDate="00/00/0000";
    }



};

int FindIndexbyCustomerID(vector<Customer> Details, string CID){
    for(int i=0 ;i< Details.size(); i++){
        if(CID.compare(Details[i].CustID)==0) return i;
    }
    return -1;
}
// Function to find the index of a given Employee ID in a vector of employees
int FindIndexbyEmployeeID(vector<Employee> Details, string CID){
    for(int i=0 ;i< Details.size(); i++){
        if(CID.compare(Details[i].EmpID)==0) return i;
    }
    return -1;
}
// Function to find the index of a given Car ID in a vector of cars
int FindIndexbyCarID(vector<Car> Details, int CIN){
    for(int i=0; i<Details.size(); i++){
        if(CIN == Details[i].CarID) return i;
    }
    return -1;
}





// Function to change customer data in the file
    void changeCustomerDataInFile(Customer cust) {
        ofstream file("customer_data.txt"); // Append mode
        if (!file.is_open()) {
            cout << "Error: Unable to open the file." << endl;
            return;
        }

        file << cust.CustID << ","
            << cust.Password<<","
            << cust.Name << ","
            << cust.PhoneNO << ","
            << cust.address << ","
            << cust.RentDues << ","
            << cust.FineDue << ","
            << cust.CustomerRecord << ",";

        // Writing rented car IDs
        for (int id : cust.RentedCars) {
            file << id << ";";
        }

        file << endl;

        file.close();
    }
    void writeCustomerDataToFile(Customer cust) {
        ofstream file("customer_data.txt", ios::app); // Append mode
        if (!file.is_open()) {
            cout << "Error: Unable to open the file." << endl;
            return;
        }

        file << cust.CustID << ","
            << cust.Password<<","
            << cust.Name << ","
            << cust.PhoneNO << ","
            << cust.address << ","
            << cust.RentDues << ","
            << cust.FineDue << ","
            << cust.CustomerRecord << ",";

        // Writing rented car IDs
        for (int id : cust.RentedCars) {
            file << id << ";";
        }

        file << endl;

        file.close();
    }
    // Function to read customer data from the file
    vector<Customer> readCustomerDatabase() {
        vector<Customer> customers;
        ifstream customerFile("customer_data.txt"); // Open the file in read mode

        if (customerFile.is_open()) {
            std::string line;
            while (getline(customerFile, line)) { // Read the file line by line
                if (line.empty()) {
                continue;
                }
                std::stringstream s(line);
                Customer customer;

                // Read each field from the line
                std::string field;
                getline(s, field, ',');
                customer.CustID = field;
                getline(s, customer.Password, ',');
                getline(s, customer.Name, ',');
                getline(s, customer.PhoneNO, ',');
                getline(s, customer.address, ',');
                getline(s, field, ',');
                customer.RentDues = std::stof(field);
                getline(s, field, ',');
                customer.FineDue = std::stof(field);
                getline(s, field, ',');
                customer.CustomerRecord = std::stoi(field);

                // Read rented car IDs
                while (getline(s, field, ';')) {
                    customer.RentedCars.push_back(std::stoi(field));
                }

                // Add the customer to the vector
                customers.push_back(customer);
            }
            customerFile.close();
        }
        else{
            cout << "Unable to open customer database file.\n";
        }

        return customers;
    }


// Function to change employee data in the file
    void ChangeEmployeeDataInFile(Employee emp) {
        ofstream file("employee_data.txt"); // Append mode
        if (!file.is_open()) {
            cout << "Error: Unable to open the file." << endl;
            return;
        }

        file << emp.EmpID << ","
            << emp.Password<<","
            << emp.Name << ","
            << emp.PhoneNO << ","
            << emp.address << ","
            << emp.FineDue << ","
            << emp.EmployeeRecord << ",";

        // Writing rented car IDs
        for (int id : emp.RentedCars) {
            file << id << ";";
        }

        file << endl;

        file.close();
    }
    void writeEmployeeDataToFile(Employee emp) {
        ofstream file("employee_data.txt", ios::app); // Append mode
        if (!file.is_open()) {
            cout << "Error: Unable to open the file." << endl;
            return;
        }

        file << emp.EmpID << ","
            << emp.Password<<","
            << emp.Name << ","
            << emp.PhoneNO << ","
            << emp.address << ","
            << emp.FineDue << ","
            << emp.EmployeeRecord << ",";

        // Writing rented car IDs
        for (int id : emp.RentedCars) {
            file << id << ";";
        }

        file << endl;

        file.close();
    }
     vector<Employee> readEmployeeDatabase() {
        vector<Employee> employee;
        ifstream employeeFile("employee_data.txt"); // Open the file in read mode

        if (employeeFile.is_open()) {
            std::string line;
            while (getline(employeeFile, line)) { // Read the file line by line
                if (line.empty()) {
                continue;
                }
                std::stringstream s(line);
                Employee emp;

                // Read each field from the line
                std::string field;
                getline(s, field, ',');
                emp.EmpID = field;
                getline(s, emp.Password, ',');
                getline(s, emp.Name, ',');
                getline(s, emp.PhoneNO, ',');
                getline(s, emp.address, ',');
                getline(s, field, ',');
                emp.FineDue = std::stof(field);
                getline(s, field, ',');
                emp.EmployeeRecord = std::stoi(field);

                // Read rented car IDs
                while (getline(s, field, ';')) {
                    emp.RentedCars.push_back(std::stoi(field));
                }

                // Add the customer to the vector
                employee.push_back(emp);
            }
            employeeFile.close();
        }
        else{
            std::cout << "Unable to open customer database file.\n";
        }

        return employee;
    }


void printAvailableCars(vector<Car> Details){
    int num=0;
    for(int i=0; i<Details.size();i++){
        if(Details[i].Availibility==1){
            num++;
            cout << "Car ID: " << Details[i].CarID << "\n";
            cout << "Company: " << Details[i].Company << "\n";
            cout << "Model: " << Details[i].Model << "\n";
            cout << "Plate Number.: " << Details[i].PlateNo << "\n";
            cout << "Condition: " << Details[i].Condition << "\n";
            cout << "Rent: " << Details[i].Rent << "\n";
            cout << "------------------------\n";            
        }
    }
    if(num==0)cout<<"Sorry, we don't have any Available Car at the moment. Please try again later."<<endl;
}


class Manager{
    public:
    string ManagerID;
    string Password;
    string Name;
    string PhoneNO;
    string address;

    Manager(string Id="NoID",string Pwd="NOTSET", string name="NULL", string phoneNO="NA", string addr="NA") {
        ManagerID = Id;
        Password=Pwd;
        Name = name;
        PhoneNO = phoneNO;
        address = addr;
    }
};




int main(){
    Manager Manager1=Manager("M1", "MPASS1","Manager1","9879879876","MADDRESS1");
    int inRentalSystem=1;
    vector<Car> CarDetails=readCarDatabase();
    vector<Customer> CustDetails=readCustomerDatabase();
    vector<Employee> EmpDetails=readEmployeeDatabase();
    while(inRentalSystem){
        cout<<"--------------------------------------------------------\n";
        cout << "Welcome to the Car Rental System\n";
        cout<<"--------------------------------------------------------\n";
        cout<<"Kindly select the appropriate options. \n";
        cout<<"0: Customer Login\n";
        cout<<"1: Employee Login\n";
        cout<<"2: Manager Login\n";
        cout<<"3: Exit the Car Rental system\n\n";
        cout<<"Enter your choice(0-3)- " ;
        int select;
        cin>>select;
        cin.ignore(); // Consume the newline character
        //EXIT THE SYSTEM
        if(select==3)inRentalSystem=0;

        //EMPLOYEE INTERFACE
        else if(select==0){
            cout<<"\nKindly enter your Customer ID-";
            string ID;
            getline(cin, ID);
            int index=FindIndexbyCustomerID(CustDetails, ID);
            if(index==-1){
                cout<<"You are not a registered User\n";
                }
            else{

                string pwd=CustDetails[index].Password;
                cout<<"Please Enter Your Password -";
                string inputpwd;
                getline(cin, inputpwd);
                if(pwd.compare(inputpwd)!=0)cout<<"Wrong Password! Please try again.\n";
                else{
                    int logged_in=1;
                    cout<<"\n\nWelcome "<<CustDetails[index].Name<<" to the Car Rental System\n";
                    while(logged_in){  
                        cout<<"What are you looking forward to do?- \n";
                        cout<<"1: View all available Cars.\n";
                        cout<<"2: View the cars which you are currently renting.\n";
                        cout<<"3: Rent a new Car.\n";
                        cout<<"4: View your details.\n";
                        cout<<"5: Log Out\n";
                        int option;
                        cin>>option;
                        //View all available Cars
                        if(option==1){
                            cout<<"Here are the details of all Available Cars-\n";
                            printAvailableCars(CarDetails);
                        }
                        //View your rented Cars
                        else if(option==2){
                            cout<<"Here are the cars which you are currently renting-\n";
                            vector<int> RC= CustDetails[index].RentedCars;
                            if(RC.size()==0)cout<<"You currently are not renting any car.\n";
                            else{
                                for(int i=0; i<RC.size(); i++){
                                    int TBF=RC[i];
                                    for(int j=0; j<CarDetails.size();j++){
                                        if(TBF==CarDetails[j].CarID){
                                            cout<<"CarID: "<<CarDetails[j].CarID<<endl;
                                            cout << "Company: " << CarDetails[i].Company << endl;
                                            cout << "Model: " << CarDetails[i].Model << endl;
                                            cout<<"PlateNo: "<<CarDetails[j].PlateNo<<endl;
                                            cout<<"----------------------------------------------------------\n";
                                        }
                                    }
                                }
                            }
                        }
                        //Rent a new Car
                        else if(option==3){
                            cout<<"Here are available cars-\n";
                            printAvailableCars(CarDetails);

                            int rentID;
                            cout<<"Enter the ID of the car you want to rented- ";
                            cin>>rentID;
                            int CarIndex=FindIndexbyCarID(CarDetails, rentID);
                            if(CarIndex==-1)cout<<"Enter a valid CarID!\n";
                            else if(CarDetails[CarIndex].Availibility!=1)cout<<"This Car is not Availible at the moment. Please try again later."<<endl;
                            else {cout<<CarIndex<<endl;
                                cout<<"Enter the due Date- (dd/mm/yyyy)- ";
                                string DD;
                                cin>>DD;
                                while(DD.length()!=10){
                                    cout<<"Enter a valid due date in the format dd/mm/yy- ";
                                    cin>>DD;
                                }
                                CustDetails[index].RentCar(CarDetails[CarIndex]);
                                CarDetails[CarIndex].DueDate=DD;
                            }
                        }
                        //View your Details
                        else if(option==4){
                            cout<<"Here are your details-\n";
                            cout << "Customer ID: " <<  CustDetails[index].CustID << "\n";
                            cout << "Name: " <<  CustDetails[index].Name << "\n";
                            cout << "Phone Number: " <<  CustDetails[index].PhoneNO << "\n";
                            cout << "Address: " <<  CustDetails[index].address << "\n";
                            cout << "Rent Dues: " <<  CustDetails[index].RentDues << "\n";
                            cout << "Fine Due: " <<  CustDetails[index].FineDue << "\n";
                            cout << "Customer Record: " <<  CustDetails[index].CustomerRecord << "\n";
                            cout << "Rented Cars: ";
                            for (int id :  CustDetails[index].RentedCars) {
                                cout << id << " ";
                                }
                        }
                        //Log OUT
                        else {
                            cout<<"Thank you for visiting Car Rental System\n";
                            logged_in=0;
                            if(CarDetails.size()>0){
                                ChangeCarDatabase(CarDetails[0]);
                                for(int i=1; i<CarDetails.size(); i++){
                                    appendToCarDatabase(CarDetails[i]);
                                }
                            }
                            if(CustDetails.size()>0){
                                changeCustomerDataInFile(CustDetails[0]);
                                for(int i=1; i<CustDetails.size(); i++){
                                    writeCustomerDataToFile(CustDetails[i]) ;
                                }
                            }
                        }                    
                    }
                }
            }
        }


//EMPLOYEE INTERFACE


        else if(select==1){
            cout<<"\nKindly enter your Employee ID-";
            string ID;
            getline(cin, ID);
            int index=FindIndexbyEmployeeID(EmpDetails, ID);
            if(index==-1){
                cout<<"This is not a valid Employee ID-\n";
            }
            else{
                string pwd=EmpDetails[index].Password;
                cout<<"Please Enter Your Password -";
                string inputpwd;
                getline(cin, inputpwd);
                if(pwd.compare(inputpwd)!=0)cout<<"Wrong Password! Please try again.\n";
                else{
                    int logged_in=1;
                    cout<<"\n\nWelcome "<<EmpDetails[index].Name<<" to the Car Rental System\n";
                    while(logged_in){
                        
                        cout<<"\nWhat are you looking forward to do?- \n";
                        cout<<"1: View all available Cars.\n";
                        cout<<"2: View the cars which you are currently renting.\n";
                        cout<<"3: Rent a new Car.\n";
                        cout<<"4: View your details.\n";
                        cout<<"5: Log Out\n";
                        int option;
                        cin>>option;
                       //View Available cars
                        if(option==1){
                            cout<<"Here are the details of all Available Cars-\n\n";
                            printAvailableCars(CarDetails);
                        }
                        //View cars which are currently being rented by the employee
                        else if(option==2){
                            cout<<"Here are the cars which you are currently renting-\n";
                            vector<int> RC= EmpDetails[index].RentedCars;
                            if(RC.size()==0)cout<<"You currently are not renting any car.\n";
                            else{
                                for(int i=0; i<RC.size(); i++){
                                    int TBF=RC[i];
                                    for(int j=0; j<CarDetails.size();j++){
                                        if(TBF==CarDetails[j].CarID){
                                            cout<<"CarID: "<<CarDetails[j].CarID<<endl;
                                            cout << "Company: " << CarDetails[i].Company << endl;
                                            cout << "Model: " << CarDetails[i].Model << endl;
                                            cout<<"PlateNo: "<<CarDetails[j].PlateNo<<endl;
                                            cout<<"----------------------------------------------------------\n";
                                        }
                                    }
                                }
                            }
                        }
                        //Rent a new car
                        else if(option==3){
                            cout<<"Here are available cars-\n";            
                            printAvailableCars(CarDetails);

                            int rentID;
                            cout<<"Enter the ID of the car you want to rented- ";
                            cin>>rentID;
                            int CarIndex=FindIndexbyCarID(CarDetails, rentID);
                            if(CarIndex==-1)cout<<"Enter a valid CarID!\n";
                            else if(CarDetails[CarIndex].Availibility!=1)cout<<"This Car is not Availible at the moment. Please try again later."<<endl;
                            else{cout<<CarIndex<<endl;
                                cout<<"Enter the due Date- (dd/mm/yyyy)- ";
                                string DD;
                                getline(cin, DD);
                                while(DD.length()!=10){
                                    cout<<"Enter a valid due date in the format dd/mm/yy- ";
                                    cin>>DD;
                                }
                                EmpDetails[index].RentCar(CarDetails[CarIndex]);
                                CarDetails[CarIndex].DueDate=DD;
                            }
                        }
                        //View Employee Details
                        else if(option==4){
                            cout<<"Here are your details-\n";
                            cout << "Employee ID: " <<  EmpDetails[index].EmpID << "\n";
                            cout << "Name: " <<  EmpDetails[index].Name << "\n";                      
                            cout << "Phone Number: " <<  EmpDetails[index].PhoneNO << "\n";
                            cout << "Address: " <<  EmpDetails[index].address << "\n";
                            cout << "Fine Due: " <<  EmpDetails[index].FineDue << "\n";
                            cout << "Customer Record: " <<  EmpDetails[index].EmployeeRecord << "\n";
                            cout << "Rented Cars: ";
                            for (int id :  EmpDetails[index].RentedCars) {
                                cout << id << " ";
                                }
                        }
                        //Log Out
                        else {
                            logged_in=0;
                            if(CarDetails.size()>0){
                                ChangeCarDatabase(CarDetails[0]);
                                for(int i=1; i<CarDetails.size(); i++){
                                    appendToCarDatabase(CarDetails[i]);
                                }
                            }
                            if(EmpDetails.size()>0){
                                ChangeEmployeeDataInFile(EmpDetails[0]);
                                for(int i=1; i<EmpDetails.size(); i++){
                                    writeEmployeeDataToFile(EmpDetails[i]) ;
                                }
                            }
                        }

                    }
                }

            }

        }


//MANAGER INTERFACE
        else if(select==2){
            cout<<"\nKindly enter your Manager ID-";
            string ID;
            getline(cin, ID);
            if(ID!=Manager1.ManagerID){
                cout<<"This is not a valid Manager ID-\n";
            }
            else{
                string pwd=Manager1.Password;
                cout<<"Please Enter Your Password -";
                string inputpwd;
                getline(cin, inputpwd);
                if(pwd.compare(inputpwd)!=0)cout<<"Wrong Password! Please try again.\n";
                else{
                    int logged_in=1;
                    cout<<"\n\nWelcome "<<Manager1.Name<<" to the Car Rental System\n\n";
                    cout<<"-----------------------------------------------------------------------------------------------\n";
                    while(logged_in){
                        cout<<"What are you looking forward to do?- \n";
                        cout<<"1: View all available Cars.\n";
                        cout<<"2: View the details of all cars which are being rented.\n";
                        cout<<"3: Update Employee Record.\n";
                        cout<<"4: Update Customer record.\n";
                        cout<<"5: Upadte Car inventory.\n";
                        cout<<"6: Log Out\n";
                        cout<<" Your Choice : ";
                        int option;
                        cin>>option;
                        if(option==1){
                            cout<<"Here are the details of all Available Cars-\n";
                            cout<<"----------------------------------------------------------------------\n";
                            printAvailableCars(CarDetails); 
                        }
                        else if(option==2){
                            cout<<"Here are the details of the cars being currently rented-\n";
                            cout<<"----------------------------------------------------------------------------\n\n\n";
                            cout<<"Cars rented by Customers- \n\n";
                            for(int i=0; i<CustDetails.size(); i++){
                                if(CustDetails[i].RentedCars.size()!=0){
                                    cout<<"=======================================================================================================\n";
                                    cout<<"Customer Name: "<<CustDetails[i].Name<<endl;
                                    cout<<"Customer Id: "<<CustDetails[i].CustID<<endl;
                                    cout<<"Customer Phone Number: "<<CustDetails[i].PhoneNO<<endl;                                   
                                    vector<int> RC= CustDetails[i].RentedCars;                               
                                    for(int i=0; i<RC.size(); i++){
                                        int TBF=RC[i];
                                        for(int j=0; j<CarDetails.size();j++){
                                            if(TBF==CarDetails[j].CarID){
                                                cout<<"CarID: "<<CarDetails[j].CarID<<endl;
                                                cout << "Company: " << CarDetails[i].Company << endl;
                                                cout << "Model: " << CarDetails[i].Model << endl;
                                                cout<<"PlateNo: "<<CarDetails[j].PlateNo<<endl;
                                                cout<<"Rent - "<<CarDetails[j].Rent<<endl;
                                                cout<<"Condition - "<<CarDetails[j].Condition<<endl;
                                                cout<<"----------------------------------------------------------\n";
                                            }
                                        }
                                    }    
                                }
                            }
                            cout<<"Cars rented by Employees- \n\n";
                            for(int i=0; i<EmpDetails.size(); i++){
                                if(EmpDetails[i].RentedCars.size()!=0){
                                    cout<<"========================================================================================================\n";
                                    cout<<"Employee Name: "<<EmpDetails[i].Name<<endl;
                                    cout<<"Employee Id: "<<EmpDetails[i].EmpID<<endl;
                                    cout<<"Employee Phone Number: "<<EmpDetails[i].PhoneNO<<endl;                                   
                                    vector<int> RC= EmpDetails[i].RentedCars;                               
                                    for(int i=0; i<RC.size(); i++){
                                        int TBF=RC[i];
                                        for(int j=0; j<CarDetails.size();j++){
                                            if(TBF==CarDetails[j].CarID){
                                                cout<<"CarID: "<<CarDetails[j].CarID<<endl;
                                                cout << "Company: " << CarDetails[i].Company << endl;
                                                cout << "Model: " << CarDetails[i].Model << endl;
                                                cout<<"PlateNo: "<<CarDetails[j].PlateNo<<endl;
                                                cout<<"Rent - "<<CarDetails[j].Rent<<endl;
                                                cout<<"Condition - "<<CarDetails[j].Condition<<endl;
                                                cout<<"----------------------------------------------------------\n";
                                            }
                                        }
                                    }    
                                }
                            }
                            cout<<endl;
                            cout<<endl;
                        }
                        //Update Employee Record
                        else if(option==3){
                                int inEmp=1;
                                while(inEmp){                                                  
                                    cout<<"Kindly select the appropriate option- \n";
                                    cout<<"1: Add an emplyoyee.\n";
                                    cout<<"2: Delete an employee.\n";
                                    cout<<"3: Clear dues of an employee.\n";
                                    cout<<"4: Return a car.\n";
                                    cout<<"5: Go Back.\n";
                                    cout<<"Enter you choice- ";
                                    int ch;
                                    cin>>ch;
                                    //Add an Employee
                                    if(ch==1){
                                        string EID, Pass, N, PNO,addr ;
                                        int notUnique=1;
                                        while(notUnique){  
                                        cout<<"Enter Employee ID- ";
                                        cin>>EID;
                                        //cin.ignore();
                                        if(FindIndexbyEmployeeID(EmpDetails, EID)!=-1){
                                            cout<<"This Employee ID is already taken."<<endl;
                                            }
                                        else notUnique=0;
                                        }
                                        cout<<"Enter defualt password- ";
                                        cin.ignore();
                                        getline(cin, Pass);                                                   
                                        cout<<"Enter Employee Name- ";
                                        getline(cin, N);
                                        cout<<"Enter Phone Number of the Employee- ";
                                        getline(cin, PNO);
                                        cout<<"Enter address of the Employee- ";
                                        getline(cin, addr);

                                        Employee newEmp(EID,Pass, N, PNO, addr);
                                        EmpDetails.push_back(newEmp);
                                        cout<<"New Employee Added."<<endl<<endl;
                                        cout<<"Details of new Employee-  "<<endl;
                                        Employee temp=EmpDetails[EmpDetails.size()-1];
                                        cout<<"-----------------------------------------------------------------\n";
                                        cout<<"Employee Id- "<<temp.EmpID<<endl;
                                        cout<<"Employee Name- "<<temp.Name<<endl;                                        
                                        cout<<"Employee PhoneNo.- "<<temp.PhoneNO<<endl;
                                        cout<<"Employee Address- "<<temp.address<<endl;
                                        cout<<"-----------------------------------------------------------------\n";
                                        cout<<"Employee Added successfuly!\n\n";
                                    }
                                    //Delete an employee.
                                    else if(ch==2){                             
                                        string EID;
                                        cout<<"Enter the Employee ID of the Employee to be deleted- ";
                                        cin.ignore();
                                        getline(cin, EID);  
                                        int index=FindIndexbyEmployeeID(EmpDetails, EID);
                                        if(index==-1){cout<<"Employee ID not found.\n";}
                                        else{
                                            vector<Employee>::iterator it = EmpDetails.begin() + index;
                                            EmpDetails.erase(it);
                                            cout<<"Details of the Employee has been deleted succesfully!\n"<<endl;
                                        }
                                    }
                                    //Clear dues of the Employee
                                    else if(ch==3){
                                        string EID;
                                        cout<<"Enter the Employee ID of the Employee- ";
                                        cin.ignore();
                                        getline(cin, EID);  
                                        int index=FindIndexbyEmployeeID(EmpDetails, EID);
                                        if(index==-1){cout<<"Employee ID not found.\n"<<endl;}
                                        else{
                                            EmpDetails[index].FineDue=0;
                                            cout<<"Dues of "<<EmpDetails[index].Name<<" cleared successfully!"<<endl;
                                        }
                                    }
                                    //Return a Car
                                    else if(ch==4){
                                        string EID;
                                        cout<<"Enter the Employee ID of the Employee- ";
                                        cin.ignore();
                                        getline(cin, EID);  
                                        int index=FindIndexbyEmployeeID(EmpDetails, EID);
                                        if(index==-1){cout<<"Employee ID not found.\n"<<endl;}
                                        else{
                                            cout<<"Here are the cars rented by the Employee-\n";
                                            vector<int> RC= EmpDetails[index].RentedCars;
                                            if(RC.size()==0)cout<<"Employee is currently not renting any car.\n"<<endl;
                                            else{
                                                for(int i=0; i<RC.size(); i++){
                                                    int TBF=RC[i];
                                                    for(int j=0; j<CarDetails.size();j++){
                                                        if(TBF==CarDetails[j].CarID){
                                                            cout<<"CarID: "<<CarDetails[j].CarID<<endl;
                                                            cout << "Company: " << CarDetails[i].Company << endl;
                                                            cout << "Model: " << CarDetails[i].Model << endl;
                                                            cout<<"PlateNo: "<<CarDetails[j].PlateNo<<endl;
                                                            cout<<"----------------------------------------------------------\n";
                                                        }
                                                    }
                                                }
                                            
                                                cout<<"\n\nEnter the Car ID of the car to be returned- ";
                                                int correct=0;
                                                int cid;
                                                while(!correct){
                                                    cin>>cid;
                                                    int i;
                                                    for (int i=0; i<RC.size(); i++){
                                                        if(RC[i]==cid){ 
                                                            correct=1;
                                                            break;
                                                        }
                                                    }
                                                    if(correct==0)cout<<"This car is not being rented by  this employee.\nPlease try again."<<endl;
                                                }   
                                                cout<<"Due Date of the Car- "<<CarDetails[cid].DueDate<<endl;
                                                cout<<"Enter the number days the car has been returned late- ";
                                                int delay;
                                                cin>>delay;
                                                cout<<"The previous condition of the car was- "<<CarDetails[cid].Condition<<endl;
                                                cout<<"Enter the new condition of the car - ";
                                                int nCond;
                                                cin>>nCond;
                                                EmpDetails[index].returnCar(CarDetails[cid], delay, nCond); 
                                                cout<<"Car returned Successfully!"<<endl;
                                                

                                            }

                                        }

                                        
                                    }
                                    else {
                                        inEmp=0;
                                    }
                                }
                            
                        }
                        else if(option==4){

                                int inCust=1;
                                while(inCust){                                                  
                                    cout<<"Kindly select the appropriate option- \n";
                                    cout<<"1: Add a Customer.\n";
                                    cout<<"2: Delete a Customer.\n";
                                    cout<<"3: Clear dues of a customer.\n";
                                    cout<<"4: Return a car by a customer.\n";
                                    cout<<"5: Go Back.\n";
                                    cout<<"Enter you choice- ";
                                    int ch;
                                    cin>>ch;
                                    if(ch==1){
                                        string CuID, Pass, N, PNO,addr;
                                        int notUnique=1;
                                        while(notUnique){  
                                        cout<<"Enter Employee ID- ";
                                        cin>>CuID;
                                        //cin.ignore();
                                        if(FindIndexbyEmployeeID(EmpDetails, CuID)!=-1){
                                            cout<<"This Employee ID is already taken."<<endl;
                                            }
                                        else notUnique=0;
                                        }
                                        cout<<"Enter defualt password- ";
                                        getline(cin, Pass);                                                   
                                        cout<<"Enter Customere Name- ";
                                        getline(cin, N);
                                        cout<<"Enter Phone Number of the Customer- ";
                                        getline(cin, PNO);
                                        cout<<"Enter address of the Customer- ";
                                        getline(cin, addr);

                                        Customer newCust(CuID,Pass, N, PNO, addr);
                                        CustDetails.push_back(newCust);
                                        cout<<"New Customer Added."<<endl;
                                        cout<<"Details of new Customer-  "<<endl;
                                        Customer temp=CustDetails[CustDetails.size()-1];
                                        cout<<"-----------------------------------------------------------------\n";
                                        cout<<"Customer Id- "<<temp.CustID<<endl;
                                        cout<<"Customer Name- "<<temp.Name<<endl;                                        
                                        cout<<"Customer PhoneNo.- "<<temp.PhoneNO<<endl;
                                        cout<<"Customer Address- "<<temp.address<<endl;
                                        cout<<"-----------------------------------------------------------------\n";
                                    }
                                    else if(ch==2){
                                        string CuID;
                                        cout<<"Enter the Customer ID of the Customer to be deleted- ";
                                        getline(cin, CuID);  
                                        int index=FindIndexbyCustomerID(CustDetails, CuID);
                                        if(index==-1){cout<<"Customer ID not found.\n";}
                                        else{
                                            vector<Customer>::iterator it = CustDetails.begin() + index;
                                            CustDetails.erase(it);
                                            cout<<"Details of the Customer has been deleted succesfully!";
                                        }
                                    }
                                    else if(ch==3){
                                        string CuID;
                                        cout<<"Enter the Employee ID of the Employee- ";         
                                        getline(cin, CuID);  
                                        int index=FindIndexbyCustomerID(CustDetails, CuID);
                                        if(index==-1){cout<<"Customer ID not found.\n";}
                                        else{
                                            CustDetails[index].FineDue=0;
                                            cout<<"Dues of "<<CustDetails[index].Name<<" cleared successfully!"<<endl;
                                        }
                                    }
                                    else if(ch==4){
                                        string CuID;
                                        cout<<"Enter the Customer ID of the Customer- ";
                                        getline(cin, CuID);  
                                        int index=FindIndexbyCustomerID(CustDetails, CuID);
                                        if(index==-1){cout<<"Customer ID not found.\n";}
                                        else{
                                            cout<<"Here are the cars rented by the Customer- \n\n";
                                            vector<int> RC= CustDetails[index].RentedCars;
                                            if(RC.size()==0)cout<<"Customer is currently not renting any car.\n";
                                            else{
                                                for(int i=0; i<RC.size(); i++){
                                                    int TBF=RC[i];
                                                    for(int j=0; j<CarDetails.size();j++){
                                                        if(TBF==CarDetails[j].CarID){
                                                            cout<<"CarID: "<<CarDetails[j].CarID<<endl;
                                                            cout << "Company: " << CarDetails[i].Company << endl;
                                                            cout << "Model: " << CarDetails[i].Model << endl;
                                                            cout<<"PlateNo: "<<CarDetails[j].PlateNo<<endl;
                                                            cout<<"----------------------------------------------------------\n";
                                                        }
                                                    }
                                                }
                                            }
                                            cout<<"\n\nEnter the Car ID of the car to be returned- ";
                                            int cid;
                                            cin>>cid;
                                            int CI=0;
                                            for(int CI=0; CI< RC.size(); CI++){
                                                if(CI==cid)break;
                                            }
                                            if(CI==RC.size())cout<<"Car is not rented by this Customer\n";
                                            else
                                            {
                                                cout<<"Due Date of the Car- "<<CarDetails[cid].DueDate<<endl;;
                                                cout<<"Enter the number days the car has been returned late- ";
                                                int delay;
                                                cin>>delay;
                                                cout<<"The previous condition of the car was- "<<CarDetails[cid].Condition<<endl;
                                                cout<<"Enter the new condition of the car - ";
                                                int nCond;
                                                cin>>nCond;
                                                CustDetails[index].returnCar(CarDetails[cid], delay, nCond);
                                                cout<<"Car returned Successfully!"<<endl;

                                            }

                                        }
                                       
                                    }
                                    else{
                                        inCust=0;
                                    }
                                }
                            
                        }
                        //UPDATE CAR INVENTORY
                        else if(option==5){
                                int inCarIn=1;
                                while(inCarIn){                                                 
                                    cout<<"Kindly select the appropriate option- \n";
                                    cout<<"1: Add a Car.\n";
                                    cout<<"2: Delete a Car.\n";
                                    cout<<"3: Update rent of a Car.\n";
                                    cout<<"4: Update Condition of a Car.\n";
                                    cout<<"5: Go Back.\n";
                                    cout<<"Enter you choice- ";
                                    int ch;
                                    cin>>ch;
                                    //Add a new car.
                                    if(ch==1){
                                        string PlateN, company, model;
                                        int CID, condition;
                                        float r;
                                        int notUnique=1;
                                        while(notUnique){       
                                        cout<<"Enter New Car ID- ";
                                        cin>>CID;
                                        if(FindIndexbyCarID(CarDetails, CID)!=-1){
                                            notUnique=0;
                                            cout<<"This Customer ID is already taken."<<endl;
                                            }
                                        }
                                        cout<<"Enter Plate Number of the Car- ";
                                        getline(cin, PlateN);                                                   
                                        cout<<"Enter Company Name of the car- ";
                                        getline(cin, company);
                                        cout<<"Enter Model Name of the car- ";
                                        getline(cin, model);
                                        cout<<"Enter Rent of the Car- ";
                                        cin>>r;
                                        cout<<"Enter curent Condition of the Car- ";
                                        cin>>condition;
                                        Car newCar(CID, PlateN, company, model, condition, r, 1, "00/00/0000");
                                        CarDetails.push_back(newCar);
                                        cout<<"New Car Added."<<endl;
                                        cout<<"Details of new Car-  "<<endl;
                                        Car temp=CarDetails[CarDetails.size()-1];
                                        cout<<"-----------------------------------------------------------------\n";
                                        cout<<"Car Id- "<<temp.CarID<<endl;
                                        cout<<"Car Company- "<<temp.Company<<endl;                                        
                                        cout<<"Car Model.- "<<temp.Model<<endl;
                                        cout<<"Car Rent- "<<temp.Rent<<endl;
                                        cout<<"Car Condition- "<<temp.Condition<<endl;
                                        cout<<"Car Due Date- "<<temp.DueDate<<endl;
                                        cout<<"-----------------------------------------------------------------\n";
                                    }
                                    //Delete a Car
                                    else if(ch==2){
                                        int CarID;
                                        cout<<"Enter the Car ID of the Car to be deleted- ";
                                        cin>>CarID;  
                                        int index=FindIndexbyCarID(CarDetails, CarID);
                                        if(index==-1){cout<<"Car ID not found.\n";}
                                        else{
                                            vector<Car>::iterator it = CarDetails.begin() + index;
                                            CarDetails.erase(it);
                                            cout<<"Details of the Car has been deleted succesfully!";
                                        }
                                    }
                                    //Update rent of a car.
                                    else if(ch==3){
                                        int CarID;
                                        cout<<"Enter the Car ID of the Car to be deleted- ";
                                        cin>>CarID;  
                                        int index=FindIndexbyCarID(CarDetails, CarID);
                                        if(index==-1){cout<<"Car ID not found.\n";}
                                        else{
                                            cout<<"Current rent of the car= "<<CarDetails[index].Rent<<endl;
                                            float newRent;
                                            cout<<"Enter new Rent- ";
                                            cin>>newRent;
                                            CarDetails[index].Rent=newRent;
                                            cout<<"Rent updated successfully!\n";
                                            
                                        }
                                    }
                                    //Update Condition of a Car.
                                    else if(ch==4){
                                        int CarID;
                                        cout<<"Enter the Car ID of the Car to be deleted- ";
                                        cin>>CarID;  
                                        int index=FindIndexbyCarID(CarDetails, CarID);
                                        if(index==-1){cout<<"Car ID not found.\n";}
                                        else{
                                            cout<<"Current condition of the car= "<<CarDetails[index].Rent<<endl;
                                            int newCond;
                                            cout<<"Enter new Condition of the car- ";
                                            cin>>newCond;
                                            CarDetails[index].Condition=newCond;
                                            cout<<"Condition of the car updated successfully!\n";
                                        }
                                       
                                    }
                                    else{
                                        inCarIn=0;
                                    }
                                }
                                                     
                        }
                        //Log Out of the system
                        else {
                            cout<<"Thank you for using Car Rental System."<<endl;
                            logged_in=0;
                            if(CarDetails.size()>0){
                                ChangeCarDatabase(CarDetails[0]);
                                for(int i=1; i<CarDetails.size(); i++){
                                    appendToCarDatabase(CarDetails[i]);
                                }
                            }
                            if(EmpDetails.size()>0){
                                ChangeEmployeeDataInFile(EmpDetails[0]);
                                for(int i=1; i<EmpDetails.size(); i++){
                                    writeEmployeeDataToFile(EmpDetails[i]) ;
                                }
                            }
                        }
                    }
                }
            }     

        }
    }
}

