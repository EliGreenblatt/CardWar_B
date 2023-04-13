#include <array>
#include <stack>
#include "player.hpp"
#include "card.hpp"
using namespace std;
//const int DECK_SIZE = 26;

namespace ariel
{    

static constexpr int DECK_SIZE = 26;
    class Game
    {
        private:
            Player &p1;
            Player &p2;
            std::string winnerName;
            std::string loserName;
            array<std::string , DECK_SIZE> logArray;
           // std::string logArray[DECK_SIZE];
            int turns;
            int inGame;
            int p1LastCardValue;
            std::string p1LastCardType;
            int p2LastCardValue;
            std::string p2LastCardType;
            int gameOver;

        public:
            Game(Player &playerOne, Player &playerTwo); // constructor with two players
            void playAll(); //playes the game untill the end
            void printWiner(); // prints the name of the winning player
            void printLog(); // prints all the turns played one line per turn (same format as game.printLastTurn())
            void printStats();// for each player prints basic statistics: win rate, cards won, <other stats you want to print>. Also print the draw rate and amount of draws that happand. (draw within a draw counts as 2 draws. )
            void playTurn();
            void printLastTurn();
            int getTurn();
            void Draw(int round);
            char * getLastTurn();
    };
}