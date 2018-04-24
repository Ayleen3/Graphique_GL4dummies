#include <GL4D/gl4dh.h>
#include "projetaudio.h"
#include <assert.h>
#include <stdlib.h>
#include <GL4D/gl4dg.h>
#include <SDL_image.h>
#include "projetanim.h"


static GLuint _quadId=0;

void exemple_d_animation_00(int state) {
  int l, i;
  Uint16 * s;
  static GLfloat c[4] = {0, 0, 0, 0};
  switch(state) {
  case GL4DH_INIT:
    return;
  case GL4DH_FREE:
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    s = (Uint16 *)ahGetAudioStream();
    l = ahGetAudioStreamLength();
    if(l >= 8)
      for(i = 0; i < 4; i++)
  c[i] = s[i] / ((1 << 16) - 1.0);
    return;
  default: 
    glClearColor(c[0], c[1], c[2], c[3]);
    glClear(GL_COLOR_BUFFER_BIT);
    return;
  }
}


static void copyFromSurface(SDL_Surface * s, int x0, int y0) {
  Uint32 * p, coul, ocoul;
  Uint8 rmix, gmix, bmix;
  double f1, f2;
  int x, y, maxx, maxy;
  assert(s->format->BytesPerPixel == 4);
  p = s->pixels;
  maxx = MIN(x0 + s->w, gl4dpGetWidth());
  maxy = MIN(y0 + s->h, gl4dpGetHeight());
  for(y = y0; y < maxy; y++) {
    for(x = x0; x < maxx; x++) {
      ocoul = gl4dpGetPixel(x, y);
      coul = p[(s->h - 1 - (y - y0)) * s->w + x - x0];
      f1 = ALPHA(coul) / 255.0; f2 = 1.0 - f1;
      rmix = f1 *   RED(coul) + f2 *   RED(ocoul);
      gmix = f1 * GREEN(coul) + f2 * GREEN(ocoul);
      bmix = f1 *  BLUE(coul) + f2 *  BLUE(ocoul);
      gl4dpSetColor(RGB(rmix, gmix, bmix));
      gl4dpPutPixel(x, y);
    }
  }
}


void fond_ecran(int state) {
  static SDL_Surface * sprite = NULL;
  static GLuint screen_id = 0;
  switch(state) {
  case GL4DH_INIT: {
    SDL_Surface * s = IMG_Load("./images/Damier.png");
    sprite = SDL_ConvertSurfaceFormat(s, SDL_PIXELFORMAT_ABGR8888, 0);
    SDL_FreeSurface(s);
    screen_id = gl4dpInitScreen();
    gl4dpClearScreenWith(0xFFFFFFFF);
    return;
  }
  case GL4DH_FREE:
    gl4dpSetScreen(screen_id);
    gl4dpDeleteScreen();
    if(sprite) {
      SDL_FreeSurface(sprite);
      sprite = NULL;
    }
    return;
    case GL4DH_UPDATE_WITH_AUDIO:
    return;
  
  default:
    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    gl4dpSetScreen(screen_id);
    copyFromSurface(sprite, gl4dpGetWidth()/999,gl4dpGetHeight()/100);
    gl4dpUpdateScreen(NULL);
    return;
  }
}

void pikachu(int state) {
  static SDL_Surface * sprite = NULL;
  static GLuint screen_id = 0;
  switch(state) {
  case GL4DH_INIT: {
    SDL_Surface * s = IMG_Load("./images/pika_fight.png");
    sprite = SDL_ConvertSurfaceFormat(s, SDL_PIXELFORMAT_ABGR8888, 0);
    SDL_FreeSurface(s);
    screen_id = gl4dpInitScreen();
    gl4dpClearScreenWith(0xFFFFFFFF);
    return;
  }
  case GL4DH_FREE:
    gl4dpSetScreen(screen_id);
    gl4dpDeleteScreen();
    if(sprite) {
      SDL_FreeSurface(sprite);
      sprite = NULL;
    }
    return;
    case GL4DH_UPDATE_WITH_AUDIO:
    return;
  
  default:
    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    gl4dpSetScreen(screen_id);
    copyFromSurface(sprite, gl4dpGetWidth()/999,gl4dpGetHeight()/100);
    gl4dpUpdateScreen(NULL);
    return;
  }
}

void charizard(int state) {
  static SDL_Surface * sprite = NULL;
  static GLuint screen_id = 0;
  switch(state) {
  case GL4DH_INIT: {
    SDL_Surface * s = IMG_Load("./images/charizard_anim2.png");
    sprite = SDL_ConvertSurfaceFormat(s, SDL_PIXELFORMAT_ABGR8888, 0);
    SDL_FreeSurface(s);
    screen_id = gl4dpInitScreen();
    gl4dpClearScreenWith(0xFFFFFFFF);
    return;
  }
  case GL4DH_FREE:
    gl4dpSetScreen(screen_id);
    gl4dpDeleteScreen();
    if(sprite) {
      SDL_FreeSurface(sprite);
      sprite = NULL;
    }
    return;
    case GL4DH_UPDATE_WITH_AUDIO:
    return;
  
  default:
    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    gl4dpSetScreen(screen_id);
    copyFromSurface(sprite, gl4dpGetWidth()/999,gl4dpGetHeight()/100);
    gl4dpUpdateScreen(NULL);
    return;
  }
}

