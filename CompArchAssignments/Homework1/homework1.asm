# homework1.asm
# Ryan Hosford - rph160030
# Displays Name monthOfBirth/DayOfBirth

# Main procedure
# Ryan Hosford - rph160030
# Displays Ryan Hosford 02/07
# No args. Output only

.data
	month: .word 2			# Define the month of birthday
	day: .word 7			# Define the day of birthday
	zero: .asciiz "0"		#Define string '0' so I can format correctly
	name: .asciiz "Ryan Hosford "	# Define my name
	slash: .asciiz "/"		# Define '/' character	
.text
	la $a0, name	# Load name into syscall register
	li $v0, 4	#Set syscall to output string
	syscall		#Print name
	la $a0, zero	# Load zero into syscall print
	li $v0, 4	#Set syscall to output string
	syscall		#Output zero
	la $t1,month 	# Load address of month
	lw $a0,0($t1)	# Load month into syscall print
	li $v0, 1	#Set syscall to output integer
	syscall		#Output month
	la $a0, slash	# load slash string into syscall register
	li $v0, 4	#Set syscall to output string
	syscall		#Output slash
	la $a0, zero	#Load zero into syscall print
	li $v0, 4	#Set syscall to output string
	syscall		#Output '0'
	la $t2, day	#Load address of day
	lw $a0 0($t2)	#Load day into syscall register
	li $v0, 1	# Set syscall to output integer
	syscall		#Output '0'
	li $v0, 10	#Set syscall to exit
	syscall		#exit program
	
