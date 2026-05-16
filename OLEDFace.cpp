/*
 * ============================================================
 *  OLEDFace.cpp  —  Arduino Library Implementation
 *  See OLEDFace.h for full usage documentation.
 * ============================================================
 */

#include "OLEDFace.h"

// ════════════════════════════════════════════════════════════
//  CONSTRUCTOR & INIT
// ════════════════════════════════════════════════════════════

OLEDFace::OLEDFace()
  : _display(OLED_W, OLED_H, &Wire, OLED_RESET),
    _sceneMs(DEFAULT_SCENE_MS),
    _sceneStart(0)
{}

bool OLEDFace::begin(uint8_t i2cAddr) {
  if (!_display.begin(SSD1306_SWITCHCAPVCC, i2cAddr)) return false;
  randomSeed(analogRead(0));
  _display.clearDisplay();
  _display.setTextColor(WHITE);
  return true;
}

void OLEDFace::setSceneDuration(uint16_t ms) { _sceneMs = ms; }

// ── Timer helpers ─────────────────────────────────────────────
void OLEDFace::_startScene()  { _sceneStart = millis(); }
bool OLEDFace::_timeUp()      { return (millis() - _sceneStart) >= _sceneMs; }

// ════════════════════════════════════════════════════════════
//  SPLASH
// ════════════════════════════════════════════════════════════

void OLEDFace::showSplash() {
  _display.clearDisplay();
  _display.setTextColor(WHITE);
  _display.setTextSize(1);
  _display.setCursor(22, 16); _display.print(F("(  ^  ^  )"));
  _display.setCursor(32, 30); _display.print(F("OLEDFace v1.0"));
  _display.setCursor(18, 44); _display.print(F("by YourName / 2025"));
  _display.display();
  delay(1800);
}

// ════════════════════════════════════════════════════════════
//  PLAY FUNCTIONS
// ════════════════════════════════════════════════════════════

void OLEDFace::playScene(uint8_t id) {
  switch (id) {
    case SCENE_CUTE_HAPPY:    _sceneCuteHappy();    break;
    case SCENE_EMO_STARE:     _sceneEmoStare();     break;
    case SCENE_UWU:           _sceneUwU();           break;
    case SCENE_CRYING:        _sceneCrying();        break;
    case SCENE_ANGRY_GLITCH:  _sceneAngryGlitch();  break;
    case SCENE_HEART_EYES:    _sceneHeartEyes();     break;
    case SCENE_DEAD_INSIDE:   _sceneDeadInside();    break;
    case SCENE_SLEEPY:        _sceneSleepy();        break;
    case SCENE_DIZZY:         _sceneDizzy();         break;
    case SCENE_WINK_CUTE:     _sceneWinkCute();      break;
    case SCENE_TWT:           _sceneTwT();           break;
    case SCENE_SURPRISE:      _sceneSurprise();      break;
    case SCENE_STAR_EYES:     _sceneStarEyes();      break;
    case SCENE_DOT_BOUNCE:    _sceneDotBounce();     break;
    case SCENE_GLITCH_SCAN:   _sceneGlitchScan();    break;
    case SCENE_SQUARE_EYES:   _sceneSquareEyes();    break;
    case SCENE_PIXEL_HAPPY:   _scenePixelHappy();    break;
    case SCENE_ROBOT_SCAN:    _sceneRobotScan();     break;
    case SCENE_LOADING:       _sceneLoading();       break;
    case SCENE_SHY_BLUSH:     _sceneShyBlush();      break;
    case SCENE_SKEPTICAL:     _sceneSkeptical();     break;
    case SCENE_WAVE:          _sceneWave();          break;
    case SCENE_THUMBS_UP:     _sceneThumbsUp();      break;
    case SCENE_HANDSHAKE:     _sceneHandshake();     break;
    case SCENE_BULLET_DODGE:  _sceneBulletDodge();   break;
    default: break;
  }
}

void OLEDFace::playAll() {
  while (true) {
    for (uint8_t i = 0; i < SCENE_COUNT; i++) {
      playScene(i);
    }
  }
}

void OLEDFace::playList(const uint8_t* ids, uint8_t count) {
  for (uint8_t i = 0; i < count; i++) {
    playScene(ids[i]);
  }
}

// ════════════════════════════════════════════════════════════
//  PRIMITIVES
// ════════════════════════════════════════════════════════════

void OLEDFace::fillOval(int cx, int cy, int rw, int rh) {
  if (rw <= 0 || rh <= 0) return;
  for (int dy = -rh; dy <= rh; dy++) {
    float ratio = 1.0f - (float)(dy * dy) / (float)(rh * rh);
    if (ratio < 0) ratio = 0;
    int hw = (int)(rw * sqrtf(ratio));
    _display.drawFastHLine(cx - hw, cy + dy, hw * 2 + 1, WHITE);
  }
}

void OLEDFace::drawOval(int cx, int cy, int rw, int rh) {
  if (rw <= 0 || rh <= 0) return;
  for (int dy = -rh; dy <= rh; dy++) {
    float ratio = 1.0f - (float)(dy * dy) / (float)(rh * rh);
    if (ratio < 0) continue;
    int hw = (int)(rw * sqrtf(ratio));
    _display.drawPixel(cx - hw, cy + dy, WHITE);
    _display.drawPixel(cx + hw, cy + dy, WHITE);
  }
}

void OLEDFace::drawMouth(int x0, int y0, int cx, int cy,
                          int x1, int y1, int steps) {
  float px = x0, py = y0;
  for (int i = 1; i <= steps; i++) {
    float t  = i / (float)steps;
    float mt = 1.0f - t;
    float nx = mt*mt*x0 + 2*mt*t*cx + t*t*x1;
    float ny = mt*mt*y0 + 2*mt*t*cy + t*t*y1;
    _display.drawLine((int)px, (int)py, (int)nx, (int)ny, WHITE);
    px = nx; py = ny;
  }
}

// ════════════════════════════════════════════════════════════
//  MOUTH SHAPES
// ════════════════════════════════════════════════════════════

void OLEDFace::smile()    { drawMouth(CX-22,MOUTH_Y,   CX,MOUTH_Y+14, CX+22,MOUTH_Y); }
void OLEDFace::smirk()    { drawMouth(CX-18,MOUTH_Y+2, CX,MOUTH_Y+8,  CX+18,MOUTH_Y+2); }
void OLEDFace::frown()    { drawMouth(CX-22,MOUTH_Y+4, CX,MOUTH_Y-8,  CX+22,MOUTH_Y+4); }
void OLEDFace::sadMouth() { drawMouth(CX-14,MOUTH_Y+2, CX,MOUTH_Y-5,  CX+14,MOUTH_Y+2); }
void OLEDFace::ohMouth()  { _display.drawCircle(CX, MOUTH_Y+2, 7, WHITE); }

