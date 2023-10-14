
##############################################################
#  Practicas de Informática Gráfica. Curso 2022/2023.
#  Makefile de ejemplo para la construccion de las practicas.
##############################################################

# EJECUTABLE=  nombre del fichero ejecutable que queremos crear
#

EXE_DIR = ./build
EJECUTABLE=  $(EXE_DIR)/practicasIG


#  MODULOS=  lista de nombres con los modulos que se van a 
#            compilar. Cada uno se corresponde con un fichero C
#            Se le pone la extension .o para indicar el fichero objeto
#            generado por el compilador.
#
#

SRC_DIR = ./src
BIN_DIR = ./bin

SOURCEC = $(wildcard $(SRC_DIR)/*.c)
SOURCECC = $(wildcard $(SRC_DIR)/*.cc)
SOURCECPP = $(wildcard $(SRC_DIR)/*.cpp)
SOURCES = $(SOURCEC) $(SOURCECC) $(SOURCECPP)

MODULOSC = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SOURCEC))
MODULOSCC = $(patsubst $(SRC_DIR)/%.cc, $(BIN_DIR)/%.o, $(SOURCECC))
MODULOSCPP = $(patsubst $(SRC_DIR)/%.cpp, $(BIN_DIR)/%.o, $(SOURCECPP))

MODULOS= $(MODULOSC) $(MODULOSCC) $(MODULOSCPP)

#  INCLUDEDIRS= Lista de caminos a los directorios donde se encuentran
#              	ficheros include. Si se cambia de instalaci� es posible
#		que se deban modificar. 
#

INCLUDEDIR= /usr/X11R6/include
INCLUDEDIR2= ./include
#MESAINCLUDE= /usr/X11R6/Mesa-3.0/include

#  LIBSDIRS= 	Lista de caminos a los directorios donde se encuentran
#              	las librerias. Si se cambia de instalaci� es posible
#		que se deban modificar. Ver lista de librerias mas abajo
#

LIBSDIR= /usr/X11R6/lib
#MESALIB= /usr/X11R6/Mesa-3.0/lib  

################ NO MODIFICAR A PARTIR DE AQUI ########################

#  CFLAGS= Parametros para el compilador de C
#        
#	      -G   (para que genere informacion para el depurador)
#             -c   (solo compilar cada modulo, no linkar)
#             -I   (indicamos directiorios donde buscar los include)

CFLAGS= -g -c -DXWINDOWS  -I$(INCLUDEDIR) -I$(INCLUDEDIR2)
CPPFLAGS= -g -c -DXWINDOWS  -I$(INCLUDEDIR) -I$(INCLUDEDIR2)
       
#  LDFLAGS= Parametros para el linkador. (ld)
#           le decimos que busque las librerias 
#           de X WINDOWS en el directorio indicado         

LDFLAGS=   -L$(LIBSDIR)
#  LIBS= librerias que vamos a linkar para hacer nuestro programa
#
#        en este caso necesitamos las siguientes:
#
#              X11      manejo de X Windows
#              c        libreria estandard de C
#              malloc   para usar la funcion malloc
#              m        funciones matematicas (sin y cos, p.ej.)

#LIBS=    -lglut -lGLU -lGL -lX11 -lXext -lXmu -lXi -lc -lm
LIBS=    -lglut -lGLU -lGL -lX11 -lXext  -lc -lm

#  CC= orden de UNIX que invoca al compilador de C
#      (en este caso "gcc" llama al compilador de C/C++ de GNU) 

CC=        g++

#   Las siguientes lineas le indican al programa make que
#   para construir el ejecutable debe compilar primero los 
#   ficheros objeto que aun no esten compilados y despues linkarlos 
#   todos juntos.

$(EJECUTABLE): $(MODULOS)
	$(CC) -o $(EJECUTABLE) $(LDFLAGS) $(MODULOS) $(LIBS)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cc
	$(CC) $(CPPFLAGS) $< -o $@

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CPPFLAGS) $< -o $@

clean:
	rm -f $(MODULOS) $(EJECUTABLE)

zip: clean
	zip -r practicasIG.zip ./*

organize:
	mkdir -p include src build bin
	mv *.h include
	mv *.c src
	mv *.cc src
	mv *.cpp src
	mv *.o bin
	mv ./practicasIG build

desorganize:
	mv include/*.h .
	mv src/*.c .
	mv src/*.cc .
	mv src/*.cpp .
	rm -r include src build bin



