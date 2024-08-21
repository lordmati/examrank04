1 º PONER LIBRERIAS  
2 º HACEMOS EL MAIN  
```c
	int fd[2];  
	int i;  
	int tmp_fd;  
	casteamos a void el argc;  
	y hacemos un dup tmp_fd = dup(0);  
 ```
3 º ITERAMOS argv[i] && argv[i + 1]
4 º MOVEMOS ARGV UNO PARA DELANTE Y PONEMOS i a 0
5 º ITERAMOS HASTA LLEGAR A PIPE NULO O PUNTO Y COMA
6 º REVISAMOS QUE LA POSICION 0 DEL ARGV SEA EL CD
	6.1 º SI i ES DISTINTO QUE 2 mostramos mensaje de error: "cd: error: bad arguments"
	6.2 º SI NO COMPROBAMOS CON EL CHDIR DEL ARGV 1 SEA DISTINTO QUE 0 SI ES IGUAL A 0 mostramos mensaje de error "cd: error: cannot change directory to " y le pasamos el argv[1];
7 º SI NO ES EL CD REVISAMOS QUE i sea distinto que 0 y COMPROBAMOS QUE ARGV[i] sea NULLO O argv[i] sea ";"
	7.1 º HACEMOS UN FORK con un if y ejecutamos
		en el hijo cerramos el tmp_fd hacemos un bucle con el 
		waitpid(-1,NULL, WUNTRACED) != -1
		y hacemos un dup al tmp_fd;
8 º SI NO ES CUMPLEN LAS CONDICIONES DEL PASO 6º Y EL PASO 7º REVISAMOS QUE i sea distinto que 0 y comprobamos que argv[i] sea "|"
	8.1 º HACEMOS EL PIPE DEL fd y hacemos el fork
	8.2 º en el hijo hacemos un dup2 del fd[1] a la salida
		cerramos ambos fd
		y ejecutamos
	8.3 º en el padre cerramos el fd[1],
		y el tmp_fd lo igualamos al fd[0]
9 º POR ULTIMO AFUERA DEL BUCLE PRINCIPAL CERRAMOS EL tmp_fd.

guia para el ejecutor

1 º PONEMOS el argv[i] a NULL
2 º HACEMOS UN dup2 del tmp_fd a 0
3 º CERRAMOS EL tmp_fd
4 º llamamos al execve
5 º imprimimos por pantalla "error: cannot execute ", argv[0]
6 º salimos.
