//Joseph Salazar c12152695
//customer.cpp


#include "customer.h"

void customer::print(ostream &out){
	out<< firstName << " " << lastName << " " << numBoxes << " " << debt << " "<< delivered << endl;
}

double customerVec::getPaymentCollected(){
	for(int x =0; x<size; x++)
	{
		if(arr[x].getstatus() == 1)
		{
			paymentcollected += arr[x].getdebt();
		}
	}
	return paymentcollected;
}

int customerVec::addCustomer(customer c){
	//Create filler array
	customer *fill;
	fill = new customer[size+1];

	//copy old data
	for(int x=0; x<size;x++)
	{
		fill[x] = arr[x];
	}

	//enter new customer
	fill[size]= c;

	//delete old and replace
	delete []arr;
	arr = fill;
	size++;
	return size;
}

bool customerVec::getCustomerAt(int loc, customer &c){ //return a customer stored in a temporary var
	if(loc < size && loc >= 0){
	c = arr[loc];
	}
	else{
		c.setc("NULL","NULL",0, 0.0);
		c.setstatus(false);
	}
	return c.getstatus();

	/* in order to utilize this function, my main might look like this
			customer f;
			Vec.getCustomerAt(0,f);
			f.print(cout);
			cout <<endl;
	*/
}

int customerVec::addPurge(customer c){
	customer *filler;
	filler = new customer[pursz+1]; //create temp

	for(int x=0; x<pursz;x++)//copy
	{
		filler[x] = pur[x];
	}

	filler[pursz] = c;
	delete []pur;
	pur = filler; //reassign
	pursz++;
	return pursz;
}

int customerVec::purge(){

	for(int x=0; x<size; x++)
	{
		if(arr[x].getstatus() == false){
			pursz = addPurge(arr[x]);
		}
	}
	delete []arr; //must reassign these variables in order for it to work with print func
	arr = pur;
	size = pursz;
	return size;	
}

void customerVec::print(ostream& out){
	for(int x=0;x<size;x++)
	{
		arr[x].print(out); 
	}
}








