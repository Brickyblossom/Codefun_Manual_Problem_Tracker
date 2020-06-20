#include<bits/stdc++.h>
#include<limits>
using namespace std;


long long length;
string problems[100000] = {};
long long stats[100000] = {}, countAC = 0;
string t={};

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

int main(){
    loadData();
    try{
       processOptions();
    }
    catch(int n){
        return 0;
    }

}

int options(){
    system("cls");
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

void fail(string s){
    system("cls");
    cout<<"The Codefun.vn problem tracker"<<endl;
    cout<<s<<endl;
    processOptions();
}

void success(){
    cin.get();
    cin.get();
    processOptions();
}

void loadData(){
    countAC=0;
    fstream fs;
    fs.open("Length.txt",fstream::in);
    fs>>length;
    fs.close();
    fs.open("Data.txt",fstream::in);
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
    fs.open("Data.txt",fstream::app);
    fs<<t<<endl;
    fs.close();
    cout<<"Problem added to list!"<<endl;
    success();
}

void showStats(){
    cout<<"User stats:"<<endl;
    cout<<"Problems solved: "<<countAC<<endl;
    cout<<"Problems total: "<<length<<endl;
    cout<<fixed<<setprecision(2);
    cout<<"AC Percentage: "<<(double)countAC/length*100<<"%"<<endl;
    success();
    return;
}

void deleteData(){
    fstream fs;
    fs.open("Data.txt",fstream::out|fstream::trunc);
    fs.close();
    cout<<"All data deleted."<<endl;
    success();
}

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
