kinetic_energy=1
alpha=30

Grafica.pdf: magnetico.py trayectoria_E_alpha.dat
	python magnetico.py

trayectoria_E_alpha.dat: ./particle_in_field
	./particle_in_field $(kinetic_energy) $(alpha) > trayectoria_E_alpha.dat

./particle_in_field: magnetico.c
	cc magnetico.c -o particle_in_field -lm

