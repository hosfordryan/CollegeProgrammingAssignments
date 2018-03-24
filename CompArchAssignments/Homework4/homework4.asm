#homework3.asm
# Ryan Hosford - rph160030
# Takes filename from user and counts the occurance of digits 0-9

.data
	inputPrompt: .asciiz "Enter the filename:\n"
	newLine: .asciiz "\n"
	space: .asciiz " "
	colon: .asciiz ":"
	output0: .asciiz "Number of times 0 occured: "
	output1: .asciiz "Number of times 1 occured: "
	output2: .asciiz "Number of times 2 occured: "
	output3: .asciiz "Number of times 3 occured: "
	output4: .asciiz "Number of times 4 occured: "
	output5: .asciiz "Number of times 5 occured: "
	output6: .asciiz "Number of times 6 occured: "
	output7: .asciiz "Number of times 7 occured: "
	output8: .asciiz "Number of times 8 occured: "
	output9: .asciiz "Number of times 9 occured: "
	
	userInputBuffer: .space 100	#Max 100 chars for input filename
	fileInputBuffer: .space 100000	#100000 bytes of space for the file input

.text
	la $a0, inputPrompt	#Load input prompt into syscall
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
		
	# Now we need to read the file
	#First, we need to open the file to get the file descriptor
	
	li $v0, 13	#Open file mode
	la $a0, userInputBuffer		#input file name
	li $a1,0	#flag for reading
	add $a2, $zero, $zero	#Set to 0. Doesn't matter, mode is ignored
	syscall		#open file
	move $s0, $v0	#save the file descriptor
	
	add $t0, $v0, $zero
	li $v0, 1
	add $a0, $t0, $zero
	syscall
	
	#Now we need to read the file
	
	li $v0, 14	#set mode to read from file
	move $a0,$s0	#load in file descriptor
	la $a1, fileInputBuffer		#address of buffer from which to read
	li $a2, 100001	# max length of 100000 chars
	syscall		#read from file
	
	li $t0, 0	#Init index to 0
	li $s0, 0	#Count for 0
	li $s1, 0	#Count for 1
	li $s2, 0	#Count for 2
	li $s3, 0	#Count for 3
	li $s4, 0	#Count for 4
	li $s5, 0	#Count for 5
	li $s6, 0	#Count for 6
	li $s7, 0	#Count for 7
	li $t8, 0	#Count for 8
	li $t9, 0	#Count for 9
	
	readLoop:
		lb $a1 fileInputBuffer($t0)	#Load in byte at index
		addi $t0, $t0, 1	#increment index
		

		
		#If we are at end of file, exit loop
		seq $t3,$a1,$zero	#see if current char is 0
		beq $t3,1,exitFileLoop	#If it is a 0, exit main loop
		
		#Branch statements for each integer
		beq $a1,48,zero		# if char is 0, branch
		beq $a1,49,one		# if char is 1, branch
		beq $a1,50,two		# if char is 2, branch
		beq $a1,51,three	# if char is 3, branch
		beq $a1,52,four		# if char is 4, branch
		beq $a1,53,five		# if char is 5, branch
		beq $a1,54,six		# if char is 6, branch
		beq $a1,55,seven	# if char is 7, branch
		beq $a1,56,eight	# if char is 8, branch
		beq $a1,57,nine		# if char is 9, branch
		
		j readLoop	#Jump to start of loop if this char isn't a digit
		
		zero:
			addi $s0,$s0,1	#increment 0 count
			j readLoop	#Jump to start of loop
		one:
			addi $s1,$s1,1	#increment 1 count
			j readLoop	#Jump to start of loop
		two:
			addi $s2,$s2,1	#increment 2 count
			j readLoop	#Jump to start of loop
		three:
			addi $s3,$s3,1	#increment 3 count
			j readLoop	#Jump to start of loop
		four:
			addi $s4,$s4,1	#increment 4 count
			j readLoop	#Jump to start of loop
		five:
			addi $s5,$s5,1	#increment 5 count
			j readLoop	#Jump to start of loop
		six:
			addi $s6,$s6,1	#increment 6 count
			j readLoop	#Jump to start of loop
		seven:
			addi $s7,$s7,1	#increment 7 count
			j readLoop	#Jump to start of loop
		eight:
			addi $t8,$t8,1	#increment 8 count
			j readLoop	#Jump to start of loop
		nine:
			addi $t9,$t9,1	#increment 9 count
			j readLoop	#Jump to start of loop
			
	exitFileLoop:
		la $a0, output0	#load in output prompt for 0
		li $v0, 4 	#output mode to string
		syscall
		li $v0, 1	#output mode to integer
		add $a0, $s0, $zero	#output 0 count
		syscall
		li $v0, 4	#output mode to string
		la $a0, newLine	#output newline
		syscall
		
		
		la $a0, output1	#load in output prompt for 1
		li $v0, 4 	#output mode to string
		syscall
		li $v0, 1	#output mode to integer
		add $a0, $s1, $zero	#output 1 count
		syscall
		li $v0, 4	#output mode to string
		la $a0, newLine	#output newline
		syscall
		
		la $a0, output2	#load in output prompt for 2
		li $v0, 4 	#output mode to string
		syscall
		li $v0, 1	#output mode to integer
		add $a0, $s2, $zero	#output 2 count
		syscall
		li $v0, 4	#output mode to string
		la $a0, newLine	#output newline
		syscall
		
		la $a0, output3	#load in output prompt for 3
		li $v0, 4 	#output mode to string
		syscall
		li $v0, 1	#output mode to integer
		add $a0, $s3, $zero	#output 3 count
		syscall
		li $v0, 4	#output mode to string
		la $a0, newLine	#output newline
		syscall
		
		la $a0, output4	#load in output prompt for 4
		li $v0, 4 	#output mode to string
		syscall
		li $v0, 1	#output mode to integer
		add $a0, $s4, $zero	#output 4 count
		syscall
		li $v0, 4	#output mode to string
		la $a0, newLine	#output newline
		syscall
		
		la $a0, output5	#load in output prompt for 5
		li $v0, 4 	#output mode to string
		syscall
		li $v0, 1	#output mode to integer
		add $a0, $s5, $zero	#output 5 count
		syscall
		li $v0, 4	#output mode to string
		la $a0, newLine	#output newline
		syscall
		
		la $a0, output6	#load in output prompt for 6
		li $v0, 4 	#output mode to string
		syscall
		li $v0, 1	#output mode to integer
		add $a0, $s6, $zero	#output 6 count
		syscall
		li $v0, 4	#output mode to string
		la $a0, newLine	#output newline
		syscall
		
		la $a0, output7	#load in output prompt for 7
		li $v0, 4 	#output mode to string
		syscall
		li $v0, 1	#output mode to integer
		add $a0, $s7, $zero	#output 7 count
		syscall
		li $v0, 4	#output mode to string
		la $a0, newLine	#output newline
		syscall
		
		la $a0, output8	#load in output prompt for 8
		li $v0, 4 	#output mode to string
		syscall
		li $v0, 1	#output mode to integer
		add $a0, $t8, $zero	#output 8 count
		syscall
		li $v0, 4	#output mode to string
		la $a0, newLine	#output newline
		syscall
		
		la $a0, output9	#load in output prompt for 9
		li $v0, 4 	#output mode to string
		syscall
		li $v0, 1	#output mode to integer
		add $a0, $t9, $zero	#output 9 count
		syscall
		li $v0, 4	#output mode to string
		la $a0, newLine	#output newline
		syscall
		
		li $v0, 17	#set syscall to exit program
		syscall		#exit program
		
		
