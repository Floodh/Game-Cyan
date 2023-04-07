#	directories:
codeDir = code/
headerDir = include/
sdl2Include = sdl2/include/
sdl2LibWindows = sdl2/lib/windows
sdl2Bin = sdl2/bin/					#	currently useless
glad = glad/

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
sources += $(codeDir)Console.cpp
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
cyan : $(sources)
	gcc -Wall -o output -m64 $(sources) -I$(headerDir) -I$(sdl2Include) -lSDL2 -L$(sdl2Bin) -DGL_GLEXT_PROTOTYPES -lXt -lX11 -lGL -lm -lstdc++
endif
