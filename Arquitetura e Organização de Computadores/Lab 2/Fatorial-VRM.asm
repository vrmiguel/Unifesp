main:
	li $v0,5 #configura o syscall para leitura de inteiro
	syscall #usa a chamada do sistema para ler o inteiro
	la $s0,($v0) #salva o número lido em s0, que será utilizado para decidir a quantidade de vezes que o laço fact passará por
	la $s1,($v0) #salva o número lido em s1, que será utilizado para armanezar os valores iterativos do fatorial
	j fact #desvia para label fact
	
fact: 
	addi $s0,$s0,-1 #diminui s0 em 1
	beqz $s0, exit #desvia para label exit caso s0 == 0
	mult $s0,$s1 #multiplica s0 por s1
	mflo $s1 #como os primeiros 32 bits da multiplicação vão para o registrador LO, salva-se LO em s1
	j fact #retorna para o início do loop
	
exit:
	la $a0,($s1) #armazena o resultado do fatorial, s1, no argumento do syscall a0
	li $v0,1 # configura o syscall para exibição de inteiro
	syscall # usa a chamada do sistema para exibir o inteiro
	li $v0,10 #configura o syscall para finalização de execução
	syscall #usa a chamada do sistema para finalizar a execução