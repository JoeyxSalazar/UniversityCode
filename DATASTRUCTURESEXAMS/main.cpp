//Joseph Salazar c12152695
//main.cpp

#include "support.h"
#include "customer.h"

int main(){
	string info = "e1data.txt";
	fstream data;
	data.open(info);

	//variables needed
	string fname; string lname; int boxes; double debt;
	customerVec Vec;

	if(data.is_open())
	{
		double stime = getCPUTime();
		while(data >> fname >> lname >> boxes >> debt)
		{
			customer c;
			c.setc(fname, lname, boxes, debt);
			Vec.addCustomer(c);
		}
		double etime = getCPUTime();
		cout << endl << endl << endl;
		cout<< "It took "<< etime - stime << " seconds to store 1000 customers in a dynamic array"<< endl << "===============================================================" << endl << endl;

		for(int x =0; x<Vec.getSize(); x++)
		{
			if(randomInRange(0,9) == 0)
			{
				Vec.setCustomerStatus(x, false);
			}
			else
			{
				Vec.setCustomerStatus(x,true);
			}
		}

		cout<< "The program collected " << Vec.getPaymentCollected() << " dollars from randomly completing deliveries" << endl << "===========================================================" << endl << endl;

		double stime2 = getCPUTime();
		Vec.purge();
		double etime2 = getCPUTime();
		cout << "It took "<< etime2 - stime2 << " seconds to purge the completed deliveries"<<endl;
		cout << "==============================================================================="<<endl;
		cout << "Here are the remaining deliveries that were unsuccessful: "<< endl << endl << endl;

		Vec.print(cout);
	}
	else
	{
		cout<< "Error reading the data file, please try again";
	}

	data.close();

	return 0;

}