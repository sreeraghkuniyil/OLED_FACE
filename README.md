# OLEDFace Arduino Library

A reusable Arduino library for animated eye + mouth expressions on a 0.96" SSD1306 OLED display. No face circle. Pure expressive eyes and mouths — emo, cute, robotic, and gesture animations.

---

## Hardware Requirements

| Component | Detail |
|---|---|
| Microcontroller | Arduino Uno (or compatible) |
| Display | 0.96" SSD1306 OLED, 128×64, I2C |
| Libraries needed | Adafruit GFX Library, Adafruit SSD1306 |

### Wiring

```
OLED VCC  →  5V (or 3.3V)
OLED GND  →  GND
OLED SDA  →  A4
OLED SCL  →  A5
```

---

## Installation

1. Copy the `OLEDFace` folder into your Arduino `libraries` directory:

```
Documents/
  Arduino/
    libraries/
      OLEDFace/
        OLEDFace.h
        OLEDFace.cpp
        OLEDFace_Demo/
          OLEDFace_Demo.ino
        README.md
```

2. Restart the Arduino IDE.
3. Open `File → Examples → OLEDFace → OLEDFace_Demo`.

---

## Quick Start

```cpp
#include "OLEDFace.h"

OLEDFace face;

void setup() {
  face.begin();          // initialise display
  face.showSplash();     // boot splash screen
  face.setSceneDuration(3000);  // 3 seconds per scene
}

void loop() {
  face.playScene(SCENE_CUTE_HAPPY);   // play one scene
  face.playScene(SCENE_WAVE);         // then another
}
```

---

## API Reference

### Initialisation

```cpp
bool begin(uint8_t i2cAddr = 0x3C);
```
Initialise the OLED. Returns `false` if display not found. Default I2C address is `0x3C` (some displays use `0x3D`).

```cpp
void setSceneDuration(uint16_t ms);
```
Set how long each scene plays. Default: `3000` (3 seconds).

```cpp
void showSplash();
```
Show the library boot splash screen (~1.8 seconds).

---

### Playing Scenes

```cpp
void playScene(uint8_t sceneId);
```
Play a single scene by its ID constant. Blocks for the scene duration.

```cpp
void playAll();
```
Cycle through **all 25 scenes** in order, forever. Never returns.

```cpp
void playList(const uint8_t* ids, uint8_t count);
```
Play a custom ordered list of scenes.

```cpp
// Example playlist:
uint8_t myList[] = { SCENE_CUTE_HAPPY, SCENE_WAVE, SCENE_BULLET_DODGE };
face.playList(myList, 3);
```

---

### Scene ID Constants

#### Cute Expressions
| Constant | Description |
|---|---|
| `SCENE_CUTE_HAPPY` | Big blinking oval eyes + wide smile |
| `SCENE_HEART_EYES` | Pulsing heart-shaped eyes + smile |
| `SCENE_UWU` | `> <` anime eyes + cat `~w~` mouth |
| `SCENE_WINK_CUTE` | Alternating wink + smile |
| `SCENE_SHY_BLUSH` | Downcast eyes + cheek blush dots + smirk |
| `SCENE_STAR_EYES` | Sparkle `✦` burst eyes + smile |
| `SCENE_DOT_BOUNCE` | Tiny bouncing dot eyes |
| `SCENE_PIXEL_HAPPY` | 3×3 pixel-art face with blink/wink |
| `SCENE_SURPRISE` | Eyes snap wide open, settle to smirk |

#### Emo Expressions
| Constant | Description |
|---|---|
| `SCENE_EMO_STARE` | Heavy-lidded eyes slowly drift left/right |
| `SCENE_CRYING` | Tears grow from eyes and reset |
| `SCENE_DEAD_INSIDE` | ✕✕ eyes + frown + random glitch lines |
| `SCENE_TWT` | TwT T-bar eyes + falling teardrops |
| `SCENE_SLEEPY` | Eyes slowly close/open + floating `Zzz` |
| `SCENE_DIZZY` | Spinning concentric-circle spiral eyes |
| `SCENE_ANGRY_GLITCH` | Angry brows + trembling jagged mouth |
| `SCENE_GLITCH_SCAN` | Scan line sweep + pixel noise |
| `SCENE_SKEPTICAL` | One normal eye, one squinted + raised brow |

#### Robot / Special Eyes
| Constant | Description |
|---|---|
| `SCENE_SQUARE_EYES` | Hollow square eyes with pupil — blink |
| `SCENE_ROBOT_SCAN` | Scan line inside square eyes + HUD readout |
| `SCENE_LOADING` | Spinning arc eyes + `...` cycling mouth |

