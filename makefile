#	directories:
codeDir = code/
headerDir = include/
sdl2Include = sdl2/include/
sdl2LibWindows = sdl2/lib/windows
sdl2Bin = sdl2/bin/					#	currently useless
glad = glad/

all : cyan
#ifdef OS
#	Windows
cyan : $(codeDir)main.cpp $(glad)glad.c 
	gcc -Wall -o output -m64 $(codeDir)main.cpp $(glad)glad.c -I$(headerDir) -I$(sdl2Include) -I$(glad) -lmingw32 -lSDL2main -lSDL2 -L$(sdl2LibWindows) -L$(sdl2Bin) -lopengl32 -lgdi32 -lstdc++

#else
#	Linux
#	consider using diffrent flags for sdl2, specificaly -lmingw32 might be specific for windows(maybe)
# cyan : $(codeDir)main.cpp $(codeDir)GraphicUnit.cpp
# 	gcc -Wall -o output -m64 $(codeDir)main.cpp $(codeDir)GraphicUnit.cpp -I$(headerDir) -I$(sdl2Include) -lmingw32 -lSDL2main -lSDL2 -L$(sdl2LibWindows) -L$(sdl2Bin) -lXt -lX11 -lGL -ldl -lglfw -lstdc++

#endif
