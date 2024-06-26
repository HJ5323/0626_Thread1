#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

class BankAccount {
private:
	atomic<int> balance;

public:
	void deposit(int amount) {
		balance.fetch_add(+amount);
		cout << "입금 금액 : " << amount << " 계좌 잔액 : " << balance << endl;
	}
	void withdraw(int amount) {
		balance.fetch_add(-amount);
		cout << "출금 금액 : " << amount << " 계좌 잔액 : " << balance << endl;
	}
};

// count 횟수만큼 amount를 입금(deposit)
void deposit_iter(BankAccount& ba, int amount, int count) {
	for (int i = 0; i < count; i++) {
		ba.deposit(amount);
	}
}

// count 횟수만큼 amount를 출금(deposit)
void withdraw_iter(BankAccount& ba, int amount, int count) {
	for (int i = 0; i < count; i++) {
		ba.withdraw(amount);
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