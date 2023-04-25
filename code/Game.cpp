#include "Game.hpp"

// #include "Player.hpp"

using namespace std;


Game::Game(int windowWidth, int windowHeight)
{
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;


    // INITIALIZE SDL:
    if (SDL_Init(SDL_INIT_EVENTS) < 0) {
        throw(std::string("Failed to initialize SDL: ") + SDL_GetError());
    }
    if (SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        throw(std::string("Failed to initialize SDL Video: ") + SDL_GetError());
    }

    // CONFIGURE OPENGL ATTRIBUTES USING SDL:
    int context_flags = SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, context_flags);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);     //  Z buffer
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    

    // CREATE AND SDL WINDOW CONFIGURED FOR OPENGL:
    if (0 == (this->window = SDL_CreateWindow("Cyan", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowWidth, SDL_WINDOW_OPENGL))) {
        throw(std::string("Failed to create window: ") + SDL_GetError());
    }
    // CREATE THE OPENGL CONTEXT AND MAKE IT CURRENT:
    if(NULL == (this->glContext = SDL_GL_CreateContext(this->window))) {
        throw(std::string("Failed to create OpenGL context"));
    }
    else SDL_GL_MakeCurrent(this->window, this->glContext);


    
    
    #if defined(_WIN32)
    // INITIALIZE GLAD:
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        throw(std::string("Failed to initialize GLAD"));
    }

    // LOG OPENGL VERSION, VENDOR (IMPLEMENTATION), RENDERER, GLSL, ETC.:
    std::cout << std::setw(34) << std::left << "OpenGL Version: " << GLVersion.major << "." << GLVersion.minor << std::endl;
    std::cout << std::setw(34) << std::left << "OpenGL Shading Language Version: " << (char *)glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << std::setw(34) << std::left << "OpenGL Vendor:" << (char *)glGetString(GL_VENDOR) << std::endl;
    std::cout << std::setw(34) << std::left << "OpenGL Renderer:" << (char *)glGetString(GL_RENDERER) << std::endl;
    
    #endif

    //glEnable( GL_DEPTH_TEST );
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_FRAMEBUFFER_SRGB);

    //  other
    this->keyboard = Keyboard();

    //  the world will be created when the user clicks on a button
    this->world = NULL;

}

Game::~Game()
{
    if (this->glContext) SDL_GL_DeleteContext(this->glContext);
    if (this->window) SDL_DestroyWindow(this->window);
}

void Game::NewGame(int level)
{
    //  level should be used to fetch the right bitmap
    //  this bitmap should later be sent to the world constructor
    int width, height, channels;
    this->levelData = LoadBMP("data/level/Level1Map.bmp", width, height, channels);
    if (levelData == NULL)
        throw std::runtime_error("Couldn't load level");
    
    std::cout << "Word loaded level: " << (unsigned int*)levelData << ", " << width << ", " << height << std::endl;
    this->world = new World(this->levelData, width, height);

    //  create player
    this->player = new Player(this->world->camera);
}


void Game::Update()
{

    if (this->keyboard.GetKey(1073741906).keypress) //  up
    {
        this->world->camera.position[0] += 0.01;

    }
    if (this->keyboard.GetKey(1073741905).keypress) //  down
    {
        this->world->camera.position[0] -= 0.01;
        
    }
    if (this->keyboard.GetKey(1073741904).keypress) //  right
    {
        
    }
    if (this->keyboard.GetKey(1073741903).keypress) //  left
    {
        
    }

    this->world->Update();
    //this->world->camera.position[1] += 0.001;
    this->player->Update(&this->keyboard);

    //  keydown and keyup is only valid for one frame, unlike the pressed state
    this->keyboard.ClearFrameEvents();

}

void Game::Draw()
{

    //  rendering here
        //  all 3d models is managed by the world
        if (this->world != NULL)
            this->world->Draw();

        this->player->Draw();

        //  draw UI here


    //  end

    SDL_GL_SwapWindow(this->window);

}


void Game::HandleEvent(const SDL_Event& event)
{
    switch (event.type)
    {
        case SDL_KEYDOWN:
            this->keyboard.HandleKeydown(event.key.keysym.sym);
            break;
        case SDL_KEYUP:
            this->keyboard.HandleKeyup(event.key.keysym.sym);
            break;
    }

}
