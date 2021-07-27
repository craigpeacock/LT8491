lt8491 : lt8491.o
	cc -o lt8491 main.o lt8491.o i2c.c
	
lt8491.o : main.c
	cc -c main.c lt8491.c i2c.c

clean :
	rm lt8491 lt8491.o