#### Gesture Animations
| Constant | Description |
|---|---|
| `SCENE_WAVE` | Mini face on left + oscillating open hand |
| `SCENE_THUMBS_UP` | Hand slides in from bottom + thumb up + blink |
| `SCENE_HANDSHAKE` | Two fists approach + shake + starburst contact |

#### Special Effects
| Constant | Description |
|---|---|
| `SCENE_BULLET_DODGE` | Bullet flies across screen, face dodges up + "DODGE!" text, then relief smirk + "phew~" |

---

### Low-Level Drawing API

For advanced use, all drawing primitives are public:

```cpp
// Geometry
face.fillOval(cx, cy, radiusW, radiusH);
face.drawOval(cx, cy, radiusW, radiusH);
face.drawMouth(x0, y0, ctrlX, ctrlY, x1, y1);  // Bezier curve

// Mouths
face.smile();      // wide grin
face.smirk();      // gentle smile
face.flatMouth();  // straight line — neutral
face.frown();      // full frown
face.sadMouth();   // small sad curve
face.ohMouth();    // open "O" circle
face.catMouth();   // ~w~ double curve
face.tremble(seed); // jagged shaking mouth

// Eyes
face.cuteEyes();         // big filled ovals + gleam
face.emoEyes();          // heavy-lid eyes
face.deadEyes();         // X X crosses
face.starEyes();         // starburst lines
face.uwuEyes();          // > < anime arrows
face.twtEyes();          // T-bar eyes
face.sleepyEyes(openH);  // half-lid, openH 1–10
face.dotEyes();          // small filled circles
face.dizzyEyes();        // concentric spirals
face.winkEyes(leftWink); // one eye closed
face.angryEyes();        // slanted + thick brows
face.heartEyes();        // heart shapes
face.cryEyes(tearLen);   // half-closed + tear
face.squareEyes();       // hollow rounded rects
face.pixelEyes(pattern); // 3x3 pixel bitmask
face.skepticalEyes();    // asymmetric brows
face.shyEyes();          // downcast + blush dots

// Hands
face.drawHandOpen(x, y);   // open palm
face.drawThumbsUp(x, y);   // thumb-up fist
face.drawFist(x, y);       // closed fist
```

---

### Customising Layout

The layout constants are defined in `OLEDFace.h`. To move eyes/mouth, change the `private` static members in the class — or modify the `#define` values in `.h` to your preference:

```cpp
static const int CX      = 64;   // screen centre X
static const int EYE_Y   = 22;   // eye row Y
static const int EYE_LX  = 38;   // left eye X
static const int EYE_RX  = 90;   // right eye X
static const int MOUTH_Y = 46;   // mouth baseline Y
```

---

## Project Structure

```
OLEDFace/
├── OLEDFace.h           ← Class declaration + scene ID constants
├── OLEDFace.cpp         ← Full implementation (all scenes)
├── OLEDFace_Demo/
│   └── OLEDFace_Demo.ino ← Example sketch with playlists
└── README.md            ← This file
```

---

## Adding Your Own Scene

1. Declare it in `OLEDFace.h`:
```cpp
#define SCENE_MY_CUSTOM  25   // bump SCENE_COUNT to 26
```

2. Add a private method declaration in `OLEDFace.h`:
```cpp
void _sceneMyCustom();
```

3. Add the switch case in `OLEDFace.cpp` inside `playScene()`:
```cpp
case SCENE_MY_CUSTOM: _sceneMyCustom(); break;
```

4. Implement it in `OLEDFace.cpp`:
```cpp
void OLEDFace::_sceneMyCustom() {
  _startScene();
  while (!_timeUp()) {
    _display.clearDisplay();
    cuteEyes();            // use any eye style
    smile();               // use any mouth style
    _display.display();
    delay(16);
  }
}
```

---

## Images

### KawaiiRobo Showcase

| Preview | Description |
|---|---|
| ![](imgs/KawaiRobo.1.jpeg) | Main front view of KawaiiRobo |
| ![](imgs/KawaiRobo.2.jpeg) | OLED facial animation demo |
| ![](imgs/KawaiRobo.3.jpeg) | Web UI interaction preview |
| ![](imgs/KawaiRobo.4.jpeg) | Hardware and assembly view |
| ![](imgs/kawaiirobo.jpeg) | Final project showcase |

---

### Gallery

#### Main Robot
![KawaiiRobo](imgs/KawaiRobo.1.jpeg)

#### OLED Expressions
![OLED Demo](imgs/KawaiRobo.2.jpeg)

#### Web Dashboard
![Web UI](imgs/KawaiRobo.3.jpeg)

#### Hardware Setup
![Hardware](imgs/KawaiRobo.4.jpeg)

#### Final Build
![Final](imgs/kawaiirobo.jpeg)

---

---

## License

MIT — free to use, modify, and distribute.
