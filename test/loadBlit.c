/*
 * 高效加载Blit并显示
 * Blit -->  内存中图像的位块传输，指的是将某一表面的全部或部分图像复制到另一表面上
 * 教程链接：http://kelvmiao.info/sdl-tutorial-cn/lessons/lesson02/index.html
 */

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

///////////////////////////////////////////////////////////////
//目前基本所有图形化的操作系统默认都采用32位色（即“真彩色“）
//显示整个视窗系统，即每一像素用32位表示，
//其中分别是红色、绿色、蓝色和Alpha混合（即RGBA），各占8位。
///////////////////////////////////////////////////////////////
#define SCREEN_BPP 32  // 位/像素

SDL_Surface* load_image(const char* filename);
SDL_Surface* load_image_pro(const char* filename);
void apply_surface(int x , int y , SDL_Surface* source , SDL_Surface* destination);

int main()
{
    SDL_Surface *message = NULL;
    SDL_Surface *background = NULL;
    SDL_Surface *screen = NULL;

    if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
        perror("Error: SDL_Init error\n");
        return -1;
    }

    // 设置窗口 ， SDL——SDL_SWSURFACE -> 系统内存
    screen = SDL_SetVideoMode(SCREEN_WIDTH , SCREEN_HEIGHT , SCREEN_BPP , SDL_SWSURFACE);
    if ( !screen ){
        perror("Error: SDL_SetVideoMode error\n");
        return -2;
    }

    //设置窗口标题
    SDL_WM_SetCaption("hello world" , NULL);
    message = load_image_pro("/home/yunzhongke/hello.bmp");
    background = load_image_pro("/home/yunzhongke/beijing.jpg");
    
    apply_surface(0 , 0 , background , screen);
    apply_surface(320 , 0 , background , screen);
    apply_surface(0 , 240 , background , screen);
    apply_surface(320 ,240 , background , screen);
    apply_surface(180 ,140 , message , screen);


    SDL_Delay(2000);

    SDL_FreeSurface(message);
    SDL_FreeSurface(background);

    SDL_Quit();
    return 0;
}

SDL_Surface* load_image(const char* filename)
{
    //用于保存临时加载的图片
    SDL_Surface* loadedImage = NULL;
    //用于保存优化后的图片
    SDL_Surface* optimizedImage = NULL;

    loadedImage = SDL_LoadBMP(filename);
    if(loadedImage){
        // 将表面转换为显示格式
       optimizedImage = SDL_DisplayFormat(loadedImage);
    }else{
        perror("Error : loadedImage is null\n");
        return NULL;
    }

    SDL_FreeSurface(loadedImage); 
    return optimizedImage;
}

SDL_Surface* load_image_pro(const char* filename)
{
    SDL_Surface *loadedImage = NULL;
    SDL_Surface *optimizedImage = NULL;
    loadedImage = IMG_Load(filename);
    if(loadedImage){
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
    //将图像应用一窗口上,也就是复制
    SDL_BlitSurface(source , NULL , destination , &offset);
    
    if (-1 == SDL_Flip(destination)){
        perror("Error: SDL_Flip error\n");
        return ;
    }

    SDL_Delay(1500);
}
