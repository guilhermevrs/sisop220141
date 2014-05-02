#include <stdio.h>
#include <time.h>
#include <math.h>

#define BUFFER_SIZE 256

int main(int argc, char **argv)
{
    int lines = 1, cols = 1;

    printf("Numero de linhas: ");
    scanf("%d", &lines);
    printf("Numero de colunas: ");
    scanf("%d", &cols);

    srand(time(NULL));

    FILE *fd = fopen("matrix.txt", "w+");

    int v = 0;

    char buf[BUFFER_SIZE];
    sprintf(buf, "LINHAS = %d\nCOLUNAS = %d\n", lines, cols);
    fputs(buf, fd);

    int x, y;
    for (x = 0; x < lines; ++x) {
        for (y = 0; y < cols; ++y) {
            v = 1;
            fprintf(fd, "%d ", v);
        }
        fprintf(fd, "\n");
    }
    fflush(fd);
    fclose(fd);
}

