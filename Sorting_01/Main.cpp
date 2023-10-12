#include <iostream>
#include <vector>

#include <queue>
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

void HeapSort(vector<int>& v)
{
	priority_queue<int,vector<int>,greater<int>> pq;
	for (int num : v)
	{
		pq.push(num);
	}
	v.clear();

	
	while (pq.empty())
	{
		v.push_back(pq.top());
		pq.pop();
	}
	// 시간 복잡도
	// O(logN){우선순위 큐에서 데이터를 밀어 넣는 시간 복잡도}
	// * O(N){ 데이터 개수 } = O(NlogN)
	//
	
	
}

// 병합정렬
// 분할 정복
// 분할(Divide) : 문제를 분할
// 정복(Conquer) : 분할된 것들을 해결
// 결합(Combine) : 결과들을 취합하여 정리

void MergeResult(vector<int>& v, int left, int mid, int right)
{
	int leftIdx = left;
	int rightIdx = mid + 1;
	vector<int> temp;
	// 나뉘어진 두 벡터의 첫번째 값끼리 비교해서 더 작은 값을 앞에 넣을 것
	while (leftIdx <= mid && rightIdx <= right)
	{
		if (v[leftIdx] <= v[rightIdx])
		{
			temp.push_back(v[leftIdx]);
			leftIdx++;
		}
		else
		{
			temp.push_back(v[rightIdx]);
			rightIdx++;
		}
	}

	// 왼쪽이 먼저 끝났으면 오른쪽 나머지를 복사
	if (leftIdx > mid)
	{
		while (rightIdx <= right)
		{
			temp.push_back(v[rightIdx]);
			rightIdx++;
		}
	}
	else
	{
		while (leftIdx <= mid)
		{
			temp.push_back(v[leftIdx]);
			leftIdx++; 
		}
	}

	// 받아온 원본 배열에 복사하기
	for (int i = 0; i < temp.size(); i++)
	{
		v[left + i] = temp[i];
	} // 우리가 v배열 전체를 사용하는 것이 아닌 함수의 인자로 left부터 right까지 일부만 받아온 것이므로
	// 인자만큼만 사용하는 것을 잊지 말자 
}
void MergeSort(vector<int>& v, int left, int right)
{
	if (left >= right)//재귀의 끝
		return;
	
	int mid = (left + right) / 2;
	MergeSort(v,left,mid);
	MergeSort(v, mid + 1, right);

	MergeResult(v, left,mid,right);
}
// 시간복잡도 분할(logN) * 결합(N) => O(NlogN)

int main()
{
	//vector<int> v{ 1,5,3,4,2 };
	vector<int> v;
	srand(time(0));
	for (int i = 0; i < 50; i++)
	{
		int randValue = rand() % 100;
		v.push_back(randValue);
	}


	//BubbleSort(v);
	//Selection(v);
	//InsertionSort(v);
	//HeapSort(v);
	MergeSort(v,0,v.size()-1);
	int a = 1;

}