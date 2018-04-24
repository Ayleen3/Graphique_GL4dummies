#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <GL4D/gl4du.h>
#include <GL4D/gl4df.h>
#include <SDL_image.h>

static GLuint _pId = 0;
static GLuint _tId[11] = {0};
static GLuint _quad = 0;

void credits2_init(void) {
  int i;
  SDL_Surface * t;
  int vp[4], w, h;
  static char * files[] = {"./images/combat.png","./images/terrain1.png","./images/charizard1.png","./images/charizard2.png","./images/charizard3.png","./images/charizard4.png","./images/charizard5.png","./images/charizard6.png","./images/charizard7.png","./images/pikachu1.png", "./images/pika.png"};
  _pId  = gl4duCreateProgram("<vs>shaders/earth.vs", "<fs>shaders/earth.fs", NULL);
  glGetIntegerv(GL_VIEWPORT, vp);
  w = vp[2] - vp[0];
  h = vp[3] - vp[1];
  gl4duGenMatrix(GL_FLOAT, "modelViewMatrix");
  gl4duGenMatrix(GL_FLOAT, "projectionMatrix");
  gl4duBindMatrix("projectionMatrix");
  gl4duLoadIdentityf();
  gl4duFrustumf(-0.5, 0.5, -0.5 * h / w, 0.5 * h / w, 1.0, 1000.0);
  gl4duBindMatrix("modelViewMatrix");
  glGenTextures(11, _tId);
  for(i = 0; i < 11; i++) {
    glBindTexture(GL_TEXTURE_2D, _tId[i]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    if( (t = IMG_Load(files[i])) != NULL ) {
#ifdef __APPLE__
      int mode = t->format->BytesPerPixel == 4 ? GL_BGRA : GL_BGR;
#else
      int mode = t->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB;
#endif       
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, t->w, t->h, 0, mode, GL_UNSIGNED_BYTE, t->pixels);
      SDL_FreeSurface(t);
    } else {
      fprintf(stderr, "can't open file %s : %s\n", files[i], SDL_GetError());
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    }
  }
  _quad = gl4dgGenQuadf();
}

void credits2_draw(void) {
  static GLuint charizard = 0.0;
  static GLuint fire = 0.0;
  static GLfloat switch_ = 1.0;
  static GLuint state = 0.0;
  static GLfloat a0 = 0.0;
  static Uint32 t0 = 0, t;
  GLfloat dt = 0.0;
  dt = ((t = SDL_GetTicks()) - t0) / 1000.0;
  t0 = t;

  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  gl4duBindMatrix("modelViewMatrix");
  gl4duLoadIdentityf();
  gl4duTranslatef(0, 0, -14);

  glUseProgram(_pId);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, _tId[0]);
  gl4duPushMatrix(); {
    gl4duScalef(300, 250, 100);
    gl4duRotatef(a0, 0, 0, 0);
    gl4duTranslatef(0, 0, -5);
    gl4duScalef(1,1,1);
    gl4duSendMatrices();
  } gl4duPopMatrix();
  glUniform1i(glGetUniformLocation(_pId, "specular"), 0);
  gl4dgDraw(_quad);
  
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, _tId[1]);
  gl4duPushMatrix(); {
    gl4duScalef(300, 250, 100);
    gl4duRotatef(a0, 0, 0, 0);
    gl4duTranslatef(0, 0, -4);
    gl4duScalef(0.7, 0.585, 0.6); //CHANGER LA TAILLE DE L'IMAGE
    gl4duSendMatrices();
  } gl4duPopMatrix();
  glUniform1i(glGetUniformLocation(_pId, "specular"), 0);
  gl4dgDraw(_quad);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, _tId[((charizard/10)%7)+2]); //Animation, passe toutes les 10 images à la suivante
  gl4duPushMatrix(); {
    gl4duScalef(50, 35, 10);
    gl4duRotatef(a0, 0, 0, 0);
    gl4duTranslatef(-0.25, 0.15, -4);
    gl4duSendMatrices();
  } gl4duPopMatrix();
  glUniform1i(glGetUniformLocation(_pId, "specular"), 0);
  gl4dgDraw(_quad);

//pika
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, _tId[9+fire]);
  gl4duPushMatrix(); {
    gl4duScalef(20, 15, 10);
    gl4duRotatef(a0, 0, 0, 0);
    gl4duTranslatef(0.35, -0.6, -3); //côté, hauteur, profondeur
    gl4duSendMatrices();
  } gl4duPopMatrix();
  glUniform1i(glGetUniformLocation(_pId, "specular"), 0);
  gl4dgDraw(_quad);

  charizard ++;

  if(charizard > (12*7)*3){
    if (charizard == (12*7)*3){
      fire ++;
    }

    if(switch_ >= 1){
      fire ++;
      state = 1;
    }
    if(switch_ <= 0){
      fire --;
      state = 0;
    }
    if(state == 0){
      switch_ += 0.3;
    }
    if(state == 1){
      switch_ -= 0.3;
    }
  }

  a0 += 360.0 * dt / (6.0);
}
