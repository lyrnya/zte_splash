#include <stdio.h>

int main(int argc, char *argv[]) {

FILE *out = fopen("logo_new.bin", "wb");

char header[4096] = {0};
fwrite(header, 1, 4096, out);

char metaData[4096] = {0};
int metaPos = 0;
unsigned int currentOffset = 0;

for(int i = 1; i < argc; i++) {
FILE *f = fopen(argv[i], "rb");
if (!f) continue;

fseek(f, 0, SEEK_END);
unsigned int size = ftell(f);
fseek(f, 0, SEEK_SET);

metaPos += sprintf(metaData + metaPos, "%s %u %u ", argv[i], currentOffset, size);

char *buffer = malloc(size);
fread(buffer, 1, size, f);
fwrite(buffer, 1, size, out);
fclose(f);
free(buffer);

currentOffset += size;
}

fseek(out, 0x10, SEEK_SET);
fwrite(metaData, 1, metaPos, out);

fclose(out);
return 0;
}
