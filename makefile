#Constantes :
SP=src/
HD=include/
BLD=bin/
CC=gcc 
CFLAGS=-Wall -ansi -pedantic -pthread -Werror -lrt
OBJ=${BLD}main.o ${BLD}frame.o ${BLD}game.o ${BLD}animation.o ${BLD}entity.o ${BLD}background.o ${BLD}movement.o ${BLD}settings.o ${BLD}player.o ${BLD}ennemy.o ${BLD}spaceship.o ${BLD}missile.o ${BLD}shooter.o ${BLD}level.o ${BLD}bonus.o ${BLD}utils.o ${BLD}menu.o ${BLD}click_actions.o ${BLD}campaign_menu.o
LDFLAGS=-lMLV -lm 
OUT=shootemup

# -lm math, -lMLV pour la librairie graphique, -lrt pour clock_gettime

#Règle pour compiler le programme :
all: ${OBJ}
	${CC} -o ${OUT} ${OBJ} ${CFLAGS} ${LDFLAGS} 

#Règles de dépendances des fichiers sources :
${BLD}main.o: ${SP}main.c ${SP}interface/frame.c ${SP}settings.c ${SP}utils/utils.c
	${CC} -c ${SP}main.c -o ${BLD}main.o ${CFLAGS} ${LDFLAGS}

${BLD}game.o: ${SP}logic/game.c ${SP}logic/entity.c ${SP}utils/background.c ${SP}logic/player.c ${SP}logic/ennemy.c ${SP}logic/level.c ${SP}logic/bonus.c ${SP}interface/menu.c
	${CC} -c ${SP}logic/game.c -o ${BLD}game.o ${CFLAGS} ${LDFLAGS}

${BLD}frame.o: ${SP}interface/frame.c ${SP}logic/game.c 
	${CC} -c ${SP}interface/frame.c -o ${BLD}frame.o ${CFLAGS} ${LDFLAGS}

${BLD}entity.o: ${SP}logic/entity.c ${SP}interface/animation.c 
	${CC} -c ${SP}logic/entity.c -o ${BLD}entity.o ${CFLAGS} ${LDFLAGS}

${BLD}animation.o: ${SP}interface/animation.c ${SP}logic/entity.c ${SP}interface/menu.c
	${CC} -c ${SP}interface/animation.c -o ${BLD}animation.o ${CFLAGS} ${LDFLAGS}

${BLD}background.o: ${SP}utils/background.c ${SP}logic/entity.c ${SP}logic/game.c ${SP}utils/movement.c
	${CC} -c ${SP}utils/background.c -o ${BLD}background.o ${CFLAGS} ${LDFLAGS}

${BLD}movement.o: ${SP}utils/movement.c ${SP}utils/utils.c
	${CC} -c ${SP}utils/movement.c -o ${BLD}movement.o ${CFLAGS} ${LDFLAGS}

${BLD}settings.o: ${SP}settings.c
	${CC} -c ${SP}settings.c -o ${BLD}settings.o ${CFLAGS} ${LDFLAGS}

${BLD}player.o : ${SP}logic/player.c ${SP}logic/entity.c ${SP}interface/animation.c ${SP}utils/movement.c ${SP}logic/spaceship.c ${SP}utils/shooter.c
	${CC} -c ${SP}logic/player.c -o ${BLD}player.o ${CFLAGS} ${LDFLAGS}

${BLD}ennemy.o : ${SP}logic/ennemy.c ${SP}logic/entity.c ${SP}interface/animation.c ${SP}utils/movement.c ${SP}logic/spaceship.c ${SP}utils/shooter.c
	${CC} -c ${SP}logic/ennemy.c -o ${BLD}ennemy.o ${CFLAGS} ${LDFLAGS}

${BLD}spaceship.o : ${SP}logic/spaceship.c
	${CC} -c ${SP}logic/spaceship.c -o ${BLD}spaceship.o ${CFLAGS} ${LDFLAGS}

${BLD}missile.o : ${SP}logic/missile.c ${SP}logic/entity.c
	${CC} -c ${SP}logic/missile.c -o ${BLD}missile.o ${CFLAGS} ${LDFLAGS}

${BLD}shooter.o : ${SP}utils/shooter.c ${SP}logic/entity.c ${SP}logic/missile.c
	${CC} -c ${SP}utils/shooter.c -o ${BLD}shooter.o ${CFLAGS} ${LDFLAGS}

${BLD}level.o : ${SP}logic/level.c 
	${CC} -c ${SP}logic/level.c -o ${BLD}level.o ${CFLAGS} ${LDFLAGS}

${BLD}bonus.o : ${SP}logic/bonus.c 
	${CC} -c ${SP}logic/bonus.c -o ${BLD}bonus.o ${CFLAGS} ${LDFLAGS}

${BLD}utils.o : ${SP}utils/utils.c
	${CC} -c ${SP}utils/utils.c -o ${BLD}utils.o ${CFLAGS} ${LDFLAGS}

${BLD}menu.o : ${SP}interface/menu.c ${SP}interface/click_actions.c
	${CC} -c ${SP}interface/menu.c -o ${BLD}menu.o ${CFLAGS} ${LDFLAGS}

${BLD}click_actions.o : ${SP}interface/click_actions.c
	${CC} -c ${SP}interface/click_actions.c -o ${BLD}click_actions.o ${CFLAGS} ${LDFLAGS}

${BLD}campaign_menu.o : ${SP}interface/campaign_menu.c
	${CC} -c ${SP}interface/campaign_menu.c -o ${BLD}campaign_menu.o ${CFLAGS} ${LDFLAGS}



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
