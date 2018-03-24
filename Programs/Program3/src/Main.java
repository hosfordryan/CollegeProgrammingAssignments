/*Class: CS 3345
 * Section: 004
 * Semester: Spring 2018
 * Project 3: Program that implements a BinarySearchTree that uses lazy deletion.*/

import java.util.Scanner;
import java.io.*;

public class Main {

    public static void main(String[] args) throws IOException {
		PrintWriter outputStream = null;	//Define output variable
		LazyBinarySearchTree bst = new LazyBinarySearchTree();	//Initialize a null tree
		try {
			Scanner in = new Scanner(new File(args[0]));	//Open input file
			outputStream = new PrintWriter(new FileWriter(args[1]));	//Open output file

			while(in.hasNextLine()){	//While we have data to read
				String line = in.nextLine();	//Get the instruction line
				//Initial input Validation. Checks if the instruction is called correctly (not including number)
				if (!line.contains("Insert:") && !line.contains("Delete:") && !line.contains("Contains:") && !line.contains("PrintTree") && !line.contains("FindMin") && !line.contains("FindMax") && !line.contains("Height") && !line.contains("Size")){
					outputStream.println("Error in Line: " + line);
				}

				//Now split into 2 categories; instructions that require a number, and instructions that don't
				if (line.contains("PrintTree") || line.contains("FindMin") || line.contains("FindMax") || line.contains("Height") || line.contains("Size")){
					//Doesn't require a number.
					if (line.equals("PrintTree"))
						outputStream.println(bst);
					if (line.equals("FindMin"))
						outputStream.println(bst.findMin());
					if (line.equals("FindMax"))
						outputStream.println(bst.findMax());
					if (line.equals("Height"))
						outputStream.println(bst.height());
					if (line.equals("Size"))
						outputStream.println(bst.size());
				}

				else if (line.contains("Insert:") || line.contains("Delete:") || line.contains("Contains:")){
					//Requires a number
					int colonLocation = line.indexOf(":");
					String instruction = line.substring(0,colonLocation);
					int number = Integer.parseInt(line.substring(colonLocation+1));
					try{
						if (instruction.equals("Insert")){
							if (bst.insert(number))
								outputStream.println("True");
							else
								outputStream.println("False");
						}
						if (instruction.equals("Delete")){
							if(bst.delete(number)){
								outputStream.println("True");
							}
							else
								outputStream.println("False");
						}
						if (instruction.equals("Contains")){
							if(bst.contains(number))
								outputStream.println("True");
							else
								outputStream.println("False");
						}

					}catch (Exception e){	//If there in an IllegalArgumentException, catch it so program doesn't end
						outputStream.println("Error in " + line.substring(0,colonLocation) + ": " + e.getClass().getSimpleName()+" raised");
					}

				}

			}

		}finally{
			if (outputStream != null){	//Close outputStream when we're done with it
				outputStream.close();
			}
		}
	}
}
