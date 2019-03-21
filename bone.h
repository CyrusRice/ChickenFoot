class bone 
{
public:
    bone(int s1, int s2);
    int getScore();
    void setSides(int num1, int num2);
    int getSide1(); // get both numbers on bone
    int getSide2(); //
    void setTaken(); // tells whether current bone is copied when invoking chickenyard copy constructor
    bool getTaken(); // returns whether taken or not
    bool isDouble();
private:
    int side1;
    int side2;
    bool taken; 
};
