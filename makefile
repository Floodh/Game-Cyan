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
cyan : $(codeDir)main.cpp $(glad)glad.c $(codeDir)GL_utilities.c $(codeDir)Terrain.cpp
	gcc -Wall -o output -m64 $(codeDir)main.cpp $(glad)glad.c $(codeDir)GL_utilities.c $(codeDir)Terrain.cpp -I$(headerDir) -I$(sdl2Include) -I$(glad) -lmingw32 -lSDL2main -lSDL2 -L$(sdl2LibWindows) -L$(sdl2Bin) -lopengl32 -lgdi32 -lstdc++

else
#	Linux

endif
