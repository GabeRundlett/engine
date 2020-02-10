
add_library(Coelengine 
	Coel/Window.cpp 
	Coel/Renderer/Batch2d.cpp 
	Coel/Renderer/Context.cpp 
	Coel/Renderer/Command.cpp 
	Coel/Renderer/Shader.cpp 
	Coel/Renderer/Texture.cpp 
	Coel/Renderer/Buffer.cpp
)

target_link_libraries(Coelengine PUBLIC glfw glad stb Math)
target_compile_features(Coelengine PUBLIC cxx_std_17)
target_include_directories(Coelengine PUBLIC ${CMAKE_CURRENT_LIST_DIR})
