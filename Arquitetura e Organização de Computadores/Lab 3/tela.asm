# CONFIGURAÇÕES NECESSAŔIAS PARA O DISPLAY:
# Unit Width in Pixels: 2, Unit Height in Pixels: 2, Display Width in Pixels: 512, Display Height in Pixels: 512, Base adress for display: 0x10040000 (heap)
# Além disso, o programa depende da utilização do MARS 4.5 com funcionalidades adicionadas por alunos da Unifesp

.data
	preto:		.word 0x000000 #código hexadecimal para a corl preta
	azul:		.word 0x008080 #código hexadecimal para a cor azul
	
.text
	li $t1, 448 # Carrega o offset horizontal inicial (128 pixels) em $t1 
	li $t2, 57344 # Carrega o offset vertical inicial (128 linhas) em $t2
	lui $t0, 0x1004 # O endereço t0 servirá para guardar o endereço base da tela
	lw $s0, preto # O endereço s0 representará a cor preta,
	lw $s1, azul #  enquanto que s1 representará a cor azul	
	move $s5, $t1 # O endereço s5 guardará o valor de offset horizontal anterior (t1)
	move $s6, $t2 # O endereço s6 guardará o valor de offset vertical anterior (t2)
	
main:
	jal telaClear
	jal telaAtualiza # Syscall de atualizar o bitmap. Somente presente no MARS modificado.
	jal desenha
	jal telaAtualiza # Syscall de atualizar o bitmap. Somente presente no MARS modificado.
	jal input
	j main

telaAtualiza:
	li $v0, 39
	syscall # Atualiza o bitmap. Somente presente no MARS modificado.
	jr $ra

telaClear:
	move $t3, $s5 # Atualização dos offsets como os antigos
	move $t4, $s6
	
	subi $t3, $t3, 32 # Início de Limpeza
	subi $t4, $t4, 8192 
	li $t5, 0
	li $t6, 0
telaClearLoop:
	beq $t6, 32, telaClearFim # Se já tivermos desenhado x linhas, saímos da rotina
	add $t7, $t3, $t4
	add $t7, $t7, $t0
	sw $s0, ($t7)
	addi $t3, $t3, 4 # Passamos pro próximo pixel...
	addi $t5, $t5, 1 # ...e incrementamos nosso contador de colunas
	beq $t5, 32, telaClearPuloDeLinha
	j telaClearLoop
telaClearPuloDeLinha:
	move $t3, $t1 # Reinicia o offset horizontal da função
	subi $t3, $t3, 32 # Mas, novamente, vamos 8 pixels a esquerda...
	addi $t4, $t4, 1024 # Passa para a próxima linha
	li $t5, 0 # Reinicia o contador de colunas
	addi $t6, $t6, 1 # E aumenta o contador de linhas
	j telaClearLoop
telaClearFim:
	li $t5, 0 # Reseta os contadores que serão usados por desenha
	li $t6, 0
	li $t7, 0 # Bem como o bichinho do endereço
	jr $ra

desenha:
	move $t3, $t1
	move $t4, $t2 
desenhaLoop:
	beq $t6, 16, desenhaFim 
	add $t7, $t3, $t4
	add $t7, $t7, $t0
	sw $s1, ($t7)
	addi $t3, $t3, 4
	addi $t5, $t5, 1
	beq $t5, 16, desenhaPulaLinha
	j desenhaLoop
desenhaPulaLinha:
	move $t3, $t1 
	addi $t4, $t4, 1024 
	li $t5, 0 
	addi $t6, $t6, 1
	j desenhaLoop
desenhaFim:
	jr $ra
		
input:
	li $v0, 12 
	syscall
	
	move $s5, $t1 
	move $s6, $t2
	
	beq $v0, 'W', inputSobe
	beq $v0, 'w', inputSobe 
	
	beq $v0, 'S', inputDesce 
	beq $v0, 's', inputDesce 
	
	beq $v0, 'A', inputEsquerda 
	beq $v0, 'a', inputEsquerda 
	
	beq $v0, 'D', inputDireita 
	beq $v0, 'd', inputDireita 
	
	j input
inputSobe:
	beq $t2, 0, inputFim 
	subi $t2, $t2, 1024
	j inputFim
inputDesce:
	beq $t2, 245760, inputFim 
	addi $t2, $t2, 1024
	j inputFim
inputEsquerda:
	beq $t1, 0, inputFim 
	subi $t1, $t1, 4
	j inputFim
inputDireita:
	beq $t1, 960, inputFim 
	addi $t1, $t1, 4
	j inputFim
inputFim:
	jr $ra
