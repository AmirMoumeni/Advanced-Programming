#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
const string new_category = "new_category";
const string add_expence = "add_expence";
const string remove_expence = "remove_expence";
const string report = "report";
const int zero =0;
const int one =1;
const int two =2;
const int three =3;
const int four =4;
struct Data 
    {
        string category_name;
        vector<string> Sub_category_names;
        vector<int> expence;

    };
Data D1;
vector<Data> Data_structure; 
vector<string> Categories;
string OperationIdentify(string in)
    {
    string Operation = in.substr(0 , in.find(' '));
    return Operation;
}
double OperationEncoder(string in){
    if(in==new_category){
        return 1;
    }
    else if(in==add_expence){
        return 2;
    }
    else if(in==remove_expence){
        return 3;
    }
    else if(in==report){
        return 4;
    }
    else
    return 0;
}
void CategoryAdder(string str) {
    stringstream ss(str);
    string s;
    vector<string> temp;
    while (getline(ss , s , ' ')){
        temp.push_back(s);
    }
    for(int i=1 ; i<temp.size() ; i++){
        if(i == 1){
            D1.category_name = temp[i];
            Categories.push_back(temp[i]);
            D1.expence.push_back(zero);
        }
        else{
        D1.Sub_category_names.push_back(temp[i]);
        D1.expence.push_back(zero);
        }
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
void ExpenceRemover(int Expence , string str){
    int first_space;
    for(int i=0 ; i<str.length(); i++){
        if(str[i] == ' '){
            first_space = i+1;
        }
    }
    string check_cat = str.substr(first_space, (str.find('/') -first_space));
    string check_sub = str.substr(str.find('/')+1 );
    int a = FindStringInVector(Categories , check_cat);
    int b = FindStringInVector(Data_structure[a].Sub_category_names , check_sub);
    Data_structure[a].expence[b] = Expence;
    }
void ExpenceAdder(int Expence , string str){
    int first_space , second_space;
    for(int i=0 ; i<str.find('/'); i++){
        if(str[i] == ' '){
            first_space = i+1;
        }
    }
    for (int i = str.find('/') ; i<str.length() ; i++){
        if(str[i] == ' '){
            second_space = i-1;
        }
    }
    string check_cat = str.substr(first_space, (str.find('/') -first_space));
    string check_sub = str.substr(str.find('/')+1 , (second_space - (str.find('/'))));
    int a = FindStringInVector(Categories , check_cat);
    int b = FindStringInVector(Data_structure[a].Sub_category_names , check_sub);
    Data_structure[a].expence[b] = Expence;
    }
int SumOfExpence(vector<int> vec){
        int sum =0;
        for(int i =0 ; i<vec.size() ; i++){
            sum += vec[i];
        }
        return sum;
    }
void Report (int threshold){
    for(int i =0 ; i< Data_structure.size() ; i++){
            cout << "Category : " <<Data_structure[i].category_name << endl
                 << "Total Expenses : " << SumOfExpence(Data_structure[i].expence) <<endl
                 <<"Subcategories Expences :" << endl;
                 for(int j =0 ; j<Data_structure[i].Sub_category_names.size() ; j++){
                    if(Data_structure[i].expence[j] > threshold){
                        cout << "    - " << Data_structure[i].Sub_category_names[j] << " : " << Data_structure[i].expence[j] <<endl;
                    }
                 }
            if (i == Data_structure.size() -1){
                cout << "**********\n" ;
            }
            else{
                cout << "----------\n" ;
            }
        }

}
double ExpenceValue(string str){
    int loc;
    for(int i = str.find('/') ; i<str.length() ; i++){
        if(str[i] == ' '){
            loc =i+1;
        }
    }
    string Num = str.substr(loc);
    double num = stoi(Num);
    return num;
}
int Threshold(string str){
    int threshold=0 ;
    if (str.length() > 7){
        threshold = stoi (str.substr(7));
    }
    return threshold;
}
void SortedReport (int threshold){
    vector <string> sorted_category = Categories;
    auto Category_first = sorted_category.begin();
    auto Category_last = sorted_category.end();
    sort(Category_first , Category_last);
    for(int i =0 ; i< Data_structure.size() ; i++){
            map<string, int> myMap;
            for (size_t j = 0; j < Data_structure[i].Sub_category_names.size(); ++j) {
                myMap[Data_structure[i].Sub_category_names[j]] = Data_structure[i].expence[j];
            }
            vector<pair<string, int>> sortedMap(myMap.begin(), myMap.end());
            
            int index = FindStringInVector(Categories , sorted_category[i]);
            cout << "Category: " <<Data_structure[index].category_name << endl
                 << "Total Expenses: " << SumOfExpence(Data_structure[index].expence) <<endl
                 <<"Subcategories Expences: " << endl;
                 sort(sortedMap.begin(), sortedMap.end(), [](const auto &a, const auto &b) {
                 if (a.second == b.second) {
                    return a.first < b.first;
                 }
                 return a.second > b.second; 
                 });

                 for(auto pair : sortedMap){
                    if(pair.second >= threshold){
                    cout << "    - " << pair.first << ": " << pair.second <<endl;
                    }
                 }
                 if (i == Data_structure.size() -1){
                cout << "**********\n" ;
            }
            else{
                cout << "----------\n" ;
            }
        }

}
void TakeAction(string INPUT){
    if (OperationEncoder(OperationIdentify(INPUT)) == one){
        CategoryAdder(INPUT);
        Data_structure.push_back(D1);
        D1={};
    }
    else if(OperationEncoder(OperationIdentify(INPUT)) == two){
        ExpenceAdder(ExpenceValue(INPUT) , INPUT);
    }
    else if(OperationEncoder(OperationIdentify(INPUT)) == three){
        ExpenceRemover(zero ,INPUT);
    }
    else if (OperationEncoder(OperationIdentify(INPUT)) == four){
        SortedReport(Threshold(INPUT));
}
    
    else{
        cout << "Invalid Command "<< OperationIdentify(INPUT) <<endl;
    }
}
int main(){
    string INPUT;
    while (getline(cin , INPUT)){ 
        TakeAction(INPUT);
    }
}