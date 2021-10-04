#include <string>
#include "support.h"
#include <fstream>


void swap(int* x, int* y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

void bubblesort(int arr[], int n)
{
	for (int i = 0; i < n - 1; i++) //Ensures n-1 passes
	{
		for (int j = 0; j < n - i - 1; j++) //Loop that actually swaps values
		{
			if (arr[j] > arr[j + 1]) //If previous is larger than next, swap
			{
				swap(&arr[j], &arr[j + 1]);
			}
		}
	}
}

void selectionsort(int arr[], int n)
{
	int min;
 
	for (int i = 0; i < n - 1 ; i++)  //Ensures n-1 passes
	{  
		min = i;
		for (int j = i + 1; j < n; j++)  //this loop depends on i because we can ignore the previous index if it has already been swapped or unchanged
		{
			if (arr[j] < arr[min])   // finds the next minimum value that needs to be swapped 
			{
				min = j;
			}
		}
		swap(&arr[min], &arr[i]);
	}
}

void insertionsort(int arr[], int n)
{
	int i, comp, j;
	for (i = 1; i < n; i++) //starts at index one until last index
	{
		comp = arr[i];  
		j = i - 1;

		while (j >= 0 && arr[j] > comp) //if arr[n-1] > arr[n], then we move int[n-1] up an index
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = comp; //insert
	}
}

int partition(int arr[], int f, int l) // f = first index l = last index
{
	int comp = arr[l]; // value chosen to divide array around, in this case its the last 
	int i = (f - 1); // Index of smaller element  

	for (int j = f; j <= l - 1; j++)
	{ 
		if (arr[j] < comp) //if value is smaller than comparison value arr[f] < arr[l]
		{
			i++;  
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[l]);
	return (i + 1);
}

void quicksort(int arr[], int f, int l)
{
	if (f < l)
	{
		int comp = partition(arr, f, l); //comp becomes last index for first array

		quicksort(arr, f, comp - 1);
		quicksort(arr, comp + 1, l);
	}
}

void merge(int arr[], int first, int m, int last) 
{
	int n1 = m - first + 1;
	int n2 = last - m;

	  
	int* ONE; //Temp array to left
	int* TWO;//Temp array to right

	ONE = new int[n1];
	TWO = new int[n2];
	
	for (int i = 0; i < n1; i++) //Now fill the arrays we just created
	{ 
		ONE[i] = arr[first + i];
	}
	for (int j = 0; j < n2; j++)
	{
		TWO[j] = arr[m + 1 + j];
	}

	
	int i = 0;
	int j = 0;
	int k = first;

	while (i < n1 && j < n2) //This while loop is comparing the values of the two arrays and inserting the smaller one into the corect position of merged array
	{
		if (ONE[i] <= TWO[j])
		{
			arr[k] = ONE[i];
			i++;				//The index value can only increase once the value has been entered into the merged array
		}
		else
		{
			arr[k] = TWO[j];
			j++;
		}
		k++;
	}
  
	while (i < n1)  //These two while loops ensure to enter any remaining values from the two sub arrays
	{
		arr[k] = ONE[i];
		i++;
		k++;
	} 
	while (j < n2)
	{
		arr[k] = TWO[j];
		j++;
		k++;
	}
}
 
void mergesort(int arr[], int first, int last)
{
	if (first < last)
	{
		int m = (first + last) / 2; // middle 

		mergesort(arr, first, m);    //begins to sort two halves
		mergesort(arr, m + 1, last);

		merge(arr, first, m, last);  //merges two halves
	}
}

/* Function to print an array */
void printArray(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		cout << arr[i] << endl;
	}
}

void print10(int arr[], int size)
{
	cout << endl << "Here is the first and last ten sorted integers from array of size "<< size << ":" << endl;
	int i;
	for(i=0; i<10; i++)
	{
		cout << arr[i] << endl;
	}
	cout <<endl;
	for(i=size-10; i<size; i++)
	{
		cout << arr[i] << endl;
	}

}

void readfile(string file, int n, int arr[])
{
	fstream data;
	data.open(file);
	int i=0;

	if (data.is_open())
	{
		while (data >> arr[i])
		{
			//cout << arr[i] << endl;
			i++;
		}
	}
	else
	{
		cout << "Error loading in file" << endl;
	}

	data.close();
		
}

 
int main() {
	int n = 500;    //First 'n' amount of integers you want to sort
	int arr[500000] = {0};  //Size of file


	int *temp;					//Declare pointer array to access outside of function
	temp = arr;
	readfile("unsort.txt", n,temp);				//Read and fill array
	
	
	double starttime = getCPUTime();
	//bubblesort(temp, n);
	//selectionsort(temp, n);
	//insertionsort(temp, n);
	quicksort(temp, 0, n);
	//mergesort(temp, 0, n);
	double endtime = getCPUTime();
	double time = endtime - starttime;


	cout<< endl << endl << endl;
	cout << "It took " << time << " seconds to sort the data" << endl;
	print10(temp, n);
	
	return 0;
}