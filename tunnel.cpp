#include <SDL_ttf.h>
#include <SDL_image.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <sstream>
//any 40*40 sprite for the ship should work
//change SDL_CreateWindow flag to SDL_WINDOW_SHOWN for 800x600 resolution
#undef main
using namespace std;
int main(int *argc,char *argv[])
{
    srand(time(NULL));
    int change=10;
    int changecount=16;
    int tunnelwidth=200;
    int startcount=0;
    int currenttime;
    int mouse_x,mouse_y;
    enum currentaction{main_menu,play,lose_screen};
    currentaction action=main_menu;
    SDL_Event input;
    bool quit=0;
    stringstream sstream;
    SDL_Color black{0,0,0};
    SDL_Color white{127,127,127};
    SDL_Color color_tunnel{255,255,255};
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    TTF_Font *font=TTF_OpenFont("opensans-bold.ttf",100);
    SDL_Window *window=SDL_CreateWindow("Tunnel",100,100,800,600,SDL_WINDOW_FULLSCREEN);
    SDL_Renderer *renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    SDL_Surface *s_ship=IMG_Load("spaceship.png");
    SDL_Surface *s_font_1=TTF_RenderText_Solid(font,"PRESS SPACE TO PLAY",white);
    SDL_Surface *s_go=TTF_RenderText_Solid(font,"GO",white);
    SDL_Surface *s_scoretext=TTF_RenderText_Solid(font,"-SCORE-",white);
    SDL_Surface *s_quit=TTF_RenderText_Solid(font,"PRESS ESCAPE TO EXIT",white);
    SDL_Surface *s_tunnel;
    SDL_Surface *s_score=TTF_RenderText_Solid(font,"0",white);
    SDL_SetColorKey(s_ship,SDL_TRUE,SDL_MapRGB(s_ship->format,255,255,255));
    SDL_SetWindowIcon(window,s_ship);
    SDL_Texture *t_font_1=SDL_CreateTextureFromSurface(renderer,s_font_1);
    SDL_Texture *t_tunnel;
    SDL_Texture *t_ship=SDL_CreateTextureFromSurface(renderer,s_ship);
    SDL_Texture *t_go=SDL_CreateTextureFromSurface(renderer,s_go);
    SDL_Texture *t_score=SDL_CreateTextureFromSurface(renderer,s_score);
    SDL_Texture *t_scoretext=SDL_CreateTextureFromSurface(renderer,s_scoretext);
    SDL_Texture *t_quit=SDL_CreateTextureFromSurface(renderer,s_quit);
    SDL_SetTextureAlphaMod(t_go,255);
    SDL_Rect rect_font_1{200,500,400,50};
    SDL_Rect rect_tunnel{300,100,200,70};
    SDL_Rect rect_player{30,300,40,40};
    SDL_Rect rect_go{360,50,80,100};
    SDL_Rect rect_scoretext{300,200,200,60};
    SDL_Rect rect_playerscore{350,300,100,40};
    SDL_Rect rect_quit{200,500,400,50};
    SDL_Rect rect_score[10];
    for(int i=0;i<10;i++)
    {
        rect_score[i].w=20*i+20;
        rect_score[i].y=550;
        rect_score[i].h=40;
        rect_score[i].x=770-20*i;
    }
    SDL_Rect validspace[80];
    validspace[0]={0,300,10,tunnelwidth};
    for(int i=1;i<80;i++)
    {
        validspace[i].w=10;
        validspace[i].x=10*i;
        validspace[i].h=tunnelwidth;
        validspace[i].y=validspace[i-1].y+=(rand()%(2*change+1)-change);
    }
    while(!quit)
    {
        currenttime=SDL_GetTicks();
        SDL_SetRenderDrawColor(renderer,20,55,10,255);
        SDL_RenderClear(renderer);
        if(action==main_menu)
        {
            color_tunnel.r+=(rand()%3-1);
            color_tunnel.g+=(rand()%3-1);
            color_tunnel.b+=(rand()%3-1);
            if(color_tunnel.r==255)
            {
                color_tunnel.r--;
            }
            else if(color_tunnel.r==0)
            {
                color_tunnel.r++;
            }
            if(color_tunnel.g==255)
            {
                color_tunnel.g--;
            }
            else if(color_tunnel.g==0)
            {
                color_tunnel.g++;
            }
            if(color_tunnel.b==255)
            {
                color_tunnel.b--;
            }
            else if(color_tunnel.b==0)
            {
                color_tunnel.b++;
            }
            SDL_RenderCopy(renderer,t_scoretext,NULL,&rect_scoretext);
            SDL_RenderCopy(renderer,t_score,NULL,&rect_playerscore);
            s_tunnel=TTF_RenderText_Solid(font,"TUNNEL",color_tunnel);
            SDL_RenderCopy(renderer,t_quit,NULL,&rect_quit);
            t_tunnel=SDL_CreateTextureFromSurface(renderer,s_tunnel);
            SDL_RenderCopy(renderer,t_font_1,NULL,&rect_font_1);
            SDL_RenderCopy(renderer,t_tunnel,NULL,&rect_tunnel);
            while(SDL_PollEvent(&input)!=0)
            {
                if(input.type==SDL_QUIT)
                {
                    quit=1;
                }
                else if(input.key.keysym.sym==SDLK_SPACE)
                {
                    action=play;
                }
                else if(input.key.keysym.sym==SDLK_ESCAPE)
                {
                    quit=1;
                }
            }
        }
        else if(action==play)
        {
            while(SDL_PollEvent(&input)!=0)
            {
                if(input.type==SDL_QUIT)
                {
                    quit=1;
                }
                else if(input.type==SDL_MOUSEMOTION)
                {
                    SDL_GetMouseState(&mouse_x,&mouse_y);
                    rect_player.y=mouse_y-20;
                    rect_player.x=mouse_x-20;
                    if(mouse_y>580)
                    {
                        rect_player.y=560;
                    }
                    if(mouse_x>780)
                    {
                        rect_player.x=760;
                    }
                }
                else if(input.key.keysym.sym==SDLK_ESCAPE)
                {
                    action=lose_screen;
                }
            }
            for(int i=0;i<79;i++)
            {
                color_tunnel.r+=(rand()%3-1);
                color_tunnel.g+=(rand()%3-1);
                color_tunnel.b+=(rand()%3-1);
                SDL_SetRenderDrawColor(renderer,color_tunnel.r,color_tunnel.g,color_tunnel.b,255);
                SDL_RenderFillRect(renderer,&validspace[i]);
                validspace[i].y=validspace[i+1].y;
            }
            change+=log(rand()%20000);
            validspace[79].y=validspace[78].y+=(rand()%(2*change+1)-change);
            tunnelwidth=200-log(2^changecount);
            if(validspace[79].y+tunnelwidth>600)
            {
                validspace[79].y=600-tunnelwidth;
            }
            else if(validspace[79].y<0)
            {
                validspace[79].y=0;
            }
            color_tunnel.r+=(rand()%3-1);
            color_tunnel.g+=(rand()%3-1);
            color_tunnel.b+=(rand()%3-1);
            SDL_SetRenderDrawColor(renderer,color_tunnel.r,color_tunnel.g,color_tunnel.b,255);
            SDL_RenderFillRect(renderer,&validspace[79]);
            SDL_RenderCopy(renderer,t_ship,NULL,&rect_player);
            changecount++;
            change=log(changecount);
            sstream.str("");
            sstream << changecount-16;
            s_score=TTF_RenderText_Solid(font,sstream.str().c_str(),white);
            t_score=SDL_CreateTextureFromSurface(renderer,s_score);
            while(1)
            {
                if(changecount>25)
                {
                    if(changecount>115)
                    {
                        if(changecount>1015)
                        {
                            if(changecount>10015)
                            {
                                if(changecount>100015)
                                {
                                    SDL_RenderCopy(renderer,t_score,NULL,&rect_score[5]);
                                    break;
                                }
                                SDL_RenderCopy(renderer,t_score,NULL,&rect_score[4]);
                                break;
                            }
                            SDL_RenderCopy(renderer,t_score,NULL,&rect_score[3]);
                            break;
                        }
                        SDL_RenderCopy(renderer,t_score,NULL,&rect_score[2]);
                        break;
                    }
                    SDL_RenderCopy(renderer,t_score,NULL,&rect_score[1]);
                    break;
                }
                SDL_RenderCopy(renderer,t_score,NULL,&rect_score[0]);
                break;
            }
            tunnelwidth=200-10*log(changecount);
            if(startcount<100)
            {
                if(startcount>35)
                {
                    SDL_SetTextureAlphaMod(t_go,396-4*startcount);
                }
                SDL_RenderCopy(renderer,t_go,NULL,&rect_go);
                startcount++;
            }
            else if(rect_player.y+5<validspace[(rect_player.x/10)-1].y || rect_player.y>validspace[(rect_player.x/10)-1].y+tunnelwidth || rect_player.y+5<validspace[(rect_player.x/10)].y || rect_player.y>validspace[(rect_player.x/10)].y+tunnelwidth)
            {
                action=lose_screen;
            }
        }
        else if(action==lose_screen)
        {
            startcount=0;
            SDL_ShowCursor(1);
            changecount=16;
            change=10;
            tunnelwidth=200;
            SDL_SetTextureAlphaMod(t_go,255);
            action=main_menu;
        }
        if(SDL_GetTicks()-currenttime<20-change)
        {
            SDL_Delay(20-change-SDL_GetTicks()+currenttime);
        }
        SDL_RenderPresent(renderer);
    }
    SDL_Quit();
    return 0;
}
