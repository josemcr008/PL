#borrar;

escribir_cadena('Bienvenido\n');
opcion:= 10;

mientras (opcion <> 0) hacer

	escribir_cadena('1. Adivina el numero.\n');
	escribir_cadena('2. Calculo mental.\n');
	escribir_cadena('0. Salir.\n');

	escribir_cadena('A que desea jugar --> ');
	leer(opcion);

	casos(opcion)
	
	valor 0:
		escribir_cadena('¡Hasta luego!\n');
	valor 1: 
		#borrar;
		escribir_cadena('Tienes que adivinar el numero del 1 al 15 que voy a pensar...\n');
		escribir_cadena('Escribe un numero --> ');
		leer(num);
		
		mientras (num <> 4)
			hacer
				escribir_cadena('Incorrecto\n');
				si (num > 4) entonces
					escribir_cadena('El numero es inferior\n');
				si_no 
					escribir_cadena('El numero es superior\n');
				fin_si;
				leer(num);

				
		fin_mientras;
		escribir_cadena('¡Correcto!\n');
			
	valor 2:
		#borrar;
		escribir_cadena('Se pondrán una serie de operaciones y tendrás que acertarlas\n');
		escribir_cadena('Cada acierto sumara 2 puntos y cada fallo restará uno\n');	
		puntos:=0;

		escribir_cadena('11*11 = ');
		leer(res);
	
		si (res = 121) entonces
			puntos := puntos +2;
		
		si_no
			puntos := puntos -1;
		fin_si;

		escribir_cadena('125 - 15 = ');
		leer(res);
	
		si (res = 110) entonces
			puntos := puntos +2;
		
		si_no
			puntos := puntos -1;
		fin_si;


		escribir_cadena('12 * 3= ');
		leer(res);
	
		si (res = 36) entonces
			puntos := puntos +2;
		
		si_no
			puntos := puntos -1;
		fin_si;


		escribir_cadena('60/5 = ');
		leer(res);
	
		si (res = 12) entonces
			puntos := puntos +2;
		
		si_no
			puntos := puntos -1;
		fin_si;


		escribir_cadena('46+64 = ');
		leer(res);
	
		si (res = 110) entonces
			puntos := puntos +2;
		
		si_no
			puntos := puntos -1;
		fin_si;

		escribir_cadena('Has conseguido un total de ');
		escribir(puntos);
		escribir_cadena('puntos\n');

	defecto: 
		escribir_cadena('Escriba otro numero\n');
	fin_casos;
fin_mientras;