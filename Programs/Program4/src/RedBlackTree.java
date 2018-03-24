/*Class: CS 3345
 * Section: 004
 * Semester: Spring 2018
 * Project 4: Program that implements a RedBlackTree.*/
import java.util.ArrayList;

public class RedBlackTree<E extends Comparable> {
    public static boolean RED = false;
    public static boolean BLACK = true;
    private int treeSize;
    private String toStringString = "";
    private Node<E> root;

    /**
     * Constructor for RedBlackTree with no given parameters
     * Sets root to null
     */
    public RedBlackTree(){
        root = null;
        treeSize = 0;
    }

    /**
     * Method that inserts an element into the tree
     * @param element is what we want to be inserted into the tree
     * @return Whether or not the insertion was successful
     * @throws NullPointerException
     */
    public boolean insert(E element) throws NullPointerException{
        if (element == null){       //Check to make sure element isn't null
            throw new NullPointerException("Trying to insert a null element");
        }
        Node<E> newNode = new Node<>(element);      //Create the node with the element
        int oldSize = treeSize;         //Save the size of the tree before insertion
        root = initialInsert(root,newNode);
        if (oldSize<treeSize){      //See if the size changed. If it did, insertion was successful and we need to fix any possible violations in the tree
            root = fixVolation(root,newNode);
            return true;
        }
        else{
            return false;
        }
    }

    /**
     * Function to fix any RedBlackTree rule violations. Restructures and recolors nodes to do this.
     * @param rootNode  Node we are looking at
     * @param newNode   Node we inserted
     * @return  Node that will = root
     */
    private Node<E> fixVolation(Node<E> rootNode, Node<E> newNode) {
        Node<E> parentOfNewNode = null;
        Node<E> grandParentOfNewNode = null;

        while((newNode != rootNode) && (newNode.color != BLACK) && (newNode.parent.color == RED)){      //While there is a violation
            parentOfNewNode = newNode.parent;       //Save the parent
            grandParentOfNewNode = newNode.parent.parent;       //Save the grandparent

            //Case A: parent of newNode is left child of Grandparent of newNode
            if (parentOfNewNode == grandParentOfNewNode.leftChild){
                Node<E> uncleOfNewNode = grandParentOfNewNode.rightChild;

                //Case 1: Uncle of newNode is also red. Only needs recoloring
                if (uncleOfNewNode != null && uncleOfNewNode.color == RED){
                    grandParentOfNewNode.color = RED;
                    parentOfNewNode.color = BLACK;
                    uncleOfNewNode.color = BLACK;
                    newNode = grandParentOfNewNode;
                }

                else{

                    //Case 2: newNode is right child of it's parent. Do left-rotation
                    if (newNode == parentOfNewNode.rightChild){
                        ArrayList<Node<E>> tempList = rotateLeft(rootNode,parentOfNewNode);     //Save the fixed nodes
                        rootNode = tempList.get(0);     //Set rootNode to the first fixed node
                        parentOfNewNode = tempList.get(1);      //Set parentNode to the second fixed node
                        newNode = parentOfNewNode;
                        parentOfNewNode = newNode.parent;
                    }

                    //Case 3: newNode is left child of parent. Do right-rotation
                    ArrayList<Node<E>> tempList = rotateRight(rootNode,grandParentOfNewNode);
                    rootNode = tempList.get(0);
                    grandParentOfNewNode = tempList.get(1);

                    //Swap their colors
                    boolean tempColor = parentOfNewNode.color;
                    parentOfNewNode.color = grandParentOfNewNode.color;
                    grandParentOfNewNode.color = tempColor;

                    newNode = parentOfNewNode;
                }
            }

            //Case B: Parent of newNode is right child of grandParent
            else{
                Node<E> uncleOfNewNode = grandParentOfNewNode.leftChild;

                //Case 1: The uncle of newNode is also red. Only need to recolor
                if (uncleOfNewNode != null && uncleOfNewNode.color == RED){
                    grandParentOfNewNode.color = RED;
                    parentOfNewNode.color = BLACK;
                    uncleOfNewNode.color = BLACK;
                    newNode = grandParentOfNewNode;
                }
                else{
                    //Case 2: newNode is left child of parent. Need to right rotate
                    if (newNode == parentOfNewNode.leftChild){
                        ArrayList<Node<E>> tempList;
                        tempList = rotateRight(rootNode,parentOfNewNode);
                        rootNode = tempList.get(0);
                        parentOfNewNode = tempList.get(1);
                        newNode = parentOfNewNode;
                        parentOfNewNode = newNode.parent;
                    }


                    //Case 3: newNode is right child of parent. Need to left rotate
                    ArrayList<Node<E>> tempList = rotateLeft(rootNode,grandParentOfNewNode);
                    rootNode = tempList.get(0);
                    grandParentOfNewNode = tempList.get(1);

                    //Swap their colors
                    boolean tempColor = parentOfNewNode.color;
                    parentOfNewNode.color = grandParentOfNewNode.color;
                    grandParentOfNewNode.color = tempColor;

                    newNode = parentOfNewNode;
                }
            }
        }
        rootNode.color = BLACK;
        return rootNode;
    }

