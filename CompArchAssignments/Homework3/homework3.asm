#homework3.asm
# Ryan Hosford - rph160030
# Takes filename from user and sums up the product of an unknown number of pairs of integers (total number of integers has to be even)

.data
	InputPrompt: .asciiz "What file contains your information?   (Maximum of 20 characters long) \n"
	multSymb: .asciiz " * "
	equalSymb: .asciiz " = "
	plusSymb: .asciiz " + "
	finalOutput: .asciiz "Final Output = "
	
	currentIndex: .asciiz "Current index is: "

	
	newLine: .asciiz "\n"
	userInputBuffer: .space 100	#Max 100 chars for input filename
	fileInputBuffer: .space 100000	#100000 bytes of space for the file input
	filename: .asciiz "homework2Input.txt"
	
.text
	la $a0, InputPrompt	#Load input prompt into syscall
	li $v0, 4	#Set syscall to output string
	syscall		#Display InputPrompt
	
	li $v0, 8	#Set syscall to read in string
	la $a0, userInputBuffer		#Load byte space into address
	li $a1, 101	#Max 100 chars for filename
	move $s0, $a0	#save string to s0
	syscall
	
	
	# Now we need to clear the \n off the end of the input
	
	li $t0, 0	#set index to 0
	remove:
		lb $a3,userInputBuffer($t0)		#Load character at index
		addi $t0,$t0,1		#increment index
		sne $t1,$a3,0		#see if character at index is 0
		beq $t1,1,remove	#if we aren't at the end, loop again
		subiu $t0,$t0,2		#backtrack index to '\n'
		sb $0, userInputBuffer($t0)		#add the terminating character in its place
		
	
	# Now we need to read the integers from the file
	#First, we need to open the file to get the file descriptor
	
	li $v0, 13	#Open file mode
	la $a0, userInputBuffer		#input file name
	li $a1,0	#flag for reading
	add $a2, $zero, $zero	#Set to 0. Doesn't matter, mode is ignored
	syscall		#open file
	move $s0, $v0	#save the file descriptor
	
	#Now we need to read the file
	
	li $v0, 14	#set mode to read from file
	move $a0,$s0	#load in file descriptor
	la $a1, fileInputBuffer		#address of buffer from which to read
	li $a2, 100001	# max length of 100000 chars
	syscall		#read from file

	
	# Now we have to loop through fileInputBuffer and split that into 2 integers

	li $t0, 0	#set index to 0
	li $t2, -1	#save a negative 1 value
	li $s0, '-'	#load ascii value of '-'
	li $s1, 13	# load ascii value of '\n'
	li $s2, '0'	# load ascii value of '0'
	li $s3, 10	#Load base value
	li $s7, 0	#Final answer
	
	
	li $v0, 4	#set syscall to output string
	la $a0, newLine	#Output newline
	syscall
	
	
fileLoop:	#Main loop to go through whole file
	
	lb $a1, fileInputBuffer($t0)	#Load in first character of file
	
	#If we are at end of file, exit loop
	seq $t3,$a1,$zero	#see if current char is 0
	beq $t3,1,exitFileLoop	#If it is a 0, exit main loop
	
	sgt $t1, $t0, 0		#See if index is greater than 1 to see if we are on the first iteration of the loop
	beqz $t1, firstIteration	#Skip outputting a + symbol if we are on the first iteration
	li $v0, 4		#Set syscall to output a string
	la $a0, plusSymb	#Output + symbol
	#syscall	
	firstIteration:
	
	li $t1, 1	#Set sign to 1
	li $s5, 0	#load 0 into s5, will be number 1
	li $s6, 0	#Load 0 into s6, will be number 2
	 
	
	#Checking first character to see if it's negative
	seq $a0,$a1,$s0		#see if first char is = '-'
	beqz $a0, nonNegative1	#Branch to nonNegative1 if they are not equal
	#If it's negative
	mult $t1,$t2	#Multiply sign value by -1
	mflo $t1	#save result back to t1
	addi $t0, $t0, 1	#increment index to pass sign character
	nonNegative1:	#Converting string to integer		
		lb $a1, fileInputBuffer($t0)	#Load in fileInputBuffer[i]
		
		
		addi $t0,$t0,1		#Index++
		seq $a0,$a1,$s1		#see if fileInputBuffer[i] != '\n'
		seq $a2,$a1,0		#see if fileInputBuffer[i] != 0
		or $a0,$a0,$a2		#or the 2 checks together and save in a0
		beq $a0,1, endOfNum1	#If either check was false, we are at the end of the first number
		mult $s5, $s3		#multiply number 1 and base
		mflo $t5		#set result to t5
		sub $t6, $a1, $s2	#subtract fileInputBuffer[i] and '0'
		add $s5, $t5,$t6	#Add those 2 together
		j nonNegative1		#Jump to start of loop
		endOfNum1:
			addi $t0,$t0,1	#Index++ to get passed \n
			lb $a1, fileInputBuffer($t0)	#Check the first byte of number 2
			#Checking first character to see if it's negative
			seq $a0,$a1,$s0		#see if first char is = '-'
			beqz $a0, nonNegative2	#Brandon to nonNegative1 if they are not equal
			#If it's negative

			mult $t1,$t2	#Multiply sign value by -1
			mflo $t1	#save result back to t1
			addi $t0, $t0, 1	#increment index to pass sign character
			nonNegative2:	#Converting string to integer
				lb $a1, fileInputBuffer($t0)	#Load in fileInputBuffer[i]
				seq $a0,$a1,$s1		#see if fileInputBuffer[i] == '\n'
				seq $a2	,$a1,0		#see if fileInputBuffer[i] == 0
				or $a0,$a2,$a0		#or the 2 checks together and save in a0
				beq $a0,1, endOfNum2	#If either check was false, we are at the end of the first number
				mult $s6, $s3		#multiply number 1 and base
				mflo $t5		#set result to t5
				sub $t6, $a1, $s2	#subtract fileInputBuffer[i] and '0'
				add $s6, $t5,$t6	#Add those 2 together
				addi $t0,$t0,1		#Index++
				j nonNegative2		#Jump to start of loop
				endOfNum2:
					addi $t0,$t0,2 	#Index+=2 to get past \n
				
					mult $s5,$s6	# Multiply number1 and number2
					mflo $s7	# Save result to s7
					mult $s7,$t1	# Multiply our sign value
					mflo $t9	#save result to t9
					add $t8,$t8,$t9	#Add this pair to total
					
					
					# Output integers
					li $v0, 1	#set syscall to output integer
					mult $s5, $t1	#multiply our sign value
					mflo $s5
					add $a0, $s5, $zero	#output number1
					syscall
					li $v0, 4	#set syscall to output string
					la $a0, multSymb	#output * symbol
					syscall
					li $v0, 1	#set syscall to output integer
					add $a0, $s6, $zero	#output number2
					syscall
					li $v0, 4	#set syscall to output string
					la $a0, equalSymb	#output " = "
					syscall
					li $v0, 1	#integer mode
					add $a0, $t9, $zero	#output result of multiplication
					syscall
					li $v0, 4	#string mode
					la $a0, newLine	#Output a newline
					syscall
					
					
					j fileLoop #restart loop
			
				exitFileLoop:	
					#Output answer
					
					
					li $v0, 4	#Output a string
					la $a0, finalOutput	#output finalOutput string
					syscall
					
					li $v0, 1	#set syscall to output integer
					add $a0,$t8,$zero	#output final answer
					syscall
					
					li $v0, 17	#set syscall to exit program
					syscall		#exit program
