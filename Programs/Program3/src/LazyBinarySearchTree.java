/*Class: CS 3345
 * Section: 004
 * Semester: Spring 2018
 * Project 3: Program that implements a BinarySearchTree that uses lazy deletion.*/
public class LazyBinarySearchTree {

    public TreeNode root;
    private int theSize;
    private String toStringString = "";

    /**
     * Constructor method for LazyBinarySearchTree that takes no arguments. Sets root to null and size to 0
     */
    public LazyBinarySearchTree(){
        root = null;
        theSize = 0;
    }

    /**
     * Constructor method for LazyBinarySearchTree that takes a node as an argument. Sets root to that arg and size to 1
     * @param node
     */
    public LazyBinarySearchTree(TreeNode node){
        root = node;
        theSize = 1;
    }

    /**
     * Method to insert a node into the Tree.
     * @param key Value to insert into tree
     * @return  whether or not the insert was successful
     */
    public boolean insert(int key){
        if (key < 1 || key > 99){   //Make sure key is valid
            throw new IllegalArgumentException();
        }

        //If there aren't any nodes in tree, make this node the root
        if (root == null){
            TreeNode temp = new TreeNode(key);
            root = temp;
            theSize++;
            return true;
        }
        int oldSize = theSize;
        doInsert(root, key);
        if (oldSize < theSize)      //Checking to see if the size changed so we can see if the insertion was successful
            return true;
        else
            return false;

    }

    private void doInsert(TreeNode node, int key) {


        if (key < node.getKey() && node.getLeftChild() != null){        //Need to keep moving through tree
            doInsert(node.getLeftChild(),key);
        }
        else if (key > node.getKey() && node.getRightChild() != null){        //Need to keep moving through tree
            doInsert(node.getRightChild(),key);
        }

        else if (node.getKey() == key && node.isDeleted()){      //We found the node we want to insert but it was previously deleted.
            node.setDeleted(false);         //Set it to not deleted
            theSize++;
            return;
        }

        else if (node.getKey() == key && !node.isDeleted()){         //The node we are trying to insert is already in tree
            return;
        }

        else if (key < node.getKey() && node.getLeftChild() == null){        //We found where we want to insert
            TreeNode newNode = new TreeNode(key);
            node.setLeftChild(newNode);
            //System.out.println("added left Child: " + key);
            theSize++;
            return;
        }
        else if (key > node.getKey() && node.getRightChild() == null){        //We found where we want to insert
            TreeNode newNode = new TreeNode(key);
            node.setRightChild(newNode);
            //System.out.println("added right Child: " + key);
            theSize++;
            return;
        }
    }

    /**
     * Method to set the delete option of a node in the tree
     * @param key value to delete from tree
     * @return Whether or not the delete was successful
     */
    public boolean delete(int key){
        if (key < 1 || key > 99){       //Make sure key is valid
            throw new IllegalArgumentException();
        }
        return doDelete(root,key);
    }

    private boolean doDelete(TreeNode node, int key) {
        if (node == null)
            return false;
        if(node.getKey() == key){
            node.setDeleted(true);
            return true;
        }
        if(key < node.getKey()){    // Need to look to the left
            return doDelete(node.getLeftChild(),key);
        }
        if(key > node.getKey()){    //Need to look to the right
            return doDelete(node.getRightChild(),key);
        }
        return false;

    }

    /**
     * Method to find the minimum value in the tree. Ignores nodes that have been "deleted"
     * @return value of the smallest node in the tree
     */
    public int findMin(){
        int[] min = new int[]{-1};      //Declare an array to store minimum value
        inOrderForMinimum(root,min);    //Call function to get minimum value
        return min[0];
    }

    private void inOrderForMinimum(TreeNode node, int[] min){
        if (node != null){
            inOrderForMinimum(node.getLeftChild(),min);     //Go as left as possible first
            if (!node.isDeleted()){     //Make sure node hasn't been deleted
                if (min[0] == -1) {     //Check if min[0] has been written to before
                    min[0] = node.getKey();
                }
                return;
            }
            inOrderForMinimum(node.getRightChild(),min);    //Then go right if we didn't find a node that works
        }
    }

