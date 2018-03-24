#project.asm
# Ryan Hosford - rph160030
# Takes filename from user and reads machine code and converts it back into MIPS assembly langauge

.data 
	inputPrompt: .asciiz "What file contains your machine code?\n"
	error: .asciiz "Error. Instruction not found.\n"
	exitMessage: .asciiz "End of Program.\n"
	labelDisplay: .asciiz "Label: "
	openParen: .asciiz "("
	closeParen: .asciiz ")"
	comma: .asciiz ","
	
	newLine: .asciiz "\n"
	userInputBuffer: .space 100	#Max 100 chars for input filename
	fileInputBuffer: .space 1000000	#1000000 bytes of space for the file input
	
	
	rTypes: .word 0,17	#array of opcodes that correspond to rTypes
	iTypes: .word 4,5,6,7,8,9,10,11,12,13,14,15,32,33,34,35,36,37,38,40,41,42,43,46,47,48,49,50,51,53,54,56,57,58,61,62 # iType opcodes
	jTypes: .word 2,3	#J-Type Opcodes
	
	registers: .asciiz "$zero  ","$at    ","$v0    ","$v1    ","$a0    ","$a1    ","$a2    ","$a3    ","$t0    ","$t1    ","$t2    ",
	"$t3    ","$t4    ","$t5    ","$t6    ","$t7    ","$s0    ","$s1    ","$s2    ","$s3    ","$s4    ","$s5    ",
	"$s6    ","$s7    ","$t8    ","$t9    ","$k0    ","$k1    ","$gp    ","$sp    ","$fp    ","$ra    "
	
	rInstructionsNormal: .asciiz "sli    ","ERROR  ","srl    " ,"sra    ","sllv   ","ERROR  ","srlv   ","srav   ","jr     ","jalr   ","movz   ","movn   ","syscall","break  ","ERROR  ","sync   ","mfhi   ","mthi   ","mflo   ","mtlo   ","ERROR  ","ERROR  ","ERROR  ","ERROR  ",
	"mult   ","multu  ","div    ","divu   ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","add    ","addu   ","sub    ","subu   ",
	"and    ","or     ","xor    ","nor    ","ERROR  ","ERROR  ","slt    ","sltu   ","ERROR  ","ERROR  ","ERROR  ","ERROR  ",
	"tge    ","tgeu   ","tlt    ","tltu   ","teq    ","ERROR  ","tne    ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  "
	
	
	##### FLOATING POINT INSTRUCTIONS ARE 9 SPACES TOTAL LONG. IN WRITING ARRAY, ACTUAL SPACES WILL BE 8*********************************************************************************************************************
	rInstructionsFp: .asciiz "add.f   ","sub.f   ","mul.f   ","div.f   ","sqrt.f  ","abs.f   ","mov.f   ","neg.f   ","ERROR   ",
	,"ERROR   ","ERROR   ","ERROR   ","round.wf","trunc.wf","ceil.wf ","floor.wf","ERROR   ","ERROR   ","movz.f  ","movn.f  "
	,"ERROR   ","ERROR   ","ERROR   ","ERROR   ","ERROR   ","ERROR   ","ERROR   ","ERROR   ","ERROR   ","ERROR   ","ERROR   "
	,"ERROR   ","cvt.s.f ","cvt.d.f ","ERROR   ","ERROR   ","cvt.w.f ","ERROR   ","ERROR   ","ERROR   ","ERROR   ","ERROR   "
	,"ERROR   ","ERROR   ","ERROR   ","ERROR   ","ERROR   ","ERROR   ","c.f.f   ","c.un.f  ","c.eq.f  ","c.ueq.f ","c.olt.f ","c.ult.f ","c.ole.f ",
	"c.ule.f ","c.sf.f  ","c.ngle.f","c.sqe.f ","c.ngl.f ","c.lt.f  ","c.nge.f ","c.le.f  ","c.ngt.f "
	
	iInstructions: .asciiz "ERROR  ","ERROR  ","ERROR  ","ERROR  ","beq    ","bne    ","blez   ","bgtz   ","addi   ","addiu  ","slti   ","sltiu  ","andi   ","ori    ","xori   ","lui    "
	,"ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  "
	,"ERROR  ","ERROR  ","ERROR  ","lb     ","lh     ","lwl    ","lw     ","lbu    ","lhu    ","lwr    ","ERROR  ",
	"sb     ","sh     ","swl    ","sw     ","ERROR  ","ERROR  ","swr    ","cache  ","li     ","lwc1   ","lwc2   ","pref   "
	,"ERROR  ","ldc1   ","ldc2   ","ERROR  ","sc     ","swc1   ","swc2   ","ERROR  ","ERROR  ","sdc1   ","sdc2   ","ERROR  "
	
	jInstructions: .asciiz "ERROR  ","ERROR  ","j      ","jal    ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  "
	,"ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  "
	,"ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  "
	,"ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  ","ERROR  "
	
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
	li $s7, '0'	# load ascii value of '0'
	
	
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
		sub $t4, $t2, $s7	#subtract fileInputBuffer[i] and '0'
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
			
			#Will find all components, then output. OpCode in s1, rs in s2, and so on...
			add $s1,$s0,$zero	#move opcode into s1 (s0 is modified)
			
			#Find rs portion (5 bits)
			li $a0, 5	#set parameter to length of section we want
			jal readBits	#get the part of machine code
			add $s2, $v0, $zero	#save returned value into $s2	
			
			#Find rt portion (5)
			li $a0, 5	#set parameter to length of section we want
			jal readBits	#get the part of machine code
			add $s3, $v0, $zero	#save returned value into $s3
		
			#find rd Portion (5)
			li $a0, 5	#set parameter to length of section we want
			jal readBits	#get the part of machine code
			add $s4, $v0, $zero	#save returned value into $s4
			
			#find shamt portion (5)
			li $a0, 5	#set parameter to length of section we want
			jal readBits	#get the part of machine code
			add $s5, $v0, $zero	#save returned value into $s5
			
			
			#find funct portion (6)
			li $a0, 6	#set parameter to length of section we want
			jal readBits	#get the part of machine code
			add $s6, $v0, $zero	#save returned value into $s6
			
			#Now output correct instruction

			
			beq $s1,0,normalRType	#If opcode = 0, normal R type
			beq $s1,17,FPRType	#if opcode = 17, FP R type
			
			normalRType:
				li $v0, 4	#set syscall to output string
				li $t8, 8	#Offset for table of instructions
				mult $s6, $t8	#multiply funct value by 8 for offset
				mflo $t9	#move result into $t9
				la $a0,rInstructionsNormal($t9)	#load correct instruction into syscall
				syscall
				j RTypeOpcodeDone	#bypass FP handling
			
			FPRType:
				li $v0, 4	#set syscall to output string
				li $t8, 9	#Offset for table of instructions
				mult $s6, $t8	#multiply funct value by 9 for offset
				mflo $t9	#move result into $t9
				la $a0,rInstructionsFp($t9)	#load correct instruction into syscall
				syscall
				j RTypeOpcodeDone	
			
			
			RTypeOpcodeDone:
			
			#Now we need to print the registers
			#rd
			li $v0, 4 	#syscall output string
			li $t8, 8	#Offset for registers
			mult $s4, $t8		#multiply rd value and offset
			mflo $t9 	#move result into $t9
			la $a0, registers($t9)	#load correct register name
			syscall	#output
			
			
			li $v0, 4	#set syscall to output string
			la $a0, comma 
			syscall	#output comma
			
			#rs
			mult $s2, $t8		#multiply rs value and offset
			mflo $t9 	#move result into $t9
			la $a0, registers($t9)	#load correct register name
			syscall	#output
			
			li $v0, 4	#set syscall to output string
			la $a0, comma 
			syscall	#output comma
			
			#rt
			mult $s3, $t8		#multiply rt value and offset
			mflo $t9 	#move result into $t9
			la $a0, registers($t9)	#load correct register name
			syscall	#output
			
			
			li $v0, 4	#Set to output string
			la $a0, newLine
			syscall		#output new line
			
			addi $t0, $t0, 2	#add 2 to get passed newline char
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
				add $s1,$s0,$zero	#move opcode into s1 (s0 is modified)
				
				#Find rs portion (5)
				li $a0, 5	#set parameter to length of section we want
				jal readBits	#get the part of machine code
				add $s2, $v0, $zero	#save returned value into $s2
				
				#Find rt portion (5)
				li $a0, 5	#set parameter to length of section we want
				jal readBits	#get the part of machine code
				add $s3, $v0, $zero	#save returned value into $s3
				
				
				#find Immed portion (16)
				li $a0, 16	#set parameter to length of section we want
				jal readBits	#get the part of machine code
				add $s4, $v0, $zero	#save returned value into $s4
	
				
				bge $s4, 32768, negativeImmed	#if the immed value is greater than or equal to the equivalent of a 1 in the 16th location,that should be the sign bit.
				j notNegative	#if it isn't negative, skip the part handling negative immed values
				
				negativeImmed:
					sub $s4,$s4,32768	#if it's negative, subtract the value of a 1 in the 16th bit
					mul $s4,$s4,-1		#make the number negative
				
				notNegative:
				
				#Now output Instruction using opcode
				li $v0, 4	#set syscall to output string
				li $t8, 8	#Offset for table of instructions
				mult $s1, $t8	#multiply funct value by 8 for offset
				mflo $t9	#move result into $t9
				la $a0,iInstructions($t9)	#load correct instruction into syscall
				syscall
				
				#output registers
				
				#Check if it is a lw. If it is, we need a different output
				beq $s1,35,itsLW
				
				#rt
				mult $s3, $t8		#multiply rt value and offset
				mflo $t9 	#move result into $t9
				la $a0, registers($t9)	#load correct register name
				syscall	#output
				
				li $v0, 4	#set syscall to output string
				la $a0, comma 
				syscall	#output comma
				
				#rs
				mult $s2, $t8		#multiply rs value and offset
				mflo $t9 	#move result into $t9
				la $a0, registers($t9)	#load correct register name
				syscall	#output
				
				
				li $v0, 4	#set syscall to output string
				la $a0, comma 
				syscall	#output comma
				
				#output immed value
				li $v0, 1	#set syscall to output integer
				add $a0, $s4, $zero
				syscall		#output immed value
				
				j doneWithLW	#Skip portion handling LW
				itsLW:
					#Output rt
					mult $s3, $t8		#multiply rt value and offset
					mflo $t9 	#move result into $t9
					la $a0, registers($t9)	#load correct register name
					syscall	#output
					
					
					li $v0, 4	#set syscall to output string
					la $a0, comma 
					syscall	#output comma
					
					#output immed value
					li $v0, 1	#set syscall to output integer
					add $a0, $s4, $zero
					syscall
					
					#output openParen
					li $v0, 4	#set syscall to output string
					la $a0, openParen	
					syscall	#output "("
					
					#rs
					mult $s2, $t8		#multiply rs value and offset
					mflo $t9 	#move result into $t9
					la $a0, registers($t9)	#load correct register name
					syscall	#output
					
					#output closeParen
					la $a0, closeParen	#set to ouput ")"
					syscall
					
					
					
				doneWithLW:
				
				
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
		
					add $s1,$s0,$zero	#move opcode into s1 (s0 is modified)
					
					#Find address portion (26)
					li $a0, 26	#set parameter to length of section we want
					jal readBits	#get the part of machine code
					add $s2, $v0, $zero	#save returned value into $s1
					
					
					#now output instruction
					li $v0, 4	#set syscall to output string
					li $t8, 8	#Offset for table of instructions
					mult $s1, $t8	#multiply opcode value by 8 for offset
					mflo $t9	#move result into $t9
					la $a0,jInstructions($t9)	#load correct instruction into syscall
					syscall
				
					#output label
					la $a0, labelDisplay	#load address label
					syscall			#display
					li $v0, 1	#set to output integer
					add $a0, $s2, $zero	#set output to address
					syscall		#display
					
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
		li $t1, 2		#base value (2)
		li $t7 , 0		#j = 0
		li $s0, 0	# Set return value to 0
		li $s7, '0'	# load ascii value of '0'
		readBitsLoop:
			beq $t7, $t5, endReadBitsLoop	#If we are past our length's iteration, we have rs
			lb $t2, fileInputBuffer($t0)	#Load in byte in file
			addi $t0, $t0, 1	# i++
			addi $t7, $t7, 1	# j++
			mult $s0, $t1		#multiply return value and base
			mflo $t3		#set result to t5
			sub $t4, $t2, $s7	#subtract fileInputBuffer[i] and '0'
			add $s0, $t3,$t4	#Add those 2 together

			j readBitsLoop		#Jump to start of loop
			endReadBitsLoop:
				add $v0, $s0, $zero	#move return value to return register
				jr $ra	#go back to where we were
			
		
		
		
	
