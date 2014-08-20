/**
 * @file psort.cpp
 */

/**
 * Public wrapper for the parallel sort implementation.
 * @param array The structure to sort
 */
#include "psort.h"
//define constants
//#define PARALLEL_INSERTION_SWITCH 200
#define INSERTION_QUICK_SWITCH 12//11
#define PARALLEL_MERGE_SWITCH 1200//1200
#define PARALLEL_SORT_SWITCH 15050//15000
//end of define constants

//psort
template <class T>
void ParallelSort::psort(vector<T>* array)
{
	psort(*array);
}

template <class T>
void ParallelSort::psort(vector<T> & array)
{
	if(array.size()<PARALLEL_SORT_SWITCH) modified_quicksort(array, 0, array.size()-1);
	else Sorter(array);
}
//end psort

//insertion sort
// template <typename T>
// void ParallelSort::insertionsort(vector<T> &array, int h, int t)
// {
// 	 int key, i;
// 	 for(int j=h+1;j<=t;j++)
// 	 {
// 	 	key=array[j];
// 	 	i=j-1;
// 	 	while(i>=h&&array[i]>key)
// 	 	{
// 	 		array[i+1]=array[i];
// 	 		i--;
// 	 	}
// 	 	array[i+1]=key;
// 	 }
// }

template<typename T>
void ParallelSort::insertionsort(vector<T> &array, int head, int tail)
{
	//int i=head;
	//if(array.size()<PARALLEL_INSERTION_SWITCH)
	//{
		for (int i=head; i <= tail; i++) 
		{
		//#pragma omp parallel for private(j)
			for (int j = i; j > head && array[j - 1] > array[j]; j--) 
			{
				swap(array, j, j - 1);
			}
		}
	//}
// 	else
// 	{
// 		#pragma omp parallel for
// 		for (int i=head; i <= tail; i++) 
// 		{
// 			//#pragma omp parallel for private(j)
// 			for (int j = i; j > head && array[j - 1] > array[j]; j--) 
// 			{
// 				swap(array, j, j - 1);
// 			}
// 		}
// 	}
// 	return;
}

//quicksort
template<typename T>
void ParallelSort::modified_quicksort(vector<T> &array, int head, int tail)
{
        if (head >= tail)
            return;

        int len = tail - head + 1;
        // use insertion sort if datasize < INSER...
        if (len <= INSERTION_QUICK_SWITCH) 
        {
        	//insertionsort(array, head, tail);
  	        insertionsort(array, head, tail);
  //           for (int i=head; i <= tail; i++) 
		// 	{
		// //#pragma omp parallel for private(j)
		// 		for (int j = i; j > head && array[j - 1] > array[j]; j--) 
		// 		{
		// 			swap(array, j, j - 1);
		// 		}
		// 	}
        }

        // Find the pivot
        int mid = head + (len >> 1);
        if (len > INSERTION_QUICK_SWITCH) {
            int left = head;
            int right = head + len - 1;
            if (len > 40) {
                int s = len / 8;
                left = median(array, left, left + s, left + 2 * s);
                mid = median(array, mid - s, mid, mid + s);
                right = median(array, right - 2 * s, right - s, right);
            }
            mid = median(array, left, mid, right);
        }

        T the = array[mid];

        //a,b scan from left and c,d scan from right
        int l1 = head, l2 = l1, r1 = head + len - 1, r2 = r1;
        while (true) {
            //try to find element bigger than pivot
            //#pragma omp parallel for
            for ( ;l2 <= r1 && array[l2] <= the;l2++) {
                //swap the element same as pivot to the left
                if (array[l2] == the)
                    swap(array, l1++, l2);
                //l2++;
            }
            //try to find element smaller than pivot
            //#pragma omp parallel for
            for (;r1 >= l2 && array[r1] >= the;r1--) {
                //swap the element same as pivot to the left
                if (array[r1] == the)
                    swap(array, r1, r2--);
                //r1--;
            }
            if (l2 > r1)
                break;
            //swapping
            swap(array, l2++, r1--);
        }

        //swap the same elements to the middle
        int small, sum = head + len;
        small = min(l1 - head, l2 - l1);
        groupswap(array, head, l2 - small, small);
        small = min(r2 - r1, sum - r2 - 1);
        groupswap(array, l2, sum - small, small);

        //recursion
        if ((small = l2 - l1) > 1)
            modified_quicksort(array, head, small + head - 1);
        if ((small = r2 - r1) > 1)
            modified_quicksort(array, sum - small, sum - 1);

    //}
	// int pivotele;
	// int i=head-1, j=tail;
	// if(tail-head<INSERTION_QUICK_SWITCH)
	// {
	// 	insertionsort(array, head, tail);
	// 	return;
	// }

	// if(head<tail)
	// {
	// 	pivotele=pivot(array, head, tail);
	// 	modified_quicksort(array, head, pivotele-1);
	// 	modified_quicksort(array,pivotele+1,tail);
	// }
}

