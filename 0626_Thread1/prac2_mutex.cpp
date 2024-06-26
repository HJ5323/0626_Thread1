#include <iostream>
#include <thread>
#include <mutex>

using namespace std;
mutex mtx;

class BankAccount {
private:
	int balance = 1000;

public:
	void deposit(int amount) {
		balance += amount;
		cout << "입금 금액 : " << amount << " 계좌 잔액 : " << balance << endl;
	}
	void withdraw(int amount) {
		if (balance >= amount) {
			balance -= amount;
			cout << "출금 금액 : " << amount << " 계좌 잔액 : " << balance << endl;
		}
		else {
			cout << "잔액이 없습니다." << endl;
		}
	}
};

// count 횟수만큼 amount를 입금(deposit)
void deposit_iter(BankAccount& ba, int amount, int count) {
		for (int i = 0; i < count; i++) {
		mtx.lock();
		ba.deposit(amount);
		mtx.unlock();
	}
}

// count 횟수만큼 amount를 출금(deposit)
void withdraw_iter(BankAccount& ba, int amount, int count) {
	for (int i = 0; i < count; i++) {
		mtx.lock();
		ba.withdraw(amount);
		mtx.unlock();
	}
}


int main() {
	BankAccount account;

	// amount = 100, count = 100
	int amount = 100;
	int count = 100;

	// deposit_iter, withdraw_iter 스레드 객체로 생성
	thread de(deposit_iter, ref(account), amount, count);
	thread wi(withdraw_iter, ref(account), amount, count);

	// 스레드가 모두 끝날 때까지 대기
	de.join();
	wi.join();

	return 0;
}

//// 실습2. 공유 자원 보호하기
//// 24.06.19 John
//
//#include <iostream>
//#include <thread>
//#include <mutex>
//
//std::mutex g_mtx;
//
//class BankAccount {
//public:
//	BankAccount(int initial_balance) : balance(initial_balance) {}
//
//	void deposit(int amount) {
//		std::lock_guard<std::mutex> lock(mtx);
//		balance += amount;
//		std::cout << "Deposited " << amount << ", new balance: " << balance << std::endl;
//	}
//
//	void withdraw(int amount) {
//		std::lock_guard<std::mutex> lock(mtx);
//		if (balance >= amount) {
//			balance -= amount;
//			std::cout << "Withdrew " << amount << ", new balance: " << balance << std::endl;
//		}
//		else {
//			std::cout << "Failed to withdraw " << amount << ", balance: " << balance << std::endl;
//		}
//	}
//
//	int get_balance() const {
//		std::lock_guard<std::mutex> lock(mtx);
//		return balance;
//	}
//
//private:
//	int balance;
//	mutable std::mutex mtx;
//};
//
//void deposit_task(BankAccount& account, int amount, int times) {
//
//	for (int i = 0; i < times; ++i) {
//		account.deposit(amount);
//	}
//}
//
//void withdraw_task(BankAccount& account, int amount, int times) {
//	for (int i = 0; i < times; ++i) {
//		account.withdraw(amount);
//	}
//}
//
//int main() {
//	BankAccount account(1000); // 초기 잔고 1000
//
//	std::thread t1(deposit_task, std::ref(account), 50, 20); // 50을 20번 입금
//	std::thread t2(withdraw_task, std::ref(account), 30, 30); // 30을 30번 출금
//
//	t1.join();
//	t2.join();
//
//	std::cout << "Final balance: " << account.get_balance() << std::endl;
//
//	return 0;
//}
