
add_library(Coelengine 
	Coel/Window.cpp 
	Coel/Camera.cpp
	Coel/Model.cpp
	
	Coel/Renderer/Context.cpp 
	Coel/Renderer/Renderer.cpp 
	Coel/Renderer/Shader.cpp 
	Coel/Renderer/Texture.cpp 
	Coel/Renderer/Buffer.cpp
	
	Coel/Renderers/Batch2d.cpp 
	Coel/Renderers/Quad2d.cpp 
	Coel/Renderers/BatchText.cpp 
	Coel/Renderers/ImGui.cpp 
)

target_link_libraries(Coelengine PUBLIC glfw glad imgui stb glm)
target_compile_features(Coelengine PUBLIC cxx_std_17)
target_include_directories(Coelengine PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_compile_options(Coelengine PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -Werror>
)