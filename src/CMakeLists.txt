add_executable(${CMAKE_PROJECT_NAME} main.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE project_options project_warnings glm::glm)
