#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <GL4D/gl4du.h>
#include <GL4D/gl4df.h>
#include <SDL_image.h>

static GLuint _pId = 0;
static GLuint _tId[12] = {0};
static GLuint _quad = 0;

void credits2_init_2(void) {
  int i;
  SDL_Surface * t;
  int vp[4], w, h;
  static char * files[] = {"./images/combat.png","./images/terrain2.png","./images/pika1.png","./images/pika2.png","./images/pika3.png","./images/pika4.png","./images/pika5.png","./images/pika6.png","./images/pika7.png","./images/charizard_back.png", "./images/chari.png", "./images/storm1_2.png"};
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
  glGenTextures(12, _tId);
  for(i = 0; i < 12; i++) {
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

void credits2_draw_2(void) {
  static GLuint charizard = 0.0;
  static GLuint storm = 0.0;
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
  glBindTexture(GL_TEXTURE_2D, _tId[((charizard/12)%7)+2]); //Animation, passe toutes les 12 images à la suivante
  gl4duPushMatrix(); {
    gl4duScalef(60, 40, 10);
    gl4duRotatef(a0, 0, 0, 0);
    gl4duTranslatef(-0.32, 0.09, -4);
    //gl4duScalef(0.5,0.5,0.5);
    gl4duSendMatrices();
  } gl4duPopMatrix();
  glUniform1i(glGetUniformLocation(_pId, "specular"), 0);
  gl4dgDraw(_quad);

//charizard
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, _tId[9+storm]);
  gl4duPushMatrix(); {
    gl4duScalef(4, 4, 4);
    gl4duRotatef(a0, 0, 0, 0);
    gl4duTranslatef(0.75, -0.8, -2); //côté, hauteur, profondeur
    //gl4duScalef(0.5,0.5,0.5);
    gl4duSendMatrices();
  } gl4duPopMatrix();
  glUniform1i(glGetUniformLocation(_pId, "specular"), 0);
  gl4dgDraw(_quad);

  charizard ++;
  
  if(charizard > (12*7)*3){
    if (charizard == (12*7)*3){
      storm ++;
    }

    if(switch_ >= 1){
      storm ++;
      state = 1;
    }
    if(switch_ <= 0){
      storm --;
      state = 0;
    }
    if(state == 0){
      switch_ += 0.5;
    }
    if(state == 1){
      switch_ -= 0.5;
    }
  }

  a0 += 360.0 * dt / (6.0);
}