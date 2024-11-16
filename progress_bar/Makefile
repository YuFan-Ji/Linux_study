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
