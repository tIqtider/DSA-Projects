/*************************************************************
	AUTHOR:     Taseen Iqtider
	FILENAME:   Header file for Genre Class
	PROGRAM 1 - CSC1310
*************************************************************/

#ifndef GENRE_H
#define GENRE_H

#include <string>
#include <iostream>
using namespace std;

// class definition
class Genre
{
private:
	string name;
	string description;

public:
	Genre() {}

	// Overloaded constructor
	Genre(string name, string description)
	{
		this->name = name;
		this->description = description;
	}

	// Mutators
	void setName(string name)
	{
		this->name = name;
	}
	void setDescription(string description)
	{
		this->description = description;
	}

	// Accessors
	string getName() const
	{
		return name;
	}
	string getDescription() const
	{
		return description;
	}

	// Overloaded operator<<
	friend ostream &operator<<(std::ostream &os, const Genre &genre)
	{
		os << genre.name << " - " << genre.description;
		return os;
	}

	// Overloaded assignment operator
	Genre &operator=(const Genre &other)
	{
		if (this == &other)
		{
			// Check for self-assignment
			return *this;
		}

		// Copy data members from the source object
		name = other.name;
		description = other.description;

		return *this;
	}
};

#endif