void OLEDFace::flatMouth() {
  _display.drawFastHLine(CX-18, MOUTH_Y,   36, WHITE);
  _display.drawFastHLine(CX-18, MOUTH_Y+1, 36, WHITE);
}

void OLEDFace::catMouth() {
  drawMouth(CX-16, MOUTH_Y+2, CX-8, MOUTH_Y+8, CX,    MOUTH_Y+2);
  drawMouth(CX,    MOUTH_Y+2, CX+8, MOUTH_Y+8, CX+16, MOUTH_Y+2);
}

void OLEDFace::tremble(int seed) {
  int x = CX - 20;
  for (int i = 0; i < 8; i++) {
    int y1 = MOUTH_Y + ((seed + i)     % 3 - 1) * 3;
    int y2 = MOUTH_Y + ((seed + i + 1) % 3 - 1) * 3;
    _display.drawLine(x, y1, x + 5, y2, WHITE);
    x += 5;
  }
}

// ════════════════════════════════════════════════════════════
//  EYE SHAPES
// ════════════════════════════════════════════════════════════

void OLEDFace::cuteEyes(int lx, int rx, int ey) {
  if (lx < 0) lx = EYE_LX;
  if (rx < 0) rx = EYE_RX;
  if (ey < 0) ey = EYE_Y;
  fillOval(lx, ey, 11, 10);
  fillOval(rx, ey, 11, 10);
  _display.fillRect(lx - 5, ey - 5, 4, 4, BLACK); // gleam
  _display.fillRect(rx - 5, ey - 5, 4, 4, BLACK);
}

void OLEDFace::emoEyes() {
  fillOval(EYE_LX, EYE_Y, 10, 9);
  fillOval(EYE_RX, EYE_Y, 10, 9);
  _display.fillRect(EYE_LX-11, EYE_Y-10, 22, 6, BLACK);
  _display.drawFastHLine(EYE_LX-11, EYE_Y-4, 22, WHITE);
  _display.fillRect(EYE_RX-11, EYE_Y-10, 22, 6, BLACK);
  _display.drawFastHLine(EYE_RX-11, EYE_Y-4, 22, WHITE);
}

void OLEDFace::deadEyes() {
  int r = 9;
  _display.drawLine(EYE_LX-r, EYE_Y-r, EYE_LX+r, EYE_Y+r, WHITE);
  _display.drawLine(EYE_LX+r, EYE_Y-r, EYE_LX-r, EYE_Y+r, WHITE);
  _display.drawLine(EYE_RX-r, EYE_Y-r, EYE_RX+r, EYE_Y+r, WHITE);
  _display.drawLine(EYE_RX+r, EYE_Y-r, EYE_RX-r, EYE_Y+r, WHITE);
}

void OLEDFace::starEyes() {
  int r = 9;
  for (int ox = -1; ox <= 1; ox++) {
    _display.drawFastHLine(EYE_LX-r, EYE_Y+ox, r*2+1, WHITE);
    _display.drawFastVLine(EYE_LX+ox, EYE_Y-r, r*2+1, WHITE);
    _display.drawFastHLine(EYE_RX-r, EYE_Y+ox, r*2+1, WHITE);
    _display.drawFastVLine(EYE_RX+ox, EYE_Y-r, r*2+1, WHITE);
  }
  int d = 7;
  _display.drawLine(EYE_LX-d, EYE_Y-d, EYE_LX+d, EYE_Y+d, WHITE);
  _display.drawLine(EYE_LX+d, EYE_Y-d, EYE_LX-d, EYE_Y+d, WHITE);
  _display.drawLine(EYE_RX-d, EYE_Y-d, EYE_RX+d, EYE_Y+d, WHITE);
  _display.drawLine(EYE_RX+d, EYE_Y-d, EYE_RX-d, EYE_Y+d, WHITE);
}

void OLEDFace::uwuEyes() {
  _display.drawLine(EYE_LX-6, EYE_Y-8, EYE_LX+7, EYE_Y,   WHITE);
  _display.drawLine(EYE_LX+7, EYE_Y,   EYE_LX-6, EYE_Y+8, WHITE);
  _display.drawLine(EYE_LX-5, EYE_Y-8, EYE_LX+8, EYE_Y,   WHITE);
  _display.drawLine(EYE_LX+8, EYE_Y,   EYE_LX-5, EYE_Y+8, WHITE);
  _display.drawLine(EYE_RX+6, EYE_Y-8, EYE_RX-7, EYE_Y,   WHITE);
  _display.drawLine(EYE_RX-7, EYE_Y,   EYE_RX+6, EYE_Y+8, WHITE);
  _display.drawLine(EYE_RX+5, EYE_Y-8, EYE_RX-8, EYE_Y,   WHITE);
  _display.drawLine(EYE_RX-8, EYE_Y,   EYE_RX+5, EYE_Y+8, WHITE);
}

void OLEDFace::twtEyes() {
  _display.drawFastHLine(EYE_LX-9, EYE_Y-2, 18, WHITE);
  _display.drawFastHLine(EYE_LX-9, EYE_Y-1, 18, WHITE);
  _display.drawFastVLine(EYE_LX,   EYE_Y-1, 10, WHITE);
  _display.drawFastVLine(EYE_LX+1, EYE_Y-1, 10, WHITE);
  _display.drawFastHLine(EYE_RX-9, EYE_Y-2, 18, WHITE);
  _display.drawFastHLine(EYE_RX-9, EYE_Y-1, 18, WHITE);
  _display.drawFastVLine(EYE_RX,   EYE_Y-1, 10, WHITE);
  _display.drawFastVLine(EYE_RX+1, EYE_Y-1, 10, WHITE);
}

void OLEDFace::sleepyEyes(int openH) {
  openH = constrain(openH, 1, 10);
  fillOval(EYE_LX, EYE_Y, 11, openH);
  fillOval(EYE_RX, EYE_Y, 11, openH);
  int maskH = 10 - openH + 1;
  _display.fillRect(EYE_LX-12, EYE_Y-10, 24, maskH, BLACK);
  _display.fillRect(EYE_RX-12, EYE_Y-10, 24, maskH, BLACK);
  _display.drawFastHLine(EYE_LX-11, EYE_Y-openH+1, 22, WHITE);
  _display.drawFastHLine(EYE_RX-11, EYE_Y-openH+1, 22, WHITE);
}

