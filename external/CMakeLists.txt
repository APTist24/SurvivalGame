# Проверим версию SFML для загрузки
set(SFML_VERSION "2.6.1")
set(SFML_URL "https://github.com/SFML/SFML/archive/${SFML_VERSION}.zip")

# Путь установки SFML
set(SFML_INSTALL_DIR "${CMAKE_BINARY_DIR}/external/sfml-install" CACHE PATH "Путь к установленной SFML")

# Указываем пути для включения в родительскую область видимости
set(SFML_INCLUDE_DIR "${SFML_INSTALL_DIR}/include" CACHE PATH "Путь к заголовочным файлам SFML")
set(SFML_LIB_DIR "${SFML_INSTALL_DIR}/lib" CACHE PATH "Путь к библиотекам SFML")

# Проверяем, существует ли уже каталог с SFML
if(NOT EXISTS "${SFML_INSTALL_DIR}")
    message(STATUS "SFML not found at ${SFML_INSTALL_DIR}, will download and build")
    
    # Загрузка и сборка SFML без аудиомодуля
    include(ExternalProject)
    ExternalProject_Add(
        sfml
        URL ${SFML_URL}
        CMAKE_ARGS 
            -DCMAKE_INSTALL_PREFIX=${SFML_INSTALL_DIR}
            -DCMAKE_POLICY_VERSION_MINIMUM=3.5
            -DBUILD_SHARED_LIBS=OFF
            -DSFML_BUILD_EXAMPLES=OFF
            -DSFML_BUILD_DOC=OFF
            -DSFML_BUILD_GRAPHICS=ON
            -DSFML_BUILD_WINDOW=ON
            -DSFML_BUILD_SYSTEM=ON
            -DSFML_BUILD_NETWORK=ON
            -DSFML_BUILD_AUDIO=OFF  # Отключаем аудиомодуль для сборки
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
else()
    message(STATUS "SFML found at ${SFML_INSTALL_DIR}, skipping download and build")
    add_custom_target(sfml)
endif()

# Отдельно скачиваем предкомпилированную версию SFML (с аудиомодулем)
if(WIN32)
    # Проверка, скачаны ли уже библиотеки
    if(NOT EXISTS "${CMAKE_BINARY_DIR}/external/precompiled-sfml")
        message(STATUS "Downloading precompiled SFML libraries...")
        
        # Создаем директорию для предкомпилированных библиотек
        file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/external/precompiled-sfml")
        
        # Здесь можно использовать file(DOWNLOAD) для скачивания предкомпилированных библиотек
        # Или добавить их непосредственно в репозиторий
        
        # Для этого примера, мы просто объявим путь к аудио библиотекам SFML
        message(STATUS "SFML Audio libraries will need to be manually provided")
    endif()
endif()

# Устанавливаем пути и переменные для аудио модуля
if(WIN32)
    # Для отладочной сборки
    set(SFML_AUDIO_DEBUG_LIBS 
        "${SFML_LIB_DIR}/sfml-audio-s-d.lib"
        CACHE STRING "SFML Audio Debug Libraries")
        
    # Для релизной сборки
    set(SFML_AUDIO_RELEASE_LIBS 
        "${SFML_LIB_DIR}/sfml-audio-s.lib"
        CACHE STRING "SFML Audio Release Libraries")
else()
    # Для других платформ (Linux/Mac)
    set(SFML_AUDIO_DEBUG_LIBS 
        "${SFML_LIB_DIR}/libsfml-audio-s-d.a"
        CACHE STRING "SFML Audio Debug Libraries")
        
    set(SFML_AUDIO_RELEASE_LIBS 
        "${SFML_LIB_DIR}/libsfml-audio-s.a"
        CACHE STRING "SFML Audio Release Libraries")
endif()