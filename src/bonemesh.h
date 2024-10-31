#ifndef BONEMESH_H
#define BONEMESH_H
#pragma warning(disable : 26495)

#include <windows.h>
#include <mmsystem.h>

#include "mesh.h"
#include "shader.h"

#define MAX_NUM_BONES_PER_VERTEX 4
#define B_AI_LOAD_FLAGS aiProcess_Triangulate | aiProcess_SortByPType | aiProcess_RemoveRedundantMaterials | aiProcess_OptimizeMeshes | aiProcess_OptimizeGraph | aiProcess_SortByPType | aiProcess_GenNormals

class BoneMesh : public Mesh {
   public:
    struct VertexBoneData {
        VertexBoneData() {
            for (int i = 0; i < MAX_NUM_BONES_PER_VERTEX; ++i) {
                BoneIDs[i] = -1;
                Weights[i] = 0.0f;
            }
        }

        unsigned int BoneIDs[MAX_NUM_BONES_PER_VERTEX];
        float Weights[MAX_NUM_BONES_PER_VERTEX];

        void addBoneData(unsigned int BoneID, float Weight) {
            for (unsigned int i = 0; i < MAX_NUM_BONES_PER_VERTEX; i++) {
                if (Weights[i] < 0.00001f) {
                    BoneIDs[i] = BoneID;
                    Weights[i] = Weight;
                    return;
                }
            }
            assert(false && "too many bones per vertex (> 4)");
        }
    };

    struct BoneInfo {
        aiMatrix4x4 offsetMatrix;
        aiMatrix4x4 lastTransformation;

        BoneInfo(const aiMatrix4x4& offset) {
            offsetMatrix = offset;
            lastTransformation = Util::GLMtoAI(mat4(0));
        }
    };

    BoneMesh() { name = "NewBoneMesh" + std::to_string(SM::unnamedBoneMeshCount++); }
    BoneMesh(std::string nm) { name = nm; }
    BoneMesh(std::string nm, std::string mesh_path) {
        name = nm;
        if (!loadMesh(mesh_path, true)) std::cout << "\n\nfailed to load mesh \"" << nm.c_str() << "\" :(\n";
    }
    BoneMesh(std::string nm, std::string mesh_path, Shader* s) {
        name = nm;
        if (!loadMesh(mesh_path, true)) std::cout << "\n\nfailed to load mesh \"" << nm.c_str() << "\" :(\n";
        shader = s;
    }

    ~BoneMesh();

    bool loadMesh(std::string mesh_path) { return loadMesh(mesh_path, true); }  // load a mesh located at `mesh_path`
    bool loadMesh(std::string mesh_path, bool populateBuffer);
    bool initScene(const aiScene*, std::string);
    void initSingleMesh(unsigned int, const aiMesh*);
    bool initMaterials(const aiScene*, std::string);
    void loadDiffuseTexture(const aiMaterial* pMaterial, std::string dir, unsigned int index);
    void loadSpecularTexture(const aiMaterial* pMaterial, std::string dir, unsigned int index);
    void populateBuffers();
    void render(unsigned int, const mat4*);
    void render(mat4);
    void loadSingleBone(unsigned int, const aiBone*);
    int getBoneID(const aiBone*);
    void getBoneTransforms(float, std::vector<aiMatrix4x4>&);
    void readNodeHierarchy(float, const aiNode*, const aiMatrix4x4&);
    const aiNodeAnim* findNodeAnim(const aiAnimation*, const std::string);
    void calcInterpolatedTranslation(aiVector3D&, float, const aiNodeAnim*);
    void calcInterpolatedScale(aiVector3D&, float, const aiNodeAnim*);
    void calcInterpolatedRotation(aiQuaternion&, float, const aiNodeAnim*);
    void update();                       // update the mesh's animations
    void update(Shader* skinnedShader);  // update the mesh's animations using an external shader

#define SK_POSITION_LOC 0     // p_vbo
#define SK_NORMAL_LOC 1       // n_vbo
#define SK_TEXTURE_LOC 2      // t_vbo
#define SK_BONE_LOC 3         // bone vbo
#define SK_BONE_WEIGHT_LOC 4  // bone weight location
#define SK_INSTANCE_LOC 5     // instance location

    aiMatrix4x4 globalInverseTrans;  // inverse matrix
    unsigned int BBO;                // bone vbo

    std::vector<VertexBoneData> m_Bones;
    std::vector<BoneInfo*> m_BoneInfo;
    std::map<std::string, unsigned int> boneToIndexMap;

    const aiScene* scene;
    Assimp::Importer importer;

    Shader* shader;
    bool shouldPopulateBuffers = true;
};

#endif /* BONEMESH_H */
