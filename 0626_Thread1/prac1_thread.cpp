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
	const int num_threads = 5; // 생성할 쓰레드의 개수
	vector<thread> threads;

	// 스레드 생성
	for (int i = 0; i < num_threads; i++) {
		threads.emplace_back(printMessage, i); // i는 스레드 ID로 전달
	}

	// 모든 스레드가 종료될 때까지 대기
	for (thread& t : threads) {
		t.join();
	}

	return 0;
}

//int main()
//{
//    vector <thread> threads;
//    threads.resize(5); // 생성할 쓰레드의 개수
//    int i = 0;
//    for (thread& th : threads)
//    {
//        th = thread(printMessage, i); // i는 스레드 ID로 전달
//        i++;
//    }
//	// 모든 스레드가 종료될 때까지 대기
//    for (thread& th : threads)
//    {
//        th.join();
//    }
//    return 0;
//}