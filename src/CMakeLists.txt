# Убедимся, что все необходимые каталоги существуют
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/core)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/entities)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/world)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/networking)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ui)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/states)

# Собираем все .cpp файлы из подкаталогов
file(GLOB_RECURSE CORE_SOURCES "core/*.cpp")
file(GLOB_RECURSE ENTITIES_SOURCES "entities/*.cpp")
file(GLOB_RECURSE WORLD_SOURCES "world/*.cpp")
file(GLOB_RECURSE NETWORKING_SOURCES "networking/*.cpp")
file(GLOB_RECURSE UI_SOURCES "ui/*.cpp")
file(GLOB_RECURSE STATES_SOURCES "states/*.cpp")

# Основной исполняемый файл
add_executable(SurvivalRoguelike
    Game.cpp
    ${CORE_SOURCES}
    ${ENTITIES_SOURCES}
    ${WORLD_SOURCES}
    ${NETWORKING_SOURCES}
    ${UI_SOURCES}
    ${STATES_SOURCES}
)

# Добавляем зависимость от внешнего проекта SFML
add_dependencies(SurvivalRoguelike sfml)

# Включаемые каталоги
target_include_directories(SurvivalRoguelike PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${SFML_INCLUDE_DIR}
)

# Подключение библиотек SFML с учетом конфигурации (Debug/Release)
if(WIN32)
    target_link_libraries(SurvivalRoguelike PRIVATE
        debug ${SFML_LIB_DIR}/sfml-system-s-d.lib optimized ${SFML_LIB_DIR}/sfml-system-s.lib
        debug ${SFML_LIB_DIR}/sfml-window-s-d.lib optimized ${SFML_LIB_DIR}/sfml-window-s.lib
        debug ${SFML_LIB_DIR}/sfml-graphics-s-d.lib optimized ${SFML_LIB_DIR}/sfml-graphics-s.lib
        debug ${SFML_LIB_DIR}/sfml-network-s-d.lib optimized ${SFML_LIB_DIR}/sfml-network-s.lib
        winmm.lib
        opengl32.lib
        freetype.lib
        ws2_32.lib
        gdi32.lib
    )
else()
    target_link_libraries(SurvivalRoguelike PRIVATE
        debug ${SFML_LIB_DIR}/libsfml-system-s-d.a optimized ${SFML_LIB_DIR}/libsfml-system-s.a
        debug ${SFML_LIB_DIR}/libsfml-window-s-d.a optimized ${SFML_LIB_DIR}/libsfml-window-s.a
        debug ${SFML_LIB_DIR}/libsfml-graphics-s-d.a optimized ${SFML_LIB_DIR}/libsfml-graphics-s.a
        debug ${SFML_LIB_DIR}/libsfml-network-s-d.a optimized ${SFML_LIB_DIR}/libsfml-network-s.a
    )
endif()

# Определения для статической линковки SFML
target_compile_definitions(SurvivalRoguelike PRIVATE
    SFML_STATIC
)

# Определение для временного отключения аудио
target_compile_definitions(SurvivalRoguelike PRIVATE
    DISABLE_AUDIO
)

# Создание структуры ресурсов
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/resources)
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/resources/fonts)
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/resources/textures)
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/resources/sounds)

# Копирование ресурсов при сборке
add_custom_command(TARGET SurvivalRoguelike POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:SurvivalRoguelike>/resources
)

# Вывод информации о путях SFML для отладки
message(STATUS "SFML Include Dir (в src): ${SFML_INCLUDE_DIR}")
message(STATUS "SFML Lib Dir (в src): ${SFML_LIB_DIR}")