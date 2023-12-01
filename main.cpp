#include "SDL2/SDL.h"
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>
#include <cstddef>
#include <stdio.h>
#include <string>
#define SCREEN_WIDTH 640
#define SCREEN_HEIGTH 480
 
bool init();
bool loadMedia();
void close();

enum KeyPressSurface{
  KEY_PRESS_SURFACE_DEFAULT,
  KEY_PRESS_SURFACE_UP,
  KEY_PRESS_SURFACE_DOWN,
  KEY_PRESS_SURFACE_LEFT,
  KEY_PRESS_SURFACE_RIGHT,
  KEY_PRESS_SURFACE_TOTAL
};

//variavles for rock, paper, scissor count
int rock_count;
int paper_count;
int scissors_count;


bool quit = false;

SDL_Event e;
//The window we'll be rendering to
SDL_Window* gwindow = NULL;
    
//The surface contained by the window
SDL_Surface* gsurface = NULL;

SDL_Surface* gKeyCurrentSurface[KEY_PRESS_SURFACE_TOTAL];

//The image we will load and show on the screen
SDL_Surface* CurrentSurface = NULL;

SDL_Surface* loadSurface(std::string path);

//rock, paper or scissors object
class RPSObject{
  public:
    //constructor, update and render
    RPSObject(int x, int y);
    void update();
    void render(SDL_Renderer* renderer);   
    void move();
    static const int MaxVel = 10;
  private:
    //position of object
    int PosX, PosY;
    //velocity of object
    int VelX, VelY;
};
RPSObject::RPSObject(int x, int y){
  int PosX = x;
  int PosY = y;
  int VelX = 0;
  int VelY = 0;
}



int main(int argc, char* args[]) {
  if(!init()){
    printf("Failed to initialize!\n");
  }
  else{
    if(!loadMedia()){
      printf("Failed to load media!\n");
    }
    else{
      SDL_BlitSurface(CurrentSurface, NULL, gsurface, NULL);
      SDL_UpdateWindowSurface( gwindow );
      SDL_Event e;
      bool quit = false;
      while(!quit){
        while( SDL_PollEvent( &e ) ){
          if( e.type == SDL_QUIT ){
            quit = true; 
          } 
        } 
      }
      close();
    }
  }
    return 0;
}




bool init(){
  bool success = true;

  if(SDL_Init(SDL_INIT_VIDEO) < 0){
    printf("SDL could not initialize, error: %s", SDL_GetError());
    success = false;
  }
  else{
    gwindow = SDL_CreateWindow("RockPaperScissors Simulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGTH,SDL_WINDOW_SHOWN);
    if(gwindow == NULL){
      printf("Window could not be created, error: %s", SDL_GetError());
      success = false;
    }
    else{
      gsurface = SDL_GetWindowSurface(gwindow);

    }
  }
  return success;
}



SDL_Surface* loadSurface(std::string path){
  SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
  if (loadedSurface == NULL) {
    printf("The Surfaces could not be loaded, file path: %s, error: %s", path.c_str(), SDL_GetError());
  }
  return loadedSurface;
}


bool loadMedia(){
  bool success = true;
  CurrentSurface = SDL_LoadBMP("image.bmp");
  if (CurrentSurface == NULL){
    printf("Unable to load image, error: %s", SDL_GetError());
    success = false;
  }
  return success;
}



void close(){
    //Deallocate surface
    SDL_FreeSurface( CurrentSurface );
    CurrentSurface = NULL;

    //Destroy window
    SDL_DestroyWindow( gwindow );
    CurrentSurface = NULL;

    //Quit SDL subsystems
    SDL_Quit();

}