void OLEDFace::dotEyes() {
  _display.fillCircle(EYE_LX, EYE_Y, 4, WHITE);
  _display.fillCircle(EYE_RX, EYE_Y, 4, WHITE);
}

void OLEDFace::dizzyEyes() {
  _display.drawCircle(EYE_LX, EYE_Y, 9, WHITE);
  _display.drawCircle(EYE_LX, EYE_Y, 5, WHITE);
  _display.drawCircle(EYE_LX, EYE_Y, 2, WHITE);
  _display.drawPixel(EYE_LX,  EYE_Y,    WHITE);
  _display.drawCircle(EYE_RX, EYE_Y, 9, WHITE);
  _display.drawCircle(EYE_RX, EYE_Y, 5, WHITE);
  _display.drawCircle(EYE_RX, EYE_Y, 2, WHITE);
  _display.drawPixel(EYE_RX,  EYE_Y,    WHITE);
}

void OLEDFace::winkEyes(bool leftWink) {
  if (leftWink) {
    _display.drawFastHLine(EYE_LX-10, EYE_Y,   20, WHITE);
    _display.drawFastHLine(EYE_LX-10, EYE_Y+1, 20, WHITE);
    cuteEyes(EYE_LX, EYE_RX); // draw only right
    // override left with wink line
    _display.fillRect(EYE_LX-12, EYE_Y-12, 24, 24, BLACK);
    _display.drawFastHLine(EYE_LX-10, EYE_Y,   20, WHITE);
    _display.drawFastHLine(EYE_LX-10, EYE_Y+1, 20, WHITE);
  } else {
    fillOval(EYE_LX, EYE_Y, 11, 10);
    _display.fillRect(EYE_LX-5, EYE_Y-5, 4, 4, BLACK);
    _display.drawFastHLine(EYE_RX-10, EYE_Y,   20, WHITE);
    _display.drawFastHLine(EYE_RX-10, EYE_Y+1, 20, WHITE);
  }
}

void OLEDFace::angryEyes() {
  fillOval(EYE_LX, EYE_Y, 10, 9);
  fillOval(EYE_RX, EYE_Y, 10, 9);
  for (int i = 0; i < 5; i++) {
    _display.drawFastHLine(EYE_LX+i-4, EYE_Y-10+i, 6-i, BLACK);
    _display.drawFastHLine(EYE_RX-i-2, EYE_Y-10+i, 6-i, BLACK);
  }
  _display.drawLine(EYE_LX-10, EYE_Y-11, EYE_LX+8,  EYE_Y-15, WHITE);
  _display.drawLine(EYE_LX-10, EYE_Y-12, EYE_LX+8,  EYE_Y-16, WHITE);
  _display.drawLine(EYE_RX-8,  EYE_Y-15, EYE_RX+10, EYE_Y-11, WHITE);
  _display.drawLine(EYE_RX-8,  EYE_Y-16, EYE_RX+10, EYE_Y-12, WHITE);
}

void OLEDFace::heartEyes() {
  int r = 5;
  _display.fillCircle(EYE_LX-r, EYE_Y, r, WHITE);
  _display.fillCircle(EYE_LX+r, EYE_Y, r, WHITE);
  _display.fillTriangle(EYE_LX-r*2, EYE_Y, EYE_LX+r*2, EYE_Y, EYE_LX, EYE_Y+r*2+2, WHITE);
  _display.fillCircle(EYE_RX-r, EYE_Y, r, WHITE);
  _display.fillCircle(EYE_RX+r, EYE_Y, r, WHITE);
  _display.fillTriangle(EYE_RX-r*2, EYE_Y, EYE_RX+r*2, EYE_Y, EYE_RX, EYE_Y+r*2+2, WHITE);
}

void OLEDFace::cryEyes(int tearLen) {
  for (int dy = 0; dy <= 8; dy++) {
    float r = 1.0f - (float)(dy*dy) / 64.0f;
    if (r < 0) r = 0;
    int hw = (int)(10 * sqrtf(r));
    _display.drawFastHLine(EYE_LX-hw, EYE_Y+dy, hw*2+1, WHITE);
    _display.drawFastHLine(EYE_RX-hw, EYE_Y+dy, hw*2+1, WHITE);
  }
  _display.fillRect(EYE_LX-11, EYE_Y-10, 22, 10, BLACK);
  _display.fillRect(EYE_RX-11, EYE_Y-10, 22, 10, BLACK);
  _display.drawFastHLine(EYE_LX-10, EYE_Y, 20, WHITE);
  _display.drawFastHLine(EYE_RX-10, EYE_Y, 20, WHITE);
  tearLen = constrain(tearLen, 0, 18);
  if (tearLen > 0) {
    _display.drawFastVLine(EYE_LX, EYE_Y+9, tearLen, WHITE);
    _display.drawFastVLine(EYE_RX, EYE_Y+9, tearLen, WHITE);
  }
}

// ── NEW: Square eyes ─────────────────────────────────────────
// Hollow rounded-rect squares — pixel/robot style
void OLEDFace::squareEyes() {
  _display.drawRoundRect(EYE_LX-10, EYE_Y-9, 20, 18, 2, WHITE);
  _display.drawRoundRect(EYE_RX-10, EYE_Y-9, 20, 18, 2, WHITE);
  // inner pupil dot
  _display.fillRect(EYE_LX-3, EYE_Y-3, 6, 6, WHITE);
  _display.fillRect(EYE_RX-3, EYE_Y-3, 6, 6, WHITE);
}

// ── NEW: Pixel eyes (3x3 grid with bit pattern) ──────────────
// pattern: bitmask of 9 bits top-left to bottom-right
void OLEDFace::pixelEyes(uint8_t pattern) {
  int sz = 5; // each pixel cell size
  for (int row = 0; row < 3; row++) {
    for (int col = 0; col < 3; col++) {
      int bit = 8 - (row * 3 + col);
      if (pattern & (1 << bit)) {
        _display.fillRect(EYE_LX - 7 + col*sz, EYE_Y - 7 + row*sz, sz-1, sz-1, WHITE);
        _display.fillRect(EYE_RX - 7 + col*sz, EYE_Y - 7 + row*sz, sz-1, sz-1, WHITE);
      }
    }
  }
}

