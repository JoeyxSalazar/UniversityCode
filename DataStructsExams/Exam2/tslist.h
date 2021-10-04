#ifndef TSLIST_H
#define TSLIST_H


#include <iostream>
#include <string>
using namespace std;

template <class A>
struct node {
	A data;
	node<A>* next;

	node() {
		next = NULL;
	}
};

template <class B>
class tslist {
private:
	//node<B>* head, * tail;
	int count;
	node<B>* iter;

public:
	node<B>* head, * tail;

	
	tslist(); //initialize
	~tslist(); //destructor

	bool isEmpty() { return (head == NULL) ? true : false; };
	int getCount() { return count; };

	int addAtHead(B&);
	int addAtTail(B&);

	int insert(B&, int(*compare)(const B&, const B&));
	void bubblesort();
	void insertionsort(int(*compare)(const B&, const B&));

	bool contains(B&); //Checks if data is already in list
	int cmp(const B&, const B&); //compare func for insert


	void clear(); //destructor method

	template <class C> //print
	friend ostream& operator<<(ostream&, const tslist<C>&);

};

template <class B>  //Initialize
tslist<B>::tslist() {
	head = NULL;
	tail = NULL;
	count = 0;

	iter = NULL;
}

template <class B>  //Destructor
tslist<B>::~tslist() {
	clear();
}

template <class B>    //Destuctor main function
void tslist<B>::clear() {

	// temp ptr
	node<B>* temp = head;
	while (head != NULL) {
		head = head->next;
		temp->next = NULL;
		delete temp;
		temp = head;
	}
	head = NULL;
	tail = NULL;
	count = 0;
}

template <class B>
int tslist<B>::addAtHead(B& data) {
if(contains(data) != true)
{
	node<B>* n;
	n = new node<B>();
	n->data = data;
	if (isEmpty()) 
	{
		head = n;
		tail = n;
	}
	else 
	{
		n->next = head;
		head = n;
	}
	count++;

	return count;
}
else
return count;

}


template <class B>
int tslist<B>::addAtTail(B& data) {
if(contains(data) != true)
{
	node<B>* n;
	n = new node<B>();
	n->data = data;
	if (isEmpty()) {
		head = n;
		tail = n;
	}
	else {
		tail->next = n;
		tail = n;
	}
	count++;
	return count;
}
else
return count;

}

template <class B>               //Part 2, 1a
bool tslist<B>::contains(B& value)
{
	node<B> *temp;
	temp=head;
	while(temp != NULL)
	{
		if(temp->data == value)
		{
			//cout << "This value exists in the list" << endl;
			return 1;
		}
		temp = temp->next;
	}	
	//cout << "Value does not exist" << endl;
	return 0;
}

template<class B>
int cmp(const B &a, const B &b)
{
	int ret = 0;
	if (a<b) ret = -1;
	else if (a>b) ret = 1;
	return ret;
}


// compare(a,b): -1:a<b, 0:a==b, 1:a>b
template <class B>
int tslist<B>::insert(B& data, int(*compare)(const B&, const B&))
{

	if (isEmpty())
	{
	 	return addAtHead(data);
	}
	else
	{
		if (compare(data, head->data) <= 0) 
		{
			return addAtHead(data);
		}
		else if (compare(data, tail->data) >= 0) 
		{
			return addAtTail(data);
		}
		else 
		{
			if(contains(data) != true)
			{
			node<B>* n = new node<B>;
			n->data = data;
			node<B>* travf, * travb;
			travf = head;
			travb = NULL;
			while (compare(data, travf->data) > 0) {
				travb = travf;
				travf = travf->next;
			}
			n->next = travf;
			travb->next = n;
			count++;
			return count; 
			}
			else
				return count;
		}
	}
}

template <class B>     //Part 2, 3 in case my insertionsort is wrong
void tslist<B>::bubblesort()
{
	node<B> *i;
	node<B> *j;
	B temp;

	for(i = head; i != NULL; i = i->next)
	{
		for(j=i->next; j != NULL; j= j->next)
		{
			if(i->data > j->data)
			{
				temp = i->data;
				i->data = j->data;
				j->data = temp;
			}
		}
	}
}

template <class B>
void tslist<B>::insertionsort(int(*cmp)(const B&, const B&))
{
	tslist<B> *newlist;
	newlist = new tslist<B>;

	node<B> *temp;
	temp = head;

	while(temp != NULL)
	{
		newlist->insert(temp->data,cmp);
		temp = temp->next;
	}
	head = newlist->head;
}


// print list
// assumes data supports operator<<
template <class B>
ostream& operator<<(ostream& out, const tslist<B>& t) {
	node<B>* temp = t.head;
	while (temp != NULL) {
		out << temp->data << endl;
		temp = temp->next;
	}
	return out;
}

#endif

