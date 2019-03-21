#include <vector>
#include "player.h"
using namespace std;
class field 
{
public:
    field();
    ~field();
    //bool add(chickenyard& deck, player* p); // old
    bool add(chickenyard* deck, player* p); // new
    int chickenFoot(); // return index of chickenfoot if there is one
    void printField();
    void setLinks(int index); // set domino at index to point to null in all ptrs
private:
    struct domino // struct holding a bone and four ptrs
    {
        bone* data;
        domino* left;
        domino* middle;
        domino* right;
        domino* fourth;
    };

    vector<domino*> board; // field
};