// ── NEW: Skeptical eyes (one raised brow) ────────────────────
void OLEDFace::skepticalEyes() {
  // left eye normal
  fillOval(EYE_LX, EYE_Y, 10, 9);
  _display.fillRect(EYE_LX-5, EYE_Y-5, 4, 4, BLACK);
  _display.drawFastHLine(EYE_LX-10, EYE_Y-12, 20, WHITE); // flat brow

  // right eye half-squinted
  for (int dy = 0; dy <= 9; dy++) {
    float r = 1.0f - (float)(dy*dy)/81.0f;
    if (r < 0) r = 0;
    int hw = (int)(10 * sqrtf(r));
    _display.drawFastHLine(EYE_RX-hw, EYE_Y+dy, hw*2+1, WHITE);
  }
  _display.fillRect(EYE_RX-11, EYE_Y-10, 22, 7, BLACK);
  _display.drawFastHLine(EYE_RX-10, EYE_Y-3, 20, WHITE);
  // raised right brow (angled)
  _display.drawLine(EYE_RX-10, EYE_Y-14, EYE_RX+10, EYE_Y-18, WHITE);
  _display.drawLine(EYE_RX-10, EYE_Y-15, EYE_RX+10, EYE_Y-19, WHITE);
}

// ── NEW: Shy eyes (looking down + blush dots) ─────────────────
void OLEDFace::shyEyes() {
  // eyes shifted down, small
  fillOval(EYE_LX, EYE_Y+3, 8, 6);
  fillOval(EYE_RX, EYE_Y+3, 8, 6);
  // eyelid cover top half
  _display.fillRect(EYE_LX-9, EYE_Y-7, 18, 10, BLACK);
  _display.fillRect(EYE_RX-9, EYE_Y-7, 18, 10, BLACK);
  _display.drawFastHLine(EYE_LX-8, EYE_Y+3, 16, WHITE); // lid line
  _display.drawFastHLine(EYE_RX-8, EYE_Y+3, 16, WHITE);
  // blush dots (3 dots each cheek)
  for (int i = 0; i < 3; i++) {
    _display.drawPixel(EYE_LX-16+i*3, EYE_Y+12, WHITE);
    _display.drawPixel(EYE_RX+ 8+i*3, EYE_Y+12, WHITE);
  }
  for (int i = 0; i < 4; i++) {
    _display.drawPixel(EYE_LX-17+i*3, EYE_Y+14, WHITE);
    _display.drawPixel(EYE_RX+ 7+i*3, EYE_Y+14, WHITE);
  }
}

// ════════════════════════════════════════════════════════════
//  GESTURE DRAWING HELPERS
// ════════════════════════════════════════════════════════════

// Open palm (5 fingers extended) — used for wave
void OLEDFace::drawHandOpen(int bx, int by) {
  // palm
  _display.fillRoundRect(bx, by+6, 18, 14, 3, WHITE);
  // 5 fingers
  int fx[] = {bx, bx+3, bx+6, bx+9, bx+13};
  int fh[] = {9,  11,   11,   10,    8};
  for (int f = 0; f < 5; f++) {
    _display.fillRoundRect(fx[f], by+6-fh[f], 3, fh[f], 1, WHITE);
  }
  // thumb on right side
  _display.fillRoundRect(bx+17, by+9, 6, 7, 2, WHITE);
}

// Thumbs-up fist
void OLEDFace::drawThumbsUp(int bx, int by) {
  // closed fist body
  _display.fillRoundRect(bx, by, 18, 14, 3, WHITE);
  // knuckle lines (black)
  _display.drawFastVLine(bx+5,  by+1, 10, BLACK);
  _display.drawFastVLine(bx+10, by+1, 10, BLACK);
  _display.drawFastVLine(bx+15, by+1, 10, BLACK);
  // thumb pointing up
  _display.fillRoundRect(bx+1, by-10, 5, 12, 2, WHITE);
  // thumb nail detail
  _display.drawFastHLine(bx+2, by-9, 3, BLACK);
}

// Closed fist (for handshake)
void OLEDFace::drawFist(int bx, int by) {
  _display.fillRoundRect(bx, by, 18, 14, 3, WHITE);
  _display.drawFastVLine(bx+5,  by+1, 10, BLACK);
  _display.drawFastVLine(bx+10, by+1, 10, BLACK);
  _display.drawFastVLine(bx+15, by+1, 10, BLACK);
  // thumb on side
  _display.fillRoundRect(bx+17, by+4, 5, 7, 2, WHITE);
}

// ════════════════════════════════════════════════════════════
//  SCENE IMPLEMENTATIONS — EXISTING EXPRESSIONS
// ════════════════════════════════════════════════════════════

void OLEDFace::_sceneCuteHappy() {
  _startScene();
  static const int heights[] = {10,8,5,2,0,2,5,8,10,10};
  static const int dls[]     = {70,55,40,30,30,30,40,55,70,600};
  int idx = 0;
  while (!_timeUp()) {
    _display.clearDisplay();
    int h = heights[idx % 10];
    if (h > 0) {
      cuteEyes();
    } else {
      // fully closed — smooth arc line
      _display.drawFastHLine(EYE_LX-11, EYE_Y, 22, WHITE);
      _display.drawFastHLine(EYE_RX-11, EYE_Y, 22, WHITE);
    }
    smile();
    _display.display();
    delay(dls[idx % 10]);
    idx++;
  }
}

void OLEDFace::_sceneEmoStare() {
  _startScene();
  static const int offsets[] = {0,0,0,-3,-5,-7,-5,-3,0,0,0,3,5,7,5,3,0};
  int idx = 0;
  while (!_timeUp()) {
    _display.clearDisplay();
    int ox = offsets[idx % 17];
    fillOval(EYE_LX+ox, EYE_Y, 10, 9);
    fillOval(EYE_RX+ox, EYE_Y, 10, 9);
    _display.fillRect(EYE_LX+ox-11, EYE_Y-10, 22, 6, BLACK);
    _display.drawFastHLine(EYE_LX+ox-11, EYE_Y-4, 22, WHITE);
    _display.fillRect(EYE_RX+ox-11, EYE_Y-10, 22, 6, BLACK);
    _display.drawFastHLine(EYE_RX+ox-11, EYE_Y-4, 22, WHITE);
    flatMouth();
    _display.display();
    delay(110);
    idx++;
  }
}

