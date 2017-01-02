//Include Needed Libraries



#include	"imagesRW.h"
#include	<string.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	<math.h>

/*
P4 = PBM raw bitmap
P5 = PGM raw greymap
P6 = PPM raw pixmap
*/
//*****************************************************************************************************//
//* Write a PGM picture (grey map)
//*****************************************************************************************************//
void writePGM_Picture(char *filename, unsigned char *inputBuffer, int sizeX, int sizeY)
{
 FILE *fp; 
 
 if((fp = fopen (filename,"wb+"))==NULL)
 {
  printf("\n - ERROR: can not open PGM file %s \n", filename);
  exit(-1);
 } 
  // pgm header
  fprintf(fp, "P5\n""%d %d\n""%d\n", sizeX, sizeY, 255);
  fwrite(inputBuffer, 1, (sizeX)*(sizeY), fp);
  putc('\n', fp);  
  fclose(fp);  
}

//*****************************************************************************************************//
//* Open a PGM picture (grey map)
//*****************************************************************************************************//
void readPGM_Picture(char *filename, unsigned char *outputBuffer, int sizeX, int sizeY)
{
 FILE *fp;
 char line[10];
 int dynamique=0;
 unsigned char * buffer = (unsigned char *)calloc((sizeX)*(sizeY), sizeof(unsigned char));
 
 if((fp = fopen (filename,"rb"))==NULL)
 {
  printf("\n - ERROR: can not open PGM file %s \n", filename);
  exit(-1);
 }
 
 // pgm header
 fscanf(fp, "%s\n""%d %d\n""%d\n", line, &sizeX, &sizeY, &dynamique);
 

 fread(buffer, sizeof(unsigned char), (sizeX)*(sizeY), fp);

 memcpy(outputBuffer,buffer, sizeof(unsigned char)*(sizeX)*(sizeY));
     
  fclose(fp);
 
}
