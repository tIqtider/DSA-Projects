/***************************************************************************
    Filename: 		Card.h
    Author: 		Taseen Iqtider
    Date Created: 	2/17/2025
    Date Updated: 	3/26/2025
    Purpose: 		header file for war source file
****************************************************************************/

#ifndef CARD_H
#define CARD_H

// Card class
class Card
{
private:
    int cardNum;   // Holds cards from 2-14 (11=Jack, 12=Queen, 13=King, 14=Ace)
    char cardSuit; // 'H'=Hearts, 'D'=diamonds, 'C'=clubs, 'S'=spades
public:
    // Default Constructor
    Card()
    {
        cardNum = 0;
        cardSuit = (' ');
    }

    // Overloaded Constructor
    Card(int num, char s)
    {
        cardNum = num;
        cardSuit = s;
    }

    // Mutator Functions
    void setCardNum(int num)
    {
        cardNum = num;
    }
    void setCardSuit(char s)
    {
        cardSuit = s;
    }

    // Accessor Functions
    int getCardNum() const
    {
        return cardNum;
    }
    char getCardSuit() const
    {
        return cardSuit;
    }

    // overloaded "==" and ">" operator functions
    bool operator==(const Card &otherCard)
    {
        return cardNum == otherCard.cardNum;
    }

    bool operator>(const Card &otherCard)
    {
        return cardNum > otherCard.cardNum;
    }
};

#endif