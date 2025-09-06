/***************************************************************************
	Filename: 		war.cpp
	Author: 		April Crockett and Taseen Iqtider
	Date Created: 	2/17/2025
	Date Updated: 	3/26/2025
	Purpose: 		WAR! (the card game) using a queue for each player's deck
					and stacks whenever we need to resolve war
****************************************************************************/

#include <iostream>
#include <vector>
#include "Queue.h"
#include "Stack.h"
#include "Card.h"
using namespace std;

// Function protoypes
void displayCard(int value, char suit);
void playerOneWins();
void playerTwoWins();
void printWar();
void play(Queue &player1Deck, Queue &player2Deck);
bool resolveWar(Card &card1, Card &card2, Queue &player1Deck, Queue &player2Deck, string name, Stack &warPile);

int main()
{
	vector<Card> deck;
	char suits[] = {'H', 'D', 'C', 'S'};

	// queue definitions
	Queue player1Deck, player2Deck;

	// creates a deck of classic playing cards with 4 suits
	for (int i = 0; i < 4; i++)
	{
		for (int v = 2; v <= 14; v++)
		{
			deck.push_back(Card(v, suits[i]));
		}
	}

	cout << "\n\nShuffling and dealing the deck! There are " << deck.size() << " cards.\n\n";
	// shuffles the cards
	srand(time(0));
	for (unsigned int i = 0; i < deck.size(); i++)
	{
		int r = rand() % deck.size();
		swap(deck[i], deck[r]);
	}

	// deal 26 cards to both players
	// each player has 26 cards in their deck (queue)
	for (unsigned int i = 0; i < deck.size(); i++)
	{
		if (i % 2 == 0)
		{
			player1Deck.enqueue(deck[i]);
		}
		else
		{
			player2Deck.enqueue(deck[i]);
		}
	}

	// call the play function, sending both player's queues to the function by reference
	play(player1Deck, player2Deck);

	return 0;
}

/******************************************************************************
	Function: 	play()
	Purpose: 	Simulates the game of War between two players,
				dequeuing cards, comparing them, and enqueuing the
				winning cards back. Handles ties by calling resolveWar().
	Parameters:
				- player1Deck (Queue&): The queue representing player 1's deck.
				- player2Deck (Queue&): The queue representing player 2's deck.
	Return Type:void
******************************************************************************/
void play(Queue &player1Deck, Queue &player2Deck)
{
	// int playerCount = player1Deck.getSize();
	// int cpuCount = player2Deck.getSize();

	// ask for user name
	string playerName;
	cout << "Player1, what is your name? ";
	getline(cin, playerName);

	while (!player1Deck.isEmpty() && !player2Deck.isEmpty())
	{
		if (player1Deck.getSize() + player2Deck.getSize() != 52)
		{
			cout << "\nDEBUG: Start of round - " << playerName << " has " << player1Deck.getSize()
				 << " cards, COMPUTER has " << player2Deck.getSize() << " cards.\n";
		}

		cout << playerName << ", press ENTER to draw your card!\n\n";
		cin.get();
		Card player1Card = player1Deck.dequeue();
		Card player2Card = player2Deck.dequeue();

		// display cards
		cout << playerName << ":\n";
		displayCard(player1Card.getCardNum(), player1Card.getCardSuit());
		cout << " vs COMPUTER:\n";
		displayCard(player2Card.getCardNum(), player2Card.getCardSuit());

		// compare cards
		if (player1Card > player2Card) // if player wins
		{
			player1Deck.enqueue(player1Card);
			player1Deck.enqueue(player2Card);
			cout << endl << playerName << " won this round and gets both cards!\n";

			// print who won the round
			cout << "\n************\n";
			cout << playerName << " has " << player1Deck.getSize() << " cards.\n";
			cout << "COMPUTER has " << player2Deck.getSize() << " cards.\n";
			cout << "************\n\n";
		}

		// compare cards
		else if (player2Card > player1Card) // if computer wins
		{
			player2Deck.enqueue(player1Card);
			player2Deck.enqueue(player2Card);
			cout << "\nCOMPUTER won this round and gets both cards!\n";

			// print who won the round
			cout << "\n************\n";
			cout << playerName << " has " << player1Deck.getSize() << " cards.\n";
			cout << "COMPUTER has " << player2Deck.getSize() << " cards.\n";
			cout << "************\n\n";
		}

		// print who won the round

		// compare cards
		else if (player1Card == player2Card)
		{
			Stack warPile;
			bool game = resolveWar(player1Card, player2Card, player1Deck, player2Deck, playerName, warPile);
			if (game == true)
			{
				break;
			}
		}
	}

	if (player1Deck.isEmpty())
	{
		playerTwoWins();
	}
	else if (player2Deck.isEmpty())
	{
		playerOneWins();
	}
}

