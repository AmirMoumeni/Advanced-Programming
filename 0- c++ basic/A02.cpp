#include <iostream>
#include <string>
#include <vector>
#include <math.h>
using namespace std;
int Add (int a , int b){
    int answer;
    answer = a + b;
    return answer;
}
int Minuse (int a , int b){
    int answer;
    answer = a - b;
    return answer;
}
int Multiply (int a , int b){
    int answer;
    answer = a * b;
    return answer;
}
int Divide (int a , int b){
    int answer;
    answer = a / b;
    return floor(answer);
}
int Power (int a , int b){
    int answer =1;
    for (int i=0 ; i<b ; i++){
        answer = answer *a;
    }
    return answer;
}


int main() {
    //cout << "Hello Elahe !" ;
    int CalcNumber;
    vector<int> first(CalcNumber) , second(CalcNumber) , answer(CalcNumber);
    vector<char> operation(CalcNumber);    
    //cout << "\nEnter Number of Calculation : " ;
    cin >> CalcNumber;
    for (int i=0 ; i<CalcNumber ; i++){
        cin >> first[i] >> operation[i] >> second[i];
    }
    for (int i=0 ; i<CalcNumber ; i++){
        if (operation[i] == '+'){
            cout << Add(first[i] , second[i]) <<endl;
        }
        else if (operation[i] == '-'){
            cout << Minuse(first[i] , second[i]) <<endl;
        }
        else if (operation[i] == '*'){
            cout << Multiply(first[i] , second[i])<<endl;
        }
        else if (operation[i] == '/'){
            cout << Divide(first[i] , second[i])<<endl;
        }
        else if (operation[i] == '^'){
            cout << Power(first[i] , second[i])<<endl;
        }
        
    }
    
}
    