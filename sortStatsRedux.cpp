#include <cstdlib>
#include <iostream>
#include <cstring>
using namespace std;

template<typename Item>
int insertionSort(Item arr[], int length);
template<typename Item>
void merge(Item arr[], int l, int m, int r, int &counter);
template<typename Item>
void mergeSort(Item arr[], int l, int r, int &counter);
template<typename Item>
void quickSort(Item arr[], int l, int h, int &counter);
template<typename Item>
int partition(Item arr[], int l, int h, int &counter);
template<typename Item>
void reheapDown( Item arr[], int parent, int last, int &counter );
template<typename Item>
void heapSort ( Item arr[], int n, int &counter);

main()
{
 	  int num;
 	  int seed;
 	  char print;
 	  int count1=0;
 	  int count2=0;
 	  int count3=0;
 	  
      cout << "This program demonstrates the number of characteristic " << endl;
      cout << "Operations for four different sorting algorithms." << endl;
      cout << "(Giving a representation of their Big-O behavior)" << endl;
      cout << "Please enter a number ";
	  cout << "of random numbers to be generated (1 to 5000):";
      cout << endl << "     ----> ";
      cin >> num;
	  if (num < 1 || num > 5000)
	  {
	  	cout << "Input outside of guidelines." << endl << endl << endl;
	  	return EXIT_SUCCESS;
	  }
      int a1[num];
      int a2[num];
      int a3[num];
      int a4[num];
      cout << "Please enter an integer seed ";
	  cout << "value for pseudo random number generator:";
      cout << endl << "     ----> ";
      cin >> seed;
      srand(seed);
      cout << "Would you like the sorted items to be displayed? (y/n):";
      cout << endl << "     ----> ";
      cin >> print;
      cout << endl << endl;
      for (int i=0; i<num; ++i)
      {
	   	  a1[i] = a2[i] = a3[i] = a4[i] = rand()%1000;
	  }
	  mergeSort(a2, 0, num-1, count1);
	  quickSort(a3, 0, num-1, count2);
	  heapSort(a4, num, count3);
	  cout << "Insertion Sort Operations: " << insertionSort(a1, num) << endl;
	  cout << "Merge Sort Operations:     " << count1 <<  endl;
	  cout << "Quick Sort Operations:     " << count2 << endl;
	  cout << "Heap Sort Operations:      " << count3 << endl;
	  
	  
	  cout << endl;
	  if ( print == 'y' || print == 'Y' )
	  {
	       for (int i=0; i<num; ++i)
	            cout << a1[i] << " ";
	       cout << endl;
	       for (int i=0; i<num; ++i)
	            cout << a2[i] << " ";
	       cout << endl;
	       for (int i=0; i<num; ++i)
	       	    cout << a3[i] << " ";
	       cout << endl;
	       for (int i=0; i<num; ++i)
	       		cout << a4[i] << " ";
	       cout << endl << endl;
	  }
	  else
	       return EXIT_SUCCESS;
}

template<typename Item>
int insertionSort(Item arr[], int length)
{
	int j, temp;
	int count = 0;	
	for (int k = 0; k < length; k++)
	{
		j = k;
		while (j > 0 && arr[j] < arr[j-1])
		{
			  temp = arr[j];
			  arr[j] = arr[j-1];
			  arr[j-1] = temp;
			  j--;
			  count++;
		}
	}
	return count;
}

template<typename Item>
void merge(Item arr[], int l, int m, int r, int &counter)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    int L[n1], R[n2];

    for(i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for(j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
        counter++;
    }
 
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
        counter++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
        counter++;
    }
}
 
template<typename Item>
void mergeSort(Item arr[], int l, int r, int &counter)
{
    if (l < r)
    {
        int m = l+(r-l)/2;
        mergeSort(arr, l, m, counter);
        mergeSort(arr, m+1, r, counter);
        merge(arr, l, m, r, counter);
    }
}

template<typename Item>
void swap(Item* a, Item* b)
{
    Item t = *a;
    *a = *b;
    *b = t;
}
 
template<typename Item> 
int partition (Item arr[], int l, int h, int &counter)
{
    int x = arr[h];  
    int i = (l - 1);  
 
    for (int j = l; j <= h- 1; j++)
    { 
        if (arr[j] <= x)
        {
        	counter++;
            i++;
            swap(&arr[i], &arr[j]);  
        }
    }
    counter++;
    swap(&arr[i + 1], &arr[h]);  
    return (i + 1);
}
 
template<typename Item>
void quickSort(Item arr[], int l, int h, int &counter)
{
    if (l < h)
    {
        int p = partition(arr, l, h, counter);
        quickSort(arr, l, p - 1, counter);
        quickSort(arr, p + 1, h, counter);
    }
}

template<typename Item>
void reheapDown( Item arr[], int parent, int last, int &counter )
{
	int maxChild, temp;
	bool done = false;
	while ( 2*parent+1 <= last && !done )
	{
		maxChild = 2*parent+1;
		if ( maxChild < last && arr[maxChild+1]>arr[maxChild] )
			++maxChild;
		if ( arr[parent]< arr[maxChild] )
		{
			temp = arr[parent];
			arr[parent] = arr[maxChild];
			arr[maxChild] = temp;
			parent = maxChild;
			++counter;
		}
		else
			done = true;
	}
}

template<typename Item>
void heapSort ( Item arr[], int n, int &counter)
{
	int i, temp;
	for ( i=(n-2)/2; i>=0; --i )
		reheapDown(arr,i,n-1, counter);
	for ( i = n-1; i>0; --i )
	{
		temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;
		reheapDown(arr, 0, i-1, counter);
	}
}
