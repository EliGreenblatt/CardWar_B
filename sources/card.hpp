#ifndef CARD_
#define CARD_
#include <string>

namespace ariel
{
    class Card
    {
        private:
            int val; // the value of the card
            int shape;// numbers 1 - 4 for each shape

        public:
            Card(int val, int shape);
            int getValue();
            int getShape();
            std::string getType();
    };
}

#endif