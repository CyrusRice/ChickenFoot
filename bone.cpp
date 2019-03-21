#include "bone.h"

bone::bone(int s1, int s2) 
{
   side1 = s1;
   side2 = s2;
   taken = false;
}

void bone::setSides(int num1, int num2) 
{
    side1 = num1;
    side2 = num2;
}

int bone::getSide1() 
{
    return side1;
}

int bone::getSide2() 
{
    return side2;
}

int bone::getScore() 
{
    return side1 + side2;
}

bool bone::getTaken()
{
    return taken;
}

void bone::setTaken()
{
   taken = true; 
}

bool bone::isDouble()
{
    return (side1 == side2);
}
