/*Class: CS 3345
 * Section: 004
 * Semester: Spring 2018
 * Project 2: Program that uses a Singly Linked List written by me, populated with objects that implement an interface created by me.*/
public class singlyLinkedList<AnyType extends IDedObject>  {
    public singlyLinkedList(){
        makeEmpty();
    }

    public Node<AnyType> endMarker;
    public Node<AnyType> beginMarker;

    public void makeEmpty(){
        endMarker = new Node<AnyType>(null,null);
        beginMarker = new Node<AnyType>(null,endMarker);
    }
    AnyType findID(int ID){
        Node<AnyType> curNode = beginMarker;
        while(curNode.getNext() != endMarker){
            if (curNode.getNext().getData().getID() == ID){
                Node<AnyType> toRet = curNode.getNext();
                return toRet.getData();
            }
            curNode = curNode.getNext();
        }
        return null;
    }

    boolean insertAtFront(AnyType x){
        if(findID(x.getID()) != null){
            return false;
        }
        Node<AnyType> newNode = new Node<>(x,beginMarker.getNext());
        beginMarker.setNext(newNode);
        return true;
    }

    AnyType deleteFromFront(){
        if(beginMarker.getNext() == endMarker){     //List is empty
            return null;
        }
        Node<AnyType> newNode = beginMarker.getNext();
        beginMarker.setNext(beginMarker.getNext().getNext());
        return newNode.getData();
    }

    AnyType delete(int ID){
        Node<AnyType> curNode = beginMarker;
        while(curNode.getNext() != endMarker){
            if (curNode.getNext().getData().getID() == ID){     //Found it
                Node<AnyType> toRet = curNode.getNext();
                curNode.setNext(curNode.getNext().getNext());
                return toRet.getData();

            }
            curNode = curNode.getNext();
        }
        return null;
    }

    void printAllRecords() {
        Node<AnyType> curNode = beginMarker.getNext();
        if (curNode == endMarker){
            System.out.println("List is empty.");
            return;
        }
        while(curNode != endMarker){
            curNode.getData().printID();
            curNode = curNode.getNext();
        }
    }
}

class Node<AnyType extends IDedObject>{
    public Node(AnyType d, Node<AnyType> n){
        data = d;
        next = n;
    }

    public Node getNext(){
        return next;
    }

    public void setData(AnyType newData){
        data = newData;
    }

    public void setNext(Node<AnyType> newNext){
        next = newNext;
    }

    public AnyType getData() {
        return data;
    }

    public AnyType data;
    private Node<AnyType> next;
}
