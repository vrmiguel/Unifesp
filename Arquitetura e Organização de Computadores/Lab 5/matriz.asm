.data 
	# Strings para saída.
	textoEntrada: .asciiz "Digite a dimensão da matriz quadrada: "
	textoMatriz1: .asciiz  "\nDigite os elemntos da Matriz A\n"
	textoMatriz2: .asciiz  "\Digite os elementos da Matriz B\n"
	textoResultado: .asciiz  "\nResultado: \n"
	espaco:	.asciiz  " "
	enter:	.asciiz  "\n"
	.align 4
	 matrizRes: .space 512  #Espaço na memória para matriz resultado.
	.align 4
	 matriz1: .space 512  #Espaço na memória para matriz 1.
	 .align 4
	 matriz2: .space 512  #Espaço na memória para matriz 2.
	 
.text
	j Main #pula para Main para dar início ao procedimento da multiplicação
	
Input:	
	addi $v0, $0, 4 #Configura-se o argumento do syscall para exibição de string
	la $a0, textoEntrada #Manda a string de entrada para ser exibida
	syscall #Executa o syscall e exibe string
	addi $v0, ,$0, 5 #Configura-se o argumento do syscall para leitura de inteiro (isto é, o valor n tal que a matriz será de dimensão n x n)
	syscall #Executa o syscall e lê o valor n
	move $t0, $v0 #Move n lido para t0
	
	la $s0, matriz1 #registrador pra matriz1 
	la $s1, matriz2 #registrador pra matriz2
	mul $t1, $t0, $t0 #t1 guardará o número de valores presentes na matriz, isto é, n x n	
	li $v0, 4 #Configura-se o argumento do syscall para exibição de string
	la $a0, textoMatriz1 #Manda a string de entrada para a matriz1 para ser exibida
	syscall #Executa o syscall e exibe string
	li $t3, 0 #Inicializa t3 com 0
	
	leituraMatriz1:	
		li $v0, 5 #Configura-se o argumento do syscall para leitura de inteiro
		syscall  #Executa o syscall e lê o inteiro
		move $t2, $v0 #Move o inteiro lido para t2
	
		sw $t2, 0($s0) #Passa o valor lido para ao registrador da  matriz1
		addi $s0, $s0, 4 #Adiciona 4 bits ao registrador da matriz1
		addi $t3, $t3, 1 #Faz t3 <- t3+1
		
		blt $t3, $t1, leituraMatriz1 # Reinicia o loop caso t3 seja menor que t1.
	
	li $v0, 4 #Configura-se o argumento do syscall para exibição de string
	la $a0, textoMatriz2 #Manda a string de entrada para ser exibida
	syscall #Executa o syscall e exibe string
	li $t3, 0 #Reseta t3 para 0
	
	leituraMatriz2:	
		li $v0, 5  #Configura-se o argumento do syscall para leitura de inteiro
		syscall #Executa o syscall e lê o inteiro
		move $t2, $v0 #Move o inteiro lido para t2
	
		sw $t2, 0($s1)  #Passa o valor lido para ao registrador da  matriz2
		addi $s1, $s1, 4 #Adiciona 4 bits ao registrador da matriz1
		addi $t3, $t3, 1 #Faz t3 <- t3+1
		
	        blt $t3, $t1, leituraMatriz2 # Reinicia o loop caso t3 seja menor que t1.
	
	jr $ra # 
		
matrizMultiplica:
	
	la $s2, matrizRes #registrador pra matrizResultado 
	
	mul $t9, $t0, 4 #t9 recebe o número de bytes na linha da matriz
	
	la $s0, matriz1 # registrador para matriz1
	addi $t3, $0, 0 # Inicializa t3 com 0
	
	lacoAuxiliar1:
		la $s1, matriz2 #registrador para matriz2
		li $t4, 0 # inicializa t4 com 0
		
		loop4:
			li $s4, 0 #inicializa-se s4, que armazenará o resultado na matriz final
			move $s5, $s0 #inicializa-se s5 
			move $s6, $s1
			li $t5, 0
			
			loop5: # laço de produto escalar (linha x coluna )
				lw $t6, ($s5)
				lw $t7, ($s6)
				mul $t8, $t6, $t7	
				add $s4, $s4, $t8
				add $s5, $s5, 4		
				add $s6, $s6, $t9	
				
				addi $t5, $t5, 1 #t5 <- t5+1
				blt $t5, $t0, loop5
			
			# Armazena o valor na matriz final na respectiva posição
			sw $s4, 0($s2) 
			addi $s2, $s2, 4
			addi $s1, $s1, 4
			addi $t4, $t4, 1
			blt $t4, $t0, loop4
			
		add $s0, $s0, $t9
		addi $t3, $t3, 1
		blt $t3, $t0, lacoAuxiliar1
			
	jr $ra #retorna fluxo de execução

Output:
	li $v0, 4 #Configura-se o argumento do syscall para exibição de string
	la $a0, textoResultado #transfere a string para o argumento do syscall
	syscall #exibe o valor de textoResultado
	la $s2, matrizRes #registrador pra matriz de resultado
	mul $t5, $t0, $t0 #t5 <- t0²
	
	li $t4, 1
	
	loop6:	
		lw $t8, 0($s2) #Carrega em t0 o valor de s2
		move $a0, $t8 #Move os conteudos de t8 para a0 (argumento do syscall)
		li $v0, 1 #Configura-se o argumento do syscall para exibição de inteiro
		syscall #Exibe o valor de t8
		
		li $v0, 4 #Configura-se o argumento do syscall para exibição de string
		la $a0, espaco ##Configura o syscall para exibir um espaço
		syscall #Exibe enter

		div $t4, $t0 
		mfhi $t6 #Envia para t6 o resultado da divisão acima
		bne $t6, 0, aux 
		li $v0, 4 #Configura-se o argumento do syscall para exibição de string
		la $a0, enter #Configura o syscall para exibir um enter
		syscall #Exibe enter

		aux:
		
		addi $s2, $s2, 4 
		addi $t4, $t4, 1
	        ble $t4, $t5, loop6
				
	jr $ra
	
Main:
	jal Input
	jal matrizMultiplica
	jal Output

		
