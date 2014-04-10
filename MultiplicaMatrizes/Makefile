#Makefile

main: fileHandler.o matrizHandler.o
	echo 'Foi'
fileHandler.o: common/fileHandler.c
	gcc -o common/fileHandler.o -c common/fileHandler.c
matrizHandler.o: common/matrizHandler.c
	gcc -o common/matrizHandler.o -c common/matrizHandler.c
clean:
	rm common/*.o
