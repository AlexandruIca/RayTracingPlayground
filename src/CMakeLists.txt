set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(
  project_utils STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/utilities.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ray.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/sphere.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/hittable.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/hittable_list.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/camera.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lambertian.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/metal.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/dielectric.cpp)
target_include_directories(project_utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(project_utils PUBLIC project_options project_warnings glm::glm)

add_executable(${CMAKE_PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE project_options project_warnings project_utils)