    /**
     * Function to do a left Rotation
     * @param rootNode The root node for the rotation
     * @param newNode The newly Inserted node
     * @return A list of the nodes that have been changed
     */
    private ArrayList<Node<E>> rotateLeft(Node<E> rootNode, Node<E> newNode) {
        ArrayList<Node<E>> listOfNodes = new ArrayList<>();


        Node<E> newNodeRightChild = newNode.rightChild;

        newNode.rightChild = newNodeRightChild.leftChild;

        if (newNode.rightChild != null)
            newNode.rightChild.parent = newNode;

        newNodeRightChild.parent = newNode.parent;

        if (newNode.parent == null){
            rootNode = newNodeRightChild;
        }

        else if(newNode == newNode.parent.leftChild){
            newNode.parent.leftChild = newNodeRightChild;
        }
        else{
            newNode.parent.rightChild = newNodeRightChild;
        }

        newNodeRightChild.leftChild = newNode;
        newNode.parent = newNodeRightChild;

        listOfNodes.add(rootNode);
        listOfNodes.add(newNode);
        return listOfNodes;
    }

    /**
     * Function to do a right Rotation
     * @param rootNode The root node for the rotation
     * @param newNode The newly Inserted node
     * @return A list of the nodes that have been changed
     */
    private ArrayList<Node<E>> rotateRight(Node<E> rootNode, Node<E> newNode){
        ArrayList<Node<E>> listOfNodes = new ArrayList<Node<E>>();

        Node<E> newNodeLeftChild = newNode.leftChild;

        newNode.leftChild = newNodeLeftChild.rightChild;

        if (newNode.leftChild != null)
            newNode.leftChild.parent = newNode;

        newNodeLeftChild.parent = newNode.parent;

        if (newNode.parent == null){
            rootNode = newNodeLeftChild;
        }

        else if(newNode == newNode.parent.leftChild)
            newNode.parent.leftChild = newNodeLeftChild;

        else
            newNode.parent.rightChild = newNodeLeftChild;

        newNodeLeftChild.rightChild = newNode;
        newNode.parent = newNodeLeftChild;

        listOfNodes.add(rootNode);
        listOfNodes.add(newNode);
        return listOfNodes;
    }

    /**
     * A BST style insertion. Inserts the node without worrying about violations to the RedBlackTree properties
     * @param rootNode current node we are on
     * @param nodeToInsert Node we are wanting to insert
     * @return The node we inserted
     */
    public Node<E> initialInsert(Node<E> rootNode, Node<E> nodeToInsert){
        if (rootNode == null){
            treeSize++;         //Increment treeSize so we can see if the insertion was successful
            return nodeToInsert;
        }

        if (nodeToInsert.element.compareTo(rootNode.element) < 0){
            rootNode.leftChild = initialInsert(rootNode.leftChild,nodeToInsert);
            rootNode.leftChild.parent = rootNode;
        }
        else if(nodeToInsert.element.compareTo(rootNode.element) > 0){
            rootNode.rightChild = initialInsert(rootNode.rightChild,nodeToInsert);
            rootNode.rightChild.parent = rootNode;
        }

        return rootNode;
    }

    /**
     * Public function for seeing the the RedBlackTree contains a certain element
     * @param object is the element that we want to see if the RedBlackTree contains
     * @return whether or not the RedBlackTree contains the desired element
     */
    public boolean contains(Comparable<E> object){
        return doContains(root,object);
    }

    /**
     * Recursive function to see if tree contains an element. Uses compareTo Method that objects posses
     * @param node Node we are currently looking at
     * @param element element we are looking for
     * @return whether or not the element was found
     */
    private boolean doContains(Node<E> node, Comparable<E> element){
        if(node == null){
            return false;
        }

        if (element.compareTo(node.element) == 0){
            return true;
        }
        if(element.compareTo(node.element) < 0){
            return doContains(node.leftChild,element);
        }
        if(element.compareTo(node.element) > 0){
            return doContains(node.rightChild,element);
        }
        return false;
    }

    /**
     * Method overriding the toString method in java.lang.Object. Calls a private recursive function doToString to print RedBlackTree using a pre-order transversal
     * @return string containing the RedBlackTree after a pre-order transversal.
     */
    public String toString(){
        doToString(root);
        String returned = toStringString;
        toStringString = "";
        return returned;
    }

    /**
     * Private recursive helper function for toString
     * @param node is current node in tree. Adds this node to string, then calls the function for leftChild and then RightChild
     */
    private void doToString(Node<E> node){
        if (node == null){
            return;
        }
        toStringString += node.toString() + " ";   //Add current node to string
        doToString(node.leftChild);   //Do function for leftChild
        doToString(node.rightChild);  //Do function for rightChild
    }


}

class Node<E extends Comparable>{
    public E element;
    public Node<E> leftChild;
    public Node<E> rightChild;
    public Node<E> parent;
    public boolean color;

    /**
     * Constructor method for Node
     * @param ele is the element of the generic type
     * @param left is the left child of this node
     * @param right is the right child of this node
     * @param par is the parent of this node
     * @param color is the color of this node. Black is 0, red is 1.
     */
    public Node(E ele,Node<E> left,Node<E> right, Node<E> par, boolean color){
        element = ele;
        leftChild = left;
        rightChild = right;
        parent = par;
        this.color = color;
    }

    /**
     * Constructor for Node with only an element given
     * @param ele is the element for tbe node
     */
    public Node(E ele){
        element = ele;
        leftChild = null;
        rightChild = null;
        parent = null;
        color = RedBlackTree.RED;
    }

    /**
     * Constructor for Node with no parameters. Set's everything to null and color to RED
     */
    public Node(){
        element = null;
        leftChild = null;
        rightChild = null;
        parent = null;
        color = RedBlackTree.RED;
    }

    @Override
    public String toString() {
        String toRet = "";
        if (color == RedBlackTree.RED) {
            toRet += "*";
        }

        toRet+=element.toString();
        return toRet;

    }
}
