/*
 * 显示一张bmp图片 
 *
 */ 
#include <stdio.h>
#include <SDL/SDL.h>

int main(int argc , char *args[])
{
    // SDL_Surface --> 图形表面结构
    SDL_Surface* hello = NULL;
    SDL_Surface* scree = NULL;
    
    //初始化SDL库
    SDL_Init(SDL_INIT_EVERYTHING);

    //设置具有指定宽度，高度和每像素位数的视频模式
    scree = SDL_SetVideoMode(640 , 480 , 32 , SDL_SWSURFACE);

    //加载bmp图片
    hello = SDL_LoadBMP("/home/yunzhongke/meinv.bmp"); 
    if (!hello){
        perror("hello is null\n");
    }

    //将图像应用一窗口上
    SDL_BlitSurface(hello , NULL , scree , NULL);

    //更新窗口，才能看到图像
    SDL_Flip(scree);

    //延时2秒
    SDL_Delay(2000);

    //释放加载的图像
    SDL_FreeSurface(hello);

    //清除所有SDL初始化的子系统
    SDL_Quit();
    return 0;
}
