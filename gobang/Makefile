OBJS = main.o AIStrategy.o checkboard.o player.o test.o util.o
gobang : $(OBJS)
	cc -o gobang $(OBJS)
main.o : gobang.h test.h utils.h
	cc -g -c main.c
AIStrategy.o : AIStrategy.h gobang.h utils.h
	cc -g -c AIStrategy.c
checkboard.o : gobang.h
	cc -g -c checkboard.c
player.o : gobang.h utils.h AIStrategy.h
	cc -g -c player.c
test.o : test.h gobang.h AIStrategy.h utils.h
	cc -g -c test.c
util.o : utils.h
	cc -g -c util.c
.PHONY : clean
clean :
	-rm gobang $(OBJS)
