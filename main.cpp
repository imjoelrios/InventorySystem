#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <string.h>
#include <string>
#include <stack>

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
    // --- Item Sub-Class ---
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

    // --------- Map Sub-Class ---------
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

    // --------- Tree Sub-Class ---------
    class Tree
    {
        // --- Node Sub-Sub-Class ---
        struct Node
        {
            Item classItem;
            Node* right = nullptr;
            Node* left = nullptr;
            int height = 0;
            int data = NULL;
            string stringData = "";
        };

    public:
        // Operators
        friend bool operator<(string left, string right)
        {
            if (left.compare(right) < 0)
                return true;
            return false;
        }
        friend bool operator>(string left, string right)
        {
            if (left.compare(right) > 0)
                return true;
            return false;
        }
        friend bool operator==(string left, string right)
        {
            if (left.compare(right) == 0)
                return true;
            return false;
        }

        // Tree functions
        void insert(int data, Item& item)
        {
            if (AVL_Root == nullptr)
            {
                Node* temp = new Node();
                temp->classItem = item;
                temp->data = data;
                AVL_Root = temp;
                temp->height = 1;
                return;
            }
            insertRecursive(AVL_Root, data, item);
        }
        void insert(string data, Item& item)
        {
            if (AVL_Root == nullptr)
            {
                Node* temp = new Node();
                temp->classItem = item;
                temp->stringData = data;
                AVL_Root = temp;
                temp->height = 1;
                return;
            }
            insertRecursive(AVL_Root, data, item);
        }

        // Choose:
        // 1. Ascending order
        // 2. Descending order
        // 3. Postorder
        // 4. Preorder
        void printTree(int choice)
        {
            cout << "Available inventory: " << endl;
            auto temp = AVL_Root;
            if (choice == 3)
            {
                printPostorder(temp);
            }
            else if (choice == 1) {
                printInorder(temp);
            }
            else if (choice == 2) {
                printReverseInorder(temp);
            }
            else if (choice == 4) {
                printPreorder(temp);
            }
            else
                cout << "Invalid option! " << endl;


        }
        Item* search(int key, Item& item)
        {
            auto temp = searchRecursive(AVL_Root, key);
            if (temp == nullptr)
                return nullptr;
            return &temp->classItem;
        }
        bool deleteValue(int key)
        {
            auto val = searchRecursive(AVL_Root, key);
            auto predecessor = inorder_predecessor(val);
            if (val == nullptr)
                return false;
            if (isALeaf(val))
            {
                auto parentNode = parent(AVL_Root, val);
                if (height(val) == 1) {
                    free(AVL_Root);
                    AVL_Root = nullptr;
                    return true;

                }
                else if (parentNode->left == val)
                    parentNode->left = nullptr;
                else if (parentNode->right == val)
                    parentNode->right = nullptr;
                free(val);
                deleteLeaf(AVL_Root, parentNode);

                return true;
            }
            else
            {
                deleteRecursive(AVL_Root, AVL_Root, predecessor, val);
                return true;
            }
        }
        bool deleteValue(string key)
        {
            auto val = searchRecursive(AVL_Root, key);
            auto predecessor = inorder_predecessor(val);
            if (val == nullptr)
                return false;
            if (isALeaf(val))
            {
                auto parentNode = parent(AVL_Root, val);
                if (parentNode->left == val)
                    parentNode->left = nullptr;
                else if (parentNode->right == val)
                    parentNode->right = nullptr;
                free(val);
                deleteLeaf(AVL_Root, parentNode);

                return true;
            }
            else
            {
                deleteRecursive(AVL_Root, AVL_Root, predecessor, val);
                return true;
            }
        }

        bool deleteHead(bool is_string) {
            if (is_string)
                return deleteValue(headValue().name);
            return deleteValue(headValue().idNumber);
        }


        Item headValue()
        {
            return AVL_Root->classItem;
        }

        bool searchInorder(string key) {
            stack<Node*> temp;
            if (AVL_Root == nullptr)
                return false;
            searchInorderHelp(key, AVL_Root, temp);
            while (!temp.empty()) {
                if (temp.top()->stringData == key) {
                    printItem(temp.top());
                    return true;
                }

                temp.pop();
            }
            return false;

        }
        bool searchInorder(int key) {
            stack<Node*>temp;
            if (AVL_Root == nullptr)
                return false;
            searchInorderHelp(key, AVL_Root, temp);
            while (!temp.empty()) {
                if (temp.top()->data == key) {
                    printItem(temp.top());
                    return true;
                }

                temp.pop();
            }
            return false;
        }






    private:

        // Tree structure
        Node* AVL_Root = nullptr;
        Node* rotateRightLeft(Node* node)
        {

            if (node == nullptr)
                return node;
            Node* rightChild = node->right;
            node->right = rightChild->left;
            rightChild->left = node->right->right;
            node->right->right = rightChild;

            auto newRightChild = node->right;
            node->right = newRightChild->left;
            newRightChild->left = node;

            if (node == AVL_Root)
                AVL_Root = newRightChild;
            newRightChild->left->height -= 2;
            newRightChild->height++;
            return newRightChild;
        }
        Node* rotateLeft(Node* node)
        {
            if (node == nullptr)
                return node;
            auto rightChild = node->right;
            node->right = node->right->left;
            rightChild->left = node;

            if (node == AVL_Root)
                AVL_Root = rightChild;
            rightChild->left->height -= 2;
            return rightChild;
        }
        Node* rotateRight(Node* node)
        {
            if (node == nullptr)
                return node;
            auto leftChild = node->left;
            node->left = node->left->right;
            leftChild->right = node;

            if (node == AVL_Root)
                AVL_Root = leftChild;
            leftChild->right->height -= 2;
            return leftChild;
        }
        Node* rotateLeftRight(Node* node)
        {
            if (node == nullptr)
                return node;
            Node* leftChild = node->left;
            node->left = leftChild->right;
            leftChild->right = node->left->left;
            node->left->left = leftChild;

            auto newLeftChild = node->left;
            node->left = newLeftChild->right;
            newLeftChild->right = node;

            if (node == AVL_Root)
                AVL_Root = newLeftChild;
            newLeftChild->right->height -= 2;
            newLeftChild->height++;
            return newLeftChild;
        }
        Node* insertRecursive(Node* root, int data, Item& item)
        {

            if (root == NULL)
            {
                Node* temp = new Node();
                temp->classItem = item;
                temp->data = data;
                temp->height = 1;
                return temp;
            }
            if (data < root->data)
                root->left = insertRecursive(root->left, data, item);
            else if (data > root->data)
                root->right = insertRecursive(root->right, data, item);

            root->height = max_height(root);
            root = balanceNodes(root);
            return root;
        }
        Node* insertRecursive(Node* root, string data, Item& item)
        {

            if (root == NULL)
            {
                Node* temp = new Node();
                temp->classItem = item;
                temp->stringData = data;
                temp->height = 1;
                return temp;
            }
            if (data < root->stringData)
                root->left = insertRecursive(root->left, data, item);
            else if (data > root->stringData)
                root->right = insertRecursive(root->right, data, item);

            root->height = max_height(root);
            root = balanceNodes(root);
            return root;
        }
        int max_height(Node* root)
        {
            if (root == nullptr)
                return 0;
            int heightLeft, heightRight;
            heightLeft = root->left == nullptr ? 0 : root->left->height;
            heightRight = root->right == nullptr ? 0 : root->right->height;

            return 1 + (heightLeft > heightRight ? heightLeft : heightRight);
        }
        int height(Node* root)
        {
            if (root == nullptr)
                return 0;
            return root->height;
        }
        Node* balanceNodes(Node* parent)
        {
            if (parent == nullptr)
                return parent;

            Node* temp = parent;

            if (height(parent->left) - height(parent->right) > 1)
            {
                if (parent->left != nullptr && height(parent->left->right) < height(parent->left->left))
                    parent = rotateRight(parent);
                else if (parent->left != nullptr && height(parent->left->right) > height(parent->left->left))
                    parent = rotateLeftRight(parent);
                else if (height(parent->right) == 0)
                    parent = rotateRight(parent);
            }
            else if (height(parent->left) - height(parent->right) < -1)
            {
                if (parent->right != nullptr && height(parent->right->left) < height(parent->right->right))
                    parent = rotateLeft(parent);
                else if (parent->right != nullptr && height(parent->right->left) > height(parent->right->right))
                    parent = rotateRightLeft(parent);
                else if (height(parent->left) == 0)
                    parent = rotateLeft(parent);
            }
            return parent;
        }



        void printItem(Node* item) {
            if (item != nullptr) {
                cout << "Name: " << item->classItem.name << endl;
                cout << "idNumber: " << item->classItem.idNumber << endl;
                cout << "Number of items: " << item->classItem.inStock << endl;
                cout << endl;
            }


        }
        void printPostorder(Node* root)
        {
            if (root == nullptr)
                return;

            printPostorder(root->left);
            printPostorder(root->right);
            printItem(root);
        }

        void printInorder(Node* root) {
            if (root == nullptr)
                return;

            printInorder(root->left);
            printItem(root);
            printInorder(root->right);


        }

        void printReverseInorder(Node* root) {
            if (root == nullptr)
                return;

            printReverseInorder(root->right);
            printItem(root);
            printReverseInorder(root->left);

        }

        void printPreorder(Node* root) {
            if (root == nullptr)
                return;

            printItem(root);
            printPreorder(root->left);
            printPreorder(root->right);

        }

        void searchInorderHelp(string key, Node* root, stack<Node*>& stack_) {
            if (root == nullptr)
                return;
            searchInorderHelp(key, root->left, stack_);
            if (root->stringData == key)
                stack_.push(root);
            searchInorderHelp(key, root->right, stack_);

        }
        void searchInorderHelp(int key, Node* root, stack<Node*>& stack_) {
            if (root == nullptr)
                return;
            searchInorderHelp(key, root->left, stack_);
            if (root->data == key)
                stack_.push(root);
            searchInorderHelp(key, root->right, stack_);

        }



        Node* searchRecursive(Node* root, int key)
        {
            if (root == nullptr)
                return nullptr;
            if (key == root->data)
                return root;
            else if (key < root->data)
                return searchRecursive(root->left, key);
            else if (key > root->data)
                return searchRecursive(root->right, key);
            return nullptr;
        }
        Node* searchRecursive(Node* root, string key)
        {
            if (root == nullptr)
                return nullptr;
            if (key == root->stringData)
                return root;
            else if (key < root->stringData)
                return searchRecursive(root->left, key);
            else if (key > root->stringData)
                return searchRecursive(root->right, key);
            return nullptr;
        }
        bool isALeaf(Node* node)
        {
            if (node == nullptr)
                return false;
            else if (node->left == nullptr && node->right == nullptr)
                return true;
            return false;
        }
        Node* deleteLeaf(Node* root, Node* parent)
        {

            if (root->data == parent->data)
            {
                root->height = max_height(root);
                root = balanceNodes(root);
                return root;
            }
            if (parent->data < root->data)
                root->left = deleteLeaf(root->left, parent);
            else if (parent->data > root->data)
                root->right = deleteLeaf(root->right, parent);

            root->height = max_height(root);
            root = balanceNodes(root);
        }
        Node* deleteRecursive(Node* root, Node* rootNonRecursive, Node*& inorder, Node* deleting)
        {
            if (inorder == nullptr) {
                auto parentSmallest = parent(AVL_Root, root);
                if (parentSmallest != nullptr) {
                    parentSmallest->left = root->right;
                    free(root);
                }
                else {
                    AVL_Root = root->right;
                    free(root);
                    return nullptr;
                }
            }
            else if (root->data == inorder->data)
            {
                auto temp = inorder->left;
                swap(deleting->data, inorder->data);
                swap(deleting->classItem, inorder->classItem);
                swap(deleting->stringData, inorder->stringData);
                free(inorder);
                if (temp == nullptr)
                    return nullptr;
                return temp;
            }
            else if (inorder->data < root->data)
                root->left = deleteRecursive(root->left, rootNonRecursive, inorder, deleting);
            else if (inorder->data > root->data)
                root->right = deleteRecursive(root->right, rootNonRecursive, inorder, deleting);

            root->height = max_height(root);
            root = balanceNodes(root);
            return root;
        }
        Node* parent(Node* root, Node* key)
        {
            if (root == nullptr || key == AVL_Root)
                return nullptr;
            if (root->left == key)
                return root;
            else if (root->right == key)
                return root;
            if (root->data > key->data)
                return parent(root->left, key);
            if (root->data < key->data)
                return parent(root->right, key);
        }
        Node* inorder_predecessor(Node* root)
        {

            if (root == nullptr)
                return nullptr;
            if (root->left == nullptr)
                return nullptr;
            auto temp = root->left;
            while (temp->right != nullptr)
                temp = temp->right;

            return temp;
        }
    };

    // Tree with inventory
    Tree inventoryTree;

    // --- System's Methods/Functions ---
    void add(string name, int idNumber, int inStock)
    {
        // TODO: make sure the item is NOT already in the system (checking idNumber)
        Item newItem = Item(name, idNumber, inStock);
        inventoryVector.push_back(newItem);
        inventoryMap.add(newItem);
        inventoryTree.insert(newItem.idNumber, newItem); //currently sorted by id Number, choose whatever
    }
    void searchByID()
    {
        // inventoryTree.search(//idNumber, item)
    }
    void searchByName()
    {
        // inventoryTree.search(//name, item)
    }
    void deleteByID()
    {
        // inventoryTree.deleteValue(//id)
    }
    void deleteByName()
    {
        // inventoryTree.deleteValue(//name)
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
    void printTree()
    {
        inventoryTree.printTree();
    }
};

// ===================== Test Cases ===========================
/*
    1. Run the function being tested on each data structure
    2. Print time

*/
void test1(InventorySystem system)
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
void test2(InventorySystem system)
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
void test3(InventorySystem system){
    // === Test edit
};
void test4(InventorySystem system){
    // Test search

    // Test search for small data sets

    // test search for large data sets

};

// Runs whole program
void run()
{
    InventorySystem system;
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

    // Run all tests
    /*
        test1(system);
        test2(system);
        test3(system);
        test4(system);
        test5(system);
        test6(system);
        test7(system);
    */
};

// ===================== Main Method ===========================
int main()
{
    // Main is used to test whatever you're working on
    // Just make sure to clear main before pushing/commiting any changes
    return 0;
};
