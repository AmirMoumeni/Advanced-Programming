#include <iostream>
#include <string>
using namespace std;

// int detectCapitalLetters(const string& input) {
//     for (char c : input) {
//         if (isupper(c)) {
//             return 1; // Return 1 if a capital letter is found
//         }
//     }
//     return 0; // Return 0 if no capital letter is found
// }

int main() {
//cout << "Hello Shahriar" <<endl ;
//cout << "Please enter the URL (50 Characters Max) (only lowercase) : " <<endl ;
string input;
cin >> input;
string Username = input.substr(5 , (input.find("github") - 5));
string Context = input.substr( (input.find("githubio") +8 ) , (input.find("query") - ((input.find("githubio") +8 ) )) );
string Idontknow;
if (input.find("query") == string::npos){
    Idontknow ="";
}
else {
    Idontknow= input.substr(input.find("query") +5 );
}
// while ((input.length() > 50) || (Username.length() == 0) || (Context.length() == 0) ||  detectCapitalLetters(input) == 1) {
//     cin >> input ;
//     Username = input.substr(5 , (input.find("github") - 5));
//     Context = input.substr( (input.find("githubio") +8 ) , (input.find("query") - ((input.find("githubio") +8 ) )) );
//     Idontknow = input.substr(input.find("query") +5 );
// if (input.length() > 50) {
//         cout << "Error ... Max 50 Characters Allowed ...  : " <<endl << input.length() << " Letter Used ... TRY AGAIN\n";
//     }
//     else if (Username.length() == 0){
//         cout << "Error ... Username can't be empty ... TRY AGAIN : " <<endl ;
//     }
//     else if (Context.length() == 0){
//         cout << "Error ... Context can't be empty ... TRY AGAIN : " <<endl ;
//     }
//     else {
//         cout << "Error ... Capital letters not allowed  ... TRY AGAIN : " <<endl ;
//     }
// }
//cout << "Correct! " <<endl ;
//cout << input.find("query") ;
//cout << "Context : " << Context <<endl;
//cout << "Username : " << Username << endl ;
//cout << "Idontknow : " <<Idontknow << endl;
if (Idontknow.length() == 0){
    cout << "https://" << Username << ".github.io/" << Context;
}
else {
    cout << "https://" << Username << ".github.io/" << Context << "/query=" <<Idontknow;
}
}

