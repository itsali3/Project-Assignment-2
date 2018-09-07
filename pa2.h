/*
 * File:   pa2.h
 * Author: Ali Sammour (1247-6981)
 * Header File: Holds declarations that are used in the
 * main source file, pa2.cpp. Also, is going to be used
 * for the Node and Linked List objects. There declarations
 * and functions included. 
 */

/* 
 * File:   pa2.h
 * Author: Ali
 *
 * Created on October 18, 2017, 4:13 PM
 */

#ifndef PA2_H
#define PA2_H
//declarations begin
#include <cstdlib>
#include <string>
#include <iostream>
#include <limits>
using namespace std;
int mem;
int choice;


/*Need to begin the program by making two objects.
 One to represent a Node and one to represent a Linked List.
 Will both have public and private fields as well as
 mutators and accessors*/
class Node {//Each Node will represent a 4kb memory
    //Each piece of memory is its own entity so it's properties will be private
    private:
        Node *next; //represents the next node the node points to
        bool free; //If the node is free to be used
        string program; //name of the program on the node
    public:
        //Constructor for the node object
        Node(){
            this->free = true;
            this->program = "";
            this->next = NULL;
        }
        //Accessors and Mutators for the private properties of the node
        bool getFree(){
            return this->free;
        }
        string getProgram(){
            return this->program;
        }
        Node *getNext(){
            return this->next;
        }
        void setFree(bool free){
            this->free = free;
        }
        void setProgram(string program){
            this->program = program;
        }
        void setNext(Node *next){
            this->next = next;
        }
        
};
class LinkedList {//List so the memory is organized and can be filled correctly
    //Each piece of memory is its own entity so it's "direction" will be private
    private:
        Node *head;//node that points to the head in the linked list
    public:
        //Accessors and Mutators for the private properties
        void setHeader(Node *head){
            this->head = head;
        }
        Node * getHead(){
            return this-> head = head;
        }
        //De-constructor to free the memory
        void freeList(){
           void free();//points all to null
        }
        //functions for the object. hNode is used and represents the path the nodes point in, place holder
        //ct(count) is a variable used as a counter
        void output(){
            int ct = 0;
            Node *hNode = head;
            //Making sure the Node is actually an object and only printing 32
            while(hNode != NULL){
                //If-else to check if the memory is free or used. prints program name or "free".  
                if(hNode->getFree() == false){
                    cout<< hNode->getProgram() << "\t";
                    hNode = hNode->getNext();
                    ct++;
                }
                else {
                    cout << "Free\t" ;
                    hNode = hNode->getNext();
                    ct++;     
                }
                //check to see if the count hits 8 in order to keep format
                if(ct%8 == 0){
                    cout << endl;
                }
            }
            
        }
        //Function for adding memory into the list in order
        void input(){
            Node * node = new Node();//constructing memory
            //If it is the first one made it will become the head/start to the list. 
            if(head == NULL) {
                head = node;
                return;
            }
            Node *hNode = head;//starting at the head
            //Loops through to find the first Free spot(!NULL value)
                while(hNode->getNext() != NULL){
                    hNode = hNode->getNext();//setting it to the Free value
                }
            hNode->setNext(node);//Setting the node object made to that spot
        }
        //Program to find a program in the list by name
        bool find(string program){
            Node *hNode = head;
                while(hNode != NULL){//Searching through the list for taken spots
                    //using string function to compare the names 
                    if(hNode->getProgram().compare(program)== 0){
                        
                        return true;
                    }
                    hNode = hNode->getNext();//In order to continue through the list
                }
            }
        //Function to remove empty the memory from the list
        int empty(string programName){
            Node *hNode = head;
            int ct = 0;
            while(hNode != NULL){//Searching through the list for taken spots
                //using string function to compare the names
                if(hNode->getProgram().compare(programName)== 0){
                    //setting it free nameless (default conditions)
                    hNode->setProgram(""); hNode->setFree(true);
                   
                    hNode = hNode->getNext(); ct++;
                }
                else{
                    hNode = hNode->getNext();//loop through
                }
            }
            return ct;
        }
        //Function to keep track of the fragments
        int fragmentCt(){
            int ct = 0;
            Node *hNode = head;
            Node *final = hNode;
            bool free;
                //While loop used to loop through the list and count the amount
                //of programs that aren't free// Using final and hNode as place holders
                while(hNode != NULL){
                    free = hNode->getFree();
                    if(free){
                       Node *path = hNode->getNext();
                       if(path != NULL && !(path->getFree())) ct++;
                    }
                    final = hNode; hNode = hNode->getNext();
                }
            //accounting for final spot
            bool finalFree = true;
            finalFree = final->getFree();
            if(!finalFree){
                return ct;
            }
            else{
                ct++;
                return ct;
            }
        }
        //Function made to clear/delete all objects in list. Loops through with
        //two place holders to delete the Node objects
        void clear(){
            Node *hNode = head; Node *path = NULL;
                while(hNode != NULL){
                    path = hNode->getNext();
                    delete hNode;
                    hNode = path;
                }
           
        }
        //Function that will incorporate the wostfit algorithim
        //when adding elements (i.e. not filling the holes.)
        //Using similar style from above to move through
        bool worstFitAdd(int size, string program){
            Node *hNode = head;
            Node *maxNode = hNode; int ct = 0;
            int maxCt = 0;
            Node *node1 = hNode;
            bool pass = false;
            bool free;
                while(hNode != NULL){
                    free = hNode->getFree();
                    Node *path = hNode->getNext();
                    if(free){
                        ct++;
                        if(ct >= size){
                            if(path == NULL){
                                if(ct> maxCt){
                                    maxCt = ct;
                                    maxNode = node1;
                                    ct++;
                                    break;
                                }
                            }
                        }
                        hNode = hNode->getNext();//loop through
                    }
                    else{
                        ct++;
                        if(ct>size && ct>maxCt){
                            maxNode = node1; maxCt = ct;
                            ct = 0;
                            hNode = hNode->getNext();
                            node1 = hNode;
                        }
                        else{
                            ct=0;
                            hNode = hNode->getNext();
                            node1 = hNode;
                        }
                    }
                }
            Node *beginning = maxNode;
            //checking to see that more memory is present than will be used
            if(maxCt <= size) pass = false;
            else{
                ct = 0;
                while(ct<size){
                    beginning->setFree(false); beginning->setProgram(program);
                    beginning = beginning->getNext(); pass = true;
                    ct++;
                }
            }
            return pass;
        }
         //Function that will incorporate the bestfit algorithim
        //when adding elements (i.e. not filling the holes.)
        //Using similar style from above to move through
        bool bestFitAdd(int size, string program){
            Node *hNode = head; Node *maxNode = hNode;
            int ct = 0; int pCt = 33;//ct must stay <33 to begin, becomes smallest size for program
            Node *node1 = hNode;
            bool pass = false;
                while(hNode != NULL){
                    bool free = hNode->getFree();
                    Node *path = hNode->getNext();
                    if(free){
                        ct++;
                        if(ct >= size){
                            if(path == NULL){
                                if(ct < pCt){
                                    ct++; 
                                    pCt = ct; maxNode = node1;//change values for loop
                                    break;
                                }
                            }
                        }
                        hNode = hNode->getNext();
                    }
                    else{
                        ct++;
                        if(ct>size && ct < pCt){
                            maxNode = node1; pCt = ct;
                            hNode = hNode->getNext();
                            node1 = hNode;
                            ct = 0;
                        }
                        else{
                            hNode = hNode->getNext();
                            node1 = hNode;
                            ct = 0;
                        }
                    }
                }
            
            Node *beginning = maxNode;
            //checking the size to make sure it can fit
            if(pCt <= size) pass = false;
            else{
                ct = 0;
                while(ct < size){
                    beginning->setFree(false); beginning->setProgram(program);
                    beginning = beginning->getNext(); pass = true;
                    ct++;
                }
            }
            return pass;
        }
        
};




#endif /* PA2_H */

