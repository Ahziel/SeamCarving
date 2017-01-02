#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <algorithm>
#include "imagesRW.h"


double convolution(unsigned char *I,int n, int m, int i, int j, int * K)
{
    int sum = 0;

    int x,y;

    y = 0;
    for(int k = -1; k < 2; k++)
    {
    	x = 0;
    	for(int l = -1; l < 2 ; l++)
    	{
    		if(i+k<0)
    		{
                sum+=I[(i+k+1)*n+(j+l)]*K[y*3+x];
    		}
    		else if(i+k>=m)
    		{
    			sum+=I[(i+k-1)*n+(j+l)]*K[y*3+x];
    		}
            else if(j+l<0 )
            {
                sum+=I[(i+k)*n+(j+l+1)]*K[y*3+x];
            }
            else if(j+l>=n)
            {
            	sum+=I[(i+k)*n+(j+l-1)]*K[y*3+x];
            }
            else  
            {
                sum += I[(i+k)*n+(j+l)]*K[y*3+x];          	
            }  
    		x++;
    	}
    	y++;
    }
    return sum;
    
}


int max(int *I,int n, int m)
{
	int max = 0;
	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < n ; j++)
		{
			if(I[i*n+j] > max)
			{
				max = I[i*n+j];
			}
		}
	}
	return max;
}			


// Calcul du gradient de imgIn  (Attention aux bords)
void IMgradientSobel ( unsigned char *imgIn, int *imgOut, int n, int m)
{
	int X[9] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
	int Y[9] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };
	int * sobelX = X;
	int * sobelY = Y;

	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < n ; j++)
		{	
			int gradX = convolution(imgIn,n,m,i,j,sobelX);
			int gradY = convolution(imgIn,n,m,i,j,sobelY);
			imgOut[i*n+j] = sqrt(gradX*gradX + gradY * gradY);
		}
	}	
	
	unsigned char * affiche;
	affiche = new unsigned char[n*m];
	int maxi = max(imgOut,n,m);

	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < n ; j++)
		{
			affiche[i*n+j] = imgOut[i*n+j]*255/maxi;
		}
	}

	//sauvegarde dans un fichier 
	char fileName[250];
	strcpy(fileName, "gradient.pgm");
    printf("Sauvegarde de %s de taille [%d,%d]\n", fileName, n, m);
    writePGM_Picture(fileName, affiche, n, m);
}

void IMgradientPrewitt ( unsigned char *imgIn, int *imgOut, int n, int m)
{
	int X[9] = { -1, 0, 1, -1, 0, 1, -1, 0, 1 };
	int Y[9] = { -1, -1, -1, 0, 0, 0, 1, 1, 1 };
	int * sobelX = X;
	int * sobelY = Y;

	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < n ; j++)
		{	
			int gradX = convolution(imgIn,n,m,i,j,sobelX);
			int gradY = convolution(imgIn,n,m,i,j,sobelY);
			imgOut[i*n+j] = sqrt(gradX*gradX + gradY * gradY);
		}
	}	
	
	unsigned char * affiche;
	affiche = new unsigned char[n*m];
	int maxi = max(imgOut,n,m);

	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < n ; j++)
		{
			affiche[i*n+j] = imgOut[i*n+j]*255/maxi;
		}
	}

	//sauvegarde dans un fichier 
	char fileName[250];
	strcpy(fileName, "gradient.pgm");
    printf("Sauvegarde de %s de taille [%d,%d]\n", fileName, n, m);
    writePGM_Picture(fileName, affiche, n, m);
}

void IMgradientLaplacien ( unsigned char *imgIn, int *imgOut, int n, int m)
{
	int X[9] = { 1, -2, 1, -2, 4, -2, 1, -2, 1 };
	int * sobelX = X;

	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < n ; j++)
		{	
			int gradX = convolution(imgIn,n,m,i,j,sobelX);
			imgOut[i*n+j] = sqrt(2*gradX*gradX);
		}
	}	
	
	unsigned char * affiche;
	affiche = new unsigned char[n*m];
	int maxi = max(imgOut,n,m);

	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < n ; j++)
		{
			affiche[i*n+j] = imgOut[i*n+j]*255/maxi;
		}
	}

	//sauvegarde dans un fichier 
	char fileName[250];
	strcpy(fileName, "gradient.pgm");
    printf("Sauvegarde de %s de taille [%d,%d]\n", fileName, n, m);
    writePGM_Picture(fileName, affiche, n, m);
}

void masquerEnlever (int *imgIn, unsigned char * masque, int n, int m)
{

	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < n ; j++)
		{	
			if(masque[i*n+j] == 0)
			{
				imgIn[i*n+j] = -1;
			}
		}
	}

}

