#ifndef CAMERA_H
#define CAMERA_H

#include "util.h"
#include "sm.h"
#include "player.h"
#include <GL/freeglut.h>

class Player;

class Camera {
   private:
    float acceleration = 10;  // lerp acceleration factor; to be multiplied by delta
   public:
    vec3 followPos;           // follow position; used for interpolated movement
    Camera() {
        pos = vec3(0.0f);
        followPos = vec3(0.0f);
        front = SM::FORWARD;
        up = SM::UP;

        // setup rotation quaternion
        processView();
        view = getViewMatrix();
    }

    // Process and update the camera's view matrix. The mouse's x- and y-coordinates are used to dictate the direction the player is looking.
    void processView();

    // Process camera movement through the world space.
    void processMovement();

    // Get the world view matrix for the camera.
    mat4 getViewMatrix();

    // Follow the target position `pos` who is pointing in the direction `dir` at some fixed distance
    void followTarget(vec3 pos, vec3 dir);

    // Follow the player
    void followTarget(Player*);

    // Set the camera position to some location
    void setPosition(vec3 p);

    // Variables
    vec3 pos;                    // Camera position
    vec3 front;                  // Camera direction
    vec3 up;                     // Camera up direction
    vec3 right;                  // Camera right direction
    vec3 target;                 // Camera target position
    mat4 view;                   // Model view matrix
    float targetDist = 12;       // Camera distance to target (fixed)
    float targetHorizontalDist;  // Camera horizontal distance to target
    float targetVerticalDist;    // Camera vertical distance to target

    float base_FOV = 60.0f;      // Normal (minimum) field of view
    float max_FOV = 105.0f;      // Maximum field of view
    float FOV = base_FOV;        // Camera field of view
    float pitch = 0.0;           // x-axis rotation (vertical)
    float yaw = 0.0;             // y-axis rotation (horizontal)
    float roll = 0.0;            // z-axis rotation
    float sensitivity = .15;     // Camera sensitivity
    float baseSpeed = 5.0f;      // Walking speed (movement speed)
    float sprintSpeed = 100.0f;  // Sprinting speed (movement speed)
    float speed = baseSpeed;     // Camera speed (movement speed)

    // Keyboard movement
    bool FORWARD = false;  // z+
    bool BACK = false;     // z-
    bool LEFT = false;     // x-
    bool RIGHT = false;    // x+
    bool UP = false;       // y+
    bool DOWN = false;     // y-
    bool CAN_FLY = true;   // can the player fly (i.e., move on y-axis at will)?
    bool SPRINT = false;   // is the player sprinting?
};

#endif /* CAMERA_H */
