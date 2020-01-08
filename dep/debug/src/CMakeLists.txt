set(sources 
    core/log.cpp 
    core/profile.cpp 
    core/timer.cpp
)

include_directories(${debug_include_dir})

add_library(${PROJECT_NAME} ${sources})
