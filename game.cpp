#include "game.h"
#include <iostream>
using namespace std;

game::game()
{
p1 = new player(5);
p2 = new player(5);
pile = new chickenyard(15);
f = new field();
}

game::~game()
{
delete p1;
delete p2;
delete pile;
delete f;
}

void game::run()
{
    cout << "CS 261 - A01 - Cyrus Rice" << endl << endl;
    pile->printYard();
    pile->shuffle();
    cout << "Yard after shuffle:" << endl;
    pile->printYard();
    //p1->draw(*pile, 5); // old
    p1->draw(pile, 5); // new
    cout << "Player 1 hand after drawing 5 cards: " << endl;
    p1->printHand();
    //p2->draw(*pile, 5); // old
    p2->draw(pile, 5); // new
    cout << "Player 2 hand after drawing 5 cards: " << endl;
    p2->printHand();
    // get highest double and play it
    bool whoFirst;
    int dummy;
    // if players have no double, draw until they do
    while(p1->highestDouble(dummy) == NULL && p2->highestDouble(dummy) == NULL)
    {
        //p1->draw(*pile, 1); // old
        //p2->draw(*pile, 1); // old
        p1->draw(pile, 1); // new
        p2->draw(pile, 1); // new
    }
    // whoever has the double starts
    if(p1->highestDouble(dummy) == NULL)
    {
        whoFirst = true;
        cout << "player 2 ";
        //f->add(*pile, p2); // old
        f->add(pile, p2); // new 
    } else if(p2->highestDouble(dummy) == NULL)
    {
        whoFirst = false;
        cout << "player 1 ";
        //f->add(*pile, p1); // old
        f->add(pile, p1); // new 
    } else if(p1->highestDouble(dummy)->getSide1() > p2->highestDouble(dummy)->getSide2())
    {
        whoFirst = false;
        cout << "player 1 ";
        //f->add(*pile, p1); // old
        f->add(pile, p1); // new 
    } else 
    {
        whoFirst = true;
        cout << "player 2 ";
        //f->add(*pile, p2); // old
        f->add(pile, p2); // new 
    }
    f->printField();
    // play game 
    bool p1NotOut;
    bool p2NotOut;
    while(p1->getNoBones() != 0 && p2->getNoBones() != 0)
    {
        if(whoFirst)
        {
            cout << "player 1 ";
            //p1NotOut = f->add(*pile, p1); // old
            p1NotOut = f->add(pile, p1); // new
            cout << "player 2 ";
            //p2NotOut = f->add(*pile, p2); // old
            p2NotOut = f->add(pile, p2); // new
            f->printField();
        } else
        {
            cout << "player 2 ";
            //p2NotOut = f->add(*pile, p2); // old
            p2NotOut = f->add(pile, p2); // new
            cout << "player 1 ";
            //p1NotOut = f->add(*pile, p1); // old
            p1NotOut = f->add(pile, p1); // new
            f->printField();
        }
            if(p1NotOut == false && p2NotOut == false) // game over due to both players bieng unable to play on
            {
                if(p1->getScore() < p2->getScore())
                {
                    cout << "Game Over, player 1 wins!" << endl;
                    cout << "Player 1 score: " << p1->getScore() << endl;
                    cout << "Player 2 score: " << p2->getScore() << endl;
                    return;
                } else if(p2->getScore() < p1->getScore())
                {
                    cout << "Game Over, player 2 wins!" << endl;
                    cout << "Player 1 score: " << p1->getScore() << endl;
                    cout << "Player 2 score: " << p2->getScore() << endl;
                    return;
                } else 
                {
                    cout << "Game Over, players tied!" << endl;
                    cout << "Player 1 score: " << p1->getScore() << endl;
                    cout << "Player 2 score: " << p2->getScore() << endl;
                    return;
                }
            }
    }

    // game over due to one player running out of cards, give winner
    if(p1->getNoBones() == 0)
    {
        cout << "Game Over, player 1 wins!" << endl;
        cout << "Player 1 score: " << p1->getScore() << endl;
        cout << "Player 2 score: " << p2->getScore() << endl;
    } else if(p2->getNoBones() == 0) 
    {
        cout << "Game Over, player 2 wins!" << endl;
        cout << "Player 1 score: " << p1->getScore() << endl;
        cout << "Player 2 score: " << p2->getScore() << endl;
    }
}
