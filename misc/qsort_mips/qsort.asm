.data 
	newLine: .asciiz "\n"
	prompt1: .asciiz "Number of elements: "
	prompt2: .asciiz "Elements: "
.text
	main:
		#print prompt1
		la $a0, prompt1
		li $v0, 4
		syscall

		#read number of elements = n
		li $v0, 5
		syscall

		move $s1, $v0

		#print newLine
		la $a0, newLine
		li $v0, 4
		syscall

		#print prompt2
		la $a0, prompt2
		li $v0, 4
		syscall

		#copy n into a1
		move $a1, $s1

		jal readArrayElements
		move $s0, $v0 #pointer

		move $a0, $s0
		move $a1, $s1
		jal printArrayElements

		move $a0, $s0
		move $a2, $s1
		addiu $a2, -1
		li $a1, 0
		jal qsort

		#print newLine
		la $a0, newLine
		li $v0, 4
		syscall

		move $a0, $s0
		move $a1, $s1
		jal printArrayElements

		#return
		li $v0, 10
		syscall


	#read elements into array 
	#arguments: a1=size of array 
	#returns: v0=arrayPointer
	readArrayElements:
		#allocate size*4 space for elements on heap
		sll $a0, $a1, 0x2
		li $v0, 0x9
		syscall

		#save array pointer into a0
		move $a0, $v0

		#read elements into s0
		move $t0, $a0
		move $t1, $a1
		for0:
			blez $t1, for0_exit

			li $v0, 0x5
			syscall #read integer 

			sw $v0, 0x0($t0) 
			addiu $t0, 0x4
			addiu $t1, -0x1

			j for0
		for0_exit:

		#save array pointer in v0
		move $v0, $a0

		#return
		jr $ra


	#print elements of an array
	#arguments: a0=arrayPointer, a1=size
	printArrayElements:
		#iterate through the array
		move $t0, $a0
		for1:
			blez $a1, for1_exit

			lw $a0, 0($t0)
			li $v0, 1
			syscall #print element
			li $a0, 32
			li $v0, 11
			syscall #print space

			addiu $t0, 0x4
			addiu $a1, -0x1

			j for1
		for1_exit:

		#return
		jr $ra


	#quicksort an array in increasing order
	#arguments: a0=arrayPointer, a1=startIndex, a2=endIndex
	qsort:
		#save s0, s1, s2, s3 on stack
		addiu $sp, $sp, -0x14
		sw $s0, 0x0($sp)
		sw $s1, 0x4($sp)
		sw $s2, 0x8($sp)
		sw $s3, 0xC($sp)
		sw $ra, 0x10($sp)

		#save array pointer into s0
		move $s0, $a0

		#save startIndex into s1
		move $s1, $a1

		#save endIndex into s2
		move $s2, $a2

		#if statement
		qsortIf:
			subu $t0, $s2, $s1
			blez $t0, qsortIfExit

			jal partition
			lw $ra, 0x10($sp)

			move $s3, $v0 #save partitionIndex into s3

			move $a0, $s0
			move $a1, $s1
			addiu $a2, $s3, -0x1
			jal qsort
			lw $ra, 0x10($sp)

			move $a0, $s0
			addiu $a1, $s3, 0x1
			move $a2, $s2
			jal qsort
			
		qsortIfExit:

		#restore s0, s1, s2, s3
		lw $s0, 0x0($sp)
		lw $s1, 0x4($sp)
		lw $s2, 0x8($sp)
		lw $s3, 0xC($sp)
		lw $ra, 0x10($sp)
		addiu $sp, $sp, 0x14

		#return
		jr $ra


	#quicksort standard partition algorithm
	#arguments: a0=arrayPointer, a1=startIndex, a2=endIndex
	#returns: v0=partitionIndex
	partition:
		#save s0, s1, s2, s3, s4 on stack
		addiu $sp, $sp, -0x14
		sw $s0, 0x0($sp)
		sw $s1, 0x4($sp)
		sw $s2, 0x8($sp)
		sw $s3, 0xC($sp)
		sw $s4, 0x10($sp)	

		#save array pointer into s0
		move $s0, $a0

		#save startIndex into s1
		move $s1, $a1

		#save endIndex into s2
		move $s2, $a2

		#smallestIndex = startIndex - 1 = s1 - 1
		addiu $s3, $s1, -0x1

		#s4 is pivot (last element in the array)
		sll $t0, $s2, 0x2
		addu $t1, $s0, $t0
		lw $s4, 0x0($t1)

		#for(j=startIndex; j < endIndex; j++)
		for2:
			subu $t0, $s2, $s1
			blez $t0, for2_exit

			partitionIf:
				sll $t0, $s1, 2
				addu $t1, $s0, $t0
				lw $t0, 0x0($t1) #element of index j

				subu $t1, $s4, $t0
				bltz $t1, partitionIf_exit

				addiu $s3, $s3, 1

				#swap elements of index s1 and s3
				sll $t0, $s1, 2 #t0 equals bytes to fistr element
				sll $t1, $s3, 2 #t0 equals bytes to second element
				addu $t2, $s0, $t0 #t2 points to first element
				addu $t3, $s0, $t1 #t3 points to second element
				lw $a0, 0($t2) #a0 equals first element
				lw $a1, 0($t3) #a1 equals second element
				sw $a0, 0($t3) #t3 now holds first element
				sw $a1, 0($t2) #t2 now holds second element

			partitionIf_exit:

			addiu $s1, $s1, 1
			j for2
		for2_exit:

		#swap elements of index s3+1 and s2
		addiu $s3, $s3, 1
		sll $t0, $s3, 2 #t0 equals bytes to first element
		sll $t1, $s2, 2 #t0 equals bytes to second element
		addu $t2, $s0, $t0 #t2 points to first element
		addu $t3, $s0, $t1 #t3 points to second element
		lw $a0, 0($t2) #a0 equals first element
		lw $a1, 0($t3) #a1 equals second element
		sw $a0, 0($t3) #t3 now holds first element
		sw $a1, 0($t2) #t2 now holds second element

		#save partitionIndex into v0
		move $v0, $s3

		#restore s0, s1, s2, s3, s4
		lw $s0, 0x0($sp)
		lw $s1, 0x4($sp)
		lw $s2, 0x8($sp)
		lw $s3, 0xC($sp)
		lw $s4, 0x10($sp)	
		addiu $sp, $sp, 0x14

		#return
		jr $ra




