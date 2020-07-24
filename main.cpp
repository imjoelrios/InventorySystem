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
// ===================== InventorySystem Class ================
class InventorySystem
{
public:
    // === Item Sub-Class
    struct Item
    {
        string name;
        int idNumber;
        int inStock;

        Item()
        {
            name = "";
            idNumber = 0;
            inStock = 0;
        }

        Item(string name_, int idNumber_, int inStock_)
        {
            name = name_;
            idNumber = idNumber_;
            inStock = inStock_;
        }
    };

    // Array with inventory
    vector<Item> inventoryVector;

    // ===================== Map  ================
    //currently based on the the keys being unsorted (if we wanted to sort them either numerically or alphabetically it would require a few changes)
    class Map
    {
    private:
        vector<int> keys;
        vector<InventorySystem::Item> values;
        int size;

    public:
        // Default constructor
        Map()
        {
        }
        // Parameterized constructor
        Map(vector<InventorySystem::Item> &inventory)
        {
            //storing the inventory data in this map data structure
            //a key and its value are at same location in their corresponding containers.
            size = inventory.size();
            for (int i = 0; i < size; i++)
            {
                //the key is the idNumber (could easily be changed)
                keys.push_back(inventory.at(i).idNumber);
                //the value is the Item itself
                values.push_back(inventory.at(i));
            }
        }
        void printMap()
        {
            for (int i = 0; i < size; i++)
            {
                cout << "idNumber: " << keys.at(i) << endl;
                cout << "Name: " << values.at(i).name << endl;
                cout << "Amount: " << values.at(i).inStock << endl;
            }
        }
        void add(InventorySystem::Item item)
        {
            //simply adds the key and value to the end of corresponding vectors
            //time complexity is O(1)
            keys.push_back(item.idNumber);
            values.push_back(item);
            size++;
        }
        void remove(int idNumber)
        {
            //time complexity is log(n)
            int index = helpFind(idNumber, 0, size);
            //this replaces the item to be removed with the last item and then deletes the last item which all can be done in O(1)
            if (index >= 0)
            {
                keys.at(index) = keys.at(size - 1);
                values.at(index) = values.at(size - 1);
                keys.pop_back();
                values.pop_back();
                size--;
            }
            /* this would just delete the item to be removes and shifts all the other ones which is done in O(n)
        if(index >= 0){
            keys.erase(keys.begin() + index);
            values.erase(values.begin() + index);
        }*/
        }
        int helpFind(int idNumber, int first, int last)
        {
            //binarySearch so time complexity is log(n)
            if (first > last)
                return -1;
            int middle = (first + last) / 2;
            if (keys.at(middle) == idNumber)
                return middle;
            if (keys.at(middle) < idNumber)
                return helpFind(idNumber, middle + 1, last);
            else
                return helpFind(idNumber, first, middle - 1);
        }
        void find(int idNumber)
        {
            //time complexity is O(log(n))
            int index = helpFind(idNumber, 0, size);
            //print statements could be removed if we want to implement them in main instead
            if (index < 0)
                cout << "Item not found" << endl;
            else
            {
                cout << "Name: " << values.at(index).name << endl;
                cout << "idNumber: " << keys.at(index) << endl;
                cout << "Number of items: " << values.at(index).inStock << endl;
            }
        }
    };

    // Map with inventory
    Map inventoryMap;

    // ===================== Tree  ================
    class Tree
    {
    };

    // Tree with inventory
    Tree inventoryTree;

    // === Methods/Functions
    void add(string name, int idNumber, int inStock)
    {
        // TODO: make sure the item is NOT already in the system (checking idNumber)
        Item newItem = Item(name, idNumber, inStock);
        inventoryVector.push_back(newItem);
        inventoryMap.add(newItem);
        // inventoryTree.add(newItem);
    }
    void searchByID()
    {
        // Search by ID
    }
    void searchByName()
    {
        // Search by Name and delete it
    }
    void deleteByID()
    {
        // Search by ID and delete it
    }
    void deleteByName()
    {
        // Search by name and delete it
    }
    void inventoryGenerator(int inventoryNumber)
    {
        for (int i = 0; i < inventoryNumber; i++)
        {
            // randomly generate an item
            // initialize it and gives a random inStock from 1-1000
            Item item;
            item.name = printRandomString(10);
            item.idNumber = i + 1;
            //randomized idNumbers
            item.idNumber = rand() % 1000;
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
    void printMap()
    {
        inventoryMap.printMap();
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
    system1.inventoryGenerator(100);
    system1.printInventoryVector();
    /*Some possible function calls for testing purpose if you guys want to see how it works
    Map map(system1.inventoryVector);  
    InventorySystem::Item item;
    item.name = printRandomString(10);
    item.idNumber = 101;
    item.inStock = 50;
    map.add(item);
    map.remove(1);
    map.printMap();
    cout << endl;
    map.find(1);
    */
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
