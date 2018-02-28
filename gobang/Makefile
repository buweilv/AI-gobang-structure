OBJS = main.o AIStrategy.o checkboard.o player.o  util.o evaluate_point.o
gobang : $(OBJS)
	cc -o gobang $(OBJS)
main.o : gobang.h  utils.h
	cc -g3 -c main.c
AIStrategy.o : AIStrategy.h gobang.h utils.h
	cc -g3 -c AIStrategy.c
checkboard.o : gobang.h
	cc -g3 -c checkboard.c
player.o : gobang.h utils.h AIStrategy.h
	cc -g3 -c player.c
util.o : utils.h
	cc -g3 -c util.c
evaluate_point.o: gobang.h AIStrategy.h utils.h
	cc -g3 -c evaluate_point.c 
.PHONY : clean
clean :
	-rm gobang $(OBJS)
