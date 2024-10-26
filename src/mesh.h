#ifndef MESH_H
#define MESH_H

#pragma warning(disable : 26495)
#include <string>
#include <map>
#include <stdio.h>
#include <stddef.h>
#include <math.h>
#include <vector>    // STL dynamic memory.
#include <assert.h>  // STL dynamic memory.

#include <assimp/cimport.h>  // scene importer
#include <assimp/Importer.hpp>
#include <assimp/scene.h>        // collects data
#include <assimp/postprocess.h>  // various extra operations

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "util.h"
#include "sm.h"
#include "texture.h"

#define AI_LOAD_FLAGS aiProcess_Triangulate | aiProcess_PreTransformVertices

class Mesh {
   public:
    struct MeshObject {
        MeshObject() {
            n_Indices = 0;
            baseVertex = 0;
            baseIndex = 0;
            materialIndex = 0;
        }
        unsigned int n_Indices;
        unsigned int baseVertex;
        unsigned int baseIndex;
        unsigned int materialIndex;
    };

    struct Material {
        vec3 ambientColour = vec3(0.0f);
        vec3 diffuseColour = vec3(0.0f);
        vec3 specularColour = vec3(0.0f);
    };

    // Create a new Mesh object without a mesh
    Mesh() { name = "NewMesh" + std::to_string(SM::unnamedMeshCount++); }

    // Create a new unnamed Mesh object
    Mesh(std::string mesh_path) {
        name = "NewMesh" + std::to_string(SM::unnamedMeshCount++);
        if (!loadMesh(mesh_path)) std::cout << "\n\nfailed to load mesh \"" << mesh_path.c_str() << "\" :(\n";
    }

    // Create a new Mesh object and give it a name.
    Mesh(std::string nm, std::string mesh_path) {
        name = nm;
        if (!loadMesh(mesh_path)) std::cout << "\n\nfailed to load mesh \"" << nm.c_str() << "\" :(\n";
    }

    // Create a new Mesh object from a atlas texture.
    // The width of the texture must be `_atlasTileSize` and the length must be at least `_atlasTileSize` * `_atlasTilesUsed`
    // If `isVerticalTexture` is `true`, the texture is assumed to be one tile wide and `_atlasTilesUsed` tiles long.
    // If `isVerticalTexture` is `false`, it is assumed the texture only uses tiles of size `_atlasTileSize`.
    Mesh(std::string nm, std::string mesh_path, int _atlasTileSize, int _atlasTilesUsed, bool isVerticalTexture = true) {
        name = nm;
        usingAtlas = true;
        atlasTileSize = _atlasTileSize;
        atlasTilesUsed = _atlasTilesUsed;
        isAtlasVertical = isVerticalTexture;
        texture = new Texture(GL_TEXTURE_2D_ARRAY);
        if (!loadMesh(mesh_path)) std::cout << "\n\nfailed to load mesh \"" << nm.c_str() << "\" :(\n";
    }
    bool loadMesh(std::string mesh_path);
    bool initScene(const aiScene*, std::string);
    void initSingleMesh(const aiMesh*);
    bool initMaterials(const aiScene*, std::string);
    void loadColours(const aiMaterial*, int);
    void populateBuffers();
    void render();                                         // render a single mesh without instancing. deprecated
    void render(unsigned int, const mat4*);                // render an array of meshes using instancing
    void render(unsigned int, const mat4*, const float*);  // render an array of meshes using instancing and atlas depths
    void render(mat4);                                     // render a single mesh
    void render(mat4, float);                              // single atlas depth

#define POSITION_LOC 0  // p_vbo
#define NORMAL_LOC 1    // n_vbo
#define TEXTURE_LOC 2   // t_vbo
#define INSTANCE_LOC 3
#define DEPTH_LOC 7  // texture depth

    std::string name;
    mat4 mat;
    vec3 dir = vec3(1, 0, 0);
    unsigned int VAO = 0;    // mesh vao
    unsigned int p_VBO = 0;  // position vbo
    unsigned int n_VBO = 0;  // normal vbo
    unsigned int t_VBO = 0;  // texture vbo
    unsigned int d_VBO = 0;  // texture depth vbo
    unsigned int EBO = 0;    // index (element) vbo (ebo)
    unsigned int IBO = 0;    // instance vbo (ibo)
    int atlasTileSize = 0, atlasTilesUsed = 1;
    bool usingAtlas = false;       // flag if the mesh is using an array texture
    bool isAtlasVertical = false;  // flag if the mesh is using a verticalarray texture

    std::vector<vec3> m_Positions;
    std::vector<vec3> m_Normals;
    std::vector<vec2> m_TexCoords;
    std::vector<unsigned int> m_Indices;
    std::vector<MeshObject> m_Meshes;
    std::vector<Texture*> m_Textures;
    Texture* texture;
    std::vector<Material> m_Materials;
};

#endif /* MESH_H */
