#include "game.hpp"
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <algorithm>
#include <random>
using namespace std;
using namespace ariel;

Game::Game(Player &p1, Player &p2) : p1(p1), p2(p2)
{
    gameOver = 0;

    //Following code is from stackover flow to shuffle a deck
    vector<Card> deck;
    for (int i = 1; i <= 13; i++)
    {
        deck.push_back(Card(i, 1));
        deck.push_back(Card(i, 2));
        deck.push_back(Card(i, 3));
        deck.push_back(Card(i, 4));
    }

    random_device rnd;
    mt19937 g(rnd());
    shuffle(deck.begin(), deck.end(), g);
    unsigned long int size = 0;
    while (size < 52)
    {
        p1.addToStack(deck[size]);
        p2.addToStack(deck[size + 1]);
        size += 2;
    }

    for (std::array<std::string, DECK_SIZE>::size_type i = 0; i < DECK_SIZE; i++) 
    {
        logArray[i] = "0";
    }
}

void Game::playAll()
{
    inGame = 1;
    int i = 0;
    cout << "Starting Game" << endl;
    while (p1.stacksize() != 0 && p2.stacksize() != 0)
    {
        i++;
        cout << "Playing turn number:" << i << endl;
        playTurn();
        printLastTurn();
        cout<<"THIS PERSON: "<< p1.getName()<<" HAS:" << p1.cardesTaken()<<endl; 
        cout<<"THIS PERSON: "<< p2.getName()<<" HAS:" << p2.cardesTaken()<<endl; 
    }
    inGame = 0;
    gameOver = 1;
    printWiner();
}

void Game::printWiner()
{
    if (inGame == 1)
    {
        cout << " Game Still In Progress " << endl;
        return;
    }
    if (p1.cardesTaken() == p2.cardesTaken())
    {
        cout << "Draw" << endl;
        return;
    }
    if (p1.cardesTaken() > p2.cardesTaken())
    {
        cout << "" << p1.getName();
        cout << " has won the game" << endl;
        return;
    }
    cout << "" << p2.getName();
    cout << " has won the game" << endl;
}

void Game::printLog()
{
    for (std::array<std::string, DECK_SIZE>::size_type i = 0; i < DECK_SIZE; ++i) {
    if(logArray[i] == "0") 
    {
        continue;;
    }
    cout << logArray[i] << endl;
}
}

void Game::printStats()
{
    cout << " " << p1.getName();
    cout << " STATS: " << endl;
    cout << "Win Rate: " << p1.getWins() / (double)p1.getLoss();
    cout << " Cards won: " << p1.cardesTaken();
    cout << " Amount of draws: " << p1.getDraw();
    cout << " Draw rate:" << p1.getDraw() / (double)turns << endl;

    cout << " " << p2.getName();
    cout << " STATS: " << endl;
    cout << "Win Rate: " << p2.getWins() / (double)p1.getLoss();
    cout << " Cards won: " << p2.cardesTaken();
    cout << " Amount of draws: " << p2.getDraw();
    cout << " Draw rate:" << p2.getDraw() / (double)turns << endl;
}

void Game::playTurn()
{
    
    if (&p1 == &p2)
    {
        throw std::runtime_error("Player cannot play against himself");
    }
    if (gameOver == 1)
    {
        throw std::runtime_error("Already finished the game");
        return;
    }
    if (p1.stacksize() == 0 || p2.stacksize() == 0)
    {
        inGame = 0;
        return;
    }
    turns++;
    Card playerOneCard = p1.getCard();
    Card playerTwoCard = p2.getCard();
    p1LastCardType = playerOneCard.getType();
    p1LastCardValue = playerOneCard.getValue();
    p2LastCardType = playerTwoCard.getType();
    p2LastCardValue = playerTwoCard.getValue();
    //logArray[turns - 1] = getLastTurn();
    logArray[static_cast<std::array<std::string, DECK_SIZE>::size_type>(turns - 1)] = getLastTurn();

    if (playerOneCard.getValue() == 1 && playerTwoCard.getValue() == 2)
    {
        cout << " p2 wins" << endl;
        p2.cardsWon();
        p2.wonRound();
        p1.lostRound();
        return;
    }
    if (playerTwoCard.getValue() == 1 && playerOneCard.getValue() == 2)
    {
        cout << " p1 wins" << endl;
        p1.wonRound();
        p2.lostRound();
        p1.cardsWon();
        return;
    }
    if (playerOneCard.getValue() > playerTwoCard.getValue())
    {
        cout << " p1 wins" << endl;
        p1.cardsWon();
        p1.wonRound();
        p2.lostRound();
        return;
    }
    else if (playerTwoCard.getValue() > playerOneCard.getValue())
    {
        cout << " p2 wins" << endl;
        p2.cardsWon();
        p2.wonRound();
        p1.lostRound();
        return;
    }

    if (playerOneCard.getValue() == playerTwoCard.getValue())
    {
        turns++;
        Draw(1);
    }
}

