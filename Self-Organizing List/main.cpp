/*

	Brandon Pyle - CSIS 215 Lab 4 - Submitted April 11, 2022

	This assignment was done for my Algorithms and Data Structures class.
	The purpose of this lab was to create a self-sorting linked list that
	automatically sorts itself using three different sorting heuristics.
	The three sorting heuristics are Move to Front, Transpose, and Count.
	Descriptions of these heuristics can be found in their repsective
	functions.

	I recieved 100% on this assignment. For more information, please
	see the Approach document in the Self-Organizing List folder.

	The files that I wrote include main, count, moveToFront, and transpose.
	I also made small modifications to llist and link

*/

#include <iostream>
#include <fstream>
#include <string>
#include "moveToFront.h"
#include "count.h"
#include "transpose.h"

using namespace std;

int main()
{
	//Create objects of each organizing heuristic for characters
	MoveToFrontSOL<char> MTF;
	CountSOL<char> Count;
	TransposeSOL<char> Transpose;

	//Create objects of each organizing heuristic for strings
	MoveToFrontSOL<string> MTF_S;
	CountSOL<string> Count_S;
	TransposeSOL<string> Transpose_S;

	ifstream file; //Creat a file input stream variable
	string word; //Create a string variable to hold each word from the file

	//COUNT
	Count.add('A');
	Count.add('B');
	Count.add('C');
	Count.add('D');
	Count.add('E');
	Count.add('F');
	Count.add('G');
	Count.add('H');

	Count.find('F');
	Count.find('D');
	Count.find('F');
	Count.find('G');
	Count.find('E');
	Count.find('G');
	Count.find('F');
	Count.find('A');
	Count.find('D');
	Count.find('F');
	Count.find('G');
	Count.find('E');
	Count.find('H');
	Count.find('I');

	//MOVE TO FRONT
	MTF.add('A');
	MTF.add('B');
	MTF.add('C');
	MTF.add('D');
	MTF.add('E');
	MTF.add('F');
	MTF.add('G');
	MTF.add('H');

	MTF.find('F');
	MTF.find('D');
	MTF.find('F');
	MTF.find('G');
	MTF.find('E');
	MTF.find('G');
	MTF.find('F');
	MTF.find('A');
	MTF.find('D');
	MTF.find('F');
	MTF.find('G');
	MTF.find('E');
	MTF.find('H');
	MTF.find('I');

	//TRANSPOSE
	Transpose.add('A');
	Transpose.add('B');
	Transpose.add('C');
	Transpose.add('D');
	Transpose.add('E');
	Transpose.add('F');
	Transpose.add('G');
	Transpose.add('H');

	Transpose.find('F');
	Transpose.find('D');
	Transpose.find('F');
	Transpose.find('G');
	Transpose.find('E');
	Transpose.find('G');
	Transpose.find('F');
	Transpose.find('A');
	Transpose.find('D');
	Transpose.find('F');
	Transpose.find('G');
	Transpose.find('E');
	Transpose.find('H');
	Transpose.find('I');

	cout << "**** CHAR TEST ****" << endl << endl;

	//Print out the data from each list
	Count.printlist();
	MTF.printlist();
	Transpose.printlist();

	cout << "**** FILE TEST ****" << endl << endl;

	file.open("test.txt"); //Open the file
	
	//Loop through each word of the file until the end is reached
	while (file >> word) //Read in each word to the file input stream
	{
		//Input each word into the organizing heuristic lists using the find function
		Count_S.find(word); 
		MTF_S.find(word);
		Transpose_S.find(word);
	}

	file.close(); //Close the file

	//Print out the data from each list
	Count_S.printlist(10);
	MTF_S.printlist(10);
	Transpose_S.printlist(10);
}