/*******************************************************************************
	Function: 	 resolveWar()
	Purpose: 	 Handles a tie ("war") situation by placing three
				 additional cards face-down and one face-up from each player.
				 This function handles the pile of cards that are face down
				 with a stack.
				 The winner takes all the cards from the war pile stack.
	Parameters:
				 - card1 (Card): The initial card drawn by player 1 that
				   resulted in a tie.
				 - card2 (Card): The initial card drawn by player 2 that
				   resulted in a tie.
				 - player1Deck(Queue&): player 1's deck.
				 - player2Deck (Queue&): player 2's deck.
				 - name1 (string): The name of player 1.
				 - warPile (Stack): required to be a parameter in case War
					happens twice (or more) in a row and needs to be called
					recursively
	Return Type: bool (indicating if the game should end due to a player not
				 having enough cards)
******************************************************************************/

bool resolveWar(Card &card1, Card &card2, Queue &player1Deck, Queue &player2Deck, string name, Stack &warPile)
{
	cout << endl;
	printWar(); // display war message

	cout << "\n"
		 << name << ", press ENTER to draw your WAR card!\n\n";
	cin.get(); // pause for user to press enter

	// push the tied cards to stack (on a 2nd iteration card1 and card2 gets pushed again but its already in the stack)
	if (warPile.getSize() == 0)
	{
		warPile.push(card1);
		warPile.push(card2);
	}

	// check if a player has < 4 cards before going into war
	if (player1Deck.getSize() < 4 || player2Deck.getSize() < 4)
	{

		if (player1Deck.getSize() < 4)
		{
			cout << name << " has no cards left for war! GAME OVER!\n";
			while (!warPile.isEmpty())
			{
				player2Deck.enqueue(warPile.pop());
			}
			playerTwoWins();
		}
		else if (player2Deck.getSize() < 4)
		{
			cout << "\nCOMPUTER has no cards left for war! GAME OVER!\n";
			while (!warPile.isEmpty())
			{
				player1Deck.enqueue(warPile.pop());
			}
			playerOneWins();
		}
		return true;
	}

	// remove 3 cards each for war
	for (int i = 0; i < 3; i++)
	{
		if (!player1Deck.isEmpty())
		{
			warPile.push(player1Deck.dequeue());
		}
		if (!player2Deck.isEmpty())
		{
			warPile.push(player2Deck.dequeue());
		}
	}

	// draw final cards
	Card warCard1 = player1Deck.dequeue();
	Card warCard2 = player2Deck.dequeue();

	warPile.push(warCard1);
	warPile.push(warCard2);

	// display war cards
	cout << name << ":\n";
	displayCard(warCard1.getCardNum(), warCard1.getCardSuit());
	cout << " vs COMPUTER:\n";
	displayCard(warCard2.getCardNum(), warCard2.getCardSuit());

	// compare who won
	if (warCard1 > warCard2) // if user wins war
	{

		cout << "\n\n"
			 << name << " won this WAR round and gets all cards!\n";
		while (!warPile.isEmpty())
		{
			player1Deck.enqueue(warPile.pop());
		}
	}
	else if (warCard2 > warCard1) // if PC wins war
	{

		cout << "\n\nCOMPUTER won this WAR round and gets all cards!\n";
		while (!warPile.isEmpty())
		{
			player2Deck.enqueue(warPile.pop());
		}
	}
	else // if a tie occurs in war
	{
		cout << "********************************************************************************************\n";
		cout << "***************************	DUPLICATE WAR!!!!!  	************************************\n";
		cout << "********************************************************************************************\n";
		cout << endl;
		return resolveWar(warCard1, warCard2, player1Deck, player2Deck, name, warPile);
	}

	// print the updated cards for each after war is resolved
	cout << "\n************\n";
	cout << name << " has " << player1Deck.getSize() << "cards.\n";
	cout << "COMPUTER has " << player2Deck.getSize() << " cards.\n";
	cout << "************\n\n";

	return false; // resume the game
}

