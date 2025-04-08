cmake_minimum_required(VERSION 3.15)
project(SurvivalRoguelike VERSION 0.1.0)

# Определение версии C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Устанавливаем политики CMake
set(CMAKE_POLICY_DEFAULT_CMP0048 NEW)
# Установка политики CMP0135 для избежания предупреждения о метках времени
if(POLICY CMP0135)
  cmake_policy(SET CMP0135 NEW)
endif()

# Опции сборки
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(BUILD_TESTS "Build test programs" OFF)

# Добавляем внешние зависимости
add_subdirectory(external)

# Добавляем глобальные директории для включения, чтобы они были доступны всем подпроектам
include_directories(${SFML_INCLUDE_DIR})
link_directories(${SFML_LIB_DIR})

# Подкаталоги проекта
add_subdirectory(src)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()

# Информация о сборке
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "SFML Include Dir: ${SFML_INCLUDE_DIR}")
message(STATUS "SFML Lib Dir: ${SFML_LIB_DIR}")