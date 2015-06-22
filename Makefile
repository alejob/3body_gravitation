objects= Part.o azar.o Vect6.o Cont.o

3cuerpos: $(objects)
	g++-4.4  $(objects) 3cuerpos.cc -o $@
	
$(objects):%.o:%.cc %.h
	g++-4.4 -c $< -o $@


	