template<typename T>
int ParallelSort::median(vector<T> &array, int a, int b, int c)
{
	return array[a]<array[b]?(array[b]<array[c]?b:array[a]<array[c]?c:a):array[b]>array[c]?b:array[a]>array[c]?c:a;
}

// template<typename T>
// int ParallelSort::pivot(vector<T> array, int head, int tail)
// {
// 	int pivot=head;
// 	T pivotele=array[head];
// 	for(int i=head+1;i<=tail;i++)
// 	{
// 		if(array[i]<=pivotele)
// 		{
// 			pivot++;
// 			swap(array[i],array[pivot]);
// 		}
// 	}
// 	swap(array[pivot],array[head]);
// 	return pivot;
// }

template<typename T>
void ParallelSort::swap(vector<T> &array, int a, int b)
{
	T temp=array[a];
	array[a]=array[b];
	array[b]=temp;
}

template<typename T>
void ParallelSort::groupswap(vector<T> &array, int a, int b, int c)
{
	for (int i = 0; i < c;i++, a++, b++)
	{
		swap(array, a, b);
	}
}
//end of quicksort

//merge
template<typename T>
void ParallelSort::unbalancedmerge(vector<T> & array, int l, int m, int r)
{
	int f = 0;
	int s = l;
	int mid = m+1;

	T *temp=new T[r-l+1];

	while(s<=m&&mid<=r)
	{
		if(array[s]<array[mid]) temp[f++]=array[s++];
		else temp[f++]=array[mid++];
	}

	//if the two parts have different length, then merge the rest
	while(s<=m) temp[f++]=array[s++];

	while(mid<=r) temp[f++]=array[mid++];

	if(r-l>PARALLEL_MERGE_SWITCH)
	{
		#pragma omp parallel for
		for(int i=l;i<=r;i++) array[i]=temp[i-l];
	}
	else
	{
		for(int i=l; i<=r; i++) array[i]=temp[i-l];
	}
}

template<typename T>
void ParallelSort::balancedmerge(vector<T> & array, int l, int m, int r)
{
	int start=l;
	int mid=m+1;
	while((start<=m)&&(mid<=r))
	{
		if(array[start]>array[mid])
		{
			// T temp = array[mid];
			// array[mid]=array[start];
			// array[start]=temp;
			swap(array, mid, start);
			mid++;
		}
		else start++;
	}
}
// 	if (mid<r)
// 	{
// 		while(mid<r)
// 		{
// 			if(array[mid]<array[mid-1])
// 			{
// 				swap(array,mid-1,mid);
// 			}
// 			mid++;
// 		}
// 	}
// 	if (start<m)
// 	{
// 		while(start<m)
// 		{
// 			if(array[start]>array[mid+1])
// 			{
// 				swap(array,start,mid+1);
// 			}
// 			start++;
// 		}
// 	}
template<typename T>
void ParallelSort::merge(vector<T> & array, int l, int m, int r)
{
	if(m-l==r-m)
	{
		balancedmerge(array, l, m, r);
	}
	else
	{
		unbalancedmerge(array, l, m, r);
	}
}


//end of merge

//Sorter
template<typename T>
void ParallelSort::Sorter(vector<T> & array)
{
	int size=array.size();
	int sortsize=size/8;

	#pragma omp parallel sections
	{
		#pragma omp section
		{
			modified_quicksort(array, 0, sortsize-1);
		}
		#pragma omp section
		{
			modified_quicksort(array, sortsize, sortsize*2-1);
		}
		#pragma omp section
		{
			modified_quicksort(array, sortsize*2, sortsize*3-1);
		}
		#pragma omp section
		{
			modified_quicksort(array, sortsize*3, sortsize*4-1);
		}
		#pragma omp section
		{
			modified_quicksort(array, sortsize*4, sortsize*5-1);
		}
		#pragma omp section
		{
			modified_quicksort(array, sortsize*5, sortsize*6-1);
		}
		#pragma omp section
		{
			modified_quicksort(array, sortsize*6, sortsize*7-1);
		}
		#pragma omp section
		{
			modified_quicksort(array, sortsize*7, size-1);
		}
	}

	#pragma omp parallel sections
	{
		#pragma omp section
		{
			merge(array, 0, (2*sortsize-1)/2, sortsize*2-1);
		}
		#pragma omp section
		{
			merge(array, sortsize*2, (6*sortsize-1)/2, sortsize*4-1);
		}
		#pragma omp section
		{
			merge(array, sortsize*4, (10*sortsize-1)/2, sortsize*6-1);
		}
		#pragma omp section
		{
			merge(array, sortsize*6, sortsize*7-1, size-1);
		}
	}

	#pragma omp parallel sections
	{
		#pragma omp section
		{
			merge(array, 0, (4*sortsize-1)/2, sortsize*4-1);
		}
		#pragma omp section
		{
			merge(array, sortsize*4, sortsize*6-1, size-1);
		}
	}
	//#pragma omp single
			merge(array, 0, sortsize*4-1, size-1);
}

