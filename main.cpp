#include <iostream>
#include <iomanip>
#include <vector>
#include <string.h>
#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;

// ===================== Random Functions ================
// Source: Program used from https://www.geeksforgeeks.org/program-generate-random-alphabets/
string printRandomString(int n)
{
	const int MAX = 26;
	char alphabet[MAX] ={ 'a', 'b', 'c', 'd', 'e', 'f', 'g',
		'h', 'i', 'j', 'k', 'l', 'm', 'n',
		'o', 'p', 'q', 'r', 's', 't', 'u',
		'v', 'w', 'x', 'y', 'z' };

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
	// Additional variables can be added to the item (depending on the inventory's complexity)
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
	void removeFromVector(int idNumber)
	{
		for (int i = 0; i < inventoryVector.size(); i++)
		{
			if (inventoryVector[i].idNumber = idNumber)
			{
				inventoryVector.erase(inventoryVector.begin() + (i - 1));
			}
		}
	}

	// --------- Map Sub-Class ---------
	//Unsorted
	class Map
	{
	private:
		vector<vector<InventorySystem::Item>> buckets;
		int size;

	public:
		// Default constructor
		Map()
		{
			//based on 100,000 item inventory size (with space for double the size for efficiency purposes)
			size = 100000 * 2;
			for (int i = 0; i < size; i++)
			{
				vector<InventorySystem::Item> bucket;
				buckets.push_back(bucket);
			}
		}
		// Parameterized constructor, requires inventory list to be sorted by idNumbers
		Map(vector<InventorySystem::Item> inventory)
		{
			size = inventory.size() * 2;
			//doubles the size of original data for efficiency purposes
			for (int i = 0; i < size / 2; i++)
			{
				vector<InventorySystem::Item> bucket;
				bucket.push_back(inventory.at(i));
				buckets.push_back(bucket);
			}
			for (int i = 0; i < size / 2; i++)
			{
				vector<InventorySystem::Item> bucket;
				buckets.push_back(bucket);
			}
		}
		void printMap() //Unsorted
		{
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < buckets.at(i).size(); j++)
				{
					cout << "Name: " << buckets.at(i)[j].name << endl;
					cout << "idNumber: " << buckets.at(i)[j].idNumber << endl;
					cout << "Amount in Stock: " << buckets.at(i)[j].inStock << endl;
					cout << endl;
				}
			}
		}
		void insert(InventorySystem::Item item)
		{
			//the idNumber % size gives the index location for the list that an item with that key (idNumbers) falls into
			int index = item.idNumber % size;
			InventorySystem::Item *pointer;
			//if their are no other items at that index, simply add it
			if (buckets.at(index).size() == 0)
			{
				buckets.at(index).push_back(item);
			}
			//if their are other items at that index, check to ensure an item with the same key (idNumber) doesn't exist before inserting
			else if ((pointer = helpFind(item.idNumber)) == nullptr)
			{
				buckets.at(index).push_back(item);
			}
			else
			{
				cout << "Item with that ID is already in the system." << endl;
			}
		}
		void remove(int idNumber)
		{
			int index = idNumber % size;
			//checking the items in the list at the index location for the associated key
			for (int i = 0; i < buckets.at(index).size(); i++)
			{
				if (buckets.at(index)[i].idNumber == idNumber)
				{
					buckets.at(index)[i] = buckets.at(index)[buckets.at(index).size() - 1];
					buckets.at(index).pop_back();
				}
			}
		}
		void searchByID(int idNumber)
		{
			InventorySystem::Item *item = helpFind(idNumber);
			if (item == nullptr)
			{
				cout << "Item not found in Map" << endl;
			}
			else
				printItem(item);
		}
		//for user input based feature, not optimized for performance
		void searchByName(string name)
		{
			for (int i = 0; i < buckets.size(); i++)
			{
				for (int j = 0; j < buckets.at(i).size(); j++)
				{
					if (buckets.at(i)[j].name.compare(name) == 0)
					{
						cout << "Name: " << buckets.at(i)[j].name << endl;
						cout << "idNumber: " << buckets.at(i)[j].idNumber << endl;
						cout << "Amount in Stock: " << buckets.at(i)[j].inStock << endl;
						cout << endl;
						return;
					}
				}
			}
			cout << "Item not found in Map" << endl;
		}
		void editAmountInStock(int idNumber, int newInStock)
		{
			int index = idNumber % size;
			for (int i = 0; i < buckets.at(index).size(); i++)
			{
				if (buckets.at(index)[i].idNumber == idNumber)
				{
					buckets.at(index)[i].inStock = newInStock;
				}
			}
		}
		InventorySystem::Item *helpFind(int idNumber)
		{
			int index = idNumber % size;
			InventorySystem::Item *pointer = nullptr;
			//checking the items in the list at the index location for the associated key, return pointer to item if it exists
			for (int i = 0; i < buckets.at(index).size(); i++)
			{
				if (buckets.at(index)[i].idNumber == idNumber)
				{
					pointer = &buckets.at(index)[i];
					return pointer;
				}
			}
			return pointer;
		}
		//given a pointer to an item itself
		void printItem(InventorySystem::Item *&item)
		{
			cout << "Name: " << item->name << endl;
			cout << "idNumber: " << item->idNumber << endl;
			cout << "Amount in Stock: " << item->inStock << endl;
			cout << endl;
		}
		//given just the item id
		void printItem(int idNumber)
		{
			searchByID(idNumber);
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
		};

	public:
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
				AVL_Root = addNewNode(newItem);
				return;
			}

			insertRecursive(AVL_Root, newItem);
		}

		void printItem(int key)
		{
			auto temp = searchRecursive(AVL_Root, key);
			if (temp == nullptr)
				cout << "Item not found in Tree" << endl;
			else
				printItem(temp);
			cout << endl;
		}
		// Choose:
		// 1. Ascending order
		// 2. Descending order
		// 3. Postorder
		// 4. Preorder
		void printTree(int choice)
		{
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

		// Tree sorted by ID number
		void searchByID(int key)
		{
			auto temp = searchRecursive(AVL_Root, key);
			if (temp == nullptr)
				cout << "Item not found in Tree" << endl;
			else
				printItem(temp);
		}
		// Will search the tree inorder, since it is sorted by Id number not name
		void searchByName(string key)
		{
			if (AVL_Root == nullptr)
			{
				cout << "Item not found in Tree" << endl;
				return;
			}
			bool flag = false;
			searchInorderHelp(key, AVL_Root, flag);
			if (!flag)
				cout << "Item not found in Tree" << endl;
		}

		// Delete by idNumber
		bool remove(int key)
		{
			auto val = searchRecursive(AVL_Root, key);
			auto predecessor = inorder_predecessor(val);
			if (val == nullptr)
				return false;
			if (isALeaf(val))
			{
				auto parentNode = parent(AVL_Root, val);
				if (AVL_Root == val)
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
				deleteRecursive(AVL_Root, AVL_Root, predecessor, val);
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

	private:
		// --- Tree structure ---
		Node *AVL_Root = nullptr;

		// Rotations and update height
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

		// Helper methods to insert 
		Node *insertRecursive(Node *root, Item &item)
		{

			if (root == nullptr)
				return addNewNode(item);
			if (item.idNumber < root->classItem.idNumber)
				root->left = insertRecursive(root->left, item);
			else if (item.idNumber > root->classItem.idNumber)
				root->right = insertRecursive(root->right, item);

			root->height = max_height(root);
			root = balanceNodes(root);
			return root;
		}

		Node* addNewNode(Item& newItem)
		{
			Node* temp = new Node();
			temp->classItem = newItem;
			temp->height = 1;
			return temp;
		}

		// Methods related to height, used in remove and insert methods
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

		// balanceNodes() method in charge of making the proper rotations during insert and delete 
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

		// Print methods
		void printItem(Node *item)
		{
			if (item != nullptr)
			{
				cout << "Name: " << item->classItem.name << endl;
				cout << "idNumber: " << item->classItem.idNumber << endl;
				cout << "Amount in Stock: " << item->classItem.inStock << endl;
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

		// Helper method for search by Id
		Node *searchRecursive(Node *root, int key)
		{
			if (root == nullptr)
				return nullptr;
			if (key == root->classItem.idNumber)
				return root;
			else if (key < root->classItem.idNumber)
				return searchRecursive(root->left, key);
			else if (key > root->classItem.idNumber)
				return searchRecursive(root->right, key);
			return nullptr;
		}
		// Helper method to searchByName
		void searchInorderHelp(string key, Node* root, bool& flag)
		{
			if (root == nullptr || flag)
				return;
			searchInorderHelp(key, root->left, flag);
			if (root->classItem.name == key)
			{
				flag = true;
				printItem(root);
				return;
			}
			searchInorderHelp(key, root->right, flag);
		}


		// Helper methods to remove. This implementation uses inorder predecessor, 
		// it can be changed to use inorder successor
		Node *deleteRecursive(Node *root, Node *rootNonRecursive, Node *&inorder, Node *deleting)
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
			else if (root->classItem.idNumber == inorder->classItem.idNumber)
			{
				auto temp = inorder->left;
				swap(deleting->classItem.idNumber, inorder->classItem.idNumber);
				swap(deleting->classItem, inorder->classItem);
				free(inorder);
				if (temp == nullptr)
					return nullptr;
				return temp;
			}

			else
			{
				if (inorder->classItem.idNumber < root->classItem.idNumber)
					root->left = deleteRecursive(root->left, rootNonRecursive, inorder, deleting);
				else if (inorder->classItem.idNumber > root->classItem.idNumber)
					root->right = deleteRecursive(root->right, rootNonRecursive, inorder, deleting);
			}

			root->height = max_height(root);
			root = balanceNodes(root);
			return root;
		}

		bool isALeaf(Node* node)
		{
			if (node == nullptr)
				return false;
			else if (node->left == nullptr && node->right == nullptr)
				return true;
			return false;
		}

		Node *parent(Node *root, Node *key)
		{
			if (root == nullptr || key == AVL_Root)
				return nullptr;
			if (root->left == key)
				return root;
			else if (root->right == key)
				return root;
			if (root->classItem.idNumber > key->classItem.idNumber)
				return parent(root->left, key);
			if (root->classItem.idNumber < key->classItem.idNumber)
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

		Node* inorder_successor(Node* root)
		{
			if (root == nullptr)
				return nullptr;
			if (root->right == nullptr)
				return nullptr;
			auto temp = root->right;
			while (temp->left != nullptr)
				temp = temp->left;
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

			// add item to inventory list/array
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
		cout << "Inventory in Map:" << endl;
		inventoryMap.printMap();
	}
	void printTree()
	{
		// Choose:
		// 1. Ascending order
		// 2. Descending order
		// 3. Postorder
		// 4. Preorder
		cout << "Inventory in Tree:" << endl;
		inventoryTree.printTree(1);
	}

	// By ID
	void searchByID(int idNumber)
	{
		cout << "In Tree:" << endl;
		inventoryTree.searchByID(idNumber);
		cout << endl;
		cout << "In Map:" << endl;
		inventoryMap.searchByID(idNumber);
	}
	void deleteByID(int idNumber)
	{
		inventoryTree.remove(idNumber);
		inventoryMap.remove(idNumber);
	}
	void editAmountInStock(int idNumber, int newAmount)
	{
		inventoryTree.editAmountInStock(idNumber, newAmount);
		inventoryMap.editAmountInStock(idNumber, newAmount);
	}
	// Search by ID in general inventory
	bool searchInventory(int idNumber)
	{
		for (int i = 0; i < inventoryVector.size(); i++)
		{
			if (inventoryVector.at(i).idNumber == idNumber)
			{
				return true;
			}
		}
		return false;
	}
	// By Name
	void searchByName(string name)
	{
		cout << "In Tree:" << endl;
		inventoryTree.searchByName(name);
		cout << endl;
		cout << "In Map:" << endl;
		inventoryMap.searchByName(name);
	}
};

// ===================== Execution Time Test Cases ===========================
/*
	1. Random inventory is added to the system amounting to 100,000 (added to the tree and map as well)
	2. A newItem is created. This item is the one that will be manipulated (insert, delete, search, etc.)
		The ID of the newItem is over 100,000 to avoid collision with an item that has that idAlready
	3. Run the function being tested on each data structure
	2. Print time

*/
void testInsert(InventorySystem &system, int inventorySize)
{
	InventorySystem::Item newItem("TestName", inventorySize + 5, 1000);
	system.inventoryVector.push_back(newItem);
	// --- Test in Map
	auto start = high_resolution_clock::now();
	system.inventoryMap.insert(newItem);
	auto stop = high_resolution_clock::now();
	auto mapExecutionTime = duration_cast<nanoseconds>(stop - start);

	// --- Test in Tree
	auto start2 = high_resolution_clock::now();
	system.inventoryTree.insert(newItem);
	auto stop2 = high_resolution_clock::now();
	auto treeExecutionTime = duration_cast<nanoseconds>(stop2 - start2);

	// --- Print execution times
	cout << "Test #1 --- Insert()" << endl;
	cout << "Execution time by map : " << mapExecutionTime.count();
	cout << " nanoseconds " << endl;

	cout << "Execution time by tree : " << treeExecutionTime.count();
	cout << " nanoseconds " << endl;
	cout << endl;
};
void testDelete(InventorySystem &system, int inventorySize)
{
	// --- Test in Map
	auto start = high_resolution_clock::now();
	system.inventoryMap.remove(inventorySize + 5);
	auto stop = high_resolution_clock::now();
	auto mapExecutionTime = duration_cast<nanoseconds>(stop - start);

	// --- Test in Tree
	auto start2 = high_resolution_clock::now();
	system.inventoryTree.remove(inventorySize + 5);
	auto stop2 = high_resolution_clock::now();
	auto treeExecutionTime = duration_cast<nanoseconds>(stop2 - start2);

	// --- Print execution times
	cout << "Test #2 --- Delete()" << endl;
	cout << "Execution time by map : " << mapExecutionTime.count();
	cout << " nanoseconds " << endl;

	cout << "Execution time by tree : " << treeExecutionTime.count();
	cout << " nanoseconds " << endl;
	cout << endl;
};
void testSearch(InventorySystem &system, int inventorySize)
{
	InventorySystem::Item newItem("TestName", inventorySize + 5, 1000);
	system.inventoryVector.push_back(newItem);
	system.inventoryMap.insert(newItem);
	system.inventoryTree.insert(newItem);
	// system.inventoryHashTable.insert(newItem);

	// --- Test in Map
	cout << "In Map:" << endl;
	auto start = high_resolution_clock::now();
	system.inventoryMap.searchByID(inventorySize + 5);
	auto stop = high_resolution_clock::now();
	auto mapExecutionTime = duration_cast<nanoseconds>(stop - start);

	// --- Test in Tree
	cout << "In Tree:" << endl;
	auto start2 = high_resolution_clock::now();
	system.inventoryTree.searchByID(inventorySize + 5);
	auto stop2 = high_resolution_clock::now();
	auto treeExecutionTime = duration_cast<nanoseconds>(stop2 - start2);

	// --- Print execution times
	cout << "Test #3 --- Search()" << endl;
	cout << "Execution time by map : " << mapExecutionTime.count();
	cout << " nanoseconds " << endl;

	cout << "Execution time by tree : " << treeExecutionTime.count();
	cout << " nanoseconds " << endl;
	cout << endl;
};
void testEdit(InventorySystem &system, int inventorySize)
{
	// --- Test in Map
	auto start = high_resolution_clock::now();
	system.inventoryMap.editAmountInStock(inventorySize + 5, 250);
	auto stop = high_resolution_clock::now();
	auto mapExecutionTime = duration_cast<nanoseconds>(stop - start);

	// --- Test in Tree
	auto start2 = high_resolution_clock::now();
	system.inventoryTree.editAmountInStock(inventorySize + 5, 250);
	auto stop2 = high_resolution_clock::now();
	auto treeExecutionTime = duration_cast<nanoseconds>(stop2 - start2);

	// --- Print execution times
	cout << "Test #4 --- Edit()" << endl;
	cout << "Execution time by map : " << mapExecutionTime.count();
	cout << " nanoseconds " << endl;

	cout << "Execution time by tree : " << treeExecutionTime.count();
	cout << " nanoseconds " << endl;
	cout << endl;
};

// Run all tests and set the random inventory size
void runTests(InventorySystem &system, int inventorySize)
{
	system.inventoryGenerator(inventorySize);
	// Run all tests
	testInsert(system, inventorySize);
	cout << endl;
	testDelete(system, inventorySize);
	cout << endl;
	testSearch(system, inventorySize);
	cout << endl;
	testEdit(system, inventorySize);
};

// ===================== Execution Time Test Cases per Data Structure ===========================
// For the map data structure
void testMapInsert(InventorySystem system)
{
	InventorySystem::Item newItem("TestName", 100005, 1000);
	system.inventoryVector.push_back(newItem);

	system.inventoryMap.printItem(100005);
	system.inventoryMap.insert(newItem); // Function being tested
	cout << endl;
	system.inventoryMap.printItem(100005);
}
void testMapDelete(InventorySystem system)
{
	InventorySystem::Item newItem("TestName", 100005, 1000);
	system.inventoryVector.push_back(newItem);
	system.inventoryMap.insert(newItem);

	system.inventoryMap.printItem(100005);
	system.inventoryMap.remove(100005); // Function being tested
	cout << endl;
	system.inventoryMap.printItem(100005);
}
void testMapSearch(InventorySystem system)
{
	InventorySystem::Item newItem("TestName", 100005, 1000);
	system.inventoryVector.push_back(newItem);
	system.inventoryMap.insert(newItem);

	system.inventoryMap.searchByID(100005); // Function being tested
}
void testMapEdit(InventorySystem system)
{
	InventorySystem::Item newItem("TestName", 100005, 1000);
	system.inventoryVector.push_back(newItem);
	system.inventoryMap.insert(newItem);

	system.inventoryMap.printItem(100005);
	system.inventoryMap.editAmountInStock(100005, 250); // Function being tested
	cout << endl;
	system.inventoryMap.printItem(100005);
}

// For the tree data structure
void testTreeInsert(InventorySystem system)
{
	InventorySystem::Item newItem("TestName", 100005, 1000);
	system.inventoryVector.push_back(newItem);

	system.inventoryTree.printItem(100005);
	system.inventoryTree.insert(newItem); // Function being tested
	cout << endl;
	system.inventoryTree.printItem(100005);
}
void testTreeDelete(InventorySystem system)
{
	InventorySystem::Item newItem("TestName", 100005, 1000);
	system.inventoryVector.push_back(newItem);
	system.inventoryTree.insert(newItem);

	system.inventoryTree.printItem(100005);
	system.inventoryTree.remove(100005); // Function being tested
	cout << endl;
	system.inventoryTree.printItem(100005);
}
void testTreeSearch(InventorySystem system)
{
	InventorySystem::Item newItem("TestName", 100005, 1000);
	system.inventoryVector.push_back(newItem);
	system.inventoryTree.insert(newItem);

	system.inventoryTree.searchByID(100005);
}
void testTreeEdit(InventorySystem system)
{
	InventorySystem::Item newItem("TestName", 100005, 1000);
	system.inventoryVector.push_back(newItem);
	system.inventoryTree.insert(newItem);

	system.inventoryTree.printItem(100005);
	system.inventoryTree.editAmountInStock(100005, 250);
	cout << endl;
	system.inventoryTree.printItem(100005);
}

// ===================== User Program ===========================
// Creates an inventory system and based on userInput lets the user insert, delete, search, and edit items
void userProgram()
{
	InventorySystem system;
	string command;
	string name;
	int idNumber;
	int inStock;

	cout << "List of commands (action | command/input):" << endl;
	cout << "insert | insert nameOfItem idNumber amountInStock" << endl;
	cout << "searchByID | searchByID idNumber" << endl;
	cout << "searchByName | searchByName name" << endl;
	cout << "delete | delete idNumber" << endl;
	cout << "editAmount | editAmount idNumber amountInStock" << endl;
	cout << "printTree | printTree" << endl;
	cout << "printMap | printMap" << endl;
	cout << "exit program | exit" << endl;
	cout << "print commands | commands" << endl;
	cout << endl;

	while (command != "exit")
	{
		cin >> command;

		if (command == "commands")
		{
			cout << "List of commands (action | command/input):" << endl;
			cout << "insert | insert nameOfItem idNumber amountInStock" << endl;
			cout << "searchByID | searchByID idNumber" << endl;
			cout << "searchByName | searchByName name" << endl;
			cout << "delete | delete idNumber" << endl;
			cout << "editAmount | editAmount idNumber amountInStock" << endl;
			cout << "printTree | printTree" << endl;
			cout << "printMap | printMap" << endl;
			cout << "exit program | exit" << endl;
			cout << "print commands | commands" << endl;
			cout << endl;
		}
		else if (command == "insert")
		{
			cin >> name;
			cin >> idNumber;
			cin >> inStock;
			system.insert(name, idNumber, inStock);
			cout << "Inserted: " << name << " " << idNumber << " " << inStock << endl;
			cout << endl;
		}
		else if (command == "searchByID")
		{
			cin >> idNumber;
			system.searchByID(idNumber);
		}
		else if (command == "searchByName")
		{
			cin >> name;
			system.searchByName(name);
		}
		else if (command == "delete")
		{
			cin >> idNumber;
			if (system.searchInventory(idNumber))
			{
				system.deleteByID(idNumber);
				cout << "Deleted item with idNumber: " << idNumber << endl;
			}
			else
				cout << "Item with that idNumber doesn't exist" << endl;
			cout << endl;
		}
		else if (command == "editAmount")
		{
			cin >> idNumber;
			cin >> inStock;
			if (system.searchInventory(idNumber))
			{
				system.editAmountInStock(idNumber, inStock);
				cout << "Edited item with idNumber: " << idNumber << endl;
				cout << "New amount in stock: " << inStock << endl;
			}
			else
				cout << "Item with that idNumber doesn't exist" << endl;
			cout << endl;
		}
		else if (command == "printTree")
		{
			system.printTree();
		}
		else if (command == "printMap")
		{
			system.printMap();
		}
		else if (command == "exit")
		{
			cout << "Program exited" << endl;
		}
		else
		{
			cout << "Not a command" << endl;
		}
	}
}

// ===================== Test Cases for User Program ===========================
void userTest1(InventorySystem system)
{
	/*
		insert
		insert
		edit 1
		search 1
		search 2
	*/
	InventorySystem::Item newItem("TestName", 100005, 1000);
	system.insert("TestName", 100005, 1000);
	system.insert("TestName2", 100007, 3000);

	system.printMap();
	system.printTree();

	system.editAmountInStock(100005, 250);
	cout << "Edited item with ID #100005, new inStock amount is 250" << endl;
	cout << endl;

	cout << "Search for item with ID #100005" << endl;
	system.searchByID(100005);

	cout << "Search for item with ID #100007" << endl;
	system.searchByID(100007);
}
void userTest2(InventorySystem system)
{
	/*
		insert
		insert
		delete 1
		search 1
		search 2
	*/
	InventorySystem::Item newItem("TestName", 100005, 1000);
	system.insert("TestName", 100005, 1000);
	system.insert("TestName2", 100007, 3000);

	system.printMap();
	system.printTree();

	system.deleteByID(100005);
	cout << "Deleted item with ID #100005" << endl;
	cout << endl;

	cout << "Search for item with ID #100005" << endl;
	system.searchByID(100005);
	cout << endl;
	cout << "Search for item with ID #100007" << endl;
	system.searchByID(100007);
}
void userTest3(InventorySystem system)
{

	/*
		Creates a tree, deletes all nodes, then inserts again
		insert
		insert
		delete
		delete
		insert
	*/
	system.insert("TestName", 100005, 1000);

	system.printTree();
	system.printMap();

	system.deleteByID(100005);

	system.printTree();
	system.printMap();
	cout << "Both data structures are empty" << endl;
	cout << endl;

	system.insert("TestName", 100005, 1000);

	system.printTree();
	system.printMap();
}
void userTest4(InventorySystem system)
{
	/*
		edit item in empty list (does nothing)
		delete item in empty list (does nothing)
		insert item
		insert item with same idNumber (does nothing)
		print
	*/
	system.editAmountInStock(100005, 1000);
	system.deleteByID(100005);
	cout << "Editing and Deleting from empty structures does nothing.";
	cout << endl;

	system.insert("TestName1", 100005, 1000);
	system.insert("TestName2", 100005, 1000);
	cout << "Cannot insert item with duplicate idNumbers.";
	cout << endl;

	system.printTree();
	system.printMap();
}

// ======= Run program (execution time analysis or user program) =======
void runProgram()
{
	cout << "Menu: " << endl;
	cout << "1 - Run execution time calculations" << endl;
	cout << "2 - Run user-based program" << endl;
	cout << "Choice: ";
	int choice;
	cin >> choice;
	if (choice == 1)
	{
		// Run all tests
		InventorySystem system;
		runTests(system, 100000);
	}
	else if (choice == 2)
	{
		// Run program based on user input
		userProgram();
	}
	else
	{
		cout << "Out of bounds choice" << endl;
	}
}

// ===================== Main Method ===========================
int main()
{

	runProgram();

	// --- Test cases based on data structure ---
	// InventorySystem system;
	// -- For map --
	// testMapInsert(system);
	// testMapDelete(system);
	// testMapSearch(system);
	// testMapEdit(system);
	// -- For tree --
	// testTreeInsert(system);
	// testTreeDelete(system);
	// testTreeSearch(system);
	// testTreeEdit(system);

	// --- Test cases for userProgram ---
	// InventorySystem system;
	// userTest1(system);
	// userTest2(system);
	// userTest3(system);
	// userTest4(system);

	return 0;
};