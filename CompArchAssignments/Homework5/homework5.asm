#homework5.asm
# Ryan Hosford - rph160030
# Takes filename from user and reads machine code and displays which kind of instruction is being read

.data 
	inputPrompt: .asciiz "What file contains your machine code?\n"
	rType: .asciiz "R-Type: Opcode: "
	iType: .asciiz "I-Type: Opcode: "
	jType: .asciiz "J-Type: Opcode: "
	rs: .asciiz ", rs: "
	rt: .asciiz ", rt: "
	rd: .asciiz ", rd: "
	shamt: .asciiz ", shamt: "
	funct: .asciiz ", funct: "
	immed: .asciiz ", immediate: "
	address: .asciiz ", address: "
	error: .asciiz "Error. Instruction not found.\n"
	exitMessage: .asciiz "End of Program.\n"
	loopMessage: .asciiz "In main loop...\n"
	
	newLine: .asciiz "\n"
	userInputBuffer: .space 100	#Max 100 chars for input filename
	fileInputBuffer: .space 1000000	#1000000 bytes of space for the file input
	
	
	rTypes: .word 0,17	#array of opcodes that correspond to rTypes
	iTypes: .word 4,5,6,7,8,9,10,11,12,13,14,15,32,33,34,35,36,37,38,40,41,42,43,46,47,48,49,50,51,53,54,56,57,58,61,62 # iType opcodes
	jTypes: .word 2,3	#J-Type Opcodes
	
	
	jIs: .asciiz "j= "
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
	li $a2, 1000001	# max length of 100000 chars
	syscall		#read from file
	
	
	# Now we have to loop through lines in file to get different parts
	
	li $t0, 0 	# Set index to 0
	li $t1, 2	# Set base value to 2 (input is binary)
	li $s2, '0'	# load ascii value of '0'
	
	
