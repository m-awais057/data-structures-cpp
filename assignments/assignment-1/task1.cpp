#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<double> transactions;

void insertTransaction(double amount)
{
    transactions.push_back(amount);
}

void deleteTransaction(int index)
{
    if (index >= 0 && index < transactions.size())
    {
        transactions.erase(transactions.begin() + index);
    }
    else
    {
        cout << "Error: Index out of bounds" << endl;
    }
}

void findAndUpdate(double oldAmount, double newAmount)
{
    bool found = false;
    for (int i = 0; i < transactions.size(); i++)
    {
        if (transactions[i] == oldAmount)
        {
            transactions[i] = newAmount;
            found = true;
        }
    }
    if (!found)
    {
        cout << "Error: The amount could not be found" << endl;
    }
}

struct TransactionStats
{
    int totalCount;
    double maxTransaction;
    double minTransaction;
    double averageTransaction;
};

TransactionStats calculateStatistics()
{
    if (transactions.empty())
        return {0, 0, 0, 0};

    int total = 0;
    double max = transactions[0];
    double min = transactions[0];
    double average = 0;

    double sum = 0;
    for (int i = 0; i < transactions.size(); i++)
    {
        if (transactions[i] > max)
        {
            max = transactions[i];
        }
        if (transactions[i] < min)
        {
            min = transactions[i];
        }
        sum += transactions[i];
        total++;
    }
    average = sum / total;

    return {total, max, min, average};
}

void display()
{
    for (int i = 0; i < transactions.size(); i++)
    {
        cout << transactions[i];
        // Print a comma and space if it is NOT the last element
        if (i < transactions.size() - 1)
        {
            cout << ", ";
        }
    }
    cout << endl;
}

void displayTransactionsSorted(bool ascending)
{
    if (ascending)
    {
        sort(transactions.begin(), transactions.end());
    }
    else
        sort(transactions.rbegin(), transactions.rend());

    display();
}

void displayStatistics(TransactionStats stats)
{
    cout << "\nTransaction Statistics:" << endl;
    cout << "Total Transactions: " << stats.totalCount << endl;
    cout << "Maximum Amount: " << stats.maxTransaction << endl;
    cout << "Minimum Amount: " << stats.minTransaction << endl;
    cout << "Average Amount: " << stats.averageTransaction << endl;
}

int main()
{
    insertTransaction(2500);
    insertTransaction(3200);
    insertTransaction(1800);
    insertTransaction(2500);
    insertTransaction(4000);

    cout << "Initial Transactions: " << endl;
    display();

    deleteTransaction(2);
    cout << "\nAfter deleteTransaction(2):  " << endl;
    display();

    cout << "\nAfter findAndUpdate(2500, 2600): " << endl;
    findAndUpdate(2500, 2600);
    display();

    TransactionStats stats = calculateStatistics();
    displayStatistics(stats);

    cout << "\nSorted in descending order: " << endl;
    displayTransactionsSorted(false);

    cout << "\n--- Edge Case Testing ---" << endl;

    // 1. Test deleting an out-of-bounds index
    cout << "Attempting to delete at index 10:" << endl;
    deleteTransaction(10);

    // 2. Test updating an amount that doesn't exist
    cout << "Attempting to update 9999 to 100:" << endl;
    findAndUpdate(9999, 100);

    return 0;
}