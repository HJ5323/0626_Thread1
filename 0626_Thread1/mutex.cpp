#include <iostream>
#include <thread>
#include <mutex>

// global
using namespace std;
mutex mtx; // ���ؽ� ��ü ����
int counter = 0; // ���� �ڿ�

void increment() {
	for (int i = 0; i < 1000; i++)
	{
        mtx.lock(); // �Ӱ� ������ ���� ���� ���
        counter++; // ���� �ڿ��� ����
        mtx.unlock(); // �Ӱ� ������ ����� ��� ����
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