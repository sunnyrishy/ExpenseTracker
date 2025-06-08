#include <bits/stdc++.h>
using namespace std;

struct Expense
{
    string date;
    string category;
    double amount;
    string note;
};

void showMenu()
{
    cout << "\n-----  Expense Tracker Menu  -----\n";
    cout << "1. Add Expense\n";
    cout << "2. View Expenses\n";
    cout << "3. Exit\n";
    cout << "4. View Total by Category\n";
    cout << "5. View Expenses by Date\n";
    cout << "6. View Monthly Summary\n";
    cout << "7. Export Expenses to CSV\n";
    cout << "8. Delete an Expense\n";
    cout << "9. Edit an Expense\n";
    cout << "10. Sort Expenses (1: Amount High->Low, 2: Date Old->New)\n";
    cout << "11. Visual Summary (Expense Bars by Category)\n";
    cout << "12. Search Expenses by Keyword (Category/Note)\n";
    cout << " Choose an option : ";
}

// save expenses to a file before exiting
void saveToFile(const vector<Expense> &expenses, const string &filename)
{
    ofstream outFile(filename);
    if (!outFile)
    {
        cout << "Error opening file to write. \n";
        return;
    }
    for (const Expense &e : expenses)
    {
        outFile << e.date << "|" << e.category << "|" << e.amount << "|" << e.note << "\n";
    }
    outFile.close();
    cout << "Expenses saved to file successfully. \n";
}

void loadFromFile(vector<Expense> &expenses, const string &filename)
{
    ifstream inFile(filename);
    if (!inFile)
    {
        cout << "No previous expenses found. \n ";
        return;
    }

    string line;
    while (getline(inFile, line))
    {
        stringstream ss(line);
        Expense e;
        string amountStr;

        getline(ss, e.date, '|');
        getline(ss, e.category, '|');
        getline(ss, amountStr, '|');
        getline(ss, e.note, '\n');

        e.amount = stod(amountStr); // converting string to double type
        expenses.push_back(e);
    }
    inFile.close();
    cout << " Previous expenses loaded successfully. \n";
}

