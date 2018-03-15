SRC := ${wildcard *.c}
CFLAGS := -Iinclude
BIN := memoryrank
$(BIN): ${SRC}
	gcc ${SRC} ${CFLAGS} -o $@

clean:
	rm $(BIN)
