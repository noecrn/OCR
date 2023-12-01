# Makefile

all: global

solver:
	gcc -o interface interface.c `pkg-config --cflags --libs gtk+-3.0`
	



clean:
	${RM} ${OBJ}   # remove object files
	${RM} ${DEP}   # remove dependency files
	${RM} interface   # remove main program

global:
	${RM} ${OBJ}   # remove object files
	${RM} ${DEP}   # remove dependency files
	${RM} interface   # remove main program
	gcc -o interface interface.c `pkg-config --cflags --libs gtk+-3.0`
	




# END   