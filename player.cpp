#include "player.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;
player::player(int sizeOfHand) 
{
    size = sizeOfHand;
    noBones = 0;
    hand = new bone*[size]; // create new hand of 20 ptrs to bones
    srand(time(NULL));
}

player::player(const player& copy)
{
    noBones = 0;
    size = copy.getSize();  
    hand = new bone*[size];
    for(int i = 0; i < size; i++) // each player has a 20 card hand
    {
        hand[i] = new bone(copy.hand[i]->getSide1(), copy.hand[i]->getSide2()); // set bone at i to sides of bone at i in copy
    }
}

player::~player() 
{
    for(int i = 0; i < size; i++)
    {
        delete []  hand[i]; // delete bone from each index
    }
    delete [] hand; //delete ptr to hand
}

//bone* player::draw(chickenyard& deck, int numCards) // old 
bone* player::draw(chickenyard* deck, int numCards) // new
{
    int index = 0;
    for(int i = 0; i < numCards; i++) 
    {
        int s1, s2 = 0;
        int j = 0;
        //deck.deal(s1, s2); // old
        deck->deal(s1, s2); // new
        if(s1 == 0 && s2 == 0) // if deck couldn't deal
        {
            bone* nullPtr = NULL;
            return nullPtr;
        }
        while(j < size && hand[j] != NULL) // find first empty index in hand to acquire card
        {
            j++;
        }
        if(j == size) // hand is full, resize hand array
        {
            bone** temp = hand;
            hand = new bone*[size + 1];
            for(int i = 0; i < size; i++)
            {
                hand[i] = temp[i]; 
                temp[i] = NULL;
            }
            delete [] temp;
            size++;
        }
        hand[j] = new bone(s1, s2);
        noBones++;
        index = j;
    }
    if(numCards == 1) // return ptr to new bone if only 1 is dealt 
    {
        return hand[index];
    } else
    {
        bone* nullPtr = NULL;
        return nullPtr;
    }
}

bone** player::getHand() const 
{
    return hand; // ptr to hand
}

int player::getScore() 
{
    int score = 0;
    for(int i = 0; i < size; i++) 
    {
        if(hand[i] != NULL)
            score += hand[i]->getSide1() + hand[i]->getSide2(); // for each bone add to sides to score
    }
    return score;
}

void player::printHand()
{
    for(int i = 0; i < size; i++) 
    {
        if(hand[i] != NULL)
            cout << "[" << hand[i]->getSide1() << "|" << hand[i]->getSide2() << "]   ";         
    }
    cout << endl << endl;
}

int player::getSize() const 
{
    return size;
}

int player::getNoBones() const 
{
    return noBones;
}

bone* player::getMatch(bone* toCompare, int& index)
{
    for(int i = 0; i < size; i++)
    {
        if(hand[i] != NULL)
        {
            if(hand[i]->getSide1() == toCompare->getSide1() || // for all bones in hand check if they match toCompare
               hand[i]->getSide2() == toCompare->getSide1() ||
               hand[i]->getSide1() == toCompare->getSide2() ||
               hand[i]->getSide2() == toCompare->getSide2())
            {
                index = i;
                return hand[i];
            }
        }
    }
    bone* nullPtr = NULL;
    return nullPtr;
}

void player::setNull(int toRemove) 
{
    hand[toRemove] = NULL;
    noBones--;
}

bone* player::highestDouble(int& slot)
{
    int highest = 0;
    int index = 0;
    for(int i = 0; i < size; i++)
    {
        if(hand[i]->getSide1() == hand[i]->getSide2()) // for each double, compare it to highest
        {
            if(hand[i]->getSide1() > highest)
            {
                highest = hand[i]->getSide1();
                index = i;
            }
        }
    }
    if(highest == 0)
    {
        bone* nullPtr = NULL;
        return nullPtr;
    } else 
    {
        slot = index;
        return hand[index];
    }
}
