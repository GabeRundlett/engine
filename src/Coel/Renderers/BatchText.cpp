#include "BatchText.hpp"
#include <glad/glad.h>
#include <array>
#include <algorithm>

#include "Assets/BatchTextShader.hpp"

struct FontAtlasInfo {
    int id, index, width, unihex, height, xoffset, yoffset, xadvance, chnl, x, y, page;
};

constexpr FontAtlasInfo fontAtlasInfos[]{
    {40, 12, 46, 0x28, 123, -4, 5, 34, 15, 0, 0, 0},       {41, 13, 46, 0x29, 123, -8, 5, 35, 15, 0, 124, 0},
    {91, 63, 38, 0x5B, 116, -3, 4, 27, 15, 0, 248, 0},     {123, 95, 50, 0x7B, 116, -7, 7, 34, 15, 0, 365, 0},
    {125, 97, 50, 0x7D, 116, -9, 7, 34, 15, 39, 248, 0},   {93, 65, 38, 0x5D, 116, -10, 4, 27, 15, 47, 0, 0},
    {106, 78, 40, 0x6A, 113, -13, 13, 24, 15, 47, 117, 0}, {36, 8, 65, 0x24, 113, -5, 2, 56, 15, 86, 0, 0},
    {64, 36, 99, 0x40, 112, -4, 15, 90, 15, 88, 114, 0},   {87, 59, 104, 0x57, 91, -7, 14, 89, 15, 152, 0, 0},
    {81, 53, 77, 0x51, 104, -5, 13, 69, 15, 0, 482, 0},    {124, 96, 27, 0x7C, 104, -1, 14, 24, 15, 51, 365, 0},
    {47, 19, 57, 0x2F, 97, -9, 14, 41, 15, 0, 587, 0},     {92, 64, 58, 0x5C, 97, -8, 14, 41, 15, 0, 685, 0},
    {98, 70, 65, 0x62, 96, -3, 10, 56, 15, 58, 587, 0},    {100, 72, 65, 0x64, 96, -5, 10, 56, 15, 78, 470, 0},
    {102, 74, 52, 0x66, 96, -7, 9, 35, 15, 79, 365, 0},    {104, 76, 62, 0x68, 95, -3, 10, 55, 15, 90, 227, 0},
    {107, 79, 64, 0x6B, 95, -3, 10, 51, 15, 132, 323, 0},  {108, 80, 29, 0x6C, 95, -2, 10, 24, 15, 153, 227, 0},
    {103, 75, 65, 0x67, 95, -5, 31, 56, 15, 183, 227, 0},  {113, 85, 65, 0x71, 94, -5, 31, 57, 15, 188, 92, 0},
    {109, 81, 94, 0x6D, 74, -3, 31, 88, 15, 0, 783, 0},    {121, 93, 65, 0x79, 94, -9, 32, 47, 15, 59, 684, 0},
    {112, 84, 65, 0x70, 94, -3, 31, 56, 15, 124, 567, 0},  {56, 28, 65, 0x38, 93, -5, 13, 56, 15, 144, 419, 0},
    {79, 51, 77, 0x4F, 93, -4, 13, 69, 15, 197, 323, 0},   {67, 39, 75, 0x43, 93, -4, 13, 65, 15, 249, 187, 0},
    {48, 20, 65, 0x30, 93, -4, 13, 56, 15, 254, 92, 0},    {51, 23, 65, 0x33, 93, -5, 13, 56, 15, 320, 0, 0},
    {38, 10, 77, 0x26, 93, -5, 13, 62, 15, 0, 858, 0},     {71, 43, 75, 0x47, 93, -4, 13, 68, 15, 78, 858, 0},
    {37, 9, 84, 0x25, 93, -5, 13, 73, 15, 125, 662, 0},    {83, 55, 72, 0x53, 93, -6, 13, 59, 15, 125, 756, 0},
    {63, 35, 60, 0x3F, 93, -6, 13, 47, 15, 190, 513, 0},   {54, 26, 65, 0x36, 92, -4, 14, 56, 15, 320, 94, 0},
    {105, 77, 31, 0x69, 92, -3, 13, 24, 15, 210, 417, 0},  {50, 22, 68, 0x32, 92, -5, 13, 56, 15, 242, 417, 0},
    {85, 57, 71, 0x55, 92, -3, 14, 65, 15, 275, 281, 0},   {74, 46, 65, 0x4A, 92, -7, 14, 55, 15, 325, 187, 0},
    {57, 29, 65, 0x39, 92, -5, 13, 56, 15, 386, 0, 0},     {53, 25, 65, 0x35, 92, -2, 14, 56, 15, 386, 93, 0},
    {33, 5, 31, 0x21, 92, -2, 14, 26, 15, 154, 850, 0},    {90, 62, 72, 0x5A, 91, -6, 14, 60, 15, 186, 850, 0},
    {78, 50, 75, 0x4E, 91, -2, 14, 71, 15, 198, 756, 0},   {80, 52, 71, 0x50, 91, -2, 14, 63, 15, 210, 607, 0},
    {76, 48, 63, 0x4C, 91, -2, 14, 54, 15, 251, 510, 0},   {82, 54, 72, 0x52, 91, -2, 14, 62, 15, 311, 374, 0},
    {75, 47, 74, 0x4B, 91, -2, 14, 63, 15, 347, 280, 0},   {84, 56, 75, 0x54, 91, -8, 14, 60, 15, 391, 186, 0},
    {73, 45, 29, 0x49, 91, -1, 14, 27, 15, 257, 0, 0},     {86, 58, 81, 0x56, 91, -9, 14, 64, 15, 452, 0, 0},
    {72, 44, 75, 0x48, 91, -2, 14, 71, 15, 452, 92, 0},    {88, 60, 77, 0x58, 91, -7, 14, 63, 15, 259, 848, 0},
    {89, 61, 78, 0x59, 91, -9, 14, 60, 15, 274, 699, 0},   {77, 49, 91, 0x4D, 91, -2, 14, 87, 15, 282, 602, 0},
    {70, 42, 64, 0x46, 91, -2, 14, 55, 15, 315, 466, 0},   {68, 40, 71, 0x44, 91, -2, 14, 66, 15, 337, 791, 0},
    {66, 38, 68, 0x42, 91, -2, 14, 62, 15, 353, 694, 0},   {65, 37, 83, 0x41, 91, -9, 14, 65, 15, 374, 558, 0},
    {35, 7, 74, 0x23, 91, -4, 14, 62, 15, 380, 466, 0},    {55, 27, 68, 0x37, 91, -6, 14, 56, 15, 384, 372, 0},
    {52, 24, 71, 0x34, 91, -7, 14, 56, 15, 422, 278, 0},   {49, 21, 47, 0x31, 91, -2, 14, 56, 15, 467, 184, 0},
    {119, 91, 91, 0x77, 73, -8, 32, 75, 15, 453, 370, 0},  {69, 41, 65, 0x45, 91, -2, 14, 57, 15, 494, 276, 0},
    {116, 88, 49, 0x74, 87, -10, 19, 33, 15, 515, 184, 0}, {59, 31, 35, 0x3B, 87, -8, 32, 21, 15, 528, 92, 0},
    {126, 98, 75, 0x7E, 40, -4, 46, 68, 15, 374, 650, 0},  {101, 73, 65, 0x65, 75, -5, 31, 53, 15, 534, 0, 0},
    {115, 87, 62, 0x73, 75, -5, 31, 52, 15, 564, 76, 0},   {97, 69, 64, 0x61, 75, -5, 31, 54, 15, 600, 0, 0},
    {111, 83, 68, 0x6F, 75, -6, 31, 57, 15, 455, 444, 0},  {99, 71, 65, 0x63, 75, -6, 31, 52, 15, 259, 940, 0},
    {58, 30, 31, 0x3A, 74, -3, 32, 24, 15, 287, 0, 0},     {114, 86, 46, 0x72, 74, -3, 31, 34, 15, 186, 942, 0},
    {110, 82, 62, 0x6E, 74, -3, 31, 55, 15, 325, 940, 0},  {117, 89, 62, 0x75, 74, -3, 32, 55, 15, 388, 883, 0},
    {120, 92, 65, 0x78, 73, -8, 32, 50, 15, 409, 786, 0},  {118, 90, 65, 0x76, 73, -8, 32, 48, 15, 422, 691, 0},
    {122, 94, 62, 0x7A, 73, -6, 32, 50, 15, 451, 860, 0},  {43, 15, 69, 0x2B, 72, -6, 26, 57, 15, 0, 952, 0},
    {95, 67, 65, 0x5F, 27, -10, 85, 45, 15, 70, 952, 0},   {60, 32, 60, 0x3C, 64, -6, 31, 51, 15, 388, 958, 0},
    {62, 34, 62, 0x3E, 64, -3, 31, 52, 15, 449, 958, 0},   {61, 33, 61, 0x3D, 48, -3, 37, 55, 15, 274, 791, 0},
    {42, 14, 60, 0x2A, 61, -9, 14, 43, 15, 512, 934, 0},   {94, 66, 55, 0x5E, 55, -7, 14, 42, 15, 210, 699, 0},
    {44, 16, 34, 0x2C, 45, -9, 74, 20, 15, 144, 513, 0},   {45, 17, 44, 0x2D, 27, -8, 51, 28, 15, 188, 187, 0},
    {34, 6, 40, 0x22, 44, -3, 10, 32, 15, 337, 883, 0},    {39, 11, 27, 0x27, 43, -5, 10, 17, 15, 95, 779, 0},
    {96, 68, 40, 0x60, 34, -7, 10, 31, 15, 90, 323, 0},    {46, 18, 31, 0x2E, 31, -3, 75, 26, 15, 275, 374, 0},
    {32, 4, 0, 0x20, 0, -10, 85, 25, 15, 58, 684, 0},
};

