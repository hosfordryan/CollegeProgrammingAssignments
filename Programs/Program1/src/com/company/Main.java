// Class: CS 3345
// Section: 004
// Semester: Spring 2018
// Project 1: Prints all of the prime numbers up to a given input using the "Sieve of Eratosthenes" algorithm.


package com.company;
import java.util.InputMismatchException;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {

        Scanner in = new Scanner(System.in);
        System.out.println("Please enter a positive integer.");
        try {
            int n = in.nextInt();
            if(n<0){
                System.out.println("Invalid Input.");
                return;
            }
            boolean[] arr = new boolean[n+1];     //Init. bool array and then set all items to true
            for (int i = 0; i < arr.length ; i++) {
                arr[i] = true;
            }
            System.out.print("Primes up to "+n+": ");
            for (int i = 2; i < n+1 ; i++) {
                int j = 0;
                if(arr[i] == true){
                    System.out.print(i+", ");
                    while((i*i)+j*i <= n){
                        arr[((i*i)+j*i)] = false;
                        j++;
                    }
                }
            }
        }catch(InputMismatchException e){
            System.out.println("Invalid Input.");
        }

    }
}
