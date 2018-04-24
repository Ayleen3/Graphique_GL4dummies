#include <stdlib.h>
#include <GL4D/gl4du.h>
#include <GL4D/gl4dh.h>
#include <GL4D/gl4duw_SDL2.h>
#include "projetanim.h"
#include "projetaudio.h"

static void init(void);
static void quit(void);
static void resize(int w, int h);
static void keydown(int keycode);

static GL4DHanime _animations[] = {
  { 8000, fond_ecran, exemple_d_animation_00, transition_fondu}, //Damier
  { 2800, vs_ash, NULL, NULL}, //pikachu 
  { 500, ash, NULL, NULL},
  { 1200, pokeball, NULL, NULL},
  { 800, pokeball, exemple_d_animation_00, transition_fondu },
  { 200, exemple_d_animation_00, NULL, NULL},
  { 800, exemple_d_animation_00, pikachu, transition_fondu },
  { 1500, pikachu, NULL, NULL},
  { 2500, vs_blondie, NULL, NULL}, //charizard 
  { 500, cynthia, NULL, NULL},
  { 800, pokeball_2, NULL, NULL},
  { 800, pokeball_2, exemple_d_animation_00, transition_fondu },
  { 200, exemple_d_animation_00, NULL, NULL},
  { 1000, exemple_d_animation_00, charizard, transition_fondu },
  { 1500, charizard, NULL, NULL}, 
  { 1500, charizard, terrain_2, transition_fondu}, 
  { 9000, terrain_2, NULL, NULL},
  { 1500, terrain_2, terrain, transition_fondu}, 
  { 9000, terrain, NULL, NULL},
  { 1500, terrain, pokeball_tourne_f, transition_fondu},
  { 3000, pokeball_tourne_f, NULL, NULL},
  { 1900, pokeball_tourne_f, pokeball_tourne, transition_fondu}, 
  { 3000, pokeball_tourne, NULL, NULL}, 
  { 1900, pokeball_tourne, credits_fin, transition_fondu},
  { 8000, credits_fin, NULL, NULL},
  {    0, NULL, NULL, NULL } /* Toujours laisser à la fin */
};

static GLfloat _dim[] = {1023, 716}; //largeur, hauteur

int main(int argc, char ** argv) {
  if(!gl4duwCreateWindow(argc, argv, "GL4Dummies DemoHelper", 
			 SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
			 _dim[0], _dim[1],
			 SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN))
    return 1;
  init();
  atexit(quit);
  gl4duwResizeFunc(resize);
  gl4duwKeyDownFunc(keydown);
  gl4duwDisplayFunc(gl4dhDraw);

  ahInitAudio("Best.mp3");
  gl4duwMainLoop();
  return 0;
}

static void init(void) {
  glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
  gl4dhInit(_animations, _dim[0], _dim[1], animationsInit);
  resize(_dim[0], _dim[1]);
}

static void resize(int w, int h) {
  _dim[0] = w; _dim[1] = h;
  glViewport(0, 0, _dim[0], _dim[1]);
}

static void keydown(int keycode) {
  switch(keycode) {
  case SDLK_ESCAPE:
  case 'q':
    exit(0);
  default: break;
  }
}

static void quit(void) {
  gl4duClean(GL4DU_ALL);
}