void Game::Draw(int round)
{
    cout << "~~~~~~~~~~~~~~Draw number:" << round << " in a row~~~~~~~~~~~~~~" << endl;
    if (p1.stacksize() == 0 || p2.stacksize() == 0)
    {
        inGame = 0;
        p1.cardsWon(round);
        p2.cardsWon(round);
        return;
    }
    p1.drawRound();
    p2.drawRound();
    Card playerOneCard = p1.getCard();
    Card playerTwoCard = p2.getCard();
    if (p1.stacksize() == 0 || p2.stacksize() == 0)
    {
        inGame = 0;
        p1.cardsWon(round + 1);
        p2.cardsWon(round + 1);
        return;
    }
    playerOneCard = p1.getCard();
    playerTwoCard = p2.getCard();
    p1LastCardType = playerOneCard.getType();
    p1LastCardValue = playerOneCard.getValue();
    p2LastCardType = playerTwoCard.getType();
    p2LastCardValue = playerTwoCard.getValue();
   // logArray[turns] = getLastTurn();
    logArray[static_cast<std::array<std::string, DECK_SIZE>::size_type>(turns)] = getLastTurn();
    if (playerOneCard.getValue() == 1 && playerTwoCard.getValue() == 2)
    {
        cout << " p1 wins" << endl;
        p1.cardsWon(round*3);
        p1.wonRound();
        p2.lostRound();
        return;
    }
    if (playerTwoCard.getValue() == 1 && playerOneCard.getValue() == 2)
    {
        cout << " p2 wins" << endl;
        p2.wonRound();
        p1.lostRound();
        p2.cardsWon(round*2);
        return;
    }
    if (playerOneCard.getValue() > playerTwoCard.getValue())
    {
        cout << " p1 wins" << endl;
        p1.cardsWon(round*2);
        p1.wonRound();
        p2.lostRound();
        return;
    }
    else if (playerTwoCard.getValue() > playerOneCard.getValue())
    {
        cout << " p2 wins" << endl;
        p2.cardsWon(round*2);
        p2.wonRound();
        p1.lostRound();
        return;
    }

    if (playerOneCard.getValue() == playerTwoCard.getValue())
    {
        turns++;
        Draw(round + 1);
    }
}
char *Game::getLastTurn()
{
    char *outputString = new char[256]; 
    strcpy(outputString, p1.getName().c_str());
    strcat(outputString, " Has played ");
    char cardValue[4];
    sprintf(cardValue, "%d", p1LastCardValue);
    strcat(outputString, cardValue);
    strcat(outputString, " of ");
    strcat(outputString, p1LastCardType.c_str());
    strcat(outputString, " and ");
    strcat(outputString, p2.getName().c_str());
    strcat(outputString, " Has played ");
    sprintf(cardValue, "%d", p2LastCardValue);
    strcat(outputString, cardValue);
    strcat(outputString, " of ");
    strcat(outputString, p2LastCardType.c_str());
    strcat(outputString, "\n");

    return outputString;
}
void Game::printLastTurn()
{
    cout << "" << p1.getName();
    cout << " Has played " << p1LastCardValue;
    cout << " of " << p1LastCardType;
    cout << " and " << p2.getName();
    cout << " Has played " << p2LastCardValue;
    cout << " of " << p2LastCardType << endl;

    string s = "" + p1.getName() + "";
}

int Game::getTurn()
{
    return turns;
}