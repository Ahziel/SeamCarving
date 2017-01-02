#ifndef IMAGESRW_H
#define IMAGESRW_H

void readPGM_Picture(char *filename, unsigned char *outputBuffer, int sizeX, int sizeY);
void writePGM_Picture(char *filename, unsigned char *inputBuffer, int sizeX, int sizeY);

#endif //IMAGESRW_H