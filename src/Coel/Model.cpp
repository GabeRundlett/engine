#include "Model.hpp"
#include "Renderer/Renderer.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace Coel {
    std::vector<Model::Vertex> Model::loadModel(const char *const filepath) {
        std::vector<Vertex> data;
        std::ifstream modelFile(filepath);
        struct TriIndex {
            struct V {
                union {
                    struct {
                        int pos, tex, nrm;
                    } vdata;
                    int data[3];
                };
            } v[3];
        };
        if (modelFile.is_open()) {
            std::string line;
            std::vector<glm::vec3> positions;
            std::vector<glm::vec2> texCoords;
            std::vector<glm::vec3> normals;
            std::vector<TriIndex> triangles;
            std::size_t triCount = 0;
            while (std::getline(modelFile, line)) {
                if (line[0] == 'v') {
                    if (line[1] == ' ') { // Position
                        line = line.substr(2);
                        positions.push_back({});
                        auto &pos = positions.back();
                        for (unsigned int i = 0; i < 3; ++i) {
                            std::size_t termEnd;
                            pos[i] = std::stof(line, &termEnd);
                            line = line.substr(termEnd);
                        }
                    } else if (line[1] == 't') { // Texture Coord
                        line = line.substr(3);
                        texCoords.push_back({});
                        auto &tex = texCoords.back();
                        for (unsigned int i = 0; i < 2; ++i) {
                            std::size_t termEnd;
                            tex[i] = std::stof(line, &termEnd);
                            line = line.substr(termEnd);
                        }
                    } else if (line[1] == 'n') { // Normal
                        line = line.substr(3);
                        normals.push_back({});
                        auto &nrm = normals.back();
                        for (unsigned int i = 0; i < 3; ++i) {
                            std::size_t termEnd;
                            nrm[i] = std::stof(line, &termEnd);
                            line = line.substr(termEnd);
                        }
                    }
                } else if (line[0] == 'f') { // Tri
                    line = line.substr(2);
                    triangles.push_back({});
                    for (unsigned int i = 0; i < 3; ++i) {
                        std::size_t termEnd;
                        auto a = std::stoi(line, &termEnd) - 1;
                        triangles[triCount].v[0].data[i] = a;
                        line = line.substr(termEnd + 1);
                    }
                    for (unsigned int i = 0; i < 3; ++i) {
                        std::size_t termEnd;
                        auto a = std::stoi(line, &termEnd) - 1;
                        triangles[triCount].v[1].data[i] = a;
                        line = line.substr(termEnd + 1);
                    }
                    for (unsigned int i = 0; i < 3; ++i) {
                        std::size_t termEnd;
                        auto a = std::stoi(line, &termEnd) - 1;
                        triangles[triCount].v[2].data[i] = a;
                        if (i < 2) line = line.substr(termEnd + 1);
                    }
                    ++triCount;
                }
            }

            data.reserve(triCount * 3);
            for (auto &t : triangles) {
                for (auto &v : t.v) {
                    data.push_back({
                        positions[v.vdata.pos],
                        normals[v.vdata.nrm],
                        texCoords[v.vdata.tex],
                        {1, 0, 1, 1},
                    });
                    // std::cout << v.pos << ", " << v.nrm << ", " << v.tex << "  ";
                }
                // std::cout << '\n';
            }
        }
        return data;
    }

    Model::Model(const char *const filepath)
        : m_vertices(loadModel(filepath)), m_vao{}, m_vbo{{{F32, 3}, {F32, 3}, {F32, 2}, {F32, 4}}} {
        create(m_vbo, m_vertices.data(), m_vertices.size() * sizeof(Vertex));
        link(m_vao, m_vbo);
    }

    void Model::draw() {
        Renderer::draw(m_vao, m_vertices.size()); //
    }
} // namespace Coel