static auto getCharInfo(unsigned char c) {
    for (const auto &info : fontAtlasInfos)
        if (info.id == c) return info;
    return FontAtlasInfo{};
}

static inline auto getCharTexCoord(const FontAtlasInfo &info) {
    return glm::vec2{(float)info.x, (float)info.y} * glm::vec2{1.f / 1024}; //
}

static inline auto getCharTexSize(const FontAtlasInfo &info) {
    return glm::vec2{(float)info.width, (float)info.height}; //
}

static inline auto getCharOffset(const FontAtlasInfo &info) {
    return glm::vec2{(float)info.xoffset, (float)info.yoffset}; //
}

namespace Coel { namespace Renderer {
    BatchText::BatchText(unsigned int vCount, unsigned int iCount)
        : m_vao(), m_vbo(nullptr, sizeof(Vertex) * vCount,
                         {{Element::F32, 2}, {Element::F32, 2}, {Element::F32, 2}, {Element::U8, 4}, {Element::U8, 4}}),
          m_ibo(nullptr, sizeof(Index) * iCount),
          m_shader(vertSrc, fragSrc), m_viewPosUniform{m_shader.findInt2("viewportPos")}, m_viewSizeUniform{m_shader.findInt2(
                                                                                              "viewportSize")},
          m_texture("Assets/RobotoFontAtlas.png"), m_maxVertexCount(vCount), m_maxIndexCount(iCount),
          m_strokeWeight(4), m_fillCol{0} {
        m_vao.add(m_vbo);
        m_texture.setMagFilter(Filter::Linear);
        m_texture.setMinFilter(Filter::Linear);
        m_texture.setWrap(Wrap::ClampToEdge);
    }