    /**
     * Method to find the maximum value in the tree. Ignores nodes that have been "deleted"
     * @return value of the largest node in the tree
     */
    public int findMax(){
        int[] max = new int[]{-1};      //Declare an array to store maximum value
        forMaximum(root,max);           //Call function to find max value
        return max[0];
    }

    private void forMaximum(TreeNode node, int[] max){
        if (node!= null){
            forMaximum(node.getRightChild(), max);      //Go as right as possible first
            if (!node.isDeleted()){                     //Make sure node hasn't been deleted
                if (max[0] == -1){                      //Check if max[0] has been written to before
                    max[0] = node.getKey();
                }
                return;
            }
            forMaximum(node.getLeftChild(), max);
        }
    }

    /**
     * Method to see if a value is within the tree
     * @param key value to look for in the tree
     * @return whether or not value was in the tree
     */
    public boolean contains(int key){
        if (key < 1 || key > 99){       //make sure key is valid
            throw new IllegalArgumentException();
        }
        return doesContain(root, key);
    }

    private boolean doesContain(TreeNode node, int key){
        if (node == null){
            return false;
        }
        if(node.getKey() == key && !node.isDeleted()){  //Check if current node matches and hasn't been deleted
            return true;
        }
        if(key < node.getKey()){    // Need to look to the left
            return doesContain(node.getLeftChild(),key);
        }
        if(key > node.getKey()){    // Need to look to the right
             return doesContain(node.getRightChild(),key);
        }
        return false;
    }

    /**
     * Method to print tree. Prints in PreOrder
     * @return string of tree in PreOrder
     */
    public String toString() {
        preorderString(root);
        String returned = toStringString;
        toStringString = "";
        return returned;
    }

    private void preorderString(TreeNode node) {
        if (node == null){
             return;
        }

        toStringString+= " ";
        if (node.isDeleted()) {
            toStringString += "*";
        }
        toStringString += node.getKey() + "";

        preorderString(node.getLeftChild());
        preorderString(node.getRightChild());


    }

    /**
     * Method to get the height of tree
     * @return height of the tree
     */
    public int height(){
        return getHeight(root);
    }

    private int getHeight(TreeNode node) {
        if (node == null){
            return -1;      //Base case is -1 because we add 1 afterwards.
        }
        return 1+ Math.max(getHeight(node.getLeftChild()),getHeight(node.getRightChild()));     //add 1 to the biggest subtree
    }

    /**
     * Method to get number of nodes in the tree (including "deleted" nodes)
     * @return number of nodes in the tree
     */
    public int size(){
        return theSize;
    }
}

class TreeNode {
    private int key;
    private boolean deleted;
    private TreeNode leftChild;
    private TreeNode rightChild;

    /**
     * Constructor for TreeNode
     * @param value key value for node to be created
     */
    public TreeNode(int value){
        key = value;
        deleted = false;
        leftChild = null;
        rightChild = null;
    }

    /**
     *
     * @return key of node
     */
    public int getKey() {
        return key;
    }

    /**
     *
     * @return Left child of node
     */
    public TreeNode getLeftChild() {
        return leftChild;
    }

    /**
     *
     * @return Right Child of node
     */
    public TreeNode getRightChild() {
        return rightChild;
    }

    /**
     * See if node is deleted
     * @return whether or not the node is marked as deleted
     */
    public boolean isDeleted() {
        return deleted;
    }

    /**
     * Set the deleted value
     * @param deleted value to set node's deleted value to
     */
    public void setDeleted(boolean deleted) {
        this.deleted = deleted;
    }

    /**
     * Change key
     * @param key value to change node's key value to
     */
    public void setKey(int key) {
        this.key = key;
    }

    /**
     * Change left child
     * @param leftChild new leftChild for node
     */
    public void setLeftChild(TreeNode leftChild) {
        this.leftChild = leftChild;
    }

    /**
     * change right child
     * @param rightChild new rightChild for node
     */
    public void setRightChild(TreeNode rightChild) {
        this.rightChild = rightChild;
    }
}