import java.util.*;
import java.util.ArrayList;
import java.util.Random;


public class InventorySystem {
    
    public class Item {
        String title = "";
        String author = "";
        int idNumber = 0;
        int inStock = 0;

        public Item(String title_, String author_, int idNumber_, int inStock_) {
            title = title_;
            author = author_;
            idNumber = idNumber_;
            inStock = inStock_;
        }
        
    }

    ArrayList<Item> inventoryList = new ArrayList<Item>(1);
    Map<Integer,String> inventoryMap; 

    // Methods/Functions 
    public void printInventory() {
        for(int i=0; i < inventoryList.size(); i++){
            System.out.println("Title: " + inventoryList.get(i).title);
            System.out.println("Author: " + inventoryList.get(i).author);
            System.out.println("ID number: " + inventoryList.get(i).idNumber);
            System.out.println("Amount in stock: " + inventoryList.get(i).inStock);
            System.out.println();
        }
    }


    // Sort Algorithms
    public void sortByTitle() {
        
    }

    public void sortByID() {
        

    }
    
    public void sortByAmountInStock() {
        
    }

    // Search algorithms
    public void searchByID(int idNumber_) {
        System.out.println(inventoryList.get(idNumber_+1));
        System.out.println("Title: " + inventoryList.get(idNumber_-1).title);
            System.out.println("Author: " + inventoryList.get(idNumber_-1).author);
            System.out.println("ID number: " + inventoryList.get(idNumber_-1).idNumber);
            System.out.println("Amount in stock: " + inventoryList.get(idNumber_-1).inStock);
            System.out.println();
    }

    public void searchByTItle() {
        
    }
    public void searchByAmountInStock(int idNumber_) {
        System.out.println(inventoryList.get(idNumber_+1));
        System.out.println("Title: " + inventoryList.get(idNumber_-1).title);
            System.out.println("Author: " + inventoryList.get(idNumber_-1).author);
            System.out.println("ID number: " + inventoryList.get(idNumber_-1).idNumber);
            System.out.println("Amount in stock: " + inventoryList.get(idNumber_-1).inStock);
            System.out.println();
    }

    // Creates an inventory with a random title, author, and amount in stock
    public void inventoryGenerator(int inventoryNumber) {
        Random randomNumber = new Random();
        // String titles[]; 
        // names[randomNumber.nextInt(names.length)];
        for(int i=0; i < inventoryNumber; i++){
            // randomly generate an item
            Item item = new Item("Title", "author", i+1, randomNumber.nextInt(1000)); 
            // add item to inventory list/arry
            inventoryList.add(item);
            // add item to inventory dictionary/map
            // inventoryMap.put(item.idNumber, item.title);
            
        }
    }
    
    // Runs program
    public static void main(String[] args) {
        // Creates an inventory system
        InventorySystem example = new InventorySystem();

        // Creates 50 random inventory items
        example.inventoryGenerator(50);

        // Prints inventory
        example.printInventory();
        
    }
}