void masquerGarder (int *imgIn, unsigned char * masque, int n, int m)
{

	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < n ; j++)
		{	
			if(masque[i*n+j] == 0)
			{
				imgIn[i*n+j] = 1000;
			}
		}
	}

}

void transpose(unsigned char * I, unsigned char * res, int n, int m)
{

    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            res[j*m+i] = I[j+i*n];
        }
    }
}



void cumule(int *imgIn, int n, int m)
{
	for(int i = 1; i < m; i++)
	{
		for(int j = 0; j < n ; j++)
		{
			int min = imgIn[(i-1)*n+j];
			if(j != 0)
			{
				min = std::min(min,imgIn[(i-1)*n+j-1]);
			}
			if(j != n-1)
			{
				min = std::min(min,imgIn[(i-1)*n+j+1]);
			}
			imgIn[i*n+j] += min;
		}
	}

	unsigned char * affiche;
	affiche = new unsigned char[n*m];
	int maxi = max(imgIn,n,m);

	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < n ; j++)
		{
			affiche[i*n+j] = imgIn[i*n+j]*255/maxi;
		}
	}

	//sauvegarde dans un fichier 
	char fileName[250];
	strcpy(fileName, "cumule.pgm");
    printf("Sauvegarde de %s de taille [%d,%d]\n", fileName, n, m);
    writePGM_Picture(fileName, affiche, n, m);

}

// Recherche du chemin d'energie minimale dans imgIn 
void min_path(int *imgIn, int *pos, int n, int m) 
{
	int min = imgIn[(m-1)*n];
	pos[m-1] = 0;

	for(int j = 1; j < n ; j++)
	{
		if(min > imgIn[(m-1)*n+j])
		{
			min = imgIn[(m-1)*n+j];
			pos[m-1] = j;
		}
	}

	for(int i = m-2; i >= 0; i--)
	{
		int j = pos[i+1];
		int min;
		if(j <= 0 )
        {
            if(imgIn[i*n+j] < imgIn[i*n+j + 1])
            {
            	min = j;
            }else{
            	min = j+1;
            }
        }
        else if(j >= n)
        {
           	if(imgIn[i*n+j] < imgIn[i*n+j -1 ])
            {
            	min = j;
            }else{
            	min = j-1;
            }
        }
        else  
        {            
        	if(imgIn[i*n+j] < imgIn[i*n+j -1 ] && imgIn[i*n+j] < imgIn[i*n+j + 1 ])
            {
            	min = j;
            }else if(imgIn[i*n+j] > imgIn[i*n+j -1 ] && imgIn[i*n+j -1] < imgIn[i*n+j + 1 ])
            {
            	min = j-1;
            }else{
            	min = j+1;
            }    	
        }  
        pos[i] = min;
	}

}

/*

Fonction pour afficher le chemin a supprimer

*/
void trace(unsigned char *I,int *pos, int n, int m)
{
	int res[n*m];

	bool passe;
	for(int i = 0; i < m; i++)
	{
		passe = false;
		for(int j = 0; j < n ; j++)
		{
			if(pos[i] == j)
			{
				res[i*n+j] = 0;
			}else{
				res[i*n+j] = I[i*n+j];
			}
		}
	}

	unsigned char * affiche;
	affiche = new unsigned char[n*m];
	int maxi = max(res,n,m);

	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < n ; j++)
		{
			affiche[i*n+j] = res[i*n+j]*255/maxi;
		}
	}

	//sauvegarde dans un fichier 
	char fileName[250];
	strcpy(fileName, "trace.pgm");
    printf("Sauvegarde de %s de taille [%d,%d]\n", fileName, n, m);
    writePGM_Picture(fileName, affiche, n, m);
}

/*

Fonction pour retirer le chemin de l'image

*/
void remove_path(unsigned char *I,unsigned char *res, int *pos, int n, int m)
{
	bool passe;
	for(int i = 0; i < m; i++)
	{
		passe = false;
		for(int j = 0; j < n ; j++)
		{
			if(pos[i] == j)
			{
				passe = true;
			}
			if(passe)
			{
				res[i*(n-1)+j] = I[i*n+j+1];
			}
			else{
				res[i*(n-1)+j] = I[i*n+j];
			}
		}
	}
}

void copie(unsigned char * I, unsigned char * IC, int n, int m)
{
	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < n ; j++)
		{
			I[i*n+j] = IC[i*n+j];
		}
	}
}


int main(int argc, char **argv)
{
	char fileName[250];
	char fileNameM1[250];
	strcpy(fileNameM1, "./images/mask1.pgm");
	char fileNameM2[250];
	strcpy(fileNameM2, "./images/mask2.pgm");
	int n;
	int m;

	int choixImage = 1;
	std::cout<<"Image :"<<std::endl;
	std::cout<<"1) Mer"<<std::endl;
	std::cout<<"2) Loup"<<std::endl;
	std::cin >> choixImage;
	if(choixImage == 1)
	{
		strcpy(fileName, "./images/mer.pgm");
		n = 500;
		m = 353;
	}
	else
	{
		strcpy(fileName, "./images/loup.pgm");
		n = 290;
		m = 425;
	}

	std::cout<<"Programme de Seam Carving"<<std::endl;
	std::cout<<"             ---------------                "<<std::endl;

	int choixVH;
	std::cout<<"Voulez supprimer de manière :"<<std::endl;
	std::cout<<"1) Horizontal"<<std::endl;
	std::cout<<"2) Vertical"<<std::endl;
	std::cin >> choixVH;

	int choixGradient;
	std::cout<<"Choix gradient :"<<std::endl;
	std::cout<<"1) Prewitt"<<std::endl;
	std::cout<<"2) Sobel"<<std::endl;
	std::cout<<"3) Laplacien"<<std::endl;
	std::cin >> choixGradient;

	int choixMasque = 2;
	if(choixImage == 1)
	{
		std::cout<<"Mettre les masques ? :"<<std::endl;
		std::cout<<"1) Oui"<<std::endl;
		std::cout<<"2) Non"<<std::endl;
		std::cin >> choixMasque;
	}

	int boucle;
	std::cout<<"Réduire de combien ?"<<std::endl;
	std::cin >> boucle;


	for (int i = 0; i < boucle; ++i)
	{

		unsigned char im1[n*m];
		printf("Ouverture de %s de taille [%d,%d]\n", fileName, n, m);
		readPGM_Picture(fileName, im1, n, m);

		unsigned char masque1[n*m];
		unsigned char masque2[n*m];

		if(choixMasque == 1 && choixImage == 1)
		{
			readPGM_Picture(fileNameM2, masque2, n, m);
			readPGM_Picture(fileNameM1, masque1, n, m);
		}


		if(choixVH == 1)
		{
			unsigned char transpo[m*n];
			transpose(im1,transpo,n,m);
			copie(im1,transpo,n,m);
			if(choixMasque == 1)
			{
				transpose(masque1,transpo,n,m);
				copie(masque1,transpo,n,m);
				transpose(masque2,transpo,n,m);
				copie(masque2,transpo,n,m);
			}
			std::swap(n,m);
		}

		int imgOut[n*m];
		int pos[m];
		unsigned char im2[(n-1)*m];
		unsigned char masque1new[(n-1)*m];
		unsigned char masque2new[(n-1)*m];

		//transpose(im1,transpo,n,m);
		switch ( choixGradient )  
     	 {  
	         case 1:  
	            IMgradientPrewitt(im1,imgOut,n,m);  
	            break;  
	         case 2:  
	            IMgradientSobel(im1,imgOut,n,m);  
	            break;  
	         case 3:  
				IMgradientLaplacien(im1,imgOut,n,m);
	            break;     
	         default:  
	            IMgradientSobel(im1,imgOut,n,m);  
     	 }  

     	if(choixMasque == 1 && choixImage == 1)
     	{
     		masquerEnlever(imgOut,masque2,n,m);
			masquerGarder(imgOut,masque1,n,m);
     	}
		cumule(imgOut,n,m);
		min_path(imgOut,pos,n,m);
		trace(im1,pos,n,m);
		remove_path(im1,im2,pos,n,m);
		if(choixMasque == 1 && choixImage == 1)
     	{
     		remove_path(masque1,masque1new,pos,n,m);
			remove_path(masque2,masque2new,pos,n,m);
     	}

     	n--;

		if(choixVH == 1)
		{
			unsigned char transpo[m*n];
			transpose(im2,transpo,n,m);
			copie(im2,transpo,n,m);
			if(choixMasque == 1 && choixImage == 1)
			{
				transpose(masque1new,transpo,n,m);
				copie(masque1new,transpo,n,m);
				transpose(masque2new,transpo,n,m);
				copie(masque2new,transpo,n,m);
			}
			std::swap(n,m);
		}

		strcpy(fileName, "carved.pgm");
	    printf("Sauvegarde de %s de taille [%d,%d]\n", fileName, n, m);
	    writePGM_Picture(fileName, im2, n, m);

	    if(choixMasque == 1 && choixImage == 1)
	    {
	    	strcpy(fileNameM1, "mask1.pgm");
		    printf("Sauvegarde de %s de taille [%d,%d]\n", fileNameM1, n, m);
		    writePGM_Picture(fileNameM1, masque1new, n, m);

		    strcpy(fileNameM2, "mask2.pgm");
		    printf("Sauvegarde de %s de taille [%d,%d]\n", fileNameM2, n, m);
		    writePGM_Picture(fileNameM2, masque2new, n, m);
	    }

	    //getchar();
	    
	}

    return 0;
}