void OLEDFace::_sceneUwU() {
  _startScene();
  static const int pulse[] = {0, 1, 2, 1, 0};
  int idx = 0;
  while (!_timeUp()) {
    _display.clearDisplay();
    int p = pulse[idx % 5];
    // > left eye
    _display.drawLine(EYE_LX-6-p, EYE_Y-8, EYE_LX+7+p, EYE_Y,   WHITE);
    _display.drawLine(EYE_LX+7+p, EYE_Y,   EYE_LX-6-p, EYE_Y+8, WHITE);
    _display.drawLine(EYE_LX-5-p, EYE_Y-8, EYE_LX+8+p, EYE_Y,   WHITE);
    _display.drawLine(EYE_LX+8+p, EYE_Y,   EYE_LX-5-p, EYE_Y+8, WHITE);
    // < right eye
    _display.drawLine(EYE_RX+6+p, EYE_Y-8, EYE_RX-7-p, EYE_Y,   WHITE);
    _display.drawLine(EYE_RX-7-p, EYE_Y,   EYE_RX+6+p, EYE_Y+8, WHITE);
    _display.drawLine(EYE_RX+5+p, EYE_Y-8, EYE_RX-8-p, EYE_Y,   WHITE);
    _display.drawLine(EYE_RX-8-p, EYE_Y,   EYE_RX+5+p, EYE_Y+8, WHITE);
    catMouth();
    _display.display();
    delay(140);
    idx++;
  }
}

void OLEDFace::_sceneCrying() {
  _startScene();
  int tearLen = 0;
  while (!_timeUp()) {
    _display.clearDisplay();
    cryEyes(min(tearLen, 18));
    sadMouth();
    _display.display();
    tearLen++;
    if (tearLen > 24) tearLen = 0;
    delay(70);
  }
}

void OLEDFace::_sceneAngryGlitch() {
  _startScene();
  int frame = 0;
  while (!_timeUp()) {
    _display.clearDisplay();
    int glx = (frame % 4 == 0) ? random(-3, 3) : 0;
    fillOval(EYE_LX+glx, EYE_Y, 10, 9);
    fillOval(EYE_RX+glx, EYE_Y, 10, 9);
    for (int i = 0; i < 5; i++) {
      _display.drawFastHLine(EYE_LX+glx+i-4, EYE_Y-10+i, 6-i, BLACK);
      _display.drawFastHLine(EYE_RX+glx-i-2, EYE_Y-10+i, 6-i, BLACK);
    }
    _display.drawLine(EYE_LX+glx-10, EYE_Y-11, EYE_LX+glx+8,  EYE_Y-15, WHITE);
    _display.drawLine(EYE_LX+glx-10, EYE_Y-12, EYE_LX+glx+8,  EYE_Y-16, WHITE);
    _display.drawLine(EYE_RX+glx-8,  EYE_Y-15, EYE_RX+glx+10, EYE_Y-11, WHITE);
    _display.drawLine(EYE_RX+glx-8,  EYE_Y-16, EYE_RX+glx+10, EYE_Y-12, WHITE);
    tremble(frame);
    _display.display();
    delay(frame % 3 == 0 ? 35 : 75);
    frame++;
  }
}

void OLEDFace::_sceneHeartEyes() {
  _startScene();
  static const int sc[] = {5, 6, 7, 6, 5};
  int idx = 0;
  while (!_timeUp()) {
    _display.clearDisplay();
    int s = sc[idx % 5];
    _display.fillCircle(EYE_LX-s, EYE_Y, s, WHITE);
    _display.fillCircle(EYE_LX+s, EYE_Y, s, WHITE);
    _display.fillTriangle(EYE_LX-s*2, EYE_Y, EYE_LX+s*2, EYE_Y, EYE_LX, EYE_Y+s*2+2, WHITE);
    _display.fillCircle(EYE_RX-s, EYE_Y, s, WHITE);
    _display.fillCircle(EYE_RX+s, EYE_Y, s, WHITE);
    _display.fillTriangle(EYE_RX-s*2, EYE_Y, EYE_RX+s*2, EYE_Y, EYE_RX, EYE_Y+s*2+2, WHITE);
    smile();
    _display.display();
    delay(110);
    idx++;
  }
}

void OLEDFace::_sceneDeadInside() {
  _startScene();
  int frame = 0;
  while (!_timeUp()) {
    _display.clearDisplay();
    deadEyes();
    frown();
    if (frame % 7 == 0) {
      _display.drawFastHLine(random(0, 64), random(5, 60), random(10, 60), WHITE);
    }
    _display.display();
    delay(90);
    frame++;
  }
}

void OLEDFace::_sceneSleepy() {
  _startScene();
  static const int heights[] = {10,8,6,4,2,1,1,1,1,2,4,6,8,10,10,10};
  static const int dls[]     = {60,60,60,55,50,80,120,100,80,55,55,60,60,60,250,250};
  int idx = 0;
  while (!_timeUp()) {
    _display.clearDisplay();
    sleepyEyes(max(1, heights[idx % 16]));
    smirk();
    _display.setTextSize(1);
    _display.setTextColor(WHITE);
    _display.setCursor(100, 5); _display.print(F("z"));
    _display.setCursor(108, 2); _display.print(F("z"));
    _display.setCursor(116, 0); _display.print(F("z"));
    _display.display();
    delay(dls[idx % 16]);
    idx++;
  }
}

void OLEDFace::_sceneDizzy() {
  _startScene();
  int frame = 0;
  while (!_timeUp()) {
    _display.clearDisplay();
    int ox = (frame % 4 < 2) ? 1 : -1;
    int oy = (frame % 4 == 0 || frame % 4 == 3) ? -1 : 1;
    _display.drawCircle(EYE_LX, EYE_Y,    10, WHITE);
    _display.drawCircle(EYE_LX+ox, EYE_Y+oy, 5, WHITE);
    _display.fillCircle(EYE_LX+ox*2, EYE_Y+oy*2, 2, WHITE);
    _display.drawCircle(EYE_RX, EYE_Y,    10, WHITE);
    _display.drawCircle(EYE_RX-ox, EYE_Y+oy, 5, WHITE);
    _display.fillCircle(EYE_RX-ox*2, EYE_Y+oy*2, 2, WHITE);
    for (int x = CX-22; x < CX+22; x++) {
      int y = MOUTH_Y + (int)(3 * sinf((x + frame) * 0.38f));
      _display.drawPixel(x, y,   WHITE);
      _display.drawPixel(x, y+1, WHITE);
    }
    _display.display();
    delay(55);
    frame++;
  }
}

void OLEDFace::_sceneWinkCute() {
  _startScene();
  bool leftSide = false;
  while (!_timeUp()) {
    _display.clearDisplay();
    winkEyes(leftSide);
    smile();
    _display.display();
    delay(850);
    leftSide = !leftSide;
    _display.clearDisplay();
    cuteEyes();
    smile();
    _display.display();
    delay(350);
  }
}

