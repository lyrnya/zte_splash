#include <stdio.h>

int main(int argc, char *argv[]) {

FILE *fp = fopen(argv[1], "rb");

fseek(fp, 0x10, SEEK_SET);

char fileName[50];
unsigned int offset, size;

while (fscanf(fp, "%s %u %u", fileName, &offset, &size) == 3) {
printf("Extracting: %s (offset: %u, size: %u)\n", fileName, offset, size);

long currentPos = ftell(fp);

FILE *out = fopen(fileName, "wb");

fseek(fp, offset + 4096, SEEK_SET);

unsigned char *buffer = malloc(size);
size_t read = fread(buffer, 1, size, fp);
fwrite(buffer, 1, size, out);

free(buffer);
fclose(out);

fseek(fp, currentPos, SEEK_SET);
}
fclose(fp);
return 0;
}
