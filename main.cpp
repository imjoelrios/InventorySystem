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
        Map(vector<InventorySystem::Item> inventory)
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
        void insert(InventorySystem::Item item)
        {
            //adds the key and value to the end of corresponding vectors if key doesn't already exists (otherwise does nothing)
            //time complexity is O(logn)
            if (helpFind(item.idNumber, 0, size) >= 0)
            {
                keys.push_back(item.idNumber);
                values.push_back(item);
                size++;
            }
            else
            {
                cout << "Item with that ID is already in the system." << endl;
            }
        }
        void remove(int idNumber)
        {
            //time complexity is log(n)
            int index = helpFind(idNumber, 0, size);
            //if the item is found, item to be removed is swapped with the last item and then last item is deleted which all can be done in O(1)
            if (index >= 0)
            {
                keys.at(index) = keys.at(size - 1);
                values.at(index) = values.at(size - 1);
                keys.pop_back();
                values.pop_back();
                size--;
            }
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
        void search(int idNumber)
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
        void editAmountInStock(int idNumber, int newInStock)
        {
            //time complexity is O(logn)
            int index = helpFind(idNumber, 0, size);
            if (index >= 0)
                values.at(index).inStock = newInStock;
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
            Node *right = nullptr;
            Node *left = nullptr;
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

        // --- Tree functions ---
        void insert(Item &newItem)
        {
            if (AVL_Root == nullptr)
            {
                Node *temp = new Node();
                temp->classItem = newItem;
                temp->data = newItem.idNumber;
                AVL_Root = temp;
                temp->height = 1;
                return;
            }
            insertRecursive(AVL_Root, newItem.idNumber, newItem);
        }
        void insert(string data, Item &item)
        {
            if (AVL_Root == nullptr)
            {
                Node *temp = new Node();
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
            else if (choice == 1)
            {
                printInorder(temp);
            }
            else if (choice == 2)
            {
                printReverseInorder(temp);
            }
            else if (choice == 4)
            {
                printPreorder(temp);
            }
            else
                cout << "Invalid option! " << endl;
        }

        // Tree organized by ID number
        void search(int key)
        {
            auto temp = searchRecursive(AVL_Root, key);
            if (temp == nullptr)
                cout << "Item not found!" << endl;
            else
                printItem(temp);
        }
        bool remove(int key)
        {
            auto val = searchRecursive(AVL_Root, key);
            auto predecessor = inorder_predecessor(val);
            if (val == nullptr)
                return false;
            if (isALeaf(val))
            {
                auto parentNode = parent(AVL_Root, val);
                if (height(val) == 1)
                {
                    free(AVL_Root);
                    AVL_Root = nullptr;
                    return true;
                }
                else if (parentNode->left == val)
                    parentNode->left = nullptr;
                else if (parentNode->right == val)
                    parentNode->right = nullptr;
                free(val);

                return true;
            }
            else
            {
                deleteRecursive(AVL_Root, AVL_Root, predecessor, val, false);
                return true;
            }
        }
        bool editAmountInStock(int id, int newAmount)
        {

            auto temp = searchRecursive(AVL_Root, id);
            if (temp != nullptr)
            {
                temp->classItem.inStock = newAmount;
                return true;
            }
            return false;
        }
        bool searchInorder(int key)
        {
            stack<Node *> temp;
            if (AVL_Root == nullptr)
                return false;
            searchInorderHelp(key, AVL_Root, temp);
            while (!temp.empty())
            {
                if (temp.top()->data == key)
                {
                    printItem(temp.top());
                    return true;
                }

                temp.pop();
            }
            return false;
        }

        // Tree organized by name
        void search(string key)
        {
            auto temp = searchRecursive(AVL_Root, key);
            if (temp == nullptr)
                cout << "Item not found!" << endl;
            else
                printItem(temp);
        }
        bool delete_(string key)
        {
            auto val = searchRecursive(AVL_Root, key);
            auto predecessor = inorder_predecessor(val);
            if (val == nullptr)
                return false;
            if (isALeaf(val))
            {
                auto parentNode = parent(AVL_Root, val);
                if (height(val) == 1)
                {
                    free(AVL_Root);
                    AVL_Root = nullptr;
                    return true;
                }
                else if (parentNode->left == val)
                    parentNode->left = nullptr;
                else if (parentNode->right == val)
                    parentNode->right = nullptr;
                free(val);

                return true;
            }
            else
            {
                deleteRecursive(AVL_Root, AVL_Root, predecessor, val, true);
                return true;
            }
        }
        bool edit(string name, int newAmount)
        {

            auto temp = searchRecursive(AVL_Root, name);
            if (temp != nullptr)
            {
                temp->classItem.inStock = newAmount;
                return true;
            }
            return false;
        }
        bool searchInorder(string key)
        {
            stack<Node *> temp;
            if (AVL_Root == nullptr)
                return false;
            searchInorderHelp(key, AVL_Root, temp);
            while (!temp.empty())
            {
                if (temp.top()->stringData == key)
                {
                    printItem(temp.top());
                    return true;
                }

                temp.pop();
            }
            return false;
        }

        bool deleteHead(bool is_string)
        {
            if (is_string)
                return delete_(headValue().name);
            return remove(headValue().idNumber);
        }
        Item headValue()
        {
            return AVL_Root->classItem;
        }

    private:
        // --- Tree structure ---
        Node *AVL_Root = nullptr;
        Node *rotateRightLeft(Node *node)
        {

            if (node == nullptr)
                return node;
            Node *rightChild = node->right;
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
        Node *rotateLeft(Node *node)
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
        Node *rotateRight(Node *node)
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
        Node *rotateLeftRight(Node *node)
        {
            if (node == nullptr)
                return node;
            Node *leftChild = node->left;
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
        Node *insertRecursive(Node *root, int data, Item &item)
        {

            if (root == NULL)
            {
                Node *temp = new Node();
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
        Node *insertRecursive(Node *root, string data, Item &item)
        {

            if (root == NULL)
            {
                Node *temp = new Node();
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
        int max_height(Node *root)
        {
            if (root == nullptr)
                return 0;
            int heightLeft, heightRight;
            heightLeft = root->left == nullptr ? 0 : root->left->height;
            heightRight = root->right == nullptr ? 0 : root->right->height;

            return 1 + (heightLeft > heightRight ? heightLeft : heightRight);
        }
        int height(Node *root)
        {
            if (root == nullptr)
                return 0;
            return root->height;
        }
        Node *balanceNodes(Node *parent)
        {
            if (parent == nullptr)
                return parent;

            Node *temp = parent;

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
        void printItem(Node *item)
        {
            if (item != nullptr)
            {
                cout << "Name: " << item->classItem.name << endl;
                cout << "idNumber: " << item->classItem.idNumber << endl;
                cout << "Number of items: " << item->classItem.inStock << endl;
                cout << endl;
            }
        }
        void printPostorder(Node *root)
        {
            if (root == nullptr)
                return;

            printPostorder(root->left);
            printPostorder(root->right);
            printItem(root);
        }
        void printInorder(Node *root)
        {
            if (root == nullptr)
                return;

            printInorder(root->left);
            printItem(root);
            printInorder(root->right);
        }
        void printReverseInorder(Node *root)
        {
            if (root == nullptr)
                return;

            printReverseInorder(root->right);
            printItem(root);
            printReverseInorder(root->left);
        }
        void printPreorder(Node *root)
        {
            if (root == nullptr)
                return;

            printItem(root);
            printPreorder(root->left);
            printPreorder(root->right);
        }
        void searchInorderHelp(string key, Node *root, stack<Node *> &stack_)
        {
            if (root == nullptr)
                return;
            searchInorderHelp(key, root->left, stack_);
            if (root->stringData == key)
                stack_.push(root);
            searchInorderHelp(key, root->right, stack_);
        }
        void searchInorderHelp(int key, Node *root, stack<Node *> &stack_)
        {
            if (root == nullptr)
                return;
            searchInorderHelp(key, root->left, stack_);
            if (root->data == key)
                stack_.push(root);
            searchInorderHelp(key, root->right, stack_);
        }
        Node *searchRecursive(Node *root, int key)
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
        Node *searchRecursive(Node *root, string key)
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
        bool isALeaf(Node *node)
        {
            if (node == nullptr)
                return false;
            else if (node->left == nullptr && node->right == nullptr)
                return true;
            return false;
        }
        Node *deleteLeaf(Node *root, Node *parent)
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
        Node *deleteRecursive(Node *root, Node *rootNonRecursive, Node *&inorder, Node *deleting, bool is_string)
        {
            if (inorder == nullptr)
            {
                auto parentSmallest = parent(AVL_Root, root);
                if (parentSmallest != nullptr)
                {
                    parentSmallest->left = root->right;
                    free(root);
                    return nullptr;
                }
                else
                {
                    AVL_Root = root->right;
                    free(root);
                    return nullptr;
                }
            }
            else if (root->data == inorder->data && !is_string)
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
            else if (root->stringData == inorder->stringData && is_string)
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
            else if (is_string)
            {
                if (inorder->stringData < root->stringData)
                    root->left = deleteRecursive(root->left, rootNonRecursive, inorder, deleting, is_string);
                else if (inorder->stringData > root->stringData)
                    root->right = deleteRecursive(root->right, rootNonRecursive, inorder, deleting, is_string);
            }
            else if (!is_string)
            {
                if (inorder->data < root->data)
                    root->left = deleteRecursive(root->left, rootNonRecursive, inorder, deleting, is_string);
                else if (inorder->data > root->data)
                    root->right = deleteRecursive(root->right, rootNonRecursive, inorder, deleting, is_string);
            }

            root->height = max_height(root);
            root = balanceNodes(root);
            return root;
        }
        Node *parent(Node *root, Node *key)
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
        Node *inorder_predecessor(Node *root)
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
    void insert(string name, int idNumber, int inStock)
    {
        // TODO: make sure the item is NOT already in the system (checking idNumber)
        Item newItem = Item(name, idNumber, inStock);
        inventoryVector.push_back(newItem);
        inventoryMap.insert(newItem);
        inventoryTree.insert(newItem);
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
            item.inStock = rand() % 1000;

            // add item to inventory list/arry
            inventoryVector.push_back(item);
            inventoryMap.insert(item);
            inventoryTree.insert(item);
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
        // Choose:
        // 1. Ascending order
        // 2. Descending order
        // 3. Postorder
        // 4. Preorder
        inventoryTree.printTree(1);
    }
};

// ===================== Test Cases ===========================
/*
    1. Random inventory is added to the system amounting to 100,000 (added to the tree and map as well)
    2. A newItem is created. This item is the one that will be manipulated (insert, delete, search, etc.)
        The ID of the newItem is over 100,000 to avoid collision with an item that has that idAlready
    3. Run the function being tested on each data structure
    2. Print time

*/
void testInsert(InventorySystem &system)
{
    system.inventoryGenerator(100000);
    InventorySystem::Item newItem("Tshirt", 100005, 1000);
    system.inventoryVector.push_back(newItem);
    // --- Test in Map
    time_t start, end;
    time(&start);
    system.inventoryMap.insert(newItem);
    time(&end);
    double mapExecutionTime = double(end - start);

    // --- Test in Tree
    time(&start);
    system.inventoryTree.insert(newItem);
    time(&end);
    double treeExecutionTime = double(end - start);

    // --- Print execution times
    cout << "Test #1 --- Insert()" << endl;
    cout << "Execution time by map : " << fixed << mapExecutionTime << setprecision(5);
    cout << " sec " << endl;

    cout << "Execution time by tree : " << fixed << treeExecutionTime << setprecision(5);
    cout << " sec " << endl;
    cout << endl;
};
void testDelete(InventorySystem &system)
{
    system.inventoryGenerator(100000);
    InventorySystem::Item newItem("Tshirt", 100005, 1000);
    system.inventoryVector.push_back(newItem);
    system.inventoryMap.insert(newItem);
    system.inventoryTree.insert(newItem);

    // --- Test in Map
    time_t start, end;
    time(&start);
    system.inventoryMap.remove(8789);
    time(&end);
    double mapExecutionTime = double(end - start);

    // --- Test in Tree
    time(&start);
    system.inventoryTree.remove(8789);
    time(&end);
    double treeExecutionTime = double(end - start);

    // --- Print execution times
    cout << "Test #2 --- Delete()" << endl;
    cout << "Execution time by map : " << fixed << mapExecutionTime << setprecision(5);
    cout << " sec " << endl;

    cout << "Execution time by tree : " << fixed << treeExecutionTime << setprecision(5);
    cout << " sec " << endl;
    cout << endl;
};
void testSearch(InventorySystem &system)
{
    system.inventoryGenerator(100000);
    InventorySystem::Item newItem("Tshirt", 100005, 1000);
    system.inventoryVector.push_back(newItem);
    system.inventoryMap.insert(newItem);
    system.inventoryTree.insert(newItem);

    // --- Test in Map
    time_t start, end;
    time(&start);
    system.inventoryMap.search(8789);
    time(&end);
    double mapExecutionTime = double(end - start);

    // --- Test in Tree
    time(&start);
    system.inventoryTree.search(8789);
    time(&end);
    double treeExecutionTime = double(end - start);

    // --- Print execution times
    cout << "Test #3 --- Search()" << endl;
    cout << "Execution time by map : " << fixed << mapExecutionTime << setprecision(5);
    cout << " sec " << endl;

    cout << "Execution time by tree : " << fixed << treeExecutionTime << setprecision(5);
    cout << " sec " << endl;
    cout << endl;
};
void testEdit(InventorySystem system)
{
    system.inventoryGenerator(100000);
    InventorySystem::Item newItem("Tshirt", 100005, 1000);
    system.inventoryVector.push_back(newItem);
    system.inventoryMap.insert(newItem);
    system.inventoryTree.insert(newItem);

    // --- Test in Map
    time_t start, end;
    time(&start);
    system.inventoryMap.editAmountInStock(8789, 250);
    time(&end);
    double mapExecutionTime = double(end - start);

    // --- Test in Tree
    time(&start);
    system.inventoryTree.editAmountInStock(8789, 250);
    time(&end);
    double treeExecutionTime = double(end - start);

    // --- Print execution times
    cout << "Test #3 --- Edit()" << endl;
    cout << "Execution time by map : " << fixed << mapExecutionTime << setprecision(5);
    cout << " sec " << endl;

    cout << "Execution time by tree : " << fixed << treeExecutionTime << setprecision(5);
    cout << " sec " << endl;
    cout << endl;
};

// ===================== Specific Test Cases ===========================

// For the map data structure
void testMapInsert(InventorySystem &system)
{
    InventorySystem::Item newItem("Tshirt", 100005, 1000);
    system.inventoryVector.push_back(newItem);
    // --- Test in Map
    time_t start, end;
    time(&start);
    system.inventoryMap.insert(newItem);
    time(&end);
    double mapExecutionTime = double(end - start);
}
void testMapDelete(InventorySystem &system)
{
    InventorySystem::Item newItem("Tshirt", 100005, 1000);
    system.inventoryVector.push_back(newItem);
    system.inventoryMap.insert(newItem);
    // --- Test in Map
    time_t start, end;
    time(&start);
    system.inventoryMap.remove(100005);
    time(&end);
    double mapExecutionTime = double(end - start);
}
void testMapSearch(InventorySystem &system)
{
    InventorySystem::Item newItem("Tshirt", 100005, 1000);
    system.inventoryVector.push_back(newItem);
    system.inventoryMap.insert(newItem);
    // --- Test in Map
    time_t start, end;
    time(&start);
    system.inventoryMap.search(100005);
    time(&end);
    double mapExecutionTime = double(end - start);
}
void testMapEdit(InventorySystem &system)
{
    InventorySystem::Item newItem("Tshirt", 100005, 1000);
    system.inventoryVector.push_back(newItem);
    system.inventoryMap.insert(newItem);
    // --- Test in Map
    time_t start, end;
    time(&start);
    system.inventoryMap.editAmountInStock(100005, 250);
    time(&end);
    double mapExecutionTime = double(end - start);
}

// For the tree data structure
void testTreeInsert(InventorySystem &system)
{
    InventorySystem::Item newItem("Tshirt", 100005, 1000);
    system.inventoryVector.push_back(newItem);
    // --- Test in Map
    time_t start, end;
    time(&start);
    system.inventoryTree.insert(newItem);
    time(&end);
    double mapExecutionTime = double(end - start);
}
void testTreeDelete(InventorySystem &system)
{
    InventorySystem::Item newItem("Tshirt", 100005, 1000);
    system.inventoryVector.push_back(newItem);
    system.inventoryTree.insert(newItem);
    // --- Test in Map
    time_t start, end;
    time(&start);
    system.inventoryTree.remove(100005);
    time(&end);
    double mapExecutionTime = double(end - start);
}
void testTreeSearch(InventorySystem &system)
{
    InventorySystem::Item newItem("Tshirt", 100005, 1000);
    system.inventoryVector.push_back(newItem);
    system.inventoryTree.insert(newItem);
    // --- Test in Map
    time_t start, end;
    time(&start);
    system.inventoryTree.search(100005);
    time(&end);
    double mapExecutionTime = double(end - start);
}
void testTreeEdit(InventorySystem &system)
{
    InventorySystem::Item newItem("Tshirt", 100005, 1000);
    system.inventoryVector.push_back(newItem);
    system.inventoryTree.insert(newItem);
    // --- Test in Map
    time_t start, end;
    time(&start);
    system.inventoryTree.editAmountInStock(100005, 250);
    time(&end);
    double mapExecutionTime = double(end - start);
}

// Runs whole program
void runTests()
{
    InventorySystem system;
    // Run all tests
};

// ===================== Main Method ===========================
int main()
{
    // For testing just uncomment the one below and run
    InventorySystem system;

    // For map
    //testMapInsert(system);
    //testMapDelete(system);
    //testMapSearch(system);
    //testMapEdit(system);

    // For tree
    // testTreeInsert(system);
    // testTreeDelete(system);
    // testTreeSearch(system);
    // testTreeEdit(system);

    return 0;
};
