#include <iostream>
#include <vector>

#include <queue>
using namespace std;

void TestTable()
{
	struct User
	{
		int userId = 0;
		string username;
	};

	vector<User> users;
	users.resize(1000);
}
// ���̺� Ű�� �˸� �����͸� �ܹ���(����ð� O(1)) ã�� ���

void TestHash()
{
	struct User
	{
		int userId = 0;
		string username;
	};

	vector<User> users;
	users.resize(1000);
	
	const int userId = 123456789;
	int key = (userId % 1000); // Hash ���� ��ȣ

	users[key] = User{ userId, "Rookiss" };

	User& user = users[key];
	if (user.userId == userId)
	{
		string name = user.username;
		cout << name << endl;
	}
}
// ���� ������ Hash ������� ���̵� ������ ���� �� ���̵� ������� ã�Ƽ� Username�� ã�� ����

// ���� 
// �̶� Key�� �ߺ����� �浹 ������ �߻���
// �浹 �ذ��� �ٸ� ���ڸ��� ã�� ����
// - ���� ����� ( Linear probing )
// hash(key) + 1 -> hash(key) + 2
//  ������ �ֵ鳢�� �پ����� �� ����
// - ���� ����� ( Quadratic probing )
// hash(key) + 1�� -> hash(key) + 2��
// - etc
// ���� �ʹ� �������� �ٸ� ����� ã�ƾ� ��

// ü�̴� ���
// ���� Ű���� �׳� �Ѱ��� ������� �̾ ��ġ��(vector ���� �迭 ����)
void TestHashTableChaining()
{
	struct User
	{
		int userId = 0;
		string username;
	};

	vector<vector<User>> users;
	users.resize(1000);
	const int userId = 123456789;
	int key = (userId % 1000); // Hash ���� ��ȣ
	users[key].push_back(User{ userId, "Rookiss" });

	// ���� ã��
	vector<User>& bucket = users[key];
	for (User& user : bucket)
	{
		if (user.userId == userId)
		{
			string name = user.username;
			cout << name << endl;
		}
	}
}
int main()
{

}