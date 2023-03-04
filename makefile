#	directories:
codeDir = code/
headerDir = include/
sdl2Include = sdl2/include/
sdl2LibWindows = sdl2/lib/windows
sdl2Bin = sdl2/bin/					#	currently useless

all : cyan
ifdef OS
#	Windows
cyan : $(codeDir)main.cpp $(codeDir)GraphicUnit.cpp
	gcc -Wall -o output -m64 $(codeDir)main.cpp $(codeDir)GraphicUnit.cpp -I$(headerDir) -I$(sdl2Include) -lmingw32 -lSDL2main -lSDL2 -L$(sdl2LibWindows) -L$(sdl2Bin) -lopengl32 -lgdi32 -lstdc++

else
#	Linux
#	replace -lopengl32 -lgdi32 with -lXt -lX11 -lGL as these are the opengl flags
#	also consider using diffrent flags for sdl2, specificaly -lmingw32 might be specific for windows(maybe)

endif