    void BatchText::begin() {
        m_vao.bind();
        m_vbo.open(&m_vertices);
        m_ibo.open(&m_indices);
    }

    float BatchText::submitText(float x, float y, float s, const std::string &str) {
        float cursorOff = 0.f;
        for (const auto &c : str) {
            auto info = getCharInfo(c);
            glm::vec2 tex = getCharTexCoord(info);
            glm::vec2 size = getCharTexSize(info);
            glm::vec2 off = getCharOffset(info) * s;
            auto texSize = size * glm::vec2{1.f / 1024};
            glm::vec2 pos{x + cursorOff, y};
            pos += off;
            submitQuad({pos, pos + size * s, tex, tex + texSize, {0, 0, 0, 0}});
            cursorOff += info.xadvance * s;
        }
        return cursorOff;
    }

    void BatchText::flush() {
        m_vbo.close();
        m_ibo.close();

        m_shader.bind();
        m_texture.bind(0);
        m_vao.drawIndexed(m_indexCount);

        m_vertexCount = 0, m_indexCount = 0;
    }

    void BatchText::resize(const glm::ivec2 &pos, const glm::ivec2 &size) {
        m_shader.send(m_viewPosUniform, &pos);
        m_shader.send(m_viewSizeUniform, &size);
    }

    void BatchText::fill(const glm::u8vec4 &c) { m_fillCol = c; }
}} // namespace Coel::Renderer
