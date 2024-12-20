#ifndef UTIL_H
#define UTIL_H

#include <cmath>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <memory>
#include <map>
#include <string>
#include <vector>
#include <random>

#define GLM_ENABLE_EXPERIMENTAL
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/matrix_interpolation.hpp>

#include <assimp/scene.h>        // collects data
#include <assimp/postprocess.h>  // various extra operations

#include "sm.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define PROJDIR "../"                                                   // path from executable to workspace folder
#define MODEL_NO_DIR(m) m.substr(0, m.find("."))                        // get model `m` without directory
#define MODELDIR(m) PROJDIR "Models/" + m.substr(0, m.find(".")) + "/"  // get model directory for model `m`
#define MIN_FLOAT_DIFF 0.00000001f                                      // minimum difference (epsilon) between floats to consider then equal

using namespace glm;
// using namespace SM;

namespace Util {
extern vec3 UP;       // World up (0, 1, 0)
extern vec3 FORWARD;  // World forward (0, 0, -1)
extern vec3 RIGHT;    // World right (1, 0, 0)
extern vec3 X;        // Value of 1 on x axis (1, 0, 0)
extern vec3 Y;        // Value of 1 on y axis (0, 1, 0)
extern vec3 Z;        // Value of 1 on z axis (0, 0, 1)
extern std::random_device rand_dev;
extern std::mt19937 mt_gen;

extern std::string readFile(const char* path);
extern float wrap(float val, float min, float max);
extern vec3 wrapV(vec3 val, vec3 min, vec3 max);
extern float sqDist(vec3 a, vec3 b);
extern float clamp(float val, float min, float max);
extern vec3 clampV(vec3 val, vec3 min, vec3 max);
extern float d2r(float val);
extern float r2d(float val);
extern aiMatrix4x4 GLMtoAI(const mat4& mat);
extern mat4 aiToGLM(const aiMatrix4x4* from);
extern vec3 aiToGLM(aiVector3D* from);
extern std::tuple<vec3, quat, vec3, vec3, vec4> decomposeMat4(mat4& mat);
extern vec3 getTranslation(mat4& mat);
extern vec3 angleToVec3(float angle);
extern float vec3ToAngle(vec3 v);
extern float lerp(float a, float b, float dt);
extern vec3 lerpV(vec3 a, vec3 b, float dt);
extern float mapRange(float v, float inLow, float inHigh, float outLow, float outHigh);
extern mat4 lookTowards(vec3 pos, vec3 to);
extern mat4 lookTowards(vec3 pos, vec3 to, vec3 up);
extern void print(vec2 v);
extern void print(vec3 v);
extern void print(vec4 v);
extern void print(mat4 m);
extern void print(aiMatrix4x4 m);
extern void print(std::vector<int>);
extern void print(std::vector<float>);
extern int compareFloat(float a, float b);
extern int random(int lo, int hi);
extern vec3 randomv(int lo, int hi);
};  // namespace Util

#endif  // UTIL_H
