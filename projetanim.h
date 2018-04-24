#ifndef _ANIMATIONS_H

#define _ANIMATIONS_H

#ifdef __cplusplus
extern "C" {
#endif
  extern void exemple_d_animation_00(int state);
  extern void transition_fondu(void (* a0)(int), void (* a1)(int), Uint32 t, Uint32 et, int state);
  extern void animation_vide(int state);
  extern void animationsInit(void);
  extern void fond_ecran(int state);
  extern void Anim(int state);
  extern void animation_base(int state);
  extern void base_init(void);
  extern void base_draw(void);
  extern void vs_ash(int state);
  extern void credits_init_ash(void);
  extern void vs_blondie(int state);
  extern void credits_init_blondie(void);
  extern void credits_draw_ash(void);
  extern void credits_draw_blondie(void);
  extern void terrain(int state);
  extern void credits2_init(void);
  extern void credits2_draw(void);
  extern void credits_init_cynthia(void);
  extern void credits_draw_cynthia(void);
  extern void cynthia(int state);
  extern void credits_init_poke(void);
  extern void credits_draw_poke(void);
  extern void pokeball(int state);
  extern void animation_base3(int state);
  extern void base_init3(void);
  extern void base_draw3(void);
  extern void charizard(int state);
  extern void credits2_draw_2(void);
  extern void credits2_init_2(void);
  extern void terrain_2(int state);
  extern void ash(int state);
  extern void credits_init_ash_2(void);
  extern void credits_draw_ash_2(void);
  extern void pikachu(int state);
  extern void credits_init_poke_2(void);
  extern void credits_draw_poke_2(void);
  extern void pokeball_2(int state);
  extern void earth_init(void);
  extern void earth_draw(void);
  extern void pokeball_tourne(int state);
  extern void earth_init_f(void);
  extern void earth_draw_f(void);
  extern void pokeball_tourne_f(int state);
  extern void credits2(void);
  extern void creditss(void);
  extern void credits_fin(int state);
  extern void mobileMove(float * G);
  extern void animation_earth(int state);
  extern void earth_init(void);
  extern void earth_draw(void);
  #ifdef __cplusplus
}
#endif

#endif