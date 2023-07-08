CMD=gcc -Wall

all :	model.o	ui.o	initialization.o	rule.o	simulation.o	main.o
	${CMD} *.o -o cocci-puce.exe

model.o :	model/coccinelle.c	model/coccinelle.h	model/direction.c	model/direction.h	model/potager.c	model/potager.h	model/puceron.c	model/puceron.h	model/tomato.c	model/tomato.h
	${CMD} -c model/coccinelle.c model/direction.c model/potager.c model/puceron.c model/tomato.c

ui.o :	ui/cui.c	ui/cui.h	ui/manager.c	ui/manager.h
	${CMD} -c ui/cui.c ui/manager.c

initialization.o :  initialization.c	initialization.h
	${CMD} -c initialization.c

rule.o : rule.c	rule.h
	${CMD} -c rule.c

simulation.o : simulation.c	simulation.h
	${CMD} -c simulation.c

main.o : main.c
	${CMD} -c main.c

launch:
	./cocci-puce.exe

clean :
	rm -f *.o *.exe