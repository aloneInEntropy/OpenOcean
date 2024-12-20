#ifndef SM_H
#define SM_H
#include <windows.h>
#include <iostream>
#include "util.h"

// #define TREE  // uncomment to enable cpu octree

#define WORLD_BOUND_HIGH 112
#define WORLD_BOUND_LOW -112

class Camera;
class Box;

// Scene Manager singleton
namespace SM {
enum CAMERA_MODE {
    FIRST = 0,
    THIRD = 1,
    FREE = 2
};

// Update the global delta value on each frame.
extern void updateDelta();
// How long the program has been running
extern float getGlobalTime();
// Update the delta mouse positions
extern void updateMouse(int nx, int ny);
extern void switchFirstAndThirdCam();
extern void toggleFreeCam();
extern void changeFlashlightState();
extern void changeBoidAttackState();

// delta time
extern float delta;

// start time of the program
extern DWORD startTime;

extern const float floor_position;
extern bool flashlightToggled;

extern int width;   // screen width
extern int height;  // screen height

extern glm::vec4 bgColour;
extern glm::vec2 fogBounds;
extern float seaLevel;
extern float updateDistance;

extern int unnamedMeshCount;
extern int unnamedBoneMeshCount;
extern int unnamedVariantMeshCount;

extern float mouseDX;  // mouse delta x
extern float mouseDY;  // mouse delta y

extern bool isFreeCam;      // in free cam, the player model is loaded and updates but does not move with the camera
extern bool isFirstPerson;  // in first person, the player model is not updated but the camera follows it anyway
extern bool isThirdPerson;  // in third person, the player model is loaded and the camera moves with it
extern Camera *camera;
extern CAMERA_MODE lastCamMode;
extern CAMERA_MODE camMode;
extern bool showNormal;

extern Box *sceneBox;
extern bool debug;

constexpr int MAX_NUM_BOIDS = 10000;  // maximum count of boids allowed to be rendered.
extern bool canBoidsAttack;           // toggle predator/prey behaviour of boids

};  // namespace SM

#endif /* SM_H */
