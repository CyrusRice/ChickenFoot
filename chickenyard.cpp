#include "chickenyard.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;
chickenyard::chickenyard(int sizeOfDeck) 
{
    size = sizeOfDeck; 
    yard = new bone*[size]; // create array of ptrs to bones
    srand(time(NULL));
    int index = 0;
    for(int i = 1; i < 6; i++) 
    {
        for(int j = i; j < 6; j++)
        {
            yard[index] = new bone(i, j); // set each bone in yard
            index++;
        }
    }
}

chickenyard::chickenyard(const chickenyard& copy)  // copy constructor
{
    size = copy.getSize();  
    yard = new bone*[size];
    for(int i = 0; i < size; i++)
    {
        yard[i] = new bone((copy.getYard())[i]->getSide1(), (copy.getYard())[i]->getSide2()); // set bone at index i based on copy 
    }
}

chickenyard::~chickenyard()
{
    for(int i = 0; i < size; i++) // delete each bone
    {
        delete  [] yard[i];
    }
    delete [] yard; // delete ptr to array
}

void chickenyard::shuffle() 
{
    bone** holder = this->getYard(); // temp ptr to current deck
    yard = new bone*[size]; // create new deck 
    srand(time(NULL));
    for(int i = 0; i < size; i++) 
    {
        int index = rand() % size;   // choose random index in old deck
        while(holder[index]->getTaken() == true) // if chosen already, choose new index
        {
            index = rand() % size;
        }
            yard[i] = new bone(holder[index]->getSide1(), holder[index]->getSide2()); // create new card in new deck from index in old deck to i in new deck
            holder[index]->setTaken(); // set index in old deck as taken
    }
    for(int i = 0; i < size; i++) // delete old deck
    {
        delete [] holder[i];
    }
    delete [] holder;
}

void chickenyard::deal(int& s1, int& s2) 
{
    int j = 0;
    while( j < size && yard[j]->getSide1() == 0 && yard[j]->getSide2() == 0)  // while empty slot in deck
    {
        j++;
    }
    if(j == size) // yard is empty
    {
        s1 = 0;
        s2 = 0;
    } else
    {
        s1 = yard[j]->getSide1(); // set both sides using card at index j
        s2 = yard[j]->getSide2();
        yard[j]->setSides(0,0); // set card at index j to (0,0) A.K.A empty
    }
}

bool chickenyard::canDeal()
{
    int j = 0;
    while( j < size && yard[j]->getSide1() == 0 && yard[j]->getSide2() == 0)  // while empty slot in deck
    {
        j++;
    }
    if(j == size) // yard is empty
    {
        return false;
    } else
    {
        return true;
    }
    
}

bone** chickenyard::getYard() const 
{
    return yard; //return ptr to deck
}

void chickenyard::printYard()
{
    cout << "Yard:" << endl;
    for(int i = 0; i < size; i++) 
    {
        cout << "[" << yard[i]->getSide1() << "|" << yard[i]->getSide2() << "]   ";         
    }
    cout << endl << endl;
}
 
int chickenyard::getSize() const 
{
    return size;
}
