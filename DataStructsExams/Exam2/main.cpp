#include "tslist.h"
#include "support.h"
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

const string alph = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

string standard(string input)
{
	for(int x=0;x<26;x++) //Removes uppercase
		{
			for(int i=0; i<input.size(); i++)
			{
				if(input[i] == alph[x])
				{
					input[i] = alph[x+26];
				}
			}
		}
	for(int i=0, l = input.size(); i<l; i++) //Removes punctuation
		{
			if(ispunct(input[i]))
			{
				input.erase(i--,1);
				l = input.size();
			}
		}
		//cout << input;
		return input;
} 

void words(struct node<string> *head, string wordarray[])
{
	int i=0;
	while(head != NULL)
	{
		wordarray[i] = head->data;
		head = head->next;
		i++;
	}
	//cout << "There are " << i << " words in Paradise Lost"<<endl;
}

void printwords(string word[], int n)
{
	cout << "There are " << n << " amount of words in the array: " << endl;
	for(int i=0; i<n; i++) //n
	{
		cout << word[i] << endl;
	}
}
void addheadwords(string word[], int n)
{
	tslist<string> wordlist;
	for(int i=0; i<n; i++) //n
	{
		wordlist.addAtHead(word[i]);
	}
	//cout <<"Before bubblesort:" << endl;
	//cout << wordlist << endl;
	//double stime = getCPUTime();
	//wordlist.bubblesort();
	wordlist.insertionsort(cmp);
	//double etime = getCPUTime();
	//cout << "It took " << etime - stime << " seconds" << endl;

	/*
	node<string> *temp;
	temp = wordlist.head;
	cout << "Heres the first 100 words from insertionsort:" << endl;
	int c=0;
	while(temp != NULL && c<100)
	{
		cout << temp->data << endl;
		temp = temp->next;
		c++;
	}
	*/
	
}

void insertwords(string word[], int n)
{
	tslist<string> wordlist;
	for(int i=0; i<n; i++)
	{
		wordlist.insert(word[i],cmp);
	}
}



int main()
{
	fstream file;
	string filename = "plost.txt";
	file.open(filename.c_str());
	//file.open("idata.txt");

	string value;
	tslist<string> list;

	string *wordarray;
	int i = 0;
	
	 //This is for entering ints into a linked list
	/*
	if (file.is_open())
	{
			while (file >> value && i<1000) 
			{
				list.insert(value,cmp); //or .addAtTail or .insert(value,cmp) Part 1, 2a
				i++;		
			}
	}
	*/
	
	if (file.is_open()) //This is for entering strings into a linked list
	{
			while (file >> value /*&& i<10*/) 
			{
				string word = standard(value);
				list.addAtTail(word); //or .addAtTail(word) or .insert(word,cmp) Part 1, 2b
				i++;		
			}
	}
	
	else
	{
		cout << "Error reading file" << endl;
	}

	wordarray = new string[i];

	//Part 2, 4 below
	words(list.head,wordarray); //inserts words into an array
	//printwords(wordarray,i);    //prints the array of words
	double stime = getCPUTime();
	//insertwords(wordarray,i);   //inserts strings from array into a linked list and sorts simultaneuosly
	addheadwords(wordarray,i);   //adds words at head of new list and then bubblesorts/insertionsorts list
	double etime = getCPUTime();
	cout << "It took " << etime-stime << " seconds to sort"<<endl;
	file.close();


	return 0;
}
