#pragma once

#include "SDL.h"
#include "GL_utilities.h"

#include "IDrawObject.hpp"

class Land : public IDrawObject
{
    public:

        //  the constructor should later receive the content of the .bmp file
        Land();
        void Draw() override;

    private:

};