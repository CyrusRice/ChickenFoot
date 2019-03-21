#include "bone.h"
class chickenyard {
public:
    chickenyard(int sizeOfDeck);
    chickenyard(const chickenyard& copy);
    ~chickenyard();
    void shuffle();
    void deal(int& s1, int& s2); 
    bool canDeal();
    bone** getYard() const; // return ptr to deck
    void printYard();
    int getSize() const;  
private:
   bone** yard;
   int size;
   
};
