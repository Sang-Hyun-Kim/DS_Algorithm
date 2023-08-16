#include <iostream>
#include <vector>
//#include <list>
#include "list.h"
// 동적배열만들기

using namespace std;

template<class T>
class Vector
{
public:
    Vector()
    {

       
    }

    ~Vector()
    {
        if (_data)
            delete[] _data;

    }
    void push_back(const T& value)
    {
        if (_size == _capacity)
        {
            // 다차서 공간 확보
            int newCapacity = static_cast<int>(_capacity * 1.5);
            if (newCapacity == _capacity)
            {
                newCapacity++;

            }

            reserve(newCapacity);

        }

        // 데이터 저장
        _data[_size] = value;
        //데이터 개수 증가
        _size++;

    }

    // capacity 수만큼 메모리 공간확보
    void reserve(int capacity)
    {
        // UB방지
        if (_capacity >= capacity)
            return;
        _capacity = capacity;
        T* newData = new T[_capacity];

        // 새로 확보한 공간에 기존 자료 복사
        for (int i = 0; i < _size; i++)
        {
            newData[i] = _data[i];
        }
        // 기존 공간 할당 해제
        if (_data)
            delete[] _data;

        // 교체
        _data = newData;
    }

    T& operator[](const int pos){ return _data[pos]; }
    int size() { return _size; }
    int capacity() { return _capacity; }

    void clear()
    {
        // 템플릿 자료형으로 다른 자료구조가 들어올 수 있으니 소멸자 호출등을 해줘야한다.
        // 메모리 오렴 방지
        if (_data)
        {
            delete[] _data;
            _data = new T[_capacity];
            // 할당 해제후 기존 capacity만큼 새로 할당
            // 실제론 new delete 대신 할당자를 따로 받아서 allocate 등을 활용
            // 직접 생성자,소멸자를 통해 해당 메모리를 활용
        }
        _size = 0;
    }

private:
    T* _data = nullptr;
    int _size = 0;
    int _capacity = 0;

};

int main()
{
    ////Vector<int> v;
    //vector<int> v;

    ////v.resize(10);

    //for (int i = 0; i < 100; i++)
    //{
    //    v.push_back(i);
    //    cout << v[i] << " " << v.size() << " " << v.capacity() << endl;
    //   
    //}
    //v.clear();
    //cout << v.size() << " " << v.capacity() << endl;

    List<int> li;
    // 중간 삭제 실습
    List<int>::iterator eraseIt;

    for (int i = 0; i < 10; i++)
    {
        if (i == 5)
        {
            // 중간 삭제 지점을 기억
            eraseIt = li.insert(li.end(), i);

        }
        else
        {
            li.push_back(i);
        }
    }
    li.pop_back();
    // 중간에 삭제해버리기
    li.erase(eraseIt);

    for (List<int>::iterator it = li.begin(); it != li.end(); it++)
    {
        cout << (*it) << endl;

    }

    // 벡터 사용시 미리 공간할당 후 사용하는게 더 효율적이다(반복할 필요가없음)
    // resize시에는 해당 공간만큼 reserve했을때처럼 size,capacity가 함께 증가
    // 처음부터 resize시, 전부 빈값으로 채워짐(int의 경우 0)
    // capacity를 100으로, 자료를 100개 넣고 resize(10)했을때
    // capacity는 그대로지만 자료는 첫 10개만 남고 다 사라짐
}
