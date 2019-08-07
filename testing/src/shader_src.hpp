#pragma once

#define CONVERT_TO_STRING(x) "#version 330 core\n" #x

constexpr char s_vert_src[] = CONVERT_TO_STRING(

    layout(location = 0) in vec2 pos; layout(location = 1) in vec3 col;

    out vec3 v_col;

    void main() {
        v_col = col;
        gl_Position = vec4(pos, 0, 1);
    }

);

constexpr char s_frag_src[] = CONVERT_TO_STRING(

    in vec3 v_col;

    out vec4 color;

    void main() { color = vec4(v_col, 1); }

);
