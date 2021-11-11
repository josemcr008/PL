<<
  Asignatura:    Procesadores de Lenguajes

  Titulaci�n:    Ingenier�a Inform�tica
  Especialidad:  Computaci�n
  Curso:         Tercero
  Cuatrimestre:  Segundo

  Departamento:  Inform�tica y An�lisis Num�rico
  Centro:        Escuela Polit�cnica Superior de C�rdoba
  Universidad de C�rdoba
 
  Curso acad�mico: 2020 - 2021

  Fichero de ejemplo para el int�rprete de pseudoc�digo en espa�ol: ipe.exe
>>

@ Bienvenida

#borrar;

#lugar(10,10);

escribir_cadena('Introduce tu nombre --> ');

leer_cadena(nombre);

#borrar;
#lugar(10,10);

escribir_cadena(' Bienvenido/a << ');

escribir_cadena(nombre);

escribir_cadena(' >> al int�rprete de pseudoc�digo en espa�ol:\'ipe.exe\'.');

#lugar(40,10);
escribir_cadena('Pulsa una tecla para continuar');
leer_cadena( pausa);


repetir 

 @ Opciones disponibles

 #borrar;

 #lugar(10,10);
 escribir_cadena(' Factorial de un n�mero --> 1 ');

 #lugar(11,10);
 escribir_cadena(' M�ximo com�n divisor ----> 2 ');

 #lugar(12,10);
 escribir_cadena(' Finalizar ---------------> 0 ');

 #lugar(15,10);
 escribir_cadena(' Elige una opcion ');

 leer(opcion);

 #borrar;

 @ Fin del programa
 si (opcion = 0)       		
    entonces  
        #lugar(10,10);
        escribir_cadena(nombre);
        escribir_cadena(': gracias por usar el int�rprete ipe.exe ');

 @ Factorial de un n�mero
 si_no 					
	si (opcion = 1)
   	    entonces
			#lugar(10,10);
			escribir_cadena(' Factorial de un numero  ');

             #lugar(11,10);
			escribir_cadena(' Introduce un numero entero ');
			leer(N);

        	factorial := 1;

       		para i desde 2 hasta N paso 1 hacer
	            factorial := factorial * i;
        	fin_para;

        	@ Resultado
	        #lugar(15,10);
			escribir_cadena(' El factorial de ');
			escribir(N);
			escribir_cadena(' es ');
			escribir(factorial);
    
   	@ M�ximo com�n divisor
	si_no 
		si (opcion = 2)
			entonces
				#lugar(10,10);
				escribir_cadena(' M�ximo com�n divisor de dos n�meros ');

				#lugar(11,10);
                		escribir_cadena(' Algoritmo de Euclides ');

                		#lugar(12,10);
                		escribir_cadena(' Escribe el primer n�mero ');
                		leer(a);

                  		#lugar(13,10);
                  		escribir_cadena(' Escribe el segundo n�mero ');
                  		leer(b);

                  		@ Se ordenan los n�meros

				si (a<b) entonces
					escribir_cadena('a menor que b\n');
					auxiliar := a;
					a := b;
					b := auxiliar;
				
				fin_si;
					@ Se guardan los valores originales
					A1 := a;
					B1 := b;

					@ Se aplica el m�todo de Euclides	
					resto  := a #mod b;
					escribir_cadena('hola\n'); 
					
					mientras (resto <> 0) hacer
						a :=  b;
						b := resto;
						resto := a #mod b;
					fin_mientras;
         
					@ Se muestra el resultado
					#lugar(15,10);
					escribir_cadena(' M�ximo com�n divisor de ');
					escribir(A1);
					escribir_cadena(' y ');
					escribir(B1);
					escribir_cadena(' es ---> ');
					escribir(b);

			@ Resto de opciones
 			si_no  
				#lugar(15,10);
			    	escribir_cadena(' Opcion incorrecta ');

 			fin_si;   
  	fin_si;                 

  fin_si;                          

 #lugar(40,10); 
 escribir_cadena('\n Pulse una tecla para continuar --> ');
 leer_cadena(pausa);
 
hasta (opcion = 0);             

@ Despedida final

#borrar;
#lugar(10,10);
escribir_cadena('El programa ha concluido');
