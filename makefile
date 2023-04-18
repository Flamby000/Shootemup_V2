#Constantes :
SP=src/
HD=include/
BLD=bin/
CC=gcc
CFLAGS=-Wall -ansi -pedantic -pthread
OBJ=${BLD}main.o ${BLD}frame.o ${BLD}game.o ${BLD}animation.o ${BLD}entity.o ${BLD}background.o
LDFLAGS=-lMLV -lm 
OUT=shootemup


#Règle pour compiler le programme :
all: ${OBJ}
	${CC} -o ${OUT} ${OBJ} ${CFLAGS} ${LDFLAGS} 

#Règles de dépendances des fichiers sources :
${BLD}main.o: ${SP}main.c ${SP}frame.c 
	${CC} -c ${SP}main.c -o ${BLD}main.o ${CFLAGS} ${LDFLAGS}

${BLD}game.o: ${SP}game.c ${SP}entity.c ${SP}background.c  
	${CC} -c ${SP}game.c -o ${BLD}game.o ${CFLAGS} ${LDFLAGS}

${BLD}frame.o: ${SP}frame.c ${SP}game.c 
	${CC} -c ${SP}frame.c -o ${BLD}frame.o ${CFLAGS} ${LDFLAGS}

${BLD}entity.o: ${SP}entity.c ${SP}animation.c 
	${CC} -c ${SP}entity.c -o ${BLD}entity.o ${CFLAGS} ${LDFLAGS}

${BLD}animation.o: ${SP}animation.c ${SP}entity.c 
	${CC} -c ${SP}animation.c -o ${BLD}animation.o ${CFLAGS} ${LDFLAGS}

${BLD}background.o: ${SP}background.c ${SP}entity.c ${SP}game.c
	${CC} -c ${SP}background.c -o ${BLD}background.o ${CFLAGS} ${LDFLAGS}



#Règle pour effacer les fichiers compilés
clean :
	rm -f ${BLD}*
	rm -f ${OUT}

#Règle pour lancer le programme
run : ${OBJ}
	${CC} -o ${OUT} ${OBJ} ${CFLAGS} ${LDFLAGS}
	./${OUT}

memcheck : ${OBJ}
	${CC} -o ${OUT} ${OBJ} ${CFLAGS} ${LDFLAGS}
	valgrind ./${OUT}

# rule to generate documentation with doxygen
doc:
	doxygen Doxyfile