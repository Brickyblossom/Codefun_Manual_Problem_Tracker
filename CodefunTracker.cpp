/*
    CodefunTracker.cpp
    Written by Brickyblossom
    June 20, 2020
    Latest revision: June 24, 2020.
    This is an open-sourced code file which is licensed under the GNU GPL v3.
    The code is used to load data onto a file, then presents the user with options to add new data, search for data, show stats and deletes all data.
*/

/*
    NOTE:
    - Some part of this code is resource-heavy due to the use of "system"
    - This code reads from a text file, which is insecure in many ways.
    - I'm working on a better alternative on both those problems.
*/

//Libraries
#include<iostream>
#include<fstream>
#include<iomanip>

//Removes std::
using namespace std;

//clrscr() which is to clear the entire console window, it is OS-dependent and theoretically works for Windows, Mac and Linux.
//However the usage of "system" makes it quite resource-intensive and dangerous.
void clrscr(){
    system("cls||clear");
    return;
}

//Global variables declaration
long long length;
string problems[100000] = {};
long long stats[100000] = {}, countAC = 0;
string t={};

//Function declaration
int options();
void fail(string s);
void success();
void loadData();
void problemSearch();
void appendProblem();
int processOptions();
void showStats();
void deleteData();
void deleteDataPrompt();
string rankVerdict();
void lexSort(string data[]);

//Main function
int main(){
    loadData();
    lexSort(problems);
    try{
       processOptions();
    }
    catch(int n){
        return 0;
    }

}

//Function definitions//

//Main menu
int options(){
    clrscr();
    cout<<"The Codefun.vn problem tracker"<<endl;
    int option;
    cout<<"Please specify an option:"<<endl;
    cout<<"1. Submit a new solved problem"<<endl;
    cout<<"2. Search for a solved problem"<<endl;
    cout<<"3. List user stats"<<endl;
    cout<<"4. Delete all data"<<endl;
    cout<<"5. Quit"<<endl;
    cout<<"Enter your option: ";
    cin>>option;
    return option;
}

//Returns error message and returns to main menu
void fail(string s){
    clrscr();
    cout<<"The Codefun.vn problem tracker"<<endl;
    cout<<s<<endl;
    processOptions();
}

//Stops the screen to read results and once a key is pressed, returns to main menu
void success(){
    cin.get();
    cin.get();
    processOptions();
}

//Loads data from files
void loadData(){
    countAC=0;
    fstream fs;
    fs.open("ProblemsLength.inp",fstream::in);
    fs>>length;
    fs.close();
    fs.open("Database.inp",fstream::in);
    for(long long i=0;i<length;i++){
        fs>>problems[i];
        if(problems[i]!=""){
            countAC++;
        }
        else{
            break;
        }
    }
    fs.close();
    return;
}

//Sort data in lexicographical order
void lexSort(string data[]){
    long long i,j,n;
    string temp = "";
    fstream fs;
    fs.open("ProblemsLength.inp",fstream::in);
    fs>>n;
    fs.close();
    for(i=0;i<=n-1;i++){
        for(j=i+1;j<=n;j++){
            if(data[i]>data[j]){
                temp = data[i];
                data[i] = data[j];
                data[j] = temp;
            }
        }
    }
    fs.open("Database.inp",fstream::out|fstream::trunc);
    for(i=0;i<=n-1;i++){
        if(data[i]=="") continue;
        fs<<data[i]<<endl;
    }
    fs.close();
}

//Main menu handler
int processOptions(){
    int option = options();
    switch(option){
        case 1: {appendProblem(); processOptions(); return 0;}
        case 2: {problemSearch(); processOptions(); return 0;}
        case 3: {showStats(); processOptions(); return 0;}
        case 4: {deleteDataPrompt(); processOptions(); return 0;}
        case 5: {throw 0;}
    }
    fail("Invalid option!");
    return 0;
}

//Search for a problem if it has been solved (exists in database)
void problemSearch(){
    cout<<"Please specify the problem code: ";
    cin>>t;
    for(long long i=0;i<length;i++){
        if(t==problems[i]){
            cout<<"This problem has been solved!"<<endl;
            success();
            return;
        }
    }
    cout<<"This problem does not exist, or it has not been solved."<<endl;
    success();
    return;
}

//Checks if a problem has already existed in the file, if not then append the problem to the database
void appendProblem(){
    cout<<"Please specify the problem code: ";
    cin>>t;
    for(long long i=0;i<length;i++){
        if(t==problems[i]){
            cout<<"This problem has already been solved!"<<endl;
            success();
        }
    }
    fstream fs;
    fs.open("Database.inp",fstream::app);
    fs<<t<<endl;
    fs.close();
    cout<<"Problem added to list!"<<endl;
    success();
}

//Gets current user rank based on number of problems solved
string rankVerdict(){
    double percentage = (double)countAC/length*100;
    //cout<<percentage<<endl;
    string s="Newbie";
    if(percentage>=2){
        s = "Beginner";
    }
    if(percentage>=5){
        s = "Novice";
    }
    if(percentage>=10){
        s = "Coder";
    }
    if(percentage>=25){
        s = "Expert";
    }
    if(percentage>=37.55){
        s = "Master";
    }
    if(percentage>=55){
        s = "Hacker";
    }
    if(percentage>=90){
        s = "Grandmaster";
    }
    return s;
}

//Shows user stats
void showStats(){
    cout<<"User stats:"<<endl;
    cout<<"Problems solved: "<<countAC<<endl;
    cout<<"Problems total: "<<length<<endl;
    cout<<fixed<<setprecision(2);
    cout<<"AC Percentage: "<<(double)countAC/length*100<<"%"<<endl;
    cout<<"Rank verdict: "<<rankVerdict()<<endl;
    success();
    return;
}

//Wipe all data
void deleteData(){
    fstream fs;
    fs.open("Database.inp",fstream::out|fstream::trunc);
    fs.close();
    cout<<"All data deleted."<<endl;
    success();
}

//Prompts data deletion
void deleteDataPrompt(){
    char ans,ans2;
    cout<<"Are you sure you want to delete all data(Y/N)?";
    cin>>ans;
    if(ans=='Y'||ans=='y'){
        cout<<"Are you REALLY sure you want to delete ALL data?(Y/N)?";
        cin>>ans2;
        if(toupper(ans2)=='Y'){
            deleteData();
        }
        else if(toupper(ans2)=='N'){
            cout<<"Data deletion canceled.";
            success();
            return;
        }
        else{
            fail("Invalid option.");
            return;
        }
    }
    else if(toupper(ans)=='N'){
        cout<<"Data deletion canceled.";
        success();
        return;
    }
    else{
        fail("Invalid option.");
        return;
    }
}
