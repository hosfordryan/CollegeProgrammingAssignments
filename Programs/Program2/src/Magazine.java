/*Class: CS 3345
 * Section: 004
 * Semester: Spring 2018
 * Project 2: Program that uses a Singly Linked List written by me, populated with objects that implement an interface created by me.*/
public class Magazine implements IDedObject{

    private int magazineID;
    private String magazineName;
    private String publisherName;

    public Magazine(int id, String magName, String pubName){
        magazineID = id;
        magazineName = magName;
        publisherName = pubName;
    }

    public void printID(){
        System.out.println("Magazine ID: " + magazineID);
        System.out.println("Magazine name: " + magazineName);
        System.out.println("Publisher name: " + publisherName);
        System.out.println();
    }
    public int getID(){
        return magazineID;
    }

    public String getMagazineName(){
        return magazineName;
    }

    public String getPublisherName(){
        return publisherName;
    }
}
