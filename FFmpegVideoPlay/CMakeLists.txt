cmake_minimum_required(VERSION 3.5)

project(FFmpegVideoPlay VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(APP_VERSION "1.1.0")


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# use coustom control
set(SRC_DIR "./")
include_directories(${SRC_DIR})


# FFmpeg
set(FFMPEG_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../3rdpart/ffmpeg")
set(FFMPEG_INCLUDE_DIR "${FFMPEG_ROOT}/include")
set(FFMPEG_LIB_DIR "${FFMPEG_ROOT}/lib")

# 添加 FFmpeg 的 include 和库目录
include_directories(${FFMPEG_INCLUDE_DIR})
link_directories(${FFMPEG_LIB_DIR})

# 链接 FFmpeg 所需的库
set(FFMPEG_LIBS
    avcodec.lib
    avformat.lib
    avutil.lib
    swscale.lib
    swresample.lib
)

set(PROJECT_SOURCES
        main.cpp
        MainWindow.cpp
        MainWindow.h
        MainWindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(FFmpegVideoPlay
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        PlayImage.h PlayImage.cpp
        VideoPlay/ReadThread.h VideoPlay/ReadThread.cpp
        VideoPlay/VideoDecode.h VideoPlay/VideoDecode.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET FFmpegVideoPlay APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(FFmpegVideoPlay SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(FFmpegVideoPlay
            ${PROJECT_SOURCES}
            PlayImage.h PlayImage.cpp
            VideoPlay/ReadThread.h VideoPlay/ReadThread.cpp
            VideoPlay/VideoDecode.h VideoPlay/VideoDecode.cpp
        )
    endif()
endif()

target_link_libraries(FFmpegVideoPlay PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${FFMPEG_LIBS})

target_compile_definitions(FFmpegVideoPlay PRIVATE APP_VERSION="${APP_VERSION}")

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatiFFmpegVideoPlaycally since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.FFmpegVideoPlay)
endif()
set_target_properties(FFmpegVideoPlay PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS FFmpegVideoPlay
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(FFmpegVideoPlay)
endif()
