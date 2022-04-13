#pragma once

#include "SelfOrderedListADT.h"
#include "llist.h"

template <typename E> class SOL : public SelfOrderedListADT<E>
{
	LList<E>* list[3];
	int comparisons[3] = { 0 };

public:
	//Default constructor/destructor
	SOL()
	{
		for (int i = 0; i < 3; i++)
		{
			list[i] = new LList<E>();
		}
	}
	~SOL() {}

	//Look for 'it'.  If found return true and execute the self-ordering
	//heuristic used for ordering the list: count, move-to-front, or transpose.
	//Increments the compare instance variable every time it compares 'it' to
	//other members of the list. Returns true if 'it' is found.
	bool find(const E& it)
	{
		bool isFound = false;
		int position = -1;

		for (int i = 0; i < 3; i++)
		{
			//std::cout << "In first for loop" << std::endl;

			if (list[i]->sizeOfList() == 0)
			{
				add(it);
				return isFound;
			}

			list[i]->moveToStart();

			for (int j = 0; j < list[i]->sizeOfList(); j++)
			{
				//std::cout << "In second for loop" << std::endl;

				comparisons[i]++;

				if (list[i]->getValue() == it)
				{
					isFound = true;
					position = i;
					break;
				}
				else
				{
					list[i]->next();
				}
			}

			if (isFound == false)
				add(it);
			else
			{
				reorder(i, position);
				//std::cout << "FOUND" << std::endl;
			}
		}
		return isFound;
	}

	//Called by find if 'it' is not in the list. Adds the new 'it' to the list
	//Can also be called independently when initially loading the list with
	//unique values and when you want to load the list in the order 'it' is 
	//read without your re-order method being called (or the number of compares
	//being incremented.
	void add(const E& it)  //Add new 'it' to the list
	{
		for (int i = 0; i < 3; i++)
		{
			list[i]->append(it);
		}
	}

	int getCompares() const   //Returns the number of accumulated compares
	{
		return comparisons[0];
	}

	int size() const       //Returns the size of the list
	{
		return list[0]->sizeOfList();
	}

	//Print the list
	//In order print of the list.  printlist() prints the entire list
	//whereas printlist(n) prints n nodes.
	void printlist()
	{
		string type[3] = { "Count", "Move to Front", "Transpose" };

		for (int i = 0; i < 3; i++)
		{
			std::cout << type[i] << " Heuristic: Size of List: " << list[0]->sizeOfList() << std::endl;
			std::cout << "Number of Compares: " << comparisons[i] << endl;
			list[i]->print();
			std::cout << std::endl << std::endl;
		}
	}

	void printlist(int n)
	{
		string type[3] = { "Count", "Move to Front", "Transpose" };

		for (int i = 0; i < 3; i++)
		{
			std::cout << type[i] << " Heuristic: Size of List: " << list[0]->sizeOfList() << std::endl;
			std::cout << "Number of Compares: " << comparisons[i] << endl;
			list[i]->print(n);
			std::cout << std::endl << std::endl;
		}
	}

	void reorder(int type, int pos)
	{
		if (type == 0) //Count
		{
			list[0]->count(pos);
		}
		else if (type == 1) //Move-To-Front
		{
			list[1]->moveToFront(pos);
		}
		else if (type == 2) //Transpose
		{
			list[2]->transpose(pos);
		}
		else
			std::cout << "Error, invalid sort type" << std::endl;
	}
};