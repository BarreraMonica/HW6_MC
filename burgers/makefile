burgers.gif : burgers.py salida.dat
	python burgers.py

salida.dat : a.out
	./a.out > salida.dat

a.out : burgers.c
	cc burgers.c -lm

clean:
	rm -f a.out burgers salida.dat burgers.gif 