void OLEDFace::_sceneTwT() {
  _startScene();
  int drop1 = 0, drop2 = 5;
  while (!_timeUp()) {
    _display.clearDisplay();
    twtEyes();
    sadMouth();
    if (drop1 < 26) _display.drawFastVLine(EYE_LX+1, EYE_Y+10+drop1, 5, WHITE);
    if (drop2 < 26) _display.drawFastVLine(EYE_RX+1, EYE_Y+10+drop2, 5, WHITE);
    _display.display();
    drop1 += 2; drop2 += 3;
    if (drop1 > 30) drop1 = 0;
    if (drop2 > 30) drop2 = 0;
    delay(55);
  }
}

void OLEDFace::_sceneSurprise() {
  _startScene();
  int phase = 0;
  unsigned long phaseStart = millis();
  while (!_timeUp()) {
    _display.clearDisplay();
    unsigned long el = millis() - phaseStart;
    if (phase == 0) {
      int s = min((int)(el / 18), 12);
      fillOval(EYE_LX, EYE_Y, s, s);
      fillOval(EYE_RX, EYE_Y, s, s);
      ohMouth();
      if (el > 220) { phase = 1; phaseStart = millis(); }
    } else if (phase == 1) {
      fillOval(EYE_LX, EYE_Y, 12, 12);
      fillOval(EYE_RX, EYE_Y, 12, 12);
      ohMouth();
      if (el > 1100) { phase = 2; phaseStart = millis(); }
    } else {
      int s = max(12 - (int)(el / 80), 9);
      fillOval(EYE_LX, EYE_Y, s, s);
      fillOval(EYE_RX, EYE_Y, s, s);
      smirk();
    }
    _display.display();
    delay(18);
  }
}

void OLEDFace::_sceneStarEyes() {
  _startScene();
  int frame = 0;
  while (!_timeUp()) {
    _display.clearDisplay();
    int r = 8 + (frame % 4 < 2 ? 1 : 0);
    int d = r - 2;
    for (int ox = -1; ox <= 1; ox++) {
      _display.drawFastHLine(EYE_LX-r, EYE_Y+ox, r*2+1, WHITE);
      _display.drawFastVLine(EYE_LX+ox, EYE_Y-r, r*2+1, WHITE);
      _display.drawFastHLine(EYE_RX-r, EYE_Y+ox, r*2+1, WHITE);
      _display.drawFastVLine(EYE_RX+ox, EYE_Y-r, r*2+1, WHITE);
    }
    _display.drawLine(EYE_LX-d, EYE_Y-d, EYE_LX+d, EYE_Y+d, WHITE);
    _display.drawLine(EYE_LX+d, EYE_Y-d, EYE_LX-d, EYE_Y+d, WHITE);
    _display.drawLine(EYE_RX-d, EYE_Y-d, EYE_RX+d, EYE_Y+d, WHITE);
    _display.drawLine(EYE_RX+d, EYE_Y-d, EYE_RX-d, EYE_Y+d, WHITE);
    smile();
    _display.display();
    delay(90);
    frame++;
  }
}

void OLEDFace::_sceneDotBounce() {
  _startScene();
  float t = 0;
  while (!_timeUp()) {
    _display.clearDisplay();
    int oy1 = (int)(7 * sinf(t));
    int oy2 = (int)(7 * sinf(t + 1.2f));
    _display.fillCircle(EYE_LX, EYE_Y + oy1, 5, WHITE);
    _display.fillCircle(EYE_RX, EYE_Y + oy2, 5, WHITE);
    flatMouth();
    _display.display();
    t += 0.13f;
    delay(28);
  }
}

void OLEDFace::_sceneGlitchScan() {
  _startScene();
  int frame = 0;
  while (!_timeUp()) {
    _display.clearDisplay();
    emoEyes();
    flatMouth();
    int scanY = (frame * 3) % OLED_H;
    _display.drawFastHLine(0, scanY, OLED_W, WHITE);
    for (int n = 0; n < 6; n++) {
      _display.drawPixel(random(OLED_W), random(OLED_H), WHITE);
    }
    _display.display();
    delay(45);
    frame++;
  }
}

// ════════════════════════════════════════════════════════════
//  SCENE IMPLEMENTATIONS — NEW EXPRESSIONS
// ════════════════════════════════════════════════════════════

// SQUARE EYES — retro/robot square pupils blink + flat mouth
void OLEDFace::_sceneSquareEyes() {
  _startScene();
  // blink: rect height shrinks to a line then reopens
  static const int hs[] = {18, 14, 10, 5, 2, 1, 2, 5, 10, 14, 18, 18, 18};
  static const int ds[] = {60, 55, 50, 40, 35, 40, 35, 40, 50, 55, 60, 300, 300};
  int idx = 0;
  while (!_timeUp()) {
    _display.clearDisplay();
    int h = hs[idx % 13];
    int yt = EYE_Y - h/2;
    _display.drawRoundRect(EYE_LX-10, yt, 20, h, 2, WHITE);
    _display.drawRoundRect(EYE_RX-10, yt, 20, h, 2, WHITE);
    if (h >= 8) {
      // pupil only when eye open enough
      _display.fillRect(EYE_LX-3, EYE_Y-3, 6, 6, WHITE);
      _display.fillRect(EYE_RX-3, EYE_Y-3, 6, 6, WHITE);
    }
    flatMouth();
    _display.display();
    delay(ds[idx % 13]);
    idx++;
  }
}

// PIXEL HAPPY — 3x3 pixel face cycles through expressions
void OLEDFace::_scenePixelHappy() {
  _startScene();
  // pixel patterns: each is a 9-bit mask, rows top→bottom
  // happy eyes: 0b010010010 = centre column lit
  // blink:      0b000000000 = all off
  // wink:       0b010000010 = left off, right lit
  static const uint8_t patterns[] = {
    0b11011011,  // full grid (surprised)
    0b01001010,  // normal open
    0b00000000,  // blink closed
    0b01001010,  // reopen
    0b01000010,  // wink (left closed)
    0b01001010,  // normal
  };
  static const int dls[] = {80, 300, 80, 300, 600, 300};
  int idx = 0;
  while (!_timeUp()) {
    _display.clearDisplay();
    pixelEyes(patterns[idx % 6]);
    // pixel mouth: happy arc drawn as 5 pixels
    _display.drawPixel(CX-6, MOUTH_Y+4, WHITE);
    _display.drawPixel(CX-3, MOUTH_Y+6, WHITE);
    _display.drawPixel(CX,   MOUTH_Y+7, WHITE);
    _display.drawPixel(CX+3, MOUTH_Y+6, WHITE);
    _display.drawPixel(CX+6, MOUTH_Y+4, WHITE);
    _display.display();
    delay(dls[idx % 6]);
    idx++;
  }
}

