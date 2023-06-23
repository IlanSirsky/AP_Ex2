all:queue startThread readChars coder 


readChars:readChars.h
	gcc -c -fpic readChars.c -lpthread -g -Wall -Werror

queue:myqueue.h	
	gcc -c -fpic myqueue.c  -lpthread -g -Wall -Werror

startThread: startThread.h
	gcc -c -fpic startThread.c -lpthread -g -Wall -Werror

coder:
	gcc coder.c -lpthread ./libCodec.so myqueue.o startThread.o readChars.o -o coder -g -Wall -Werror


.PHONY: clean
clean:
	rm -f encoder tester coder 2>/dev/null *.o
