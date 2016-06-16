BIN=arp

INCLUDE=../headers

LIB_UTIL=../blocks

arp:  main_arp.c util.c 
	gcc -I$(INCLUDE) $(LIB_UTIL)/util.o main_arp.c -o $(BIN)

clean:
	rm arp

