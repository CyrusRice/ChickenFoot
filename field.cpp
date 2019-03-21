#include "field.h"
#include <iostream>
using namespace std;
field::field()
{
  
}

field::~field()
{
    for(unsigned int i = 0; i < board.size(); i++)
    {
        delete [] board[i]->data; // new
        delete [] board[i];
    }
}

//bool field::add(chickenyard& deck, player* p) // old
bool field::add(chickenyard* deck, player* p) // new
{
    int index = 0;
    // play first highest double to start round
    if(board.size() == 0)
    {
        if(p->highestDouble(index) != NULL) // if there is a highest double
        {
            domino* first = new domino; // create new domino, initialize it, and push it onto field
            first->data = p->highestDouble(index);
            board.push_back(first);
            p->setNull(index);                 // take card from hand
            setLinks(0); // point first domino to null at all ptrs
            cout << "plays the highest double [" << first->data->getSide1() << "," << first->data->getSide2() << "]" << endl;
            return true;
        } else // no double
        {
            bone* newCard = p->draw(deck, 1); // draw card
            cout << "draws a " << "[" << newCard->getSide1() << "," << newCard->getSide2() << "]" << endl; 
            return true;
        }
    }

    // play next 4 dominoes off highest double
    if(board.size() < 5)
    {
        if(p->getMatch(board[0]->data, index) != NULL) // if there is a match in player hand to first domino
        {
            domino* next = new domino;
            next->data = p->getMatch(board[0]->data, index);
            board.push_back(next);
            p->setNull(index);                 // take card from hand
            setLinks(board.size() - 1);
            if(board[0]->left == NULL) // set first domino to point to this new one
            {
                board[0]->left = next;
            } else if(board[0]->right == NULL)
            {
                board[0]->right = next;
            } else if(board[0]->middle == NULL)
            {
                board[0]->middle = next;
            } else if(board[0]->fourth == NULL)
            {
                board[0]->fourth = next;
            }
            cout << "plays a [" << next->data->getSide1() << "," << next->data->getSide2() << "]" << endl;
            return true;
        } else // no match, draw card from yard 
        {
            //if(deck.canDeal()) // old
            if(deck->canDeal()) // new
            {
                bone* newCard = p->draw(deck, 1);
                cout << "draws a " << "[" << newCard->getSide1() << "," << newCard->getSide2() << "]" << endl; 
                return true;
            } else // deck empty
            {
                cout << "ran out of cards to pick" << endl;
                return false;
            }
        }
    }

    // play next 3 dominoes off chicken foot
    if(chickenFoot())
    {
        if(p->getMatch(board[chickenFoot()]->data, index) != NULL)
        {
            domino* next = new domino;                // create new domino
            next->data = p->getMatch(board[chickenFoot()]->data, index);                  // put card from hand in data
            board.push_back(next);                      // add new domino to field
            p->setNull(index);                 // take card from hand
            setLinks(board.size() - 1);
            if(board[chickenFoot()]->left == NULL)     // point chickenfoot to appropriate domino
            {
                board[chickenFoot()]->left = next;
            } else if(board[chickenFoot()]->right == NULL)
            {
                board[chickenFoot()]->right = next;
            } else if(board[chickenFoot()]->middle == NULL)
            {
                board[chickenFoot()]->middle = next;
            }
            cout << "plays a [" << next->data->getSide1() << "," << next->data->getSide2() << "]" << endl;
            return true;
        } else 
        {
            //if(deck.canDeal()) // old
            if(deck->canDeal()) // new
            {
                bone* newCard = p->draw(deck, 1);
                cout << "draws a " << "[" << newCard->getSide1() << "," << newCard->getSide2() << "]" << endl; 
                return true;
            } else
            {
                cout << "ran out of cards to pick" << endl;
                return false;
            }
        }
    }

    // play next domino off any match
    for(unsigned int i = 1; i < board.size(); i++)
    {
        if(p->getMatch(board[i]->data, index) != NULL) 
        {
            if(board[i]->middle == NULL)
            {
                domino* next = new domino;
                next->data = p->getMatch(board[i]->data, index);
                board.push_back(next);
                p->setNull(index);
                setLinks(board.size() - 1);
                board[i]->middle = next;
                cout << "plays a [" << next->data->getSide1() << "," << next->data->getSide2() << "]" << endl;
                return true;
            } 
        } 
    }
        //if(deck.canDeal()) // old
        if(deck->canDeal()) // new
        {
            bone* newCard = p->draw(deck, 1);
            cout << "draws a " << "[" << newCard->getSide1() << "," << newCard->getSide2() << "]" << endl; 
            return true;
        } else
        {
            cout << "ran out of cards to pick" << endl;
            return false;
        }
}

void field::printField()
{
    cout << "Field: " << endl;
    for(unsigned int i = 0; i < board.size(); i++)
    {
       cout << "[" << board[i]->data->getSide1() << "|" << board[i]->data->getSide2() << "]   "; 
    }
    cout << endl << endl;
}

int field::chickenFoot() 
{
    for(unsigned int i = 1; i < board.size(); i++)
    {
        if(board[i]->data->getSide1() == board[i]->data->getSide2())
        {
            if(board[i]->left == NULL || board[i]->middle == NULL || board[i]->right == NULL)
            {
                return i;
            }
        }
    }
    return 0;
}

void field::setLinks(int index)
{
    board[index]->left = NULL;
    board[index]->middle = NULL;
    board[index]->right = NULL;
    board[index]->fourth = NULL;
}