/*******************************************************************************
	Function: 	displayCard()
	Purpose: 	Prints a visual representation of a card to the console.
	Parameters:
				- value (int): 	The numerical value of the card (
								2-14, where 11=J, 12=Q, 13=K, 14=A).
				- suit (char): 	The suit of the card ('H', 'D', 'C', 'S').
	Return Type:void
*******************************************************************************/
void displayCard(int value, char suit)
{

	// Convert value to display string
	string cardValue;
	switch (value)
	{
	case 11:
		cardValue = "J";
		break;
	case 12:
		cardValue = "Q";
		break;
	case 13:
		cardValue = "K";
		break;
	case 14:
		cardValue = "A";
		break;
	default:
		cardValue = std::to_string(value);
		break;
	}
	cout << " ____ \n";
	cout << "|";
	// if we have a single digit card value
	if ((value >= 2 && value <= 9) || (value >= 11 && value <= 14))
		cout << cardValue << "   |\n";
	else // if we have a double digit card value
		cout << cardValue << "  |\n";

	// print out the picture of the suit
	switch (suit)
	{
	case 'H':
		cout << "|(\\/)|\n"
			 << "| \\/ |\n"
			 << "|   ";
		break;

	case 'D':
		cout << "| /\\ |\n"
			 << "| \\/ |\n"
			 << "|   ";
		break;

	case 'C':
		cout << "| /\\ |\n"
			 << "|(__)|\n"
			 << "| /\\";
		break;
	case 'S':
		cout << "| &  |\n"
			 << "|&|& |\n"
			 << "| | ";
		break;
	}
	if ((value >= 2 && value <= 9) || (value >= 11 && value <= 14))
		cout << cardValue << "|\n";
	else // if we have a double digit card value
		cout << "\b" << cardValue << "|\n";

	cout << "`----`\n";
}

/********************************************************************************
	Function: 	 printWar()
	Purpose: 	 Displays an ASCII representation of the word "WAR!" to
				 indicate a tie situation.
	Parameters:  none
	Return Type: void
********************************************************************************/
void printWar()
{
	cout << " (  (       (      )\\ )  |   / \n";
	cout << " )\\))(   '  )\\    (()/(  |  /\n";
	cout << "((_)()\\ )((((_)(   /(_)) | /\n";
	cout << "_(())\\_)())\\ _ )\\ (_))   |/\n";
	cout << "\\ \\((_)/ /(_)_\\(_)| _ \\ (\n";
	cout << " \\ \\/\\/ /  / _ \\  |   / )\\\n";
	cout << "  \\_/\\_/  /_/ \\_\\ |_|_\\((_)    \n";
}

/********************************************************************************
	Function: 	 playerOneWins()
	Purpose: 	 Displays an ASCII art message indicating that player one
				 has won the game.
	Parameters:  none
	Return Type: void
********************************************************************************/
void playerOneWins()
{
	cout << " (                                   )                                            ____ \n";
	cout << " )\\ )  (                          ( /(                 (  (                      |   /\n";
	cout << "(()/(  )\\    )  (       (   (     )\\())           (    )\\))(   ' (               |  /\n";
	cout << " /(_))((_)( /(  )\\ )   ))\\  )(   ((_)\\    (      ))\\  ((_)()\\ )  )\\   (     (    | /\n";
	cout << "(_))   _  )(_))(()/(  /((_)(()\\    ((_)   )\\ )  /((_) _(())\\_)()((_)  )\\ )  )\\   |/\n";
	cout << "| _ \\ | |((_)_  )(_))(_))   ((_)  / _ \\  _(_/( (_))   \\ \\((_)/ / (_) _(_/( ((_) (\n";
	cout << "|  _/ | |/ _` || || |/ -_) | '_| | (_) || ' \\))/ -_)   \\ \\/\\/ /  | || ' \\))(_-< )\\\n";
	cout << "|_|   |_|\\__,_| \\_, |\\___| |_|    \\___/ |_||_| \\___|    \\_/\\_/   |_||_||_| /__/((_)\n";
	cout << "                |__/                                                                   \n";
}

/********************************************************************************
	Function: 	 playerTwoWins()
	Purpose: 	 Displays an ASCII art message indicating that player two
				 has won the game.
	Parameters:  none
	Return Type: void
********************************************************************************/
void playerTwoWins()
{
	cout << " (                                                                                ____ \n";
	cout << " )\\ )  (                           *   )               (  (                      |   /\n";
	cout << "(()/(  )\\    )  (       (   (    ` )  /( (  (          )\\))(   ' (               |  /\n";
	cout << " /(_))((_)( /(  )\\ )   ))\\  )(    ( )(_)))\\))(    (   ((_)()\\ )  )\\   (     (    | /\n";
	cout << "(_))   _  )(_))(()/(  /((_)(()\\  (_(_())((_)()\\   )\\  _(())\\_)()((_)  )\\ )  )\\   |/\n";
	cout << "| _ \\ | |((_)_  )(_))(_))   ((_) |_   _|_(()((_) ((_) \\ \\((_)/ / (_) _(_/( ((_) (\n";
	cout << "|  _/ | |/ _` || || |/ -_) | '_|   | |  \\ V  V // _ \\  \\ \\/\\/ /  | || ' \\))(_-< )\\\n";
	cout << "|_|   |_|\\__,_| \\_, |\\___| |_|     |_|   \\_/\\_/ \\___/   \\_/\\_/   |_||_||_| /__/((_)\n";
}