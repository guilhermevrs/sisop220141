#Makefile

main: fileHandler.o matrizHandler.o
	gcc -o bin/ProcessApp ProcessApp/processApp.c & gcc -o bin/ThreadApp ThreadApp/threadApp.c

fileHandler.o: common/fileHandler.c
	gcc -o common/fileHandler.o -c common/fileHandler.c
matrizHandler.o: common/matrizHandler.c
	gcc -o common/matrizHandler.o -c common/matrizHandler.c
clean:
	rm common/*.o bin/ProcessApp bin/ThreadApp
