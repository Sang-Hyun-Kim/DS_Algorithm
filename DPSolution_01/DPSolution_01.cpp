// DPSolution_01.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>

using namespace std;

// LIS(Longest Increasing Sequence)

// Seq : 1 9 2 5 7
// 부분 수열 : 일부 숫자를 지우고 남은 수열
// ex) 9를 지운 1 2 5 7
// 순 증가 부분 수열
// ex) 1 2 5 부분 수열 중 숫자의 크기가 커지는 수열


// LIS : 제일 긴 [순 증가 부분 수열]의 길이
// 1 2 5 7 = > 길이 4

vector<int> seq;
int cache[100];
// 부분 수열을 만들어 주고 몇번 째 부터 시작하고 있는지 위치를 잡아주는 pos를 인자로 가져가는 함수
int LIS(int pos)
{
    // 기본적인 DP 과정
    // 기저사항 확인

    // 캐시확인
    int& ret = cache[pos];
    if (ret != -1)
        return ret;
    // 구하기
    // 1 9 => 2 : 9보다 큰 값이 없기에 LIS가 끝남
    // 1 2 / 5 7 => 4
    // 1 5 / 7 => 3 1(0) + LIS(3) => 1+(1+LIS(4))
    // 1 7 => 2 => 1+ LIS(4)
    // 따라서 LIS(1) = 1
    // 그러므로 LIS(0) = LIS(1) + 1 = 2 
    //
    
    // 최소 seq[pos]는 있으니 1부터 시작
    ret = 1;
    
    for (int next = pos + 1; next < seq.size(); next++)
        if (seq[pos] < seq[next]) // 순 증가 부분 순열에 대한 조건 검증
            ret = max(ret, 1 + LIS(next)); // 1번째(0번칸)부터 시작하는 조합중 가장 큰것으로 선택
    
    return ret;
}

int main()
{
    // 사용하지 않는 Cache 부분 메모리 초기화
    ::memset(cache, -1, sizeof(cache));

    seq = vector<int>{ 10, 0 , 1, 9, 2, 5, 7 };


    // 코드 자체가 0번째를 기준으로 실행 한 것이니 모든 시작점에 대한 경우를 순회해서 조사해야함
    int ret = 0;
    for (int pos = 0; pos < seq.size(); pos++)
    {
        ret = max(ret, LIS(pos)); // 모든 경우중 최대값
    }

    cout << ret << endl;
}

