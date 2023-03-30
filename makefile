#	directories:
codeDir = code/
headerDir = include/
sdl2Include = sdl2/include/
sdl2LibWindows = sdl2/lib/windows
sdl2Bin = sdl2/bin/					#	currently useless
glad = glad/

all : cyan
ifdef OS
#	Windows
cyan : $(codeDir)main.cpp $(glad)glad.c $(codeDir)GL_utilities.c $(codeDir)Game.cpp $(codeDir)Keyboard.cpp $(codeDir)KeyboardKey.cpp  $(codeDir)Camera.cpp $(codeDir)World.cpp $(codeDir)Terrain.cpp $(codeDir)Water.cpp
	gcc -Wall -o output -m64 $(codeDir)main.cpp $(glad)glad.c $(codeDir)GL_utilities.c $(codeDir)Game.cpp $(codeDir)Keyboard.cpp $(codeDir)KeyboardKey.cpp $(codeDir)Camera.cpp $(codeDir)World.cpp $(codeDir)Terrain.cpp $(codeDir)Water.cpp -I$(headerDir) -I$(sdl2Include) -I$(glad) -lmingw32 -lSDL2main -lSDL2 -L$(sdl2LibWindows) -L$(sdl2Bin) -lopengl32 -lgdi32 -lstdc++

else
#	Linux
cyan : $(codeDir)main.cpp $(codeDir)GL_utilities.c $(codeDir)Game.cpp $(codeDir)Keyboard.cpp $(codeDir)KeyboardKey.cpp $(codeDir)Camera.cpp $(codeDir)World.cpp $(codeDir)Terrain.cpp $(codeDir)Water.cpp
	gcc -Wall -o output -m64 $(codeDir)main.cpp $(codeDir)GL_utilities.c $(codeDir)Game.cpp $(codeDir)Keyboard.cpp $(codeDir)KeyboardKey.cpp $(codeDir)Camera.cpp $(codeDir)World.cpp $(codeDir)Terrain.cpp $(codeDir)Water.cpp -I$(headerDir) -I$(sdl2Include) -lSDL2 -L$(sdl2Bin) -lXt -lX11 -lGL -lm -lstdc++
endif