mainLoop:	#main loop. Loop until end of file
	li $s0, 0	# Set opcode to 0
	li $t7, 0	# Set j = 0

	
	
	li $t2, 0	#clear t2
	lb $t2, fileInputBuffer($t0)	#Load in byte in file
	seq $t3,$t2,$zero	#see if current char is 0
	beq $t3,1,exitFileLoop	#If it is a 0, exit main loop
	
	
	opcodeLoop:	#Loop for getting opcode
		beq $t7, 6, gotOpcode	#If we are on our 7th iteration, we have the opcode
		lb $t2, fileInputBuffer($t0)	#Load in byte in file
		addi $t0, $t0, 1	# index++
		addi $t7, $t7, 1	# j++
		mult $s0, $t1		#multiply opcode and base
		mflo $t3		#set result to t5
		sub $t4, $t2, $s2	#subtract fileInputBuffer[i] and '0'
		add $s0, $t3,$t4	#Add those 2 together
		j opcodeLoop		#Jump to start of loop
	gotOpcode:
		
		#First check if opcode is a R-type
		li $t3, 0	#set j = 0
		la $t4, rTypes	#load rTypes array into t4
		rCheckLoop:
			beq $t3, 8, rLoopDone	#if we are at the end of array, exit loop
			add $t6, $t4, $t3	#combine to elements of address
			lw $t6, 0($t6)	#get item in array
			beq $s0, $t6, isRType	#if read opcode matches item in array, it's an R-type
			addi $t3, $t3, 4	#j+=4
			j rCheckLoop		#restart loop
		isRType:
			# It's an R-Type instruction, now find components of it.
			li $v0, 4
			la $a0, rType
			syscall		#Say it is an R-Type
			
			li $v0, 1		#Output opcode portion
			add $a0, $s0, $zero
			syscall
				
			#Find rs portion (5 bits)
			li $a0, 5	#set parameter to length of section we want
			jal readBits	#get the part of machine code
			add $s0, $v0, $zero	#save returned value into $s0
			li $v0, 4
			la $a0, rs		#output correct label
			syscall
			add $a0, $s0, $zero	#load result into syscall
			li $v0, 1		#output rs section
			syscall		
			
			#Find rt portion (5)
			li $a0, 5	#set parameter to length of section we want
			jal readBits	#get the part of machine code
			add $s0, $v0, $zero	#save returned value into $s0
			li $v0, 4
			la $a0, rt		#output correct label
			syscall
			li $v0, 1
			add $a0, $s0, $zero	#Output value of rt
			syscall	
				
			#find rd Portion (5)
			li $a0, 5	#set parameter to length of section we want
			jal readBits	#get the part of machine code
			add $s0, $v0, $zero	#save returned value into $s0
			li $v0, 4
			la $a0, rd		#output correct label
			syscall
			li $v0, 1
			add $a0, $s0, $zero	#Output value of rd
			syscall		
			
			#find shamt portion (5)
			li $a0, 5	#set parameter to length of section we want
			jal readBits	#get the part of machine code
			add $s0, $v0, $zero	#save returned value into $s0
			li $v0, 4
			la $a0, shamt		#output correct label
			syscall
			li $v0, 1
			add $a0, $s0, $zero	#Output value of shamt
			syscall
			
			#find funct portion (6)
			li $a0, 6	#set parameter to length of section we want
			jal readBits	#get the part of machine code
			add $s0, $v0, $zero	#save returned value into $s0
			li $v0, 4
			la $a0, funct		#output correct label
			syscall
			li $v0, 1
			add $a0, $s0, $zero	#Output value of funct
			syscall
			
			li $v0, 4	#Set to output string
			la $a0, newLine
			syscall		#output new line
			
			addi $t0, $t0, 2	#add one to get passed newline char
			j mainLoop	#jump to start of loop
			
			
		rLoopDone:
			#Now we need to check if it is an I-Type
			li $t3, 0	#set j = 0
			la $t4, iTypes	#load ITypes array into t4
			iCheckLoop:
				beq $t3, 92, iLoopDone	#if we are at the end of array, exit loop
				add $t6, $t4, $t3	#combine to elements of address
				lw $t6, 0($t6)	#get item in array
				beq $s0, $t6, isIType	#if read opcode matches item in array, it's an R-type
				addi $t3, $t3, 4	#j+=4
				j iCheckLoop		#restart loop
				
			isIType:
				# It's an I-Type instruction, now find components of it
				li $v0, 4
				la $a0, iType
				syscall		#Say that it is an I-Type
				
				li $v0, 1		#Output opcode portion
				add $a0, $s0, $zero
				syscall
				
				#Find rs portion (5)
				li $a0, 5	#set parameter to length of section we want
				jal readBits	#get the part of machine code
				add $s0, $v0, $zero	#save returned value into $s0
				li $v0, 4
				la $a0, rs		#output correct label
				syscall
				li $v0, 1
				add $a0, $s0, $zero	#Output value of rs
				syscall
				
				#Find rt portion (5)
				li $a0, 5	#set parameter to length of section we want
				jal readBits	#get the part of machine code
				add $s0, $v0, $zero	#save returned value into $s0
				li $v0, 4
				la $a0, rt		#output correct label
				syscall
				li $v0, 1
				add $a0, $s0, $zero	#Output value of rt
				syscall
				
				#find Immed portion (16)
				li $a0, 16	#set parameter to length of section we want
				jal readBits	#get the part of machine code
				add $s0, $v0, $zero	#save returned value into $s0
				li $v0, 4
				la $a0, immed		#output correct label
				syscall
				li $v0, 1
				add $a0, $s0, $zero	#Output value of immed
				syscall
				
				li $v0, 4	#Set to output string
				la $a0, newLine
				syscall		#output new line
				
				addi $t0, $t0, 2	#add one to get passed newline char
				j mainLoop	#jump to start of loop
				
			iLoopDone:
				#Now we need to check if it's a J-Type
				li $t3, 0	#set j = 0
				la $t4, jTypes	#load jTypes array into t4
				jCheckLoop:
					beq $t3, 8, jLoopDone	#if we are at the end of array, exit loop
					add $t6, $t4, $t3	#combine to elements of address
					lw $t6, 0($t6)	#get item in array
					beq $s0, $t6, isJType	#if read opcode matches item in array, it's an R-type
					addi $t3, $t3, 4	#j+=4
					j jCheckLoop		#restart loop
				
				isJType:
					# It's an J-Type instruction, now find components of it
					li $v0, 4
					la $a0, jType
					syscall		#Say that it is a J-Type
					
					li $v0, 1		#Output opcode portion
					add $a0, $s0, $zero
					syscall
					
					#Find address portion (26)
					li $a0, 26	#set parameter to length of section we want
					jal readBits	#get the part of machine code
					add $s0, $v0, $zero	#save returned value into $s0
					li $v0, 4
					la $a0, address		#output correct label
					syscall
					li $v0, 1
					add $a0, $s0, $zero	#Output value of address
					syscall
					
					li $v0, 4	#Set to output string
					la $a0, newLine
					syscall		#output new line
					
					addi $t0, $t0, 2	#add one to get passed newline char
					j mainLoop	#jump to start of loop
					
			jLoopDone:
				#It is neither of the 3 types
				li $v0, 4	#Set to output string
				la $a0, error
				syscall		#output error message
				addi $t0, $t0, 28	#add 26 to get to end of line, then 1 more to get passed newline character*************************************************************************
				j mainLoop	#jump to start of loop

exitFileLoop:
	li $v0, 4	#set to output string
	la $a0, exitMessage
	syscall
	
	li $v0,17	#set syscall to exit program
	syscall		#exit program			
		
		
	readBits:	#Function to read bits
		add $t5, $a0, $zero 	#set t5 to parameter
		li $t1, 2
		li $t7 , 0		#j = 0
		li $s0, 0	# Set return value to 0
		li $s2, '0'	# load ascii value of '0'
		readBitsLoop:
			beq $t7, $t5, endReadBitsLoop	#If we are past our length's iteration, we have rs
			lb $t2, fileInputBuffer($t0)	#Load in byte in file
			addi $t0, $t0, 1	# i++
			addi $t7, $t7, 1	# j++
			mult $s0, $t1		#multiply return value and base
			mflo $t3		#set result to t5
			sub $t4, $t2, $s2	#subtract fileInputBuffer[i] and '0'
			add $s0, $t3,$t4	#Add those 2 together
		
			
			j readBitsLoop		#Jump to start of loop
			endReadBitsLoop:
				add $v0, $s0, $zero	#move return value to return register
				jr $ra	#go back to where we were
			
		
		
		
	
