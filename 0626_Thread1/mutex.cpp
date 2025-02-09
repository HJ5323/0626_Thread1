#include <iostream>
#include <thread>
#include <mutex>

// global
using namespace std;
mutex mtx; // 뮤텍스 객체 생성
int counter = 0; // 공유 자원

void increment() {
	for (int i = 0; i < 1000; i++)
	{
        mtx.lock(); // 임계 구역에 들어가기 전에 잠금
        counter++; // 공유 자원에 접근
        mtx.unlock(); // 임계 구역을 벗어나면 잠금 해제
	}
}

int main()
{
    thread t1(increment);
    thread t2(increment);

    t1.join();
    t2.join();

    cout << "Final counter value: " << counter << endl;
    return 0;

}

void incrementCounter() {
    for (int i = 0; i < 1000; i++) {
        lock_guard<mutex> lock(mtx);
        counter++;
    }
}