@Pseudocódigo de serie de fibonacci

#borrar;
escribir_cadena('Ingrese un numero: ');
leer(dato);

a:= 1;
b:= 1;
i:=1;

Mientras (i<dato) hacer
escribir(a);
c:= a+b;
a:=b;
b:=c;
i:=i+1;
fin_mIENtras;

escribir_cadena('El resultado es: ');
escribir(a);
