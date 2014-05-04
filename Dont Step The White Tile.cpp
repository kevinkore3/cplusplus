#include <SDL_ttf.h>
#include <ctime>
#include <cstdlib>
#include <sstream>
using namespace std;
//incomplete dont step the white tile clone by Kevin Liu
//Created on May 3, 2014
int main(int argc,char *argv[])
{
    enum currentaction
    {
        main_menu,long_run,longrun_lose_screen,options,time_attack,timeattack_lose_screen,timeattack_win_screen
    };
    currentaction action;
    action=main_menu;
    enum currentcontrols
    {
        jkl,asdf,one234,nine0
    };
    currentcontrols option_controls;
    option_controls=jkl;
    srand(time(NULL));
    int x,y;
    int timeleft;
    int totaltime;
    int timecount;
    int currenttile=0;
    bool board[10000][4];
    SDL_Rect time_rect{260,200,50,20};
    SDL_Color black{0,0,0};
    SDL_Color white{255,255,255};
    SDL_Event input;
    bool quit_long_run=0;
    bool quit_time_attack=0;
    bool quit=0;
    bool longrun_down=0;
    bool exit_down=0;
    bool options_down=0;
    bool timeattack_down=0;
    bool long_run_loaded=0;
    bool timeattack_loaded=0;
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    TTF_Font *font=TTF_OpenFont("OpenSans-Bold.ttf",100);
    SDL_Surface *surface_timeleft;
    SDL_Texture *texture_timeleft;
    stringstream time;
    stringstream ss_score;
    SDL_Window *window=SDL_CreateWindow("TILES CLONE",200,200,320,240,SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    //main menu
    SDL_Rect mainmenublack1{60,80,100,60};
    SDL_Rect mainmenublack2{160,140,100,60};
    SDL_Rect mainmenutimeattack{60,140,100,60};
    SDL_Rect mainmenuoptions{160,80,100,60};
    SDL_Surface *s_mainmenutitle=TTF_RenderText_Solid(font,"MAIN MENU",black);
    SDL_Rect rect_mainmenutitle{80,20,160,40};
    SDL_Texture *t_mainmenutitle=SDL_CreateTextureFromSurface(renderer,s_mainmenutitle);
    SDL_Surface *s_mainmenulongrun=TTF_RenderText_Solid(font,"LONG RUN",white);
    SDL_Rect rect_longrun{60,100,100,20};
    SDL_Texture *t_mainmenulongrun=SDL_CreateTextureFromSurface(renderer,s_mainmenulongrun);
    SDL_Surface *s_mainmenuquit=TTF_RenderText_Solid(font,"EXIT",white);
    SDL_Rect rect_quit{185,160,50,20};
    SDL_Texture *t_mainmenuquit=SDL_CreateTextureFromSurface(renderer,s_mainmenuquit);
    SDL_Surface *s_mainmenuoptions=TTF_RenderText_Solid(font,"OPTIONS",black);
    SDL_Texture *t_mainmenuoptions=SDL_CreateTextureFromSurface(renderer,s_mainmenuoptions);
    SDL_Rect rect_mainmenuoptions{180,100,60,20};
    SDL_Surface *s_timeattack=TTF_RenderText_Solid(font,"TIME ATTACK",black);
    SDL_Rect rect_timeattack{60,160,100,20};
    SDL_Texture *t_mainmenutimeattack=SDL_CreateTextureFromSurface(renderer,s_timeattack);
    //long run lose screen
    SDL_Rect rect_longrunlose{80,20,160,40};
    SDL_Surface *s_longrunlose=TTF_RenderText_Solid(font,"YOU LOST",black);
    SDL_Texture *t_longrunlose=SDL_CreateTextureFromSurface(renderer,s_longrunlose);
    SDL_Rect rect_longrunscore{100,80,120,40};
    SDL_Surface *s_longrunscore=TTF_RenderText_Solid(font,"-SCORE-",black);
    SDL_Texture *t_longrunscore=SDL_CreateTextureFromSurface(renderer,s_longrunscore);
    SDL_Rect rect_longrunplayerscore{140,140,40,40};
    SDL_Surface *s_longrunplayerscore;
    SDL_Texture *t_longrunplayerscore;
    //time attack
    SDL_Rect rect_timeattackscore{130,140,60,40};
    SDL_Surface *s_timeattackwin=TTF_RenderText_Solid(font,"YOU WIN",black);
    SDL_Texture *t_timeattackwin=SDL_CreateTextureFromSurface(renderer,s_timeattackwin);
    SDL_Rect rect_timeelapsed{60,80,200,40};
    SDL_Surface *s_timeelapsed=TTF_RenderText_Solid(font,"-TIME ELAPSED-",black);
    SDL_Texture *t_timeelapsed=SDL_CreateTextureFromSurface(renderer,s_timeelapsed);
    //options
    SDL_Rect rect_options{95,20,130,40};
    SDL_Surface *s_options=TTF_RenderText_Solid(font,"OPTIONS",black);
    SDL_Texture *t_options=SDL_CreateTextureFromSurface(renderer,s_options);
    SDL_Rect rect_controls{10,60,170,40};
    SDL_Surface *s_controls=TTF_RenderText_Solid(font,"< CONTROLS:",black);
    SDL_Texture *t_controls=SDL_CreateTextureFromSurface(renderer,s_controls);
    SDL_Rect rect_controlkeys{200,60,110,40};
    SDL_Surface *s_1234=TTF_RenderText_Solid(font,"1 2 3 4 >",black);
    SDL_Texture *t_1234=SDL_CreateTextureFromSurface(renderer,s_1234);
    SDL_Surface *s_jkl=TTF_RenderText_Solid(font,"J K L ; >",black);
    SDL_Texture *t_jkl=SDL_CreateTextureFromSurface(renderer,s_jkl);
    SDL_Surface *s_asdf=TTF_RenderText_Solid(font,"A S D F >",black);
    SDL_Texture *t_asdf=SDL_CreateTextureFromSurface(renderer,s_asdf);
    SDL_Surface *s_90=TTF_RenderText_Solid(font,"9 0 - = >",black);
    SDL_Texture *t_90=SDL_CreateTextureFromSurface(renderer,s_90);
    for(int i=0;i<10000;i++)
    {
        for(int z=0;z<4;z++)
        {
            board[i][z]=0;
        }
    }
    while(!quit)
    {
        while(action==options)
        {
            while(SDL_PollEvent(&input)!=0)
            {
                if(input.type==SDL_QUIT)
                {
                    quit=1;
                }
                if(input.type==SDL_MOUSEMOTION)
                switch(input.key.keysym.sym)
                {
                case SDL_QUIT:
                    quit=1;
                    break;
                case SDLK_RIGHT:
                    switch(option_controls)
                    {
                    case jkl:
                        option_controls=asdf;
                        break;
                    case asdf:
                        option_controls=one234;
                        break;
                    case one234:
                        option_controls=nine0;
                        break;
                    case nine0:
                        option_controls=jkl;
                        break;
                    }
                    break;
                    case SDLK_LEFT:
                    switch(option_controls)
                    {
                    case jkl:
                        option_controls=nine0;
                        break;
                    case asdf:
                        option_controls=jkl;
                        break;
                    case one234:
                        option_controls=asdf;
                        break;
                    case nine0:
                        option_controls=one234;
                        break;
                    }
                    break;
                }
            }
            SDL_SetRenderDrawColor(renderer,255,255,255,255);
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer,t_options,NULL,&rect_options);
            SDL_RenderCopy(renderer,t_controls,NULL,&rect_controls);
            switch(option_controls)
            {
            case one234:
                SDL_RenderCopy(renderer,t_1234,NULL,&rect_controlkeys);
                break;
            case jkl:
                SDL_RenderCopy(renderer,t_jkl,NULL,&rect_controlkeys);
                break;
            case asdf:
                SDL_RenderCopy(renderer,t_asdf,NULL,&rect_controlkeys);
                break;
            case nine0:
                SDL_RenderCopy(renderer,t_90,NULL,&rect_controlkeys);
                break;
            }
            SDL_RenderPresent(renderer);
            if(quit)
            {
                break;
            }
        }
        while(action==main_menu)
        {
            while(SDL_PollEvent(&input)!=0)
            {
                if(input.key.keysym.sym==SDLK_ESCAPE)
                {
                    quit=1;
                }
                switch(input.type)
                {
                case SDL_QUIT:
                    quit=1;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&x,&y);
                    if(x>60 && x<160 && y>80 && y<140)
                    {
                        SDL_SetRenderDrawColor(renderer,20,70,40,255);
                        SDL_RenderFillRect(renderer,&mainmenublack1);
                        SDL_RenderCopy(renderer,t_mainmenulongrun,NULL,&rect_longrun);
                        longrun_down=1;
                    }
                    else if(x>160 && x<260 && y>140 && y<200)
                    {
                        SDL_SetRenderDrawColor(renderer,20,70,40,255);
                        SDL_RenderFillRect(renderer,&mainmenublack2);
                        SDL_RenderCopy(renderer,t_mainmenuquit,NULL,&rect_quit);
                        exit_down=1;
                    }
                    else if(x>60 && x<160 && y>140 && y<200)
                    {
                        SDL_SetRenderDrawColor(renderer,235,185,215,255);
                        SDL_RenderFillRect(renderer,&mainmenutimeattack);
                        SDL_RenderCopy(renderer,t_mainmenutimeattack,NULL,&rect_timeattack);
                        timeattack_down=1;
                    }
                    else if(x>160 && x<260 && y>80 && y<140)
                    {
                        SDL_SetRenderDrawColor(renderer,235,185,215,255);
                        SDL_RenderFillRect(renderer,&mainmenuoptions);
                        SDL_RenderCopy(renderer,t_mainmenuoptions,NULL,&rect_mainmenuoptions);
                        options_down=1;
                    }
                    SDL_RenderPresent(renderer);
                    break;
                case SDL_MOUSEBUTTONUP:
                    if(x>60 && x<160 && y>80 && y<140 && longrun_down)
                    {
                        long_run_loaded=0;
                        action=long_run;
                    }
                    else if(x>160 && x<260 && y>140 && y<200 && exit_down)
                    {
                        quit=1;
                    }
                    else if(x>60 && x<160 && y>140 && y<200 && timeattack_down)
                    {
                        action=time_attack;
                    }
                    else if(x>160 && x<260 && y>80 && y<140 && options_down)
                    {
                        action=options;
                    }
                default:
                {
                    SDL_SetRenderDrawColor(renderer,255,255,255,255);
                    SDL_RenderClear(renderer);
                    SDL_SetRenderDrawColor(renderer,0,0,0,255);
                    SDL_RenderFillRect(renderer,&mainmenublack1);
                    SDL_RenderFillRect(renderer,&mainmenublack2);
                    SDL_RenderCopy(renderer,t_mainmenutitle,NULL,&rect_mainmenutitle);
                    SDL_RenderCopy(renderer,t_mainmenulongrun,NULL,&rect_longrun);
                    SDL_RenderCopy(renderer,t_mainmenuquit,NULL,&rect_quit);
                    SDL_RenderCopy(renderer,t_mainmenutimeattack,NULL,&rect_timeattack);
                    SDL_RenderCopy(renderer,t_mainmenuoptions,NULL,&rect_mainmenuoptions);
                    SDL_RenderPresent(renderer);
                    longrun_down=0;
                    exit_down=0;
                    timeattack_down=0;
                    options_down=0;
                }
                break;
                }
            }
            if(quit)
            {
                break;
            }
            SDL_Delay(10);
        }
        if(action==longrun_lose_screen)
        {
            SDL_SetRenderDrawColor(renderer,255,255,255,255);
            SDL_RenderClear(renderer);
            ss_score.str("");
            ss_score << currenttile;
            SDL_RenderCopy(renderer,t_longrunlose,NULL,&rect_longrunlose);
            SDL_RenderCopy(renderer,t_longrunscore,NULL,&rect_longrunscore);
            s_longrunplayerscore=TTF_RenderText_Solid(font,ss_score.str().c_str(),black);
            t_longrunplayerscore=SDL_CreateTextureFromSurface(renderer,s_longrunplayerscore);
            SDL_RenderCopy(renderer,t_longrunplayerscore,NULL,&rect_longrunplayerscore);
            SDL_RenderPresent(renderer);
            long_run_loaded=0;
            for(int i=0;i<200;i++)
            {
                while(SDL_PollEvent(&input)!=0)
                {
                    if(input.type==SDL_QUIT)
                    {
                        quit=1;
                    }
                }
                if(quit)
                {
                    break;
                }
                SDL_Delay(10);
            }
            action=main_menu;
        }
        while(action==long_run)
        {
            if(!long_run_loaded)
            {
                for(int i=0;i<(currenttile+10);i++)
                {
                    for(int z=0;z<4;z++)
                    {
                        board[i][z]=0;
                    }
                }
                long_run_loaded=1;
                currenttile=0;
                for(int i=0;i<10;i++)
                    {
                        switch(rand()%4)
                        {
                        case 0:
                            board[i][0]=1;
                            break;
                        case 1:
                            board[i][1]=1;
                            break;
                        case 2:
                            board[i][2]=1;
                            break;
                        case 3:
                            board[i][3]=1;
                        }
                    }
                timeleft=11000+SDL_GetTicks();
            }
            if(board[currenttile+10][0]==0 && board[currenttile+10][1]==0 && board[currenttile+10][2]==0 && board[currenttile+10][3]==0)
            {
                switch(rand()%4)
                {
                case 0:
                    board[currenttile+10][0]=1;
                    break;
                case 1:
                    board[currenttile+10][1]=1;
                    break;
                case 2:
                    board[currenttile+10][2]=1;
                    break;
                case 3:
                    board[currenttile+10][3]=1;
                    break;
                }
            }
            while(SDL_PollEvent(&input)!=0)
            {
                if(input.type==SDL_QUIT)
                {
                    quit=1;
                    quit_long_run=1;
                }
                if(input.type==SDL_KEYDOWN)
                {
                    switch(input.key.keysym.sym)
                    {
                    case SDLK_a:
                        if(board[currenttile][0]==1)
                        {
                            currenttile++;
                        }
                        else
                        {
                            action=longrun_lose_screen;
                        }
                        break;
                    case SDLK_s:
                        if(board[currenttile][1]==1)
                        {
                            currenttile++;
                        }
                        else
                        {
                            action=longrun_lose_screen;
                        }
                        break;
                    case SDLK_d:
                        if(board[currenttile][2]==1)
                        {
                            currenttile++;
                        }
                        else
                        {
                            action=longrun_lose_screen;
                        }
                        break;
                    case SDLK_f:
                        if(board[currenttile][3]==1)
                        {
                            currenttile++;
                        }
                        else
                        {
                            action=longrun_lose_screen;
                        }
                        break;
                    case SDLK_ESCAPE:
                        action=main_menu;
                        break;
                    }
                }
            }
            SDL_SetRenderDrawColor(renderer,255,255,255,255);
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer,0,0,0,255);
            for(int i=0;i<4;i++)
            {
                for(int z=0;z<4;z++)
                {
                    SDL_Rect currentrect{80+40*i,180-(60*z),40,60};
                    if(board[currenttile+z][i]==1)
                    {

                        SDL_SetRenderDrawColor(renderer,0,0,0,255);
                        SDL_RenderFillRect(renderer,&currentrect);
                    }
                    else
                    {
                        SDL_SetRenderDrawColor(renderer,255,255,255,255);
                        SDL_RenderFillRect(renderer,&currentrect);
                    }
                }
            }
            SDL_SetRenderDrawColor(renderer,0,0,0,255);
            SDL_RenderDrawLine(renderer,80,0,80,240);
            SDL_RenderDrawLine(renderer,120,0,120,240);
            SDL_RenderDrawLine(renderer,160,0,160,240);
            SDL_RenderDrawLine(renderer,200,0,200,240);
            SDL_RenderDrawLine(renderer,240,0,240,240);
            SDL_RenderDrawLine(renderer,80,60,240,60);
            SDL_RenderDrawLine(renderer,80,120,240,120);
            SDL_RenderDrawLine(renderer,80,180,240,180);
            if((timeleft-SDL_GetTicks())>10000000)
            {
                action=longrun_lose_screen;
                quit_long_run=1;
            }
            if(currenttile%50==0 && currenttile!=0)
            {
                timeleft+=10000;
            }
            time.str("");
            time << timeleft-SDL_GetTicks();
            surface_timeleft=TTF_RenderText_Solid(font,time.str().c_str(),black);
            texture_timeleft=SDL_CreateTextureFromSurface(renderer,surface_timeleft);
            SDL_RenderCopy(renderer,texture_timeleft,NULL,&time_rect);
            if(quit_long_run==1 || action!=long_run)
            {
                break;
            }
            SDL_RenderPresent(renderer);
            SDL_Delay(10);
        }
        while(action==time_attack)
        {
            if(!timeattack_loaded)
            {
                for(int i=0;i<(currenttile+10);i++)
                {
                    for(int z=0;z<4;z++)
                    {
                        board[i][z]=0;
                    }
                }
                timeattack_loaded=1;
                currenttile=0;
                for(int i=0;i<10;i++)
                    {
                        switch(rand()%4)
                        {
                        case 0:
                            board[i][0]=1;
                            break;
                        case 1:
                            board[i][1]=1;
                            break;
                        case 2:
                            board[i][2]=1;
                            break;
                        case 3:
                            board[i][3]=1;
                        }
                    }
                totaltime=SDL_GetTicks();
            }
            if(board[currenttile+10][0]==0 && board[currenttile+10][1]==0 && board[currenttile+10][2]==0 && board[currenttile+10][3]==0)
            {
                switch(rand()%4)
                {
                case 0:
                    board[currenttile+10][0]=1;
                    break;
                case 1:
                    board[currenttile+10][1]=1;
                    break;
                case 2:
                    board[currenttile+10][2]=1;
                    break;
                case 3:
                    board[currenttile+10][3]=1;
                    break;
                }
            }
            while(SDL_PollEvent(&input)!=0)
            {
                if(input.type==SDL_QUIT)
                {
                    quit=1;
                    quit_time_attack=1;
                }
                if(input.type==SDL_KEYDOWN)
                {
                    switch(input.key.keysym.sym)
                    {
                    case SDLK_a:
                        if(board[currenttile][0]==1)
                        {
                            currenttile++;
                        }
                        else
                        {
                            action=timeattack_lose_screen;
                        }
                        break;
                    case SDLK_s:
                        if(board[currenttile][1]==1)
                        {
                            currenttile++;
                        }
                        else
                        {
                            action=timeattack_lose_screen;
                        }
                        break;
                    case SDLK_d:
                        if(board[currenttile][2]==1)
                        {
                            currenttile++;
                        }
                        else
                        {
                            action=timeattack_lose_screen;
                        }
                        break;
                    case SDLK_f:
                        if(board[currenttile][3]==1)
                        {
                            currenttile++;
                        }
                        else
                        {
                            action=timeattack_lose_screen;
                        }
                        break;
                    case SDLK_ESCAPE:
                        action=main_menu;
                        break;
                    }
                }
            }
            SDL_SetRenderDrawColor(renderer,255,255,255,255);
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer,0,0,0,255);
            for(int i=0;i<4;i++)
            {
                for(int z=0;z<4;z++)
                {
                    SDL_Rect currentrect{80+40*i,180-(60*z),40,60};
                    if(board[currenttile+z][i]==1)
                    {

                        SDL_SetRenderDrawColor(renderer,0,0,0,255);
                        SDL_RenderFillRect(renderer,&currentrect);
                    }
                    else
                    {
                        SDL_SetRenderDrawColor(renderer,255,255,255,255);
                        SDL_RenderFillRect(renderer,&currentrect);
                    }
                }
            }
            SDL_SetRenderDrawColor(renderer,0,0,0,255);
            SDL_RenderDrawLine(renderer,80,0,80,240);
            SDL_RenderDrawLine(renderer,120,0,120,240);
            SDL_RenderDrawLine(renderer,160,0,160,240);
            SDL_RenderDrawLine(renderer,200,0,200,240);
            SDL_RenderDrawLine(renderer,240,0,240,240);
            SDL_RenderDrawLine(renderer,80,60,240,60);
            SDL_RenderDrawLine(renderer,80,120,240,120);
            SDL_RenderDrawLine(renderer,80,180,240,180);
            if(currenttile==50)
            {
                action=timeattack_win_screen;
            }
            time.str("");
            time << SDL_GetTicks()-totaltime;
            surface_timeleft=TTF_RenderText_Solid(font,time.str().c_str(),black);
            texture_timeleft=SDL_CreateTextureFromSurface(renderer,surface_timeleft);
            SDL_RenderCopy(renderer,texture_timeleft,NULL,&time_rect);
            if(quit_time_attack==1 || action!=time_attack)
            {
                break;
            }
            SDL_RenderPresent(renderer);
            SDL_Delay(10);
        }
        if(action==timeattack_lose_screen)
        {
            SDL_SetRenderDrawColor(renderer,255,255,255,255);
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer,t_longrunlose,NULL,&rect_longrunlose);
            SDL_RenderPresent(renderer);
            timeattack_loaded=0;
            for(int i=0;i<200;i++)
            {
                while(SDL_PollEvent(&input)!=0)
                {
                    if(input.type==SDL_QUIT)
                        quit=1;
                }
                if(quit)
                {
                    break;
                }
                SDL_Delay(10);
            }
            action=main_menu;
        }
        if(action==timeattack_win_screen)
        {
            SDL_SetRenderDrawColor(renderer,255,255,255,255);
            SDL_RenderClear(renderer);
            ss_score.str("");
            ss_score << SDL_GetTicks()-totaltime;
            s_longrunplayerscore=TTF_RenderText_Solid(font,ss_score.str().c_str(),black);
            t_longrunplayerscore=SDL_CreateTextureFromSurface(renderer,s_longrunplayerscore);
            SDL_RenderCopy(renderer,t_timeattackwin,NULL,&rect_longrunlose);
            SDL_RenderCopy(renderer,t_timeelapsed,NULL,&rect_timeelapsed);
            SDL_RenderCopy(renderer,t_longrunplayerscore,NULL,&rect_timeattackscore);
            SDL_RenderPresent(renderer);
            timeattack_loaded=0;
            for(int i=0;i<200;i++)
            {
                while(SDL_PollEvent(&input)!=0)
                {
                    if(input.type==SDL_QUIT)
                        quit=1;
                }
                if(quit)
                {
                    break;
                }
                SDL_Delay(10);
            }
            action=main_menu;
        }
    }
    SDL_Quit();
    return 0;
}
