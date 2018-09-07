/*
 * File:   pa2.cpp
 * Author: Ali Sammour (1247-6981)
 * Class: COP3503
 * Scope: A C++ program that emulates the operating system's responsibility 
 * to allocate memory to programs. The program has 32 pages of contiguous and unused memory.
 * 
 * Source File: pa2.cpp is the main/source file which includes the main part of the
 * program as well as some functions. Includes pa2.h in order to use declarations and the classes
 * there to allocate memory.
 */

/* 
 * File:   pa2.cpp
 * Author: Ali
 *
 * Created on October 18, 2017, 4:13 PM
 */

//Including a header file in order to incorporate the declarations in it
#include "pa2.h"
using namespace std;
LinkedList memTot;//Making the list to represent the memory

//Function to convert kbs to pages
int mem2page (int kb){
    if(kb % 4 == 0){
        mem = kb/4;
    }
    else {
        mem = ((kb/4) + 1);
    }
    return mem;
}
//Function to kill a program. Uses the empty function to remove the program 
//and return the count of pages
void kill(){
    cout<<"Program name - ";
    string progName; 
    cin>>progName;
    cout<<endl;
    int pagesBack = memTot.empty(progName);
    //Two functions to check if the program was there and give a value
    if(pagesBack > 0)cout<< "Program "<<progName<<" successfully killed, "<<pagesBack<<" page(s) reclaimed.";
    else cout<< "Program "<<progName<<" could not be found and killed. Check your spelling.";
    
}
//Function to output the fragment count           
void fragmentation(){
    cout<<endl;
    int ct = memTot.fragmentCt();
    cout<<"There are "<<ct<<" fragment(s)";
}
//Function to add a program. //0 is worst fit, 1 is best fit
void progAdd(int gdFit){
    string program; int kb;
    bool sameName = false; bool pass = false;
    cout<<"Program name - ";
    cin>>program;
    cout<<"Program size (KB) - ";
    cin>>kb;
    int pages = mem2page(kb);
    //Searches for program and makes sure it isnt running
    if(memTot.find(program)){
        sameName = true;
        cout<<endl;
        cout<<endl<<"Error, Program "<<program<<" already running.";
    }
    else{
        if(gdFit == 1){
            pass = memTot.bestFitAdd(pages, program);
        }
        else if(gdFit ==0){
            pass = memTot.worstFitAdd(pages, program);
        }
    }
    //Makes sure enough memory was present
    if(pass){
        cout<<endl<<"Program "<<program<<" added successfully: "<<pages<<" page(s) used.";
    }
    else{
        cout<<endl<<"Error, Not enough memory for Program "<<program;
    }
}


        
int main(int argc, char** argv) {
    //User to choose the algorithim they want to use
    string fit = "";
    int gdFit = 0;//0 for worst fit, 1 for best
    int ct = 0;//counter
    cout<<"Would you like to use the \"worst\" or \"best\" fit algorithm?"<<endl;
    //While loop used for input to ensure the program understands the input
    while(true){
        cin>>fit;
        if(fit.compare("best") == 0){
            gdFit = 1;
            cout<<"Using best fit algorithm"<<endl;
            break;
        }
        else if(fit.compare("worst") == 0){
            cout<<"Using worst fit algorithm"<<endl;
            break;
        }
        else{
            cout<<"Your input was not understood. Please type the word: \"worst\" or \"best\" ";
        }
    }
    //Forming the list to be made up of the nodes
    while(ct<32){
        memTot.input();
        ct++;
    }
    int selection = 0;
    cout<<endl;
    cout<<"1. Add program"<<endl;
    cout<<"2. Kill program"<<endl;
    cout<<"3. Fragmentation"<<endl;
    cout<<"4. Print memory"<<endl;
    cout<<"5. Exit"<<endl;
    //do while loop to make sure the choice is accurate and completed
    //and to terminate at choice 5
    do{
        cout<<endl<<"Choice - ";
        while(!(cin >> choice)){
            cin.clear();
            //Need this function so input is limited to the line. Until enter is clicked. Vital for multiple inputs.
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Bad Input, Please enter a number 1-5."<<endl;
            cout<<"Choice - ";
        }  
        selection = choice;
        if(choice < 1 && choice > 5 ){
		cout<<"Bad Input, Please enter a number 1-5.";
		continue;
        }
        switch(choice){
            case 1: progAdd(gdFit); break;
            case 2: kill(); break;
            case 3: fragmentation(); break;
            case 4: memTot.output(); break;
            case 5: memTot.freeList(); break;
        }
        cout<<endl;
    }while(selection != 5);//To terminate
    
 return 0;
}

