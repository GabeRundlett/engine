cmake_minimum_required(VERSION 3.12)

project(imgui VERSION 1.0.0)

if (NOT TARGET imgui)
    set(Headers 
        "src/imconfig.h"
        "src/imgui.h"
        "src/imgui_internal.h"
        "src/imstb_rectpack.h"
        "src/imstb_textedit.h"
        "src/imstb_truetype.h"
    )

    set(Sources 
        "src/imgui/imgui.cpp"
        "src/imgui/imgui_demo.cpp"
        "src/imgui/imgui_draw.cpp"
        "src/imgui/imgui_widgets.cpp"
    )

    add_library(imgui STATIC ${Sources} ${Headers})
    target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src)
endif()
