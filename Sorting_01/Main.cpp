#include <iostream>
#include <vector>
using namespace std;

// 1. 기본적인 Sort
// a. BubbleSort

void BubbleSort(vector<int>& v)
{
	const int n = v.size();
	int temp = 0;
	for (int j = 0; j < n - 1; j++)
	{
		for (int i = 0; i < n - 1-j; i++)
		{
			temp = v[i];
			if (v[i] > v[i + 1])
			{

				v[i] = v[i + 1];
				v[i + 1] = temp;
			}
		}
	}
	
}


// b. Selection Sort
void Selection(vector<int>& v)
{

	const int n = v.size();
	
	for (int i = 0; i < n - 1; i++)
	{
		int bestindex = i;
		for (int j = i + 1; j < n; j++)
		{
			if (v[j] < v[bestindex])
			{
				bestindex = j;
			}
		}

		// 교환
		int temp = v[i];
		v[i] = v[bestindex];
		v[bestindex] = temp; 

	}

}
// c. Insertion Sort
void InsertionSort(vector<int>& v)
{
	const int n = v.size();

	for (int i = 1; i< n; i++)
	{
		int insertData = v[i];

		int j;
		for (j = i-1; j >= 0; j--)
		{
			if (v[j] > insertData)
				v[j + 1] = v[j];
			else
				break;
		}
		v[j + 1] = insertData;
	}

}


int main()
{
	vector<int> v{ 1,5,3,4,2 };
	//BubbleSort(v);
	//Selection(v);
	InsertionSort(v);
	int a = 1;

}