#include "card.hpp"

using namespace ariel;
using namespace std;

Card::Card(int otherVal , int otherShape)
{
    val = otherVal;
    shape = otherShape;
}

int Card::getValue()
{
    return val;
}

string Card::getType()
{
    if(shape == 1)
    {
        return "Hearts";
    }    
    if(shape == 2)
    {
        return "Diamonds";
    }    
    if(shape == 3)
    {
        return "Clubs";
    }    
    return "Spades";
    
}

int Card::getShape()
{
    return shape;
}