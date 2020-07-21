#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>

using namespace std;

// ===================== Random Functions ================
string printRandomString(int n)
{
    const int MAX = 26;
    char alphabet[MAX] = {'a', 'b', 'c', 'd', 'e', 'f', 'g',
                          'h', 'i', 'j', 'k', 'l', 'm', 'n',
                          'o', 'p', 'q', 'r', 's', 't', 'u',
                          'v', 'w', 'x', 'y', 'z'};

    string res = "";
    for (int i = 0; i < n; i++)
        res = res + alphabet[rand() % MAX];

    return res;
}

// ===================== Map  ================
class Tree
{
public:
};

// ===================== Tree  ================
class Map
{
public:
};

// ===================== InventorySystem Class ================
class InventorySystem
{
public:
    // === Item Sub-Class
    struct Item
    {
        string name;
        ;
        int idNumber;
        ;
        int inStock;
        ;
    };

    // Array with inventory
    vector<Item> inventoryVector;

    // === Methods/Functions
    void inventoryGenerator(int inventoryNumber)
    {
        for (int i = 0; i < inventoryNumber; i++)
        {
            // randomly generate an item
            // initialize it and gives a random inStock from 1-1000
            Item item;
            item.name = printRandomString(10);
            item.idNumber = i + 1;
            item.inStock = rand() % 1000;

            // add item to inventory list/arry
            inventoryVector.push_back(item);
        }
    }
    void printInventoryVector()
    {
        for (int i = 0; i < inventoryVector.size(); i++)
        {
            cout << "Name: " << inventoryVector[i].name << endl;
            cout << "ID Number: " << inventoryVector[i].idNumber << endl;
            cout << "Amount in Stock: " << inventoryVector[i].inStock << endl;
            cout << endl;
        }
    }
};

// ===================== Test Cases ===========================
/*
    1. Run the function being tested on each data structure
    2. Print time 

*/
void test1()
{
    // === Test insert

    // --- Test in Map
    time_t start, end;
    time(&start);
    //Function being tested
    time(&end);
    double mapExecutionTime = double(end - start);

    // --- Test in Tree
    time(&start);
    //Function being tested
    time(&end);
    double treeExecutionTime = double(end - start);

    // --- Print execution times
    cout << "Execution time by map : " << fixed << mapExecutionTime << setprecision(5);
    cout << " sec " << endl;

    cout << "Execution time by tree : " << fixed << treeExecutionTime << setprecision(5);
    cout << " sec " << endl;
};
void test2()
{
    // === Test delete

    // --- Test in Map
    time_t start, end;
    time(&start);
    //Function being tested
    time(&end);
    double mapExecutionTime = double(end - start);

    // --- Test in Tree
    time(&start);
    //Function being tested
    time(&end);
    double treeExecutionTime = double(end - start);

    // --- Print execution times
    cout << "Execution time by map : " << fixed << mapExecutionTime << setprecision(5);
    cout << " sec " << endl;

    cout << "Execution time by tree : " << fixed << treeExecutionTime << setprecision(5);
    cout << " sec " << endl;
};
void test3(){
    // === Test edit
};
void test4(){
    // Test search

    // Test search for small data sets

    // test search for large data sets

};

// Runs whole program
void run()
{
    InventorySystem system1;
    // system1.inventoryGenerator(100);
    // system1.printInventoryVector();

    /*
        test1();
        test2();
        test3();
        test4();
        test5();
        test6();
        test7();
    */
};

// ===================== Main Method ===========================
int main()
{
    // Main is used to test whatever you're working on
    // Just make sure to clear main before pushing/commiting any changes

    return 0;
};
