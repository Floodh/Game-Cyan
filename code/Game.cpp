#include "Game.hpp"

// #include "Player.hpp"

using namespace std;


Game::Game(int windowWidth, int windowHeight)
    : camera{this->mouse}
{
    this->gameState = GameState::Loading;

    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;


    // INITIALIZE SDL:
    if (SDL_Init(SDL_INIT_EVENTS) < 0) {
        throw(string("Failed to initialize SDL: ") + SDL_GetError());
    }
    if (SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        throw(string("Failed to initialize SDL Video: ") + SDL_GetError());
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
    if (0 == (this->window = SDL_CreateWindow("Cyan", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_OPENGL))) {
        throw(string("Failed to create window: ") + SDL_GetError());
    }
    // CREATE THE OPENGL CONTEXT AND MAKE IT CURRENT:
    if(NULL == (this->glContext = SDL_GL_CreateContext(this->window))) {
        throw(string("Failed to create OpenGL context"));
    }
    else SDL_GL_MakeCurrent(this->window, this->glContext);


    
    
    #if defined(_WIN32)
    // inti glad:
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        throw(string("Failed to initialize GLAD"));
    }

    //  Display Information
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

    //  garbage collection:
    //  corrently there will always be a somewhat small
    //  amount of memory that will be leaked when creating
    //  a new game, but we don't have time to do the proper destructors
    //  to fix that and its not noticeable by the user anyway
        // free(this->levelData);
        // free(this->mainMenu); 
        // free(this->world);
        // free(this->player);


    //  level should be used to fetch the right bitmap
    //  this bitmap should later be sent to the world constructor
    this->currentLevel = level;

    int width, height;

    string path = "data/level/Level" + to_string(level) +  "Map.bmp";
    cout << "Trying to load level " << path << endl;
    this->levelData = LoadBMP(path.c_str(), width, height);
    if (levelData == NULL)
        throw runtime_error("Couldn't load level");
    
    cout << "World loaded level: " << (unsigned int*)levelData << ", " << width << ", " << height << endl;
    this->world = new World(this->levelData, width, height, this->mouse, this->camera, this->backgroundColor, this->frameCount);

    if (level == 0)
    {
        gameState = GameState::MainMenu;
        this->mainMenu = new MainMenu(this->windowWidth, this->windowHeight, this->mouse);
        this->camera.SetPosition(30.0, 6.0, 12.0);
        this->camera.SetLookAt(20.0, 0.75, 24.0);
    }
    else
    {
        gameState = GameState::Playing;
        this->world->camera.SetPosition(0.0, 2.0, 0.0);
        this->world->camera.SetLookAt(3.0, 1.0, 3.0);
    }

    // for (int index = 0; index < width * height * 4; index +=4)
    //     std::cout << "levelData: " << (int)this->levelData[index] << " levelData: "<< (int)this->levelData[index+1] << " levelData: " << (int)this->levelData[index+2] << std::endl;


    // for (int i=0; i < width*height*4; i++)
    //     std::cout << (int)this->levelData[i] << std::endl;
    //  create player
    if (this->player == NULL)
        this->player = new Player(this->world->camera, this->levelData, width, height);
    else
        this->player->updateLevel(this->levelData, width, height);
    if (this->portal == NULL)
        this->portal = new Portal(5.0, 1.0, 5.0, *this->player, this->camera, this->backgroundColor);

    if (this->playerOther == NULL)
    {
        this->playerOther = new PlayerOther(this->world->camera, this->levelData, width, height);
        this->playerOther->setPosition(0.5, 0.5, 0.5);
    }


    this->world->terrain.land.player = this->player;

    switch (this->currentLevel)
    {
        case 1:
            this->NG1_Init();
            break;
        case 2:
            this->NG2_Init();
            break;
        case 3:
            this->NG3_Init();
            break;
        case 4:
            this->NG4_Init();
            break;   
        default:
            break;
    }

}


void Game::Update()
{

    switch (this->gameState)
    {
        case GameState::Loading:
            cout << "Warning: Is in loading state while trying to update!" << endl;
            break;
        case GameState::MainMenu:
        {
            GLfloat cameraX = 20.0 + (sin((GLfloat)frameCount / 250.0) * 10.0);   //  from 30 to 10
            this->camera.SetPosition(cameraX, 6.0, 12.0);
            //  handle UI here
            if (this->mainMenu != NULL)
            {
                this->mainMenu->Update();
                if (this->mainMenu->response == MainMenu_Load)
                {
                    this->NewGame(this->mainMenu->loadMap);
                }
                else if (this->mainMenu->response == MainMenu_Quit)
                    this->gameState = GameState::Quit;
            }
            break;
        }

        case GameState::Playing:
            if (this->world != NULL)
                this->world->Update();
            if (this->player != NULL)
                this->player->Update(&this->keyboard);
            if (this->portal != NULL)
                if (this->portal->IsPlayerInside())
                    cout << "Player inside portal" << endl;
            if (this->playerOther != NULL)
                this->playerOther->Update();
            switch (this->currentLevel)
            {
                case 1:
                    if (this->NG1_Update())
                        NewGame(++this->currentLevel);
                    break;
                case 2:
                    if (this->NG2_Update()) 
                        NewGame(++this->currentLevel);
                    break;
                case 3:
                    if (this->NG3_Update())
                        NewGame(++this->currentLevel);
                    break;
                case 4:
                    if (this->NG4_Update())
                        NewGame(1);
                    break;   
                default:
                    break;
            }                             
            break;

        default:
            throw runtime_error("Entered invalid gamestate in update function");
    }



    if (this->world != NULL)
        this->world->Update();

    //  keydown and keyup is only valid for one frame, unlike the pressed state
    camera.UpdateViewMatrix();
    this->keyboard.ClearFrameEvents();
    this->mouse.ClearFrameEvents();

}

void Game::Draw()
{
    // Clear the screen
    glClearColor(0.5f, 0.5f, 0.8f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (this->world != NULL)    //  this null check is redundant, but safty is important
        this->world->Draw();


    switch (this->gameState)
    {
        case GameState::Loading:
            cout << "Warning: Is in loading state while trying to update!" << endl;
            break;
        case GameState::MainMenu:
            if (this->mainMenu != NULL)
                this->mainMenu->Draw();
            break;
        case GameState::Playing:
            if (this->player != NULL)
                this->player->Draw();
            if (this->portal != NULL)
                this->portal->Draw();
            if (this->playerOther != NULL)
            {
                this->playerOther->Draw();
            }
                
            switch (this->currentLevel)
            {
                case 1:
                    this->NG1_Draw();
                    break;
                case 2:
                    this->NG2_Draw();
                    break;
                case 3:
                    this->NG3_Draw();
                    break;
                case 4:
                    this->NG4_Draw();
                    break;   
                default:
                    break;
            }

            break;
        default:
            throw runtime_error("Entered invalid gamestate in update function");
    }



    //  opengl rendering
    SDL_GL_SwapWindow(this->window);

    //  SDL_Renderer rendering


    frameCount++;
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
        case SDL_MOUSEMOTION:
            this->mouse.HandleMouseMotion(event.motion);
            break;
        case SDL_MOUSEBUTTONDOWN:
            this->mouse.HandleMouseButton(event.button);
            break;
        case SDL_MOUSEBUTTONUP:
            this->mouse.HandleMouseButton(event.button);
            break;
        default:
            break;
    }

}
