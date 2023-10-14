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
// 테이블 키를 알면 데이터를 단번에(상수시간 O(1)) 찾는 방식

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
	int key = (userId % 1000); // Hash 고유 번호

	users[key] = User{ userId, "Rookiss" };

	User& user = users[key];
	if (user.userId == userId)
	{
		string name = user.username;
		cout << name << endl;
	}
}
// 대충 임의의 Hash 기법으로 아이디를 저장한 다음 그 아이디 기반으로 찾아서 Username을 찾는 예제

// 보안 
// 이때 Key값 중복으로 충돌 문제가 발생함
// 충돌 해결은 다른 빈자리를 찾는 것임
// - 선형 조사법 ( Linear probing )
// hash(key) + 1 -> hash(key) + 2
//  인접한 애들끼리 붙어있을 수 있음
// - 이차 조사법 ( Quadratic probing )
// hash(key) + 1² -> hash(key) + 2²
// - etc
// 수가 너무 많아지면 다른 방법을 찾아야 함

// 체이닝 기법
// 같은 키값을 그냥 한곳에 순서대로 이어서 배치함(vector 이중 배열 마냥)
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
	int key = (userId % 1000); // Hash 고유 번호
	users[key].push_back(User{ userId, "Rookiss" });

	// 정보 찾기
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