int main()
{
    vector<Expense> expenses;
    loadFromFile(expenses, "expenses.txt");
    int choice;

    while (true)
    {
        showMenu();
        cin >> choice;

        if (choice == 1)
        {
            Expense newExpense;
            cout << "\nEnter Date (YYYY-MM-DD) : ";
            cin >> ws; // this will ignore leftover white spaces or new line
            getline(cin, newExpense.date);

            cout << "Enter Category (e.g., Food, Travel...) : ";
            getline(cin, newExpense.category);

            cout << "Enter Amount : ";
            cin >> newExpense.amount;

            cout << "Enter note (optional) :  ";
            cin >> ws;
            getline(cin, newExpense.note);

            expenses.push_back(newExpense);
            cout << "Expense Added Successfully ! \n";
        }
        else if (choice == 2)
        {
            if (expenses.empty())
            {
                cout << "\nNo expenses recorded \n";
            }
            else
            {
                cout << "\n-----  All Expenses  -----\n";
                for (size_t i = 0; i < expenses.size(); i++)
                {
                    cout << "Expense #" << i + 1 << ":\n";
                    cout << " Date: " << expenses[i].date << "\n";
                    cout << " Category: " << expenses[i].category << "\n";
                    cout << " Amount: " << expenses[i].amount << "\n";
                    cout << " Note: " << expenses[i].note << "\n";
                    cout << " --------------------\n";
                }
            }
        }
        else if (choice == 3)
        {
            saveToFile(expenses, "expenses.txt");
            cout << "Exiting... \n";
            break;
        }
        else if (choice == 4)
        {
            string searchCategory;
            cout << "Enter category to calculate total : ";
            cin >> ws;
            getline(cin, searchCategory);

            double total = 0.00;
            for (const auto &e : expenses)
            {
                if (e.category == searchCategory)
                {
                    total += e.amount;
                }
            }
            cout << "Total spent on " << searchCategory << " : $" << total << "\n";
        }
        else if (choice == 5)
        {
            string searchDate;
            cout << "Enter Date (YYYY-MM-DD): ";
            cin >> ws;
            getline(cin, searchDate);

            bool found = false;
            for (const auto &e : expenses)
            {
                if (e.date == searchDate)
                {
                    found = true;
                    cout << "\n Date : " << e.date;
                    cout << "\n Category : " << e.category;
                    cout << "\n Amount : $" << e.amount;
                    cout << "\nNode : " << e.note;
                    cout << endl;
                    cout << "-----------------------------------------";
                }
            }
            if (!found)
            {
                cout << "No expenses found on this date. \n";
            }
        }
        else if (choice == 6)
        {
            string searchMonth;
            cout << "Enter month (YYYY-MM): ";
            cin >> ws;
            getline(cin, searchMonth);

            double total = 0.00;
            bool found = false;
            for (const auto &e : expenses)
            {
                if (e.date.substr(0, 7) == searchMonth)
                {
                    found = true;
                    total += e.amount;
                }
            }
            if (found)
            {
                cout << "Total expenses in " << searchMonth << " : $" << total << "\n";
            }
            else
            {
                cout << "No expenses found for this month.\n";
            }
        }
        else if (choice == 7)
        {
            ofstream csvFile("expenses.csv");
            if (!csvFile)
            {
                cout << "Error creating CSV file.\n";
            }
            else
            {
                csvFile << "Date, Category, Amount, Note\n";
                for (const auto &e : expenses)
                {
                    csvFile << e.date << "," << e.category << "," << e.amount << "," << e.note << "\n";
                }
                csvFile.close();
                cout << "Expenses exported to 'expenses.csv' successfully !\n";
            }
        }
        else if (choice == 8)
        {
            if (expenses.empty())
            {
                cout << "No expenses to delete.\n";
            }
            else
            {
                int index;
                cout << "Enter the expense number to delete (1 to " << expenses.size() << "): ";
                cin >> index;

                if (index >= 1 && index <= expenses.size())
                {
                    expenses.erase(expenses.begin() + index - 1);
                    cout << "Expense deleted successfully.\n";
                }
                else
                {
                    cout << " Invalid expense number. \n";
                }
            }
        }
        else if (choice == 9)
        {
            if (expenses.empty())
            {
                cout << "No expenses to edit.\n";
            }
            else
            {
                int index;
                cout << "Enter the expense number to edit (1 to " << expenses.size() << "): ";
                cin >> index;

                if (index >= 1 && index <= expenses.size())
                {
                    Expense &e = expenses[index - 1];

                    cout << "Current Date : " << e.date << "\nEnter New Date (or -1 to skip): ";
                    string input;
                    cin >> ws;
                    getline(cin, input);
                    if (input != "-1")
                        e.date = input;

                    cout << "Current Category: " << e.category << "\nEnter New Category (or -1 to skip): ";
                    getline(cin, input);
                    if (input != "-1")
                        e.category = input;

                    cout << "Current Amount: $" << e.amount << "\nEnter New Amount (or -1 to skip): ";
                    double amt;
                    cin >> amt;
                    if (amt != -1)
                        e.amount = amt;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // this will clear input buffer

                    cout << "Current Note: " << e.note << "\nEnter New Note (or -1 to skip): ";
                    cin >> ws;
                    getline(cin, input);
                    if (input != "-1")
                        e.note = input;

                    cout << "Expense updated successfully.\n";
                }
                else
                {
                    cout << "Invalid expense number.\n";
                }
            }
        }
        else if (choice == 10)
        {
            if (expenses.empty())
            {
                cout << "No expenses to sort.\n";
            }
            else
            {
                int sortChoice;
                cout << "Sory by:\n1. Amount (High -> Low)\n2. Date (Old -> New)\nEnter choice: ";
                cin >> sortChoice;

                if (sortChoice == 1)
                {
                    sort(expenses.begin(), expenses.end(), [](const Expense &a, const Expense &b)
                         { return a.amount > b.amount; });
                    cout << "Expenses sorted by amount.\n";
                }
                else if (sortChoice == 2)
                {
                    sort(expenses.begin(), expenses.end(), [](const Expense &a, const Expense &b)
                         { return a.date < b.date; });
                    cout << "Expenses sorted by date.\n";
                }
                else
                {
                    cout << "Invalid sorting option.\n";
                }
            }
        }
        else if (choice == 11)
        {
            if (expenses.empty())
            {
                cout << "No expenses to summarize.\n";
            }
            else
            {
                map<string, double> categoryTotals;
                // sum amount per category
                for (const auto &e : expenses)
                {
                    categoryTotals[e.category] += e.amount;
                }
                cout << "\n---------------  Expense Summary  ---------------\n";
                cout << "Each = represents $10 speny\n\n";
                for (const auto &entry : categoryTotals)
                {
                    string category = entry.first;
                    double total = entry.second;
                    int barLength = static_cast<int>(total / 10);

                    cout << setw(12) << left << category << " | ";
                    for (int i = 0; i < barLength; ++i)
                        cout << "=";
                    cout << " $" << fixed << setprecision(2) << total << "\n";
                }
                cout << "----------------------------------------\n";
            }
        }
        else if (choice == 12)
        {
            if (expenses.empty())
            {
                cout << "No expenses to search. \n";
            }
            else
            {
                string keyword;
                cout << "Enter keyword to search (case-sensitive): ";
                cin >> ws;
                getline(cin, keyword);

                bool found = false;
                cout << "\n------------  Search Results  ------------\n";
                for (const auto &e : expenses)
                {
                    if (e.category.find(keyword) != string::npos || e.note.find(keyword) != string::npos)
                    {
                        found = true;
                        cout << "Date: " << e.date << "\n";
                        cout << "Category: " << e.category << "\n";
                        cout << "Amount: $" << e.amount << "\n";
                        cout << "Note: " << e.note << "\n";
                        cout << "---------------------------------\n";
                    }
                }
                if (!found)
                {
                    cout << "No expenses found matching '" << keyword << "'.\n";
                }
            }
        }
        else
        {
            cout << "Invalid choice. Try again \n";
        }
    }
    return 0;
}