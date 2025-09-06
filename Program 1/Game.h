/*************************************************************
	AUTHOR:     Taseen Iqtider
	FILENAME:   Header file for Game Class
	PROGRAM 1 - CSC1310
*************************************************************/

#ifndef GAME_H
#define GAME_H

#include <string>
#include <iostream>
#include "Genre.h"
#include "Steam.h"
using namespace std;

// class definition
class Game
{
private:
	string name;
	long long copiesSold;
	double revenue;
	string publisherClass;
	string publishers;
	string developers;
	vector<Genre> genres;
	Steam steam;

public:
	// constructor
	Game() {}

	// Mutators
	void setName(string name)
	{
		this->name = name;
	}
	void setCopiesSold(long long copiesSold)
	{
		this->copiesSold = copiesSold;
	}
	void setRevenue(double revenue)
	{
		this->revenue = revenue;
	}
	void setPublisherClass(string publisherClass)
	{
		this->publisherClass = publisherClass;
	}
	void setPublishers(string publishers)
	{
		this->publishers = publishers;
	}
	void setDevelopers(string developers)
	{
		this->developers = developers;
	}
	void setGenreElement(Genre genre)
	{
		this->genres.push_back(genre);
	}
	void setSteam(Steam steam)
	{
		this->steam = steam;
	}

	// Accessors
	string getName() const
	{
		return name;
	}
	long long getCopiesSold() const
	{
		return copiesSold;
	}
	double getRevenue() const
	{
		return revenue;
	}
	string getPublisherClass() const
	{
		return publisherClass;
	}
	string getPublishers() const
	{
		return publishers;
	}
	string getDevelopers() const
	{
		return developers;
	}
	vector<Genre> getGenres() const
	{
		return genres;
	}
	Steam getSteam() const
	{
		return steam;
	}

	// Overloaded operator<<
	friend ostream &operator<<(std::ostream &os, const Game &game)
	{

		os << "Name: " << game.name
		   << "\nCopies Sold: " << game.copiesSold
		   << "\nRevenue: $" << game.revenue
		   << "\nPublisher Class: " << game.publisherClass
		   << "\nPublishers: " << game.publishers
		   << "\nDevelopers: " << game.developers
		   << "\nGenres: ";
		for (unsigned int i = 0; i < game.genres.size(); i++)
		{
			os << game.genres.at(i).getName();
			if (i != game.genres.size() - 1) // Avoid comma for the last genre
				os << ", ";
		}
		os << "\nSteam Details:\n"
		   << game.steam;

		return os;
	}
};

#endif
