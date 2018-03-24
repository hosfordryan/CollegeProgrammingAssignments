/*Class: CS 3345
* Section: 004
* Semester: Spring 2018
* Project 2: Program that uses a Singly Linked List written by me, populated with objects that implement an interface created by me.*/
import java.util.Scanner;

public class main {

    public static Scanner in = new Scanner(System.in);
    public static void main(String[] args){
        singlyLinkedList<Magazine> list = new singlyLinkedList<>();

        int choice=0;
        while(choice != 7){
            System.out.println();
            System.out.println("Operations on List:");
            System.out.println("1. Make Empty");
            System.out.println("2. Find ID");
            System.out.println("3. Insert At Front");
            System.out.println("4. Delete From Front");
            System.out.println("5. Delete ID");
            System.out.println("6. Print All Records");
            System.out.println("7. Done");
            System.out.println("\n Please enter a number 1-7...");

            choice = getInt();
            if (choice == 1)
                makeEmpty(list);
            else if (choice == 2)
                findID(list);
            else if (choice == 3)
                insertAtFront(list);
            else if (choice == 4)
                deleteFromFront(list);
            else if (choice == 5)
                deleteID(list);
            else if (choice == 6)
                printAllRecords(list);
            else if (choice >= 7 && choice < Integer.MAX_VALUE)
                done();
        }
    }

    public static void makeEmpty(singlyLinkedList<Magazine> lst){
        System.out.println("Your choice: 1");
        lst.makeEmpty();
    }
    public static void findID(singlyLinkedList<Magazine> lst){
        System.out.println("Your choice: 2");
        System.out.println("Which ID do you want to find?");
        try {
            int tar = getInt();
            if (tar == Integer.MAX_VALUE)
                return;
            lst.findID(tar).printID();
        }catch (NullPointerException e){
            System.out.println("ID not found");
        }
    }
    public static void insertAtFront(singlyLinkedList<Magazine> lst){
        System.out.println("Your choice: 3");
        System.out.println("Enter Magazine ID: ");
        int id = getInt();
        if (id == Integer.MAX_VALUE)
            return;
        System.out.println("Enter Magazine Name: ");
        String magName = in.nextLine();
        System.out.println("Enter Publisher Name" );
        String pubName = in.nextLine();
        Magazine newMag = new Magazine(id,magName,pubName);
        lst.insertAtFront(newMag);
        System.out.println("...");
        System.out.println("Magazine Added.");
    }
    public static void deleteFromFront(singlyLinkedList<Magazine> lst){
        System.out.println("Your choice: 4");
        try {
            Magazine deleted = lst.deleteFromFront();
            System.out.println("Deleted: ");
            deleted.printID();
        }catch(NullPointerException e){
            System.out.println("List is empty.");
        }
    }
    public static void deleteID(singlyLinkedList<Magazine> lst){
        System.out.println("Your choice: 5");
        System.out.println("Which ID would you like to delete?");
        int tar = getInt();
        if (tar == Integer.MAX_VALUE)
            return;
        try {
            Magazine deleted = lst.delete(tar);
            System.out.println("Deleted: ");
            deleted.printID();
        }catch(NullPointerException e) {
            System.out.println("ID not found.");
        }

    }
    public static void printAllRecords(singlyLinkedList<Magazine> lst){
        System.out.println("Your choice: 6");
        lst.printAllRecords();
    }
    public static void done(){
        System.exit(0);
    }

    public static int getInt(){
        try{
            int tar = Integer.parseInt(in.nextLine());
            return tar;
        }catch(NumberFormatException e){
            System.out.println("Not a valid integer");
        }
        return Integer.MAX_VALUE;
    }

}
