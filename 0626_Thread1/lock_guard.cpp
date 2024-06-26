// mutex, lock_guard »ç¿ë¹ý
// 24.06.20 John

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;
int counter = 0;
mutex mtx;

void incrementCounter() {
    for (int i = 0; i < 1000; ++i) {
        lock_guard<mutex> lock(mtx);
        ++counter;
    }
}

int main() {
    vector<thread> threads;

    for (int i = 0; i < 4; ++i) {
        threads.emplace_back(incrementCounter);
    }

    for (auto& th : threads) {
        th.join();
    }

    cout << "Final counter value: " << counter << endl;

    return 0;
}