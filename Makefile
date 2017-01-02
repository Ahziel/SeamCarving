CC      =       g++
OPTIONS  = -c -g -static

SOURCES = .
INC = .

#######	Build rules

all : tache

tache	: tpSeam.o imagesRW.o
	$(CC) -g  -o tpSeam \
	tpSeam.o imagesRW.o 
	\rm *.o

tpSeam.o : $(SOURCES)/tpSeam.cpp
	$(CC) $(OPTIONS) -I $(INC) $(SOURCES)/tpSeam.cpp

imagesRW.o	: $(SOURCES)/imagesRW.cpp
	$(CC) $(OPTIONS) -I $(INC) $(SOURCES)/imagesRW.cpp
