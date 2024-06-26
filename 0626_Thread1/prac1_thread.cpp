#include <iostream>
#include <thread>
#include <vector>

using namespace std;

void printMessage(int thread_num) {
	for (int i = 0; i < 10; i++)
	{
		cout << thread_num << " : " << i + 1 << endl;
	}
}

int main() {
	const int num_threads = 5; // ������ �������� ����
	vector<thread> threads;

	// ������ ����
	for (int i = 0; i < num_threads; i++) {
		threads.emplace_back(printMessage, i); // i�� ������ ID�� ����
	}

	// ��� �����尡 ����� ������ ���
	for (thread& t : threads) {
		t.join();
	}

	return 0;
}

//int main()
//{
//    vector <thread> threads;
//    threads.resize(5); // ������ �������� ����
//    int i = 0;
//    for (thread& th : threads)
//    {
//        th = thread(printMessage, i); // i�� ������ ID�� ����
//        i++;
//    }
//	// ��� �����尡 ����� ������ ���
//    for (thread& th : threads)
//    {
//        th.join();
//    }
//    return 0;
//}