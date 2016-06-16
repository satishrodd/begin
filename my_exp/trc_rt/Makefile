BIN=trace

INCLUDE=../headers

LIB_UTIL=../blocks

trace:  main_trace_route.c util.c 
	gcc -I$(INCLUDE) $(LIB_UTIL)/util.o main_trace_route.c -o $(BIN)

clean:
	rm trace
