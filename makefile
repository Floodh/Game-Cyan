#	directories:
codeDir = code/
headerDir = include/
sdl2Include = sdl2/include/
sdl2LibWindows = sdl2/lib/windows
sdl2Bin = sdl2/bin/					#	currently useless
glad = glad/
compiledDir = code/compiled/

#	all cpp and c files
sources =  $(codeDir)main.cpp 
sources += $(codeDir)GL_utilities.c 
sources += $(codeDir)Game.cpp
sources += $(codeDir)Keyboard.cpp 
sources += $(codeDir)KeyboardKey.cpp  
sources += $(codeDir)Camera.cpp 
sources += $(codeDir)World.cpp 
sources += $(codeDir)Terrain.cpp 
sources += $(codeDir)Water.cpp
sources += $(codeDir)Land.cpp
sources += $(codeDir)TheSun.cpp
sources += $(codeDir)LoadBMP.cpp
sources += $(codeDir)MainMenu.cpp
sources += $(codeDir)Console.cpp
sources += $(codeDir)Player.cpp

compiled =  $(compiledDir)main.o 
compiled += $(compiledDir)GL_utilities.o 
compiled += $(compiledDir)Game.o
compiled += $(compiledDir)Keyboard.o 
compiled += $(compiledDir)KeyboardKey.o  
compiled += $(compiledDir)Camera.o 
compiled += $(compiledDir)World.o 
compiled += $(compiledDir)Terrain.o 
compiled += $(compiledDir)Water.o
compiled += $(compiledDir)Land.o
compiled += $(compiledDir)TheSun.o
compiled += $(compiledDir)LoadBMP.o
compiled += $(compiledDir)Console.o
compiled += $(compiledDir)Player.o

CC = gcc
CFLAGS = -Wall -m64 -lSDL2 -DGL_GLEXT_PROTOTYPES -lXt -lX11 -lGl -lm -lstdc++
CINCLUDE = -I$(headerDir) -I$(sdl2Include)

ifdef OS
	sources += $(glad)glad.c 
endif

all : cyan
ifdef OS
#	Windows
cyan : $(sources)
	gcc -Wall -o output -m64 $(sources) -I$(headerDir) -I$(sdl2Include) -I$(glad) -lmingw32 -lSDL2main -lSDL2 -L$(sdl2LibWindows) -L$(sdl2Bin) -lopengl32 -lgdi32 -lstdc++

else
#	Linux
cyan : $(compiled)
	gcc -Wall -o output -m64 $(compiled) -I$(headerDir) -I$(sdl2Include) -lSDL2 -L$(sdl2Bin) -DGL_GLEXT_PROTOTYPES -lXt -lX11 -lGL -lm -lstdc++

$(compiledDir)main.o: $(codeDir)main.cpp
	$(CC) $(CFLAGS) -c -o $(compiledDir)main.o $(codeDir)main.cpp $(CINCLUDE)

$(compiledDir)GL_utilities.o: $(codeDir)GL_utilities.c
	$(CC) $(CFLAGS) -c -o $(compiledDir)GL_utilities.o $(codeDir)GL_utilities.c $(CINCLUDE)

$(compiledDir)Game.o: $(codeDir)Game.cpp
	$(CC) $(CFLAGS) -c -o $(compiledDir)Game.o $(codeDir)Game.cpp $(CINCLUDE)

$(compiledDir)Keyboard.o: $(codeDir)Keyboard.cpp
	$(CC) $(CFLAGS) -c -o $(compiledDir)Keyboard.o $(codeDir)Keyboard.cpp $(CINCLUDE)

$(compiledDir)KeyboardKey.o: $(codeDir)KeyboardKey.cpp
	$(CC) $(CFLAGS) -c -o $(compiledDir)KeyboardKey.o $(codeDir)KeyboardKey.cpp $(CINCLUDE)

$(compiledDir)Camera.o: $(codeDir)Camera.cpp
	$(CC) $(CFLAGS) -c -o $(compiledDir)Camera.o $(codeDir)Camera.cpp $(CINCLUDE)

$(compiledDir)World.o: $(codeDir)World.cpp
	$(CC) $(CFLAGS) -c -o $(compiledDir)World.o $(codeDir)World.cpp $(CINCLUDE)

$(compiledDir)Terrain.o: $(codeDir)Terrain.cpp
	$(CC) $(CFLAGS) -c -o $(compiledDir)Terrain.o $(codeDir)Terrain.cpp $(CINCLUDE)

$(compiledDir)Water.o: $(codeDir)Water.cpp
	$(CC) $(CFLAGS) -c -o $(compiledDir)Water.o $(codeDir)Water.cpp $(CINCLUDE)

$(compiledDir)Land.o: $(codeDir)Land.cpp
	$(CC) $(CFLAGS) -c -o $(compiledDir)Land.o $(codeDir)Land.cpp $(CINCLUDE)

$(compiledDir)TheSun.o: $(codeDir)TheSun.cpp
	$(CC) $(CFLAGS) -c -o $(compiledDir)TheSun.o $(codeDir)TheSun.cpp $(CINCLUDE)

$(compiledDir)LoadBMP.o: $(codeDir)LoadBMP.cpp
	$(CC) $(CFLAGS) -c -o $(compiledDir)LoadBMP.o $(codeDir)LoadBMP.cpp $(CINCLUDE)

$(compiledDir)Console.o: $(codeDir)Console.cpp
	$(CC) $(CFLAGS) -c -o $(compiledDir)Console.o $(codeDir)Console.cpp $(CINCLUDE)

$(compiledDir)Player.o: $(codeDir)Player.cpp
	$(CC) $(CFLAGS) -c -o $(compiledDir)Player.o $(codeDir)Player.cpp $(CINCLUDE)


clean: 
	rm $(compiledDir)*.o

run: 
	./output
endif
