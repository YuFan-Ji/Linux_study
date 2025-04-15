# 最终代码
BIN=mytest
#SRC=$(shell ls *.c)
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
CC=gcc
RM=rm -f

$(BIN):$(OBJ)
	@$(CC) $^ -o $@
	@echo "链 接 $^ 成 $@"
%.o:%.c
	@$(CC) -c $<
	@echo "编译. . .$< 成 $@"
.PHONY:clean
clean:
	$(RM) $(BIN) $(OBJ)


## 二代代码
#BIN=mytest
#SRC=test.c
#OBJ=test.o
#CC=gcc
#RM=rm -f
#
#$(BIN):$(OBJ)
#	$(CC) $(OBJ) -o $(BIN)
#$(OBJ):$(SRC)
#	$(CC) -c $(SRC) -o $(OBJ)
#
#.PHONY: clean
#clean:
#	$(RM) $(BIN) $(OBJ)



## 一代代码
#mytest:test.o
#	gcc test.o -o mytest 
#
#test.o:test.c
#	gcc -c test.c -o test.o
#
#.PHONY:clean
#	rm -f *.o mytest






#mytest:test.o
#	gcc test.o -o mytest
#test.o:test.s
#	gcc -c test.s -o test.o
#test.s:test.i
#	gcc -S test.i -o test.s
#test.i:test.c
#	gcc -E test.c -o test.i
#
#.PHONY:clean 
#clean:
#	rm -f *.i *.s *.o  mytest
