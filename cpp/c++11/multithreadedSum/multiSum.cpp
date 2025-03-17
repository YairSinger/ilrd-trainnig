#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <mutex>
#include <cassert>

using namespace std;

class BankAccount {
public:
    BankAccount(int balance) : balance(balance) {}

    void deposit(int amount) {
    const std::lock_guard<std::mutex> lock(mtx);
        balance += amount; // Add to balance
    }

    bool withdraw(int amount) {
    const std::lock_guard<std::mutex> lock(mtx);
        if (balance >= amount) {
            balance -= amount; // Subtract from balance
            return true;
        }
        return false; // Insufficient funds
    }

    int getBalance()  {
   const std::lock_guard<std::mutex> lock(mtx);
        return balance;
    }

private:
   volatile int balance;
    mutex mtx;
};

void processTransactions(BankAccount& account, int numTransactions, double maxAmount) {
    std::thread::id threadId = std::this_thread::get_id();
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(1, maxAmount);

    for (int i = 0; i < numTransactions; i++) {
        int amount = dis(gen);
        account.deposit(amount);
        account.withdraw(amount);        
    }
}

bool testBank(){
    BankAccount account(1000.0); // Initial balance = 1000
    const int numThreads = 4;
    const int numTransactions = 500;

    vector<thread> threads;

    // Spawn threads to process transactions
    for (int i = 0; i < numThreads; i++) {
        threads.emplace_back(processTransactions, ref(account), numTransactions, 100.0);
    }

    // Join all threads
    for (auto& t : threads) {
        t.join();
    }
    double res = account.getBalance();
    if (res != 1000.0) {
    cout << res << endl;   // Print the final balance
        
    }
    return 1000 == int(res) ? true : false;

}

int main() {
    clock_t start = clock();
    int failedTests = 0;
    for (size_t i = 0; i < 1000; i++)
    {
        if(!testBank()){
            failedTests++;
        }
    }
cout <<failedTests<<  "/1000 faild in: " << double(clock() - start) / CLOCKS_PER_SEC <<"[sec]" << endl;    

    return 0;
}
