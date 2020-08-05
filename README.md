# InventorySystem

**Description**

The AVL tree and map data structures are implemented from scratch in order to handle all of the system's data and the execution times of their methods are calculated (displayed in nanoseconds) and compared.

A user program was also added enabling real-time functionality.

In essence, the most simplified version (MVP) of an inventory system is created.

**Notes**

- User input validation hasn't been added, therefore errors can occur or the user program might crash if the input is incorrect.

- The entire project is based on **C++11**. Some errors may occur otherwise.

- Press _run_ in your IDE and the program should execute!

**Initial Menu**

```
-- Menu --
1 - Run execution time calculations
2 - Run user-based program
Choice:
```

### Execution Time Program

**Example - Output of Execution Time Program**

In the example below (the standard test), an inventory system is created with randomly generated data for 100,000 items/products (each with a random name, assigned idNumber, and random amount in stock). However, the inventory size can be modified.

```
Test #1 --- Insert()
Execution time by map : 675 nanoseconds
Execution time by tree : 910 nanoseconds

Test #2 --- Delete()
Execution time by map : 636 nanoseconds
Execution time by tree : 14407 nanoseconds

In Map:
Name: TestName
idNumber: 100005
Amount in Stock: 1000

In Tree:
Name: TestName
idNumber: 100005
Amount in Stock: 1000

Test #3 --- Search()
Execution time by map : 8893 nanoseconds
Execution time by tree : 6239 nanoseconds

Test #4 --- Edit()
Execution time by map : 199 nanoseconds
Execution time by tree : 314 nanoseconds
```

### User Program

**User Program Menu**

```
-- List of commands (action | command/input) --
insert | insert nameOfItem idNumber amountInStock
searchByID | searchByID idNumber
searchByName | searchByName name
delete | delete idNumber
editAmount | editAmount idNumber amountInStock
printTree | printTree
printMap | printMap
exit program | exit
print commands | commands
```

**User Program Output Examples**

Imagine it's Tesla's inventory system.

```
insert ModelX 1 2500
Inserted: ModelX 1 2500
```

```
insert ModelY 2 3000
Inserted: ModelY 2 3000
```

```
delete 2
Deleted item with idNumber: 2
```

```
searchByID 1
In Tree:
Name: ModelX
idNumber: 1
Amount in Stock: 2500

In Map:
Name: ModelX
idNumber: 1
Amount in Stock: 2500
```

```
editAmount 1 200
Edited item with idNumber: 1
New amount in stock: 200
```

```
exit
Program exited
```
