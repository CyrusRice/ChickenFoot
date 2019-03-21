#include "field.h"
using namespace std;
class game 
{
public:
    game();
    ~game();
    void run();
private:
    player* p1;
    player* p2;
    chickenyard* pile;
    field* f;
};
