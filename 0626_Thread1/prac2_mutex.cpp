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
		cout << "�Ա� �ݾ� : " << amount << " ���� �ܾ� : " << balance << endl;
	}
	void withdraw(int amount) {
		if (balance >= amount) {
			balance -= amount;
			cout << "��� �ݾ� : " << amount << " ���� �ܾ� : " << balance << endl;
		}
		else {
			cout << "�ܾ��� �����ϴ�." << endl;
		}
	}
};

// count Ƚ����ŭ amount�� �Ա�(deposit)
void deposit_iter(BankAccount& ba, int amount, int count) {
		for (int i = 0; i < count; i++) {
		mtx.lock();
		ba.deposit(amount);
		mtx.unlock();
	}
}

// count Ƚ����ŭ amount�� ���(deposit)
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

	// deposit_iter, withdraw_iter ������ ��ü�� ����
	thread de(deposit_iter, ref(account), amount, count);
	thread wi(withdraw_iter, ref(account), amount, count);

	// �����尡 ��� ���� ������ ���
	de.join();
	wi.join();

	return 0;
}

//// �ǽ�2. ���� �ڿ� ��ȣ�ϱ�
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
//	BankAccount account(1000); // �ʱ� �ܰ� 1000
//
//	std::thread t1(deposit_task, std::ref(account), 50, 20); // 50�� 20�� �Ա�
//	std::thread t2(withdraw_task, std::ref(account), 30, 30); // 30�� 30�� ���
//
//	t1.join();
//	t2.join();
//
//	std::cout << "Final balance: " << account.get_balance() << std::endl;
//
//	return 0;
//}
