.data
	um: .double 1.0
.text
	# Método de Cálculo de Fatorial
	# s0: resposta do fatorial
	# t9: "argumento" da função
	# t0: 'i'
main:
	addi $t3, $0, 1
	l.d $f12, um #Resposta final do programa
	l.d $f2, um #Usado na soma dos termos da série
serie:
	# t3: Usado como variável de iteração
	# s0: Retorno do procedimento do calculo do fatorial
	bgt $t3, 9, saida
	jal fact #Calcula o fatorial de t9 e o retorna no registrador s0
	mtc1 $s0, $f6 #Converte s0 de int para float
	cvt.d.w $f6, $f6 #Converte o valor em f6 de 'word' para double
	div.d $f10, $f2, $f6
	add.d $f12, $f12, $f10
	addi $t3, $t3, 1
	j serie

fact:
	addi $s0, $0, 1 #Inicializa-se s0 com 1, servirá para guardar o resultado do cálculo do fatorial
	addi $t0, $0, 1 #inicializa-se t0 com 1, servirá como variável de iteração
	j factLoop
	
factLoop:
	bgt $t0, $t3, factSaida #Caso t0 for maior que t3, desvia-se para a label factSaida 
	mul $s0, $s0, $t0 # Multiplica-se s0 por t0 e se salva o resultado em s0
	addi $t0, $t0, 1 # t0 = t0 + 1
	j factLoop #Reinicia o loop
									
factSaida: # A label factSaida retorna a execução para aonde o label fact foi chamado.
	jr $ra 
	
saida:
	addi $v0, $0, 3 #Configura-se o argumento do syscall para exibição de double
	syscall #Chama-se o syscall para exibir o double localizado no registrador f12.
	
		
	
	
	
	