// ROBOT SCAN — scan line through square eyes + data readout
void OLEDFace::_sceneRobotScan() {
  _startScene();
  int scanLine = EYE_Y - 9;
  int dir = 1;
  int frame = 0;
  while (!_timeUp()) {
    _display.clearDisplay();
    // square eye frames
    _display.drawRoundRect(EYE_LX-10, EYE_Y-9, 20, 18, 2, WHITE);
    _display.drawRoundRect(EYE_RX-10, EYE_Y-9, 20, 18, 2, WHITE);
    // moving scan line inside eyes
    _display.drawFastHLine(EYE_LX-9, scanLine, 18, WHITE);
    _display.drawFastHLine(EYE_RX-9, scanLine, 18, WHITE);
    flatMouth();
    // data text on right
    _display.setTextSize(1); _display.setTextColor(WHITE);
    _display.setCursor(0, 2);
    _display.print(F("SYS:"));
    _display.setCursor(0, 12);
    _display.print(F("OK"));
    // progress bar at bottom
    int barW = (frame * 3) % OLED_W;
    _display.drawRect(0, OLED_H-6, OLED_W, 5, WHITE);
    _display.fillRect(1, OLED_H-5, barW > 0 ? min(barW, OLED_W-2) : 1, 3, WHITE);
    _display.display();
    scanLine += dir;
    if (scanLine >= EYE_Y+8 || scanLine <= EYE_Y-9) dir = -dir;
    delay(50);
    frame++;
  }
}

// LOADING — spinning arc eyes + "..." mouth
void OLEDFace::_sceneLoading() {
  _startScene();
  int angle = 0;
  int dots = 0;
  int dotTimer = 0;
  while (!_timeUp()) {
    _display.clearDisplay();
    // spinning arcs for each eye using partial circle segments
    int r = 10;
    for (int deg = angle; deg < angle + 270; deg += 5) {
      float rad = deg * 3.14159f / 180.0f;
      int px = EYE_LX + (int)(r * cosf(rad));
      int py = EYE_Y  + (int)(r * sinf(rad));
      _display.drawPixel(px, py, WHITE);
      _display.drawPixel(px+1, py, WHITE);
      px = EYE_RX + (int)(r * cosf(rad + 3.14159f));
      py = EYE_Y  + (int)(r * sinf(rad + 3.14159f));
      _display.drawPixel(px, py, WHITE);
      _display.drawPixel(px+1, py, WHITE);
    }
    // dot-dot-dot mouth cycling
    _display.setTextSize(1); _display.setTextColor(WHITE);
    _display.setCursor(CX-10, MOUTH_Y);
    for (int d = 0; d <= dots; d++) _display.print(F("."));
    _display.display();
    angle = (angle + 18) % 360;
    dotTimer++;
    if (dotTimer > 8) { dotTimer = 0; dots = (dots + 1) % 3; }
    delay(40);
  }
}

// SHY BLUSH — eyes look down, blush, small smile
void OLEDFace::_sceneShyBlush() {
  _startScene();
  // gentle look-down then up motion
  static const int lookY[] = {3, 4, 5, 5, 5, 5, 4, 3, 2, 1, 0, 0};
  int idx = 0;
  while (!_timeUp()) {
    _display.clearDisplay();
    int ly = lookY[idx % 12];
    fillOval(EYE_LX, EYE_Y + ly, 8, 6);
    fillOval(EYE_RX, EYE_Y + ly, 8, 6);
    // eyelid
    _display.fillRect(EYE_LX-9, EYE_Y+ly-8, 18, 8, BLACK);
    _display.fillRect(EYE_RX-9, EYE_Y+ly-8, 18, 8, BLACK);
    _display.drawFastHLine(EYE_LX-8, EYE_Y+ly-2, 16, WHITE);
    _display.drawFastHLine(EYE_RX-8, EYE_Y+ly-2, 16, WHITE);
    // blush (dotted cheeks)
    for (int i = 0; i < 5; i++) {
      _display.drawPixel(EYE_LX-18+i*3, EYE_Y+14, i%2==0 ? WHITE : BLACK);
      _display.drawPixel(EYE_RX+ 6+i*3, EYE_Y+14, i%2==0 ? WHITE : BLACK);
    }
    // small sweet smile
    smirk();
    _display.display();
    delay(160);
    idx++;
  }
}

// SKEPTICAL — one eye normal, one squinted + raised brow
void OLEDFace::_sceneSkeptical() {
  _startScene();
  // slow brow raise animation then hold
  int browY = -14;
  int browDir = -1;
  unsigned long holdStart = 0;
  bool holding = false;
  while (!_timeUp()) {
    _display.clearDisplay();
    skepticalEyes();
    flatMouth();
    _display.display();
    delay(200);  // skeptical is slow and deliberate
  }
}

// ════════════════════════════════════════════════════════════
//  SCENE IMPLEMENTATIONS — GESTURES
// ════════════════════════════════════════════════════════════

// WAVE — small face left, hand waves right
void OLEDFace::_sceneWave() {
  _startScene();
  // hand Y oscillation path (smooth sine-like)
  static const int waveY[] = {18,21,25,29,33,29,25,21,18};
  int idx = 0;
  while (!_timeUp()) {
    _display.clearDisplay();
    // mini face, left side
    fillOval(18, 26, 8, 7);   // left eye
    fillOval(34, 26, 8, 7);   // right eye
    _display.fillRect(14, 22, 5, 4, BLACK); // gleam L
    _display.fillRect(30, 22, 5, 4, BLACK); // gleam R
    drawMouth(10, 40, 26, 50, 42, 40);     // smile
    // waving hand right side
    drawHandOpen(84, waveY[idx % 9]);
    _display.display();
    delay(70);
    idx++;
  }
}

// THUMBS UP — build up then hold
void OLEDFace::_sceneThumbsUp() {
  _startScene();
  // Phase 1: hand slides in from bottom
  for (int y = OLED_H; y > 30 && !_timeUp(); y -= 4) {
    _display.clearDisplay();
    cuteEyes();
    smile();
    drawThumbsUp(88, y);
    _display.display();
    delay(40);
  }
  // Phase 2: hold with happy face blinking
  static const int bh[] = {10, 6, 2, 0, 2, 6, 10, 10};
  static const int bd[] = {60, 45, 30, 30, 30, 45, 60, 600};
  int idx = 0;
  while (!_timeUp()) {
    _display.clearDisplay();
    int h = bh[idx % 8];
    if (h > 0) { cuteEyes(); } else {
      _display.drawFastHLine(EYE_LX-11, EYE_Y, 22, WHITE);
      _display.drawFastHLine(EYE_RX-11, EYE_Y, 22, WHITE);
    }
    smile();
    drawThumbsUp(88, 30);
    _display.display();
    delay(bd[idx % 8]);
    idx++;
  }
}

// HANDSHAKE — two fists approach, clasp, shake up/down
void OLEDFace::_sceneHandshake() {
  _startScene();
  int by = 28;
  // approach phase
  for (int sep = 38; sep >= 0 && !_timeUp(); sep -= 4) {
    _display.clearDisplay();
    // left fist (mirrored — draw pointing right)
    drawFist(CX - 22 - sep/2, by);
    // right fist
    drawFist(CX + 4  + sep/2, by);
    _display.display();
    delay(50);
  }
  // shake phase — up/down with starburst on first contact
  static const int shakeY[] = {28, 23, 28, 33, 28, 23, 28};
  int idx = 0;
  bool burst = true;
  while (!_timeUp()) {
    _display.clearDisplay();
    int sy = shakeY[idx % 7];
    drawFist(CX-22, sy);
    drawFist(CX+ 4, sy);
    // contact starburst on first few frames
    if (burst && idx < 4) {
      int bx = CX-1, bby = sy+7;
      for (int d = 0; d < 8; d++) {
        float a = d * 3.14159f / 4;
        _display.drawLine(bx, bby,
                          bx + (int)(8*cosf(a)),
                          bby + (int)(8*sinf(a)), WHITE);
      }
    } else { burst = false; }
    _display.display();
    delay(75);
    idx++;
  }
}

// ════════════════════════════════════════════════════════════
//  SCENE IMPLEMENTATION — BULLET DODGE
// ════════════════════════════════════════════════════════════

void OLEDFace::_sceneBulletDodge() {
  _startScene();

  // Face is centred. Bullet flies in from left, face dodges up/down.
  // Phase: 0=approach+neutral, 1=bullet close+dodge, 2=bullet past+return, 3=relief

  float bulletX   = -8.0f;   // bullet X position
  float bulletY   = EYE_Y + 12; // bullet travels at mouth height
  float faceOffY  = 0.0f;    // face Y offset (dodge)
  int   phase     = 0;
  unsigned long phaseT = millis();

  while (!_timeUp()) {
    _display.clearDisplay();

    // ── Update state ──
    unsigned long el = millis() - phaseT;

    if (phase == 0) {
      // bullet approaching fast
      bulletX += 3.5f;
      if (bulletX > CX - 30) { phase = 1; phaseT = millis(); }
    }
    else if (phase == 1) {
      // bullet close! face dodges up
      bulletX += 4.5f;
      faceOffY -= 3.0f;
      faceOffY = max(faceOffY, -18.0f);
      if (bulletX > OLED_W + 8) { phase = 2; phaseT = millis(); }
    }
    else if (phase == 2) {
      // bullet gone, face returns down smoothly
      faceOffY += 2.0f;
      faceOffY = min(faceOffY, 0.0f);
      if (el > 400) { phase = 3; phaseT = millis(); }
    }
    else {
      // relief blink + smirk, then reset bullet
      faceOffY = 0;
      if (el > 1500) {
        bulletX = -8.0f;
        phase   = 0;
        phaseT  = millis();
      }
    }

    int fo = (int)faceOffY;

    // ── Draw eyes at offset position ──
    if (phase == 1) {
      // wide surprised eyes during dodge
      fillOval(EYE_LX, EYE_Y + fo, 12, 12);
      fillOval(EYE_RX, EYE_Y + fo, 12, 12);
    } else if (phase == 3) {
      // relief: sleepy/smiling eyes
      sleepyEyes(4);
      // shift upward manually not possible since sleepyEyes uses const — re-draw offset:
      _display.clearDisplay();
      fillOval(EYE_LX, EYE_Y, 10, 4);
      fillOval(EYE_RX, EYE_Y, 10, 4);
      _display.fillRect(EYE_LX-11, EYE_Y-10, 22, 7, BLACK);
      _display.fillRect(EYE_RX-11, EYE_Y-10, 22, 7, BLACK);
      _display.drawFastHLine(EYE_LX-10, EYE_Y-3, 20, WHITE);
      _display.drawFastHLine(EYE_RX-10, EYE_Y-3, 20, WHITE);
    } else {
      // normal cute eyes at offset
      fillOval(EYE_LX, EYE_Y + fo, 11, 10);
      fillOval(EYE_RX, EYE_Y + fo, 11, 10);
      _display.fillRect(EYE_LX-5, EYE_Y+fo-5, 4, 4, BLACK);
      _display.fillRect(EYE_RX-5, EYE_Y+fo-5, 4, 4, BLACK);
    }

    // ── Draw mouth at offset ──
    if (phase == 1) {
      ohMouth(); // surprised O mouth
    } else if (phase == 3) {
      smirk();   // relief smirk
    } else {
      flatMouth(); // neutral while watching
    }

    // ── Draw bullet (only during phases 0 and 1) ──
    if (phase < 2 && bulletX > -8 && bulletX < OLED_W + 8) {
      int bx = (int)bulletX;
      int bby = (int)bulletY;
      // bullet body
      _display.fillRect(bx-6, bby-2, 10, 4, WHITE);
      // bullet tip (triangle-ish)
      _display.fillTriangle(bx+4, bby-2, bx+4, bby+2, bx+9, bby, WHITE);
      // motion trail
      for (int t = 1; t <= 4; t++) {
        int ty = bby + (t % 2 == 0 ? 0 : 1);
        _display.drawFastHLine(bx-6-t*4, ty-1, 5, WHITE);
      }
    }

    // ── "DODGE!" text when dodging ──
    if (phase == 1 && faceOffY < -10) {
      _display.setTextSize(1); _display.setTextColor(WHITE);
      _display.setCursor(2, 54); _display.print(F("DODGE!"));
    }

    // ── "phew~" text on relief ──
    if (phase == 3) {
      _display.setTextSize(1); _display.setTextColor(WHITE);
      _display.setCursor(CX+10, EYE_Y-8); _display.print(F("phew~"));
    }

    _display.display();
    delay(28);
  }
}
