/*
 * ============================================================
 *  OLEDFace_Demo.ino  —  Example Sketch
 *
 *  Demonstrates every feature of the OLEDFace library:
 *    • All facial expressions (emo + cute)
 *    • New expressions: square eyes, pixel, robot, loading,
 *      shy blush, skeptical
 *    • Gesture animations: wave, thumbs up, handshake
 *    • Special: bullet dodge
 *    • Custom playlists
 *    • Adjustable scene duration
 *
 *  Wiring (Arduino Uno + 0.96" SSD1306 I2C OLED):
 *    OLED VCC  →  3.3V or 5V
 *    OLED GND  →  GND
 *    OLED SDA  →  A4
 *    OLED SCL  →  A5
 *
 *  Library folder setup:
 *    Arduino/libraries/
 *      OLEDFace/
 *        OLEDFace.h
 *        OLEDFace.cpp
 *    Sketches/
 *      OLEDFace_Demo/
 *        OLEDFace_Demo.ino   ← this file
 * ============================================================
 */

#include "OLEDFace.h"

OLEDFace face;

void setup() {
  Serial.begin(9600);

  // Initialise the display.
  // Returns false if SSD1306 is not found — check your wiring.
  if (!face.begin()) {
    Serial.println(F("OLED not found! Check wiring (SDA=A4, SCL=A5)"));
    while (true);  // halt
  }

  // Show the boot splash for ~1.8 seconds
  face.showSplash();

  // ── Optional: change how long each scene plays ────────────
  // Default is 3000 ms (3 seconds). Change to taste:
  face.setSceneDuration(3000);
}

void loop() {
  // ── DEMO MODE A: play every scene once, then loop ─────────
  // Uncomment this line for a full automatic demo:
  // face.playAll();

  // ── DEMO MODE B: play a hand-picked playlist ──────────────
  // Pick any scenes you want using the SCENE_* constants.
  // They play in order, then the function returns.
  // Wrap in loop() to repeat.

  // === CUTE PLAYLIST ========================================
  uint8_t cutePL[] = {
    SCENE_CUTE_HAPPY,   // big blinking eyes + smile
    SCENE_HEART_EYES,   // pulsing heart eyes
    SCENE_UWU,          // uwu  > < eyes + cat mouth
    SCENE_WINK_CUTE,    // alternating wink
    SCENE_SHY_BLUSH,    // downcast eyes + blush dots
    SCENE_STAR_EYES,    // sparkle * eyes
    SCENE_DOT_BOUNCE,   // bouncing dot eyes
    SCENE_PIXEL_HAPPY,  // 3x3 pixel face
  };
  face.playList(cutePL, sizeof(cutePL));

  // === EMO PLAYLIST =========================================
  uint8_t emoPL[] = {
    SCENE_EMO_STARE,    // heavy-lid eyes drift
    SCENE_CRYING,       // growing tears
    SCENE_DEAD_INSIDE,  // X eyes + glitch lines
    SCENE_TWT,          // TwT falling tears
    SCENE_SLEEPY,       // slow-close eyes + Zzz
    SCENE_DIZZY,        // spinning spiral eyes
    SCENE_ANGRY_GLITCH, // angry brows + shaking mouth
    SCENE_GLITCH_SCAN,  // scan line + pixel noise
    SCENE_SKEPTICAL,    // one squinted eye + raised brow
  };
  face.playList(emoPL, sizeof(emoPL));

  // === ROBOT / SPECIAL PLAYLIST =============================
  uint8_t robotPL[] = {
    SCENE_SQUARE_EYES,  // retro square eyes blink
    SCENE_ROBOT_SCAN,   // scan line inside square eyes
    SCENE_LOADING,      // spinning arc eyes + dot mouth
  };
  face.playList(robotPL, sizeof(robotPL));

  // === GESTURE PLAYLIST =====================================
  uint8_t gesturePL[] = {
    SCENE_WAVE,         // mini face + waving hand
    SCENE_THUMBS_UP,    // hand slides up + blink
    SCENE_HANDSHAKE,    // two fists approach + shake
  };
  face.playList(gesturePL, sizeof(gesturePL));

  // === SPECIAL EFFECT =======================================
  face.playScene(SCENE_SURPRISE);      // snap-wide eyes
  face.playScene(SCENE_BULLET_DODGE);  // bullet flies by, face dodges!

  // After one full loop, start again from the top of loop()
}

// ════════════════════════════════════════════════════════════
//  QUICK REFERENCE — All scene IDs
// ════════════════════════════════════════════════════════════
/*
  FACIAL EXPRESSIONS (Cute)
    SCENE_CUTE_HAPPY    Big blinking oval eyes + wide smile
    SCENE_HEART_EYES    Pulsing heart-shaped eyes
    SCENE_UWU           > < anime eyes + cat ~w~ mouth
    SCENE_WINK_CUTE     Alternating wink + smile
    SCENE_SHY_BLUSH     Downcast eyes + cheek blush dots
    SCENE_STAR_EYES     Sparkle / starburst * eyes
    SCENE_DOT_BOUNCE    Tiny bouncing dot eyes
    SCENE_PIXEL_HAPPY   3x3 pixelated face
    SCENE_SURPRISE      Eyes snap wide open then settle

  FACIAL EXPRESSIONS (Emo)
    SCENE_EMO_STARE     Heavy-lidded eyes drift left/right
    SCENE_CRYING        Tears grow longer then reset
    SCENE_DEAD_INSIDE   X X eyes + frown + glitch lines
    SCENE_TWT           TwT T-shaped eyes + falling tears
    SCENE_SLEEPY        Eyes slowly close/open + Zzz
    SCENE_DIZZY         Spinning concentric-circle eyes
    SCENE_ANGRY_GLITCH  Angry brows + trembling mouth
    SCENE_GLITCH_SCAN   Scan line sweep + pixel noise
    SCENE_SKEPTICAL     One normal, one squinted + raised brow

  ROBOT / SPECIAL EYES
    SCENE_SQUARE_EYES   Hollow square eyes blink
    SCENE_ROBOT_SCAN    Scan line inside square eyes + HUD
    SCENE_LOADING       Spinning arc eyes + "..." mouth

  GESTURES
    SCENE_WAVE          Mini face + oscillating open hand
    SCENE_THUMBS_UP     Hand slides in + thumb up + blink
    SCENE_HANDSHAKE     Two fists approach + handshake shake

  SPECIAL ANIMATION
    SCENE_BULLET_DODGE  Bullet flies in, face dodges + "DODGE!"
                        then relief smirk + "phew~"
*/
