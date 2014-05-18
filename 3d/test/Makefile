INCLS =  -I /usr/include -I /usr/local/include
LIBS = -L/usr/X11R6/lib -lX11 -lXi -lXmu -lglut -lGL -lGLU -lm   
CFLAGS = -g -O2 -Wall -fomit-frame-pointer -ffast-math -fexpensive-optimizations -fstrict-aliasing -malign-loops=2 -malign-jumps=2 -malign-functions=2 -D_REENTRANT -DPTHREADS

CC = gcc
OPT =  -G

%.o: %.cc %.h
	etags -C -a $^
	$(CC) $(OPT) -c $< $(INCLS)

%.o: %.cc 
	etags -C -a $^
	$(CC) $(OPT) -c $< $(INCLS)

alpha3D: alpha3D.o
	$(CC) $^ -o $@ -lm $(LIBS)

alpha3D.o: alpha3D.cc TAGS
	$(CC) $(OPT) -c $< $(INCLS)

TAGS: *.cc
	etags -C -a $^
clean:
	rm -f *.o













