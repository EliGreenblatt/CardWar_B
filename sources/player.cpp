#include "player.hpp"
#include <iostream>
using namespace std;
using namespace ariel;

Player::Player(): name("player")
{
    cout<<" Creating player " << endl;
    rank = 0;
    amountOfCards = 0;
    points = 0;
    timesWon = 0;
    timesLost = 0;
    timesDraw = 0;
}

Player::Player(string name) : name(name)
{
    cout<<" Creating player " << endl;
    rank = 0;
    amountOfCards = 0;
    points = 0;
    timesWon = 0;
    timesLost = 0;
    timesDraw = 0;
}

int Player::cardesTaken()
{
   // cout<<"The amount of taken cards is "<<points <<endl;
    return points;
}

int Player::stacksize()
{
   // cout<<"The stack size is "<< amountOfCards <<endl;
    return amountOfCards;
}

void Player::addToStack(Card card)
{
    stack.push(card);
    amountOfCards =  amountOfCards+1;
}

Card Player::getCard()
{
    Card card = stack.top();
    stack.pop();
    amountOfCards--;
    return card;
}

string Player:: getName()
{
    return name;
}

void Player::cardsWon()
{
    points = points + 2;
}

void Player::cardsWon(int round)
{
    points = points + 2 * round + 2;
}

void Player::wonRound()
{
    timesWon++;
}

void Player::lostRound()
{
    timesLost++;
}

void Player::drawRound()
{
    timesDraw++;
}

int Player::getWins()
{
    return timesWon;
}

int Player::getLoss()
{
    return timesLost;
}

int Player::getDraw()
{
    return timesDraw;
}