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
		cout << "�Ա� �ݾ� : " << amount << " ���� �ܾ� : " << balance << endl;
	}
	void withdraw(int amount) {
		balance.fetch_add(-amount);
		cout << "��� �ݾ� : " << amount << " ���� �ܾ� : " << balance << endl;
	}
};

// count Ƚ����ŭ amount�� �Ա�(deposit)
void deposit_iter(BankAccount& ba, int amount, int count) {
	for (int i = 0; i < count; i++) {
		ba.deposit(amount);
	}
}

// count Ƚ����ŭ amount�� ���(deposit)
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

	// deposit_iter, withdraw_iter ������ ��ü�� ����
	thread de(deposit_iter, ref(account), amount, count);
	thread wi(withdraw_iter, ref(account), amount, count);

	// �����尡 ��� ���� ������ ���
	de.join();
	wi.join();

	return 0;
}