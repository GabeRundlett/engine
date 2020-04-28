#include "Model.hpp"
#include "Renderer/Renderer.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Coel {
    static std::vector<Texture> loadTextures(Model::Object &object, aiMaterial *mat, aiTextureType type, std::string rootdir) {
        std::vector<Texture> tempTextures;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
            aiString str;
            mat->GetTexture(type, i, &str);
            Texture texture;
            create(texture, (rootdir + '/' + str.C_Str()).c_str());
            tempTextures.push_back(texture);
            object.textures.push_back(texture);
        }
        return tempTextures;
    }

    static void processNode(Model &model, aiNode *node, const aiScene *scene, std::string rootdir) {
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
            Model::Object tempObj;

            std::vector<Model::Vertex> vertices;
            std::vector<unsigned int> indices;

            for (unsigned int j = 0; j < mesh->mNumVertices; j++) {
                Model::Vertex vertex;
                auto v = mesh->mVertices[j];
                vertex.pos = *(glm::vec3 *)(mesh->mVertices + j);
                vertex.nrm = *(glm::vec3 *)(mesh->mNormals + j);
                vertex.tex = *(glm::vec3 *)(mesh->mTextureCoords[0] + j);
                vertices.push_back(vertex);
            }
            for (unsigned int j = 0; j < mesh->mNumFaces; j++) {
                aiFace face = mesh->mFaces[j];
                for (unsigned int k = 0; k < face.mNumIndices; k++) {
                    if (face.mNumIndices != 3) std::cout << "index count: " << face.mNumIndices << '\n';
                    indices.push_back(face.mIndices[k]);
                }
            }

            aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

            std::vector<Texture> diffMaps = loadTextures(tempObj, material, aiTextureType_DIFFUSE, rootdir);
            tempObj.textures.insert(tempObj.textures.end(), diffMaps.begin(), diffMaps.end());
            std::vector<Texture> specMaps = loadTextures(tempObj, material, aiTextureType_SPECULAR, rootdir);
            tempObj.textures.insert(tempObj.textures.end(), specMaps.begin(), specMaps.end());
            std::vector<Texture> nrmMaps = loadTextures(tempObj, material, aiTextureType_HEIGHT, rootdir);
            tempObj.textures.insert(tempObj.textures.end(), nrmMaps.begin(), nrmMaps.end());
            std::vector<Texture> heightMaps = loadTextures(tempObj, material, aiTextureType_AMBIENT, rootdir);
            tempObj.textures.insert(tempObj.textures.end(), heightMaps.begin(), heightMaps.end());

            create(tempObj.vao);
            create(tempObj.vbo, vertices.data(), (uint32_t)vertices.size() * sizeof(Model::Vertex));
            create(tempObj.ibo, indices.data(), (uint32_t)indices.size() * sizeof(unsigned int));
            link(tempObj.vao, tempObj.vbo);
            tempObj.indexCount = (uint32_t)indices.size();
            model.objects.push_back({tempObj});
        }
        for (unsigned int i = 0; i < node->mNumChildren; i++)
            processNode(model, node->mChildren[i], scene, rootdir);
    }

    void open(Model &model, std::string filepath) {
        Assimp::Importer import;
        const aiScene *scene = import.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
            return;
        }
        processNode(model, scene->mRootNode, scene, filepath.substr());
    }
} // namespace Coel
