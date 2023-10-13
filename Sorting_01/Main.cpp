#include <iostream>
#include <vector>

#include <queue>
using namespace std;

// 1. �⺻���� Sort
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

		// ��ȯ
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
		} /*for(j=i-1; j >= 0 && v[j] > insertData ;j--)*/
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
	// �ð� ���⵵
	// O(logN){�켱���� ť���� �����͸� �о� �ִ� �ð� ���⵵}
	// * O(N){ ������ ���� } = O(NlogN)
	//
	
	
}

// ��������
// ���� ����
// ����(Divide) : ������ ����
// ����(Conquer) : ���ҵ� �͵��� �ذ�
// ����(Combine) : ������� �����Ͽ� ����

void MergeResult(vector<int>& v, int left, int mid, int right)
{
	int leftIdx = left;
	int rightIdx = mid + 1;
	vector<int> temp;
	// �������� �� ������ ù��° ������ ���ؼ� �� ���� ���� �տ� ���� ��
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

	// ������ ���� �������� ������ �������� ����
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

	// �޾ƿ� ���� �迭�� �����ϱ�
	for (int i = 0; i < temp.size(); i++)
	{
		v[left + i] = temp[i];
	} // �츮�� v�迭 ��ü�� ����ϴ� ���� �ƴ� �Լ��� ���ڷ� left���� right���� �Ϻθ� �޾ƿ� ���̹Ƿ�
	// ���ڸ�ŭ�� ����ϴ� ���� ���� ���� 
}
void MergeSort(vector<int>& v, int left, int right)
{
	if (left >= right)//����� ��
		return;
	
	int mid = (left + right) / 2;
	MergeSort(v,left,mid);
	MergeSort(v, mid + 1, right);

	MergeResult(v, left,mid,right);
}
// �ð����⵵ ����(logN) * ����(N) => O(NlogN)



int Partition(vector<int>& v, int left, int right)
{
	int pivot = v[left];
	int low = left + 1;
	int high = right;

	while (low <= high)
	{
		while (low <= right && pivot >= v[low])
			low++;

		while (high >= left + 1 && pivot <= v[high])
			high--;
		if (low < high)
			swap(v[low], v[high]);
	}

	swap(v[left], v[high]);
	return high;
}
// [5][1][3][7][9][2][4][6][8]
//	p
//	  low					high
void QuickSort(vector<int>& v, int left, int right)
{
	if (left > right)
		return;
	int pivot = Partition(v, left, right);
	QuickSort(v, left, pivot -1);
	QuickSort(v, pivot + 1, right);
}
// �ð� ���⵵
// ������ �ι������� ������ High�� Low�� ����� ���� �����̱� ������ N��
// Partition�� ȣ�� Ƚ���� ������
// Pivot�� �ִ�, �Ǵ� �ּ� ���� ��� ���ʿ� �����Ƿ� �־��� ��Ȳ�� ���� �� ������ ������ N����ŭ ȣ���
// �־��� ��� O( N��), ��������� O(NlogN)
// ���� NlogN�̿��� �� �ٸ� merge�� ��� �ӽ� ������ �����ؼ� �����ϱ� ������ ��������� ����
// QuickSort�� ��� ���絵 ���� ��κ��� ��Ȳ���� ������ �۵���

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
	//MergeSort(v,0,v.size()-1);
	QuickSort(v, 0, v.size() - 1);
	int a = 1;

}