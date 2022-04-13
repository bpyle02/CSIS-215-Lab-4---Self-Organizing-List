#pragma once

#include "SelfOrderedListADT.h"
#include "llist.h"

template <typename E> class TransposeSOL : public SelfOrderedListADT<E>
{
	LList<E>* list;
	int comparisons;

public:
	//Default constructor/destructor
	TransposeSOL()
	{
		list = new LList<E>();
	}

	~TransposeSOL() {}

	//Look for 'it'.  If found return true and execute the self-ordering
	//heuristic used for ordering the list: count, move-to-front, or transpose.
	//Increments the compare instance variable every time it compares 'it' to
	//other members of the list. Returns true if 'it' is found.
	bool find(const E& it)
	{
		bool isFound = false; //Boolean used to determine whether the record has been found
		int position = -1; //Int variable used to make a copy of the position of the record if found

		//If the size of the list is 0, just add the record
		if (list->length() == 0)
		{
			add(it); //Adds the record to the list
			return isFound; //Returns false, exiting the function
		}

		list->moveToStart(); //Moves to the beginning of the list in order to begin the search

		//Loops through the following code until i reaches the value of the length of the list
		for (int i = 0; i < list->length(); i++)
		{
			comparisons++; //Increments comparisons
			position = i; //Makes a copy of i and stores it in the position variable

			//Checks to see if the value of the record at the position matches the value passed in ('it')
			if (list->getValue() == it)
			{
				isFound = true; //Sets isFound to true
				list->incrementFrequency(); //Increments the frequency variable
				reorder(position); //Call the reorder function to sort the list
				break; //Exits the function
			}
			else //If the value is not a match, move to the next element in the list
			{
				list->next(); //Moves to the next element in the list as long as it is not the tail
			}
		}

		//If the element is not found, the following code will execute
		if (isFound == false)
		{
			add(it); //Add the element to the list
			position = list->length() - 1; //Set position to the last element in the list
		}

		list->moveToStart(); //Move the the beginning of the list

		return isFound;
	}

	//Called by find if 'it' is not in the list. Adds the new 'it' to the list
	//Can also be called independently when initially loading the list with
	//unique values and when you want to load the list in the order 'it' is 
	//read without your re-order method being called (or the number of compares
	//being incremented.
	//Add new 'it' to the list
	void add(const E& it)
	{
		list->append(it);
	}

	//Returns the number of accumulated compares
	int getCompares() const   
	{
		return comparisons;
	}

	//Returns the size of the list
	int size() const
	{
		return list->length();
	}

	//Print the list
	//In order print of the list.  printlist() prints the entire list
	//whereas printlist(n) prints n nodes.
	void printlist()
	{
		std::cout << "**** Transpose Heuristic ****" << std::endl;
		std::cout << "Size of List: " << list->length() << std::endl;
		std::cout << "Number of Compares: " << comparisons << endl;
		list->print();
		std::cout << std::endl << std::endl;
	}

	void printlist(int n)
	{
		std::cout << "**** Transpose Heuristic ****" << std::endl;
		std::cout << "Size of List: " << list->length() << std::endl;
		std::cout << "Number of Compares: " << comparisons << endl;
		list->print(n);
		std::cout << std::endl << std::endl;
	}

	//This function reorders the nodes using the Transpose Heuristic
	//The Transpose Heuristic simply swaps the accessed record with
	//the record immediately in front of it
	void reorder(int pos)
	{
		E temp; //Temporary variable used to copy one of the nodes
		int tempFrequency = 0; //Temporary variable to hold a copy of the frequency

		list->moveToPos(pos); //Moves to the node that is found in the find() function

		tempFrequency = list->getCurrentFrequency(); //Sets tempFrequency to the lists current frequency
		temp = list->remove(); //Removes the node at the current position and sets temp equal to that node

		//As long as pos is a value greater than 0, decrement it
		if (pos != 0)
			pos--;

		list->moveToPos(pos); //Moves to the new position, which is now the previous node
		list->insert(temp); //Inserts the element stored in temp into the linked list at the current position
		list->setCurrentFrequency(tempFrequency); //Sets the frequency of the list to the tempFrequency variable
		list->moveToStart(); //Moves back to the beginning of the list in order to reset
	}
};