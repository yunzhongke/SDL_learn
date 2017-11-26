/*
 * 事件的驱动
 * 链接：http://kelvmiao.info/sdl-tutorial-cn/lessons/lesson04/index.html
 */

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mouse.h>

#define SCREEN_WITH 640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP 32

SDL_Surface *image = NULL;
SDL_Surface *screen = NULL;

//事件结构体
SDL_Event event;

SDL_Surface* load_image(const char* filename)
{
    SDL_Surface *loadedImage = NULL;
    SDL_Surface *optimizedImage = NULL;

    loadedImage = IMG_Load(filename);
    if (loadedImage){
        optimizedImage = SDL_DisplayFormat(loadedImage);
        SDL_FreeSurface(loadedImage);
    }

    return optimizedImage;
}

void apply_surface(int x , int y , SDL_Surface* source , SDL_Surface* destination)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;

    SDL_BlitSurface(source , NULL , destination , &offset);
}

int init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
        perror("Error: SDL_Init\n");
        return 0;
    }

    screen = SDL_SetVideoMode(SCREEN_WITH , SCREEN_HEIGHT , SCREEN_BPP , SDL_SWSURFACE);
    if (!screen){
        perror("Error: SDL_SetVideoMode error \nn");
        return 0;
    }

    SDL_WM_SetCaption("Event test" , NULL);
    return 1;
}

int load_files()
{
    image = load_image("/home/yunzhongke/meinv.jpg");
    if (!image)
        return 0;

    return 1;
}

void clean_up()
{
    SDL_FreeSurface(image);
    SDL_FreeSurface(screen);
    SDL_Quit();
}

int main(int argc , char** args)
{
    int quit = 0;

    if (!init()){
        return -1;
    }

    if (!load_files())
        return -2;
    apply_surface(0 , 0 , image , screen);
    if (SDL_Flip(screen) == -1)
        return -3;
    int x = 0 , y = 0;
    while(!quit){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                quit = 1;
            }
            if (event.type == SDL_MOUSEMOTION){
                printf("mouse event\n");
                
            }
        }
    }
    clean_up();
    return 0;
}
