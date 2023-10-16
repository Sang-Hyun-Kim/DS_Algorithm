// DP(DynamicProgramming).cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <Windows.h>
//#include <sysinfoapi.h>

using namespace std;
int cache[50][50]; // 함수의 모양에 따라 달라지는 것을 유의
int combination(int n, int r);

int main()
{
    ::memset(cache, -1, sizeof(cache)); // 초기화

    unsigned __int64 start = GetTickCount64();

    int lotto = combination(45, 6);
    unsigned __int64 end = GetTickCount64();

    cout << lotto << endl;
    cout << end - start << " ms" << endl;
    
}

int combination(int n, int r)
{
    if (r == 0 || n == r)
        return 1;
    int& ret = cache[n][r];

    if (ret != -1) // 조회
        return ret; // 이미 있으니까 반환

    // 없을 경우 저장
    return ret = combination(n - 1, r - 1) + combination(n - 1, r);
}
// 해당 재귀함수 호출은 시간이 많이 걸림
// 똑같은 함수를 여러번 호출하는 시간 낭비가 발생함
// DP는 이미 수행된 함수를 Cach[][]를 통해 memorization하여 재사용함으로써
// 동작 시간 소요를 감소시키는 방법이다.

// DP
// 1. 기저 사례 만들기(0일때, 1일때 , etc...)
// 2. 사례에 대한 캐시 조회 후
// 2-1. 이미 답을 구한적이 있으면 바로 반환
// 2-2. 새로 답을 구해서 캐시에 저장