/*Class: CS 3345
 * Section: 004
 * Semester: Spring 2018
 * Project 4: Program that implements a RedBlackTree.*/

import java.util.Scanner;
import java.io.*;

public class Main {

    public static void main(String[] args) throws IOException{
	    PrintWriter outputStream = null;
	    try {
            Scanner in = new Scanner(new File(args[0]));        //Opening the input file
            outputStream = new PrintWriter(new FileWriter(args[1]));        //Opening the output file
            String dataType = in.nextLine();
            //Initial check to see if data type being used is valid.
            if (!dataType.contains("Integer") && !dataType.contains("String")) {
                outputStream.println("Only works for objects Integers and Strings");
            } else if (dataType.equals("Integer")) {    //It is an integer
                RedBlackTree<Integer> tree = new RedBlackTree<>();      //Initalize a null tree of type integer
                while (in.hasNextLine()) {      //Loop through the input file
                    String line = in.nextLine();        //Read line in file
                    if (!line.contains("Insert:") && !line.contains("Contains:") && !line.contains("PrintTree")) {      //See if line read contains one of the instructions we are looking for
                        outputStream.println("Error in Line: " + line);
                    }

                    //Now split into 2 categories. Instructions that require a number, and ones that don't.
                    if (line.contains("PrintTree")) {
                        //Doesn't require a number
                        if (line.equals("PrintTree"))
                            outputStream.println(tree);
                    } else if (line.contains("Insert:") || line.contains("Contains:")) {
                        //requires a number
                        boolean numberValid = false;        //Keep track if we read a valid integer
                        int number = 0;
                        int colonLocation = line.indexOf(":");
                        String instruction = line.substring(0, colonLocation );
                        if (line.length() > (line.substring(0,colonLocation + 1)).length()) {   //Checking if there is an integer after the semi-colon on the line
                            number = Integer.parseInt(line.substring(colonLocation + 1));       //Save that integer
                            numberValid = true;     //Say we read a valid integer
                        }
                        try{
                            if (instruction.equals("Insert") && numberValid){       //See if we read a valid integer and we want to insert
                                if (tree.insert(number))
                                    outputStream.println("True");
                                else
                                    outputStream.println("False");
                            }
                            if (instruction.equals("Contains") && numberValid){     //See if we read a valid integer and we want to see if the tree contains something
                                if (tree.contains(number))
                                    outputStream.println("True");
                                else{
                                    outputStream.println("False");
                                }
                            }
                        }catch(Exception e){
                        outputStream.println("Error in " + line.substring(0,colonLocation) + ": " + e.getClass().getSimpleName()+" raised");
                        }
                        if (!numberValid)
                            outputStream.println("Error in Line: " + line);
                    }
                }
            } else if (dataType.equals("String")) {     //It is a string
                RedBlackTree<String> tree = new RedBlackTree<>();      //Initalize a null tree of type String
                while (in.hasNextLine()) {
                    String line = in.nextLine();
                    if (!line.contains("Insert") && !line.contains("Contains") && !line.contains("PrintTree")) {
                        outputStream.println("Error in Line: " + line);
                    }

                    //Now split into 2 categories. Instructions that require an element, and ones that don't.
                    if (line.contains("PrintTree")) {
                        //Doesn't require an element
                        if (line.equals("PrintTree"))
                            outputStream.println(tree);
                    } else if (line.contains("Insert:") || line.contains("Contains:")) {
                        //requires an element
                        int colonLocation = line.indexOf(":");
                        String instruction = line.substring(0, colonLocation);
                        String element = (line.substring(colonLocation + 1));
                        try{
                            if (instruction.equals("Insert")){
                                if (tree.insert(element))
                                    outputStream.println("True");
                                else
                                    outputStream.println("False");
                            }
                            if (instruction.equals("Contains")){
                                if (tree.contains(element))
                                    outputStream.println("True");
                                else{
                                    outputStream.println("False");
                                }
                            }
                        }catch(Exception e){
                            outputStream.println("Error in " + line.substring(0,colonLocation) + ": " + e.getClass().getSimpleName()+" raised");
                        }
                    }

                }
            }

        }finally {
	        if (outputStream!=null)
	            outputStream.close();       //Close the outputStream when we are done with it
        }
    }
}
