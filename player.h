#include "chickenyard.h"
class player {
public:
    player(int sizeOfHand);
    player(const player& copy);
    ~player();
    //bone* draw(chickenyard& deck, int numCards); // old
    bone* draw(chickenyard* deck, int numCards); // new
    bone** getHand() const; 
    int getScore();
    void printHand();
    int getSize() const; // get num of slots in hand array
    int getNoBones() const; // get num of occupied slots in hand array
    bone* highestDouble(int& slot); // get highest double
    bone* getMatch(bone* toCompare, int& index); // get bone in hand that matches toCompare
    void setNull(int toRemove); // set hand at index toRemove to NULL
private:
   bone** hand;
   int size; // size of array
   int noBones; // num bones in array
   
};