void transition_fondu(void (* a0)(int), void (* a1)(int), Uint32 t, Uint32 et, int state) {
  int vp[4], i;
  GLint tId;
  static GLuint tex[2], pId;
  switch(state) {
  case GL4DH_INIT:
    glGetIntegerv(GL_VIEWPORT, vp);
    glGenTextures(2, tex);
    for(i = 0; i < 2; i++) {
      glBindTexture(GL_TEXTURE_2D, tex[i]);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, vp[2], vp[3], 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    }
    pId = gl4duCreateProgram("<vs>shaders/basic.vs", "<fs>shaders/mix.fs", NULL);
    return;
  case GL4DH_FREE:
    if(tex[0]) {
      glDeleteTextures(2, tex);
      tex[0] = tex[1] = 0;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    if(a0) a0(state);
    if(a1) a1(state);
    return;
  default:
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, &tId);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,  tex[0],  0);
    if(a0) a0(state);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,  tex[1],  0);
    if(a1) a1(state);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,  tId,  0);
    glDisable(GL_DEPTH);
    glUseProgram(pId);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tex[1]);
    if(et / (GLfloat)t > 1) {
      fprintf(stderr, "%d-%d -- %f\n", et, t, et / (GLfloat)t);
      exit(0);
    }
    glUniform1f(glGetUniformLocation(pId, "dt"), et / (GLfloat)t);
    glUniform1i(glGetUniformLocation(pId, "tex0"), 0);
    glUniform1i(glGetUniformLocation(pId, "tex1"), 1);
    gl4dgDraw(_quadId);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    return;
  }
}

void animation_vide(int state) {
  switch(state) {
  case GL4DH_DRAW:
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    return;
  default:
    return;
  }
}


void vs_ash(int state) {
  switch(state) {
  case GL4DH_INIT:
    credits_init_ash();
    return;
  case GL4DH_FREE:
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    return;
  default: /* GL4DH_DRAW */
    credits_draw_ash();
    return;
  }
}

void vs_blondie(int state) {
  switch(state) {
  case GL4DH_INIT:
    credits_init_blondie();
    return;
  case GL4DH_FREE:
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    return;
  default: /* GL4DH_DRAW */
    credits_draw_blondie();
    return;
  }
}

void cynthia(int state) {
  switch(state) {
  case GL4DH_INIT:
    credits_init_cynthia();
    return;
  case GL4DH_FREE:
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    return;
  default: /* GL4DH_DRAW */
    credits_draw_cynthia();
    return;
  }
}

void ash(int state) {
  switch(state) {
  case GL4DH_INIT:
    credits_init_ash_2();
    return;
  case GL4DH_FREE:
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    return;
  default: /* GL4DH_DRAW */
    credits_draw_ash_2();
    return;
  }
}

void pokeball(int state) {
  switch(state) {
  case GL4DH_INIT:
    credits_init_poke();
    return;
  case GL4DH_FREE:
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    return;
  default: /* GL4DH_DRAW */
    credits_draw_poke();
    return;
  }
}

void pokeball_2(int state) {
  switch(state) {
  case GL4DH_INIT:
    credits_init_poke_2();
    return;
  case GL4DH_FREE:
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    return;
  default: /* GL4DH_DRAW */
    credits_draw_poke_2();
    return;
  }
}

void terrain(int state) {
  switch(state) {
  case GL4DH_INIT:
    credits2_init();
    return;
  case GL4DH_FREE:
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    return;
  default: /* GL4DH_DRAW */
    credits2_draw();
    return;
  }
}

void terrain_2(int state) {
  switch(state) {
  case GL4DH_INIT:
    credits2_init_2();
    return;
  case GL4DH_FREE:
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    return;
  default: /* GL4DH_DRAW */
    credits2_draw_2();
    return;
  }
}

void pokeball_tourne(int state) {
  switch(state) {
  case GL4DH_INIT:
    earth_init();
    return;
  case GL4DH_FREE:
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    return;
  default: /* GL4DH_DRAW */
    earth_draw();
    return;
  }
}

void pokeball_tourne_f(int state) {
  switch(state) {
  case GL4DH_INIT:
    earth_init_f();
    return;
  case GL4DH_FREE:
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    return;
  default: /* GL4DH_DRAW */
    earth_draw_f();
    return;
  }
}

void credits_fin(int state) {
  switch(state) {
  case GL4DH_INIT:
    credits2();
    return;
  case GL4DH_FREE:
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    return;
  default: /* GL4DH_DRAW */
    creditss();
    return;
  }
}

void animationsInit(void) {
  if(!_quadId)
    _quadId = gl4dgGenQuadf();
}
