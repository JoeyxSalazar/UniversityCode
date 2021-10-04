//Joseph Salazar c12152695
//customer.h


#ifndef customer_h
#define customer_h

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class customer{
private:
	string firstName;
	string lastName;
	int numBoxes;
	double debt;
	bool delivered;

public:
	customer(){ //constructor
		firstName = "";
		lastName = "";
		numBoxes = 0;
		debt = 0.00;
		delivered = 0;
	}

	~customer(){} //destructor
	void setc(string fname, string lname, int boxes, double due){ //set customer
	firstName = fname;
	lastName = lname;
	numBoxes= boxes;
	debt = due;
	} 
	void setstatus(bool stat){
	delivered = stat;
	} //set delivery status  

	string getfname() { return firstName;} //get fname
	string getlname(){return lastName;} //get lname
	int getnumboxes(){return numBoxes;} //get numboxes
	double getdebt(){return debt;} //get debt
	bool getstatus(){return delivered;} //get status
	void print(ostream &out);
	
};

class customerVec{
private:
	customer *arr = NULL;
	int size;
	customer *pur = NULL;
	int pursz;
	double paymentcollected;

public:
	customerVec(){
		size =0;
		pursz=0;
		paymentcollected = 0.00;
	}//constructor
	~customerVec(){}//destructor

	int getSize() {return size;} //get size of array
	double getPaymentCollected(); //get payment collected
	int addCustomer(customer cust); //add customer, return size array
	bool getCustomerAt(int loc, customer &cust); //??

	void setCustomerStatus(int loc, bool status){ //set customer status
	arr[loc].setstatus(status);
	}

	int addPurge(customer c); //add failed delivery to list i.e purge completed ones
	int purge(); // loop through and find completed deliveries to remove
	void print(ostream&);
};


#endif 