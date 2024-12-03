#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <algorithm> 

using namespace std;
// const string parkingFileName = "Parking.csv";
// const string carsFileName = "Cars.csv";
// const string priceFileName = "Price.csv";
const string CMD_request_spot = "request_spot";
const string CMD_assign_spot = "assign_spot";
const string CMD_report_parking = "report_parking";
const string CMD_checkout = "checkout";
const string CMD_pass_time = "pass_time";
const string Covered = "covered";
const string CCTV = "CCTV";
const int coveredParkingOverPriceConst = 50;
const int CCTVParkingOverPriceConst = 80;
const int coveredParkingOverPriceDaily = 30;
const int CCTVParkingOverPriceDaily = 60;


struct parkingSlot {
    vector<string> id;
    vector<int> size;
    vector<string> type;
    vector<bool> free;
    vector<int> checkInTime;
};
struct car {
    vector<string> name;
    vector<int> size;
};
struct price {
    vector<int> size;
    vector<int> staticPrice;
    vector<int> pricePerDay;
};
parkingSlot readParkingsData(const string &parkingFileName) {
    ifstream file(parkingFileName);
    parkingSlot parking;
    string line;
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string item;
        
        getline(ss, item, ',');
        parking.id.push_back(item);
        
        getline(ss, item, ',');
        int size = stoi(item);
        parking.size.push_back(size);
        
        getline(ss, item, ',');
        parking.type.push_back(item);
        parking.free.push_back(true);
        parking.checkInTime.push_back(0);
        
    }
    
    file.close();
    return parking;
}
car readcarsData(const string &carsFileName) {
    ifstream file(carsFileName);
    car car;
    string line;
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string name;
        int size;
        
        getline(ss, name, ',');
        car.name.push_back(name);
        
        getline(ss, name, ',');
        size = stoi(name);
        car.size.push_back(size);
    }
    
    file.close();
    return car;
}
price readPriceData(const string &priceFileName) {
    ifstream file(priceFileName);
    price prices;
    string line;
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        int size;
        int staticPrice;
        int pricePerDay;
        
        getline(ss, line, ',');
        size = stoi(line);
        prices.size.push_back(size);
        
        getline(ss, line, ',');
        staticPrice = stoi(line);
        prices.staticPrice .push_back(staticPrice);

        getline(ss, line, ',');
        pricePerDay = stoi(line);
        prices.pricePerDay .push_back(pricePerDay);
    }
    
    file.close();
    return prices;
}
void printParkingData(parkingSlot parking , int time) {
    vector<pair<string, int>> parkingData; 

    for (int i = 0; i < parking.size.size(); ++i) {
        parkingData.push_back(make_pair(parking.id[i], i));
    }

    sort(parkingData.begin(), parkingData.end(), [](const auto &a, const auto &b) {
        return a.first < b.first;
    });

    cout << "------------------\n";
    cout << "Parking Data : Day " <<time<< "\n";
    for (const auto &item : parkingData) {
        int idx = item.second;
        cout << parking.id[idx] << " : " << parking.size[idx] << " " << parking.type[idx] << " :: "
             << (parking.free[idx] ? "Free" : ("Full Since " + to_string(parking.checkInTime[idx]))) << endl;
    }
}
double FindStringInVector(vector<string> vec , string str){
    for (int i=0 ; i<vec.size() ; i++){
        if(vec[i] == str){
            return i;
        }
    }
    return -1;
}
double FindIntInVector(vector<int> vec , int num){
    for (int i=0 ; i<vec.size() ; i++){
        if(vec[i] == num){
            return i;
        }
    }
    // vec = backup;

    return -1;
}
void requestSpot(const string &input, const parkingSlot &parking, const car &car, const price &price) {
    string carName = input.substr(input.find(' ') + 1);
    int carIndex = FindStringInVector(car.name, carName);
    if(carIndex != -1){
        int priceIndex = FindIntInVector(price.size, car.size[carIndex]);

    vector<pair<string, int>> parkingData;
    for (int i = 0; i < parking.id.size(); ++i) {
        if (parking.size[i] == car.size[carIndex] && parking.free[i]) {
            parkingData.push_back(make_pair(parking.id[i], i));
        }
    }

    sort(parkingData.begin(), parkingData.end(), [](const auto &a, const auto &b) {
        return a.first < b.first;
    });

    for (const auto &item : parkingData) {
        int idx = item.second;
        cout << parking.id[idx] << ": " << parking.type[idx] << " ";
        if (parking.type[idx] == Covered) {
            cout << price.staticPrice[priceIndex] + coveredParkingOverPriceConst << " "
                 << price.pricePerDay[priceIndex] + coveredParkingOverPriceDaily << endl;
        } else if (parking.type[idx] == CCTV) {
            cout << price.staticPrice[priceIndex] + CCTVParkingOverPriceConst << " "
                 << price.pricePerDay[priceIndex] + CCTVParkingOverPriceDaily << endl;
        } else {
            cout << price.staticPrice[priceIndex] << " "
                 << price.pricePerDay[priceIndex] << endl;
        }
    }
    }
    else {
        cout << "Car " << carName <<" not found\n";
    }
}
void assignSpot(const string &input, parkingSlot &parking , int entranceTime) {
    string id = input.substr(input.find(' ') + 1);
    int index = FindStringInVector(parking.id, id);
    if (index != -1) {
        if(parking.free[index] == true){
            parking.free[index] = false;
            parking.checkInTime[index] = entranceTime;
            cout << "Spot " << parking.id[index] << " is occupied now." << endl;
        }
        else{
            cout << "Spot "<< parking.id[index] <<" Already in Use\n";
        }
    } 
    else {
        cout << "Spot " << id << " not found." << endl;
    }
}
int costCalculator (parkingSlot parking , price pricelist, int now , int index){
    int totalCost , staticCost , perDayCost;
    int priceIndex = FindIntInVector(pricelist.size , parking.size[index]);
    
    if(parking.type[index] == Covered){
        staticCost = pricelist.staticPrice[priceIndex] + coveredParkingOverPriceConst;
        perDayCost = pricelist.pricePerDay[priceIndex] + coveredParkingOverPriceDaily;
    }
    else if (parking.type[index] == CCTV){
        staticCost = pricelist.staticPrice[priceIndex] + CCTVParkingOverPriceConst;
        perDayCost = pricelist.pricePerDay[priceIndex] + CCTVParkingOverPriceDaily;
    }
    else{
        staticCost = pricelist.staticPrice[priceIndex];
        perDayCost = pricelist.pricePerDay[priceIndex];
    }
    totalCost = staticCost + (now - parking.checkInTime[index])*perDayCost;
    return totalCost;
}
void checkout (string input , parkingSlot &parking , price pricelist , int now){
    int index = FindStringInVector(parking.id , input.substr(input.find(' ') +1));
    if (index!= -1){
        if(parking.free[index] == false){
        parking.free[index] = true;
        cout << "Spot " <<parking.id[index] << " is free now.\n"
         <<"Total cost: " << costCalculator(parking , pricelist , now , index) << endl;
    }
    else{
        cout << "Spot " <<parking.id[index] << " wasn't occupied.\n";
    }
    }
    else 
        cout << "Spot " <<input.substr(input.find(' ') +1) << " not found\n";
}
void passTime(string input ,int &today ){
    int passedTime = stoi(input.substr(input.find(' ') +1));
    today += passedTime;
}
int main(int argc ,char* argv[]) {
    int time=0;
    string input;
    parkingSlot parking = readParkingsData(argv[2]);
    car car = readcarsData(argv[1]);
    price price = readPriceData(argv[3]);
    while (getline(cin , input)){
        if (input.find(CMD_request_spot) ==0)
            requestSpot(input , parking , car , price);
        else if(input.find(CMD_assign_spot) == 0)
            assignSpot(input , parking , time);
        else if(input.find(CMD_report_parking) == 0)
            printParkingData(parking , time);  
        else if(input.find(CMD_checkout) == 0)
            checkout(input , parking , price , time);
        else if(input.find(CMD_pass_time) ==0)
            passTime(input , time);
        else
           cout <<"Command " <<input.substr(0 , input.find(' ')) <<" Invalid\n" ;
    }
}