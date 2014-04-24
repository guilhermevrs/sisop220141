#Makefile

main: ProcessApp ThreadApp

ProcessApp: fileHandler.o matrizHandler.o ProcessApp/processApp.c
	gcc -o bin/ProcessApp ProcessApp/processApp.c common/fileHandler.o common/matrizHandler.o

ThreadApp: fileHandler.o matrizHandler.o ThreadApp/threadApp.c
	gcc -o bin/ThreadApp ThreadApp/threadApp.c common/fileHandler.o common/matrizHandler.o

fileHandler.o: common/fileHandler.c
	gcc -o common/fileHandler.o -c common/fileHandler.c

matrizHandler.o: common/matrizHandler.c
	gcc -o common/matrizHandler.o -c common/matrizHandler.c

clean:
	rm common/*.o bin/ProcessApp bin/ThreadApp
