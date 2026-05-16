/*
 * ============================================================
 *  OLEDFace.h  —  Arduino Library Header
 *  OLED Eye + Mouth Animation Library
 *
 *  Supports : 0.96" SSD1306 128x64 I2C OLED
 *  Requires : Adafruit GFX + Adafruit SSD1306
 *
 *  Style    : Eyes + mouth only (no face circle)
 *             Mixed emo + cute + gesture + special animations
 *
 *  Usage:
 *    #include "OLEDFace.h"
 *    OLEDFace face;
 *    face.begin();
 *    face.playScene(SCENE_CUTE_HAPPY);
 *    // or cycle all scenes automatically:
 *    face.playAll();
 * ============================================================
 */

#ifndef OLEDFACE_H
#define OLEDFACE_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ── Display dimensions ───────────────────────────────────────
#define OLED_W        128
#define OLED_H         64
#define OLED_RESET     -1
#define OLED_I2C_ADDR  0x3C

// ── Default scene duration (ms) ──────────────────────────────
#define DEFAULT_SCENE_MS  3000

// ── Scene IDs ────────────────────────────────────────────────
// Facial expressions (emo + cute)
#define SCENE_CUTE_HAPPY      0
#define SCENE_EMO_STARE       1
#define SCENE_UWU             2
#define SCENE_CRYING          3
#define SCENE_ANGRY_GLITCH    4
#define SCENE_HEART_EYES      5
#define SCENE_DEAD_INSIDE     6
#define SCENE_SLEEPY          7
#define SCENE_DIZZY           8
#define SCENE_WINK_CUTE       9
#define SCENE_TWT             10
#define SCENE_SURPRISE        11
#define SCENE_STAR_EYES       12
#define SCENE_DOT_BOUNCE      13
#define SCENE_GLITCH_SCAN     14
// New expressions
#define SCENE_SQUARE_EYES     15
#define SCENE_PIXEL_HAPPY     16
#define SCENE_ROBOT_SCAN      17
#define SCENE_LOADING         18
#define SCENE_SHY_BLUSH       19
#define SCENE_SKEPTICAL       20
// Gestures
#define SCENE_WAVE            21
#define SCENE_THUMBS_UP       22
#define SCENE_HANDSHAKE       23
// Special
#define SCENE_BULLET_DODGE    24

#define SCENE_COUNT           25

// ── OLEDFace class ───────────────────────────────────────────
class OLEDFace {
public:
  // Constructor
  OLEDFace();

  // Initialise display. Returns false if display not found.
  bool begin(uint8_t i2cAddr = OLED_I2C_ADDR);

  // Set how long each scene runs (milliseconds)
  void setSceneDuration(uint16_t ms);

  // Play a single scene by ID (blocks for scene duration)
  void playScene(uint8_t sceneId);

  // Cycle through ALL scenes in order, forever
  void playAll();

  // Cycle through a custom list of scene IDs
  // e.g. uint8_t list[] = {SCENE_CUTE_HAPPY, SCENE_WAVE};
  //      face.playList(list, 2);
  void playList(const uint8_t* ids, uint8_t count);

  // Show boot splash screen
  void showSplash();

  // ── Direct draw primitives (public for advanced use) ──────
  void fillOval(int cx, int cy, int rw, int rh);
  void drawOval(int cx, int cy, int rw, int rh);
  void drawMouth(int x0,int y0,int cx,int cy,int x1,int y1,int steps=20);

  // ── Mouth shapes ──────────────────────────────────────────
  void smile();
  void smirk();
  void flatMouth();
  void frown();
  void sadMouth();
  void ohMouth();
  void catMouth();
  void tremble(int seed);

  // ── Eye shapes ────────────────────────────────────────────
  void cuteEyes(int lx=-1, int rx=-1, int ey=-1);
  void emoEyes();
  void deadEyes();
  void starEyes();
  void uwuEyes();
  void twtEyes();
  void sleepyEyes(int openH=5);
  void dotEyes();
  void dizzyEyes();
  void winkEyes(bool leftWink=false);
  void angryEyes();
  void heartEyes();
  void cryEyes(int tearLen);
  void squareEyes();                // NEW — square pixel eyes
  void pixelEyes(uint8_t pattern);  // NEW — 3x3 pixel pattern
  void skepticalEyes();             // NEW — one brow raised
  void shyEyes();                   // NEW — looking down, blush

  // ── Gesture drawing helpers ───────────────────────────────
  void drawHandOpen(int bx, int by);   // open palm / wave
  void drawThumbsUp(int bx, int by);   // thumb up fist
  void drawFist(int bx, int by);       // closed fist

private:
  Adafruit_SSD1306 _display;
  uint16_t         _sceneMs;

  // Layout geometry (private, but consistent)
  static const int CX      = 64;
  static const int EYE_Y   = 22;
  static const int EYE_LX  = 38;
  static const int EYE_RX  = 90;
  static const int MOUTH_Y = 46;

  // Timer helpers
  unsigned long _sceneStart;
  void   _startScene();
  bool   _timeUp();

  // ── Internal scene runners ────────────────────────────────
  void _sceneCuteHappy();
  void _sceneEmoStare();
  void _sceneUwU();
  void _sceneCrying();
  void _sceneAngryGlitch();
  void _sceneHeartEyes();
  void _sceneDeadInside();
  void _sceneSleepy();
  void _sceneDizzy();
  void _sceneWinkCute();
  void _sceneTwT();
  void _sceneSurprise();
  void _sceneStarEyes();
  void _sceneDotBounce();
  void _sceneGlitchScan();
  void _sceneSquareEyes();
  void _scenePixelHappy();
  void _sceneRobotScan();
  void _sceneLoading();
  void _sceneShyBlush();
  void _sceneSkeptical();
  void _sceneWave();
  void _sceneThumbsUp();
  void _sceneHandshake();
  void _sceneBulletDodge();
};

#endif // OLEDFACE_H
