#borrar;

escribir_cadena('Que tabla de multiplicar desea ver --> ');
leer(num);

si (num>=1 #y num<=10)
	entonces
	para x desde 0 hasta 10 hacer
		escribir_cadena('\n');
		escribir(x*num);

	fin_para;
si_no
	escribir_cadena('El numero debe estar entre 0 y 10\n');
fin_si;