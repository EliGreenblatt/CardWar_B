#ifndef PLAYER_
#define PLAYER_
#include <stack>
#include "card.hpp"
#include <string>


using namespace std;
namespace ariel
{
    class Player
    {
        private:
            std::stack<Card> stack;
            std::string name;
            int rank;
            int amountOfCards;
            int points;
            int timesWon;
            int timesLost;
            int timesDraw;

        public:
            Player(); // default constructor
            Player(std::string name); // constructor taking the players name
            int stacksize(); //prints the amount of cards left. 
            int cardesTaken(); // prints the amount of cards this player has won. 
            void addToStack(Card card);
            void cardsWon();
            void cardsWon(int round);
            void wonRound();
            void lostRound();
            void drawRound();
            string getName();
            Card getCard();
            int getWins();
            int getLoss();
            int getDraw();
    };
   
}

#endif