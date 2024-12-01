cmake_minimum_required(VERSION 3.5)

project(FFmpegVideoPlayHWGL VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
    qt_add_executable(FFmpegVideoPlayHWGL
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        VideoPlay/videodecode.h VideoPlay/videodecode.cpp
        VideoPlay/readthread.h VideoPlay/readthread.cpp
        playimage.h playimage.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET FFmpegVideoPlayHWGL APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(FFmpegVideoPlayHWGL SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(FFmpegVideoPlayHWGL
            ${PROJECT_SOURCES}
            VideoPlay/videodecode.h VideoPlay/videodecode.cpp
            VideoPlay/readthread.h VideoPlay/readthread.cpp
            playimage.h playimage.cpp
            res.qrc
            
        )
    endif()
endif()

target_link_libraries(FFmpegVideoPlayHWGL PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${FFMPEG_LIBS})

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.FFmpegVideoPlayHWGL)
endif()
set_target_properties(FFmpegVideoPlayHWGL PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS FFmpegVideoPlayHWGL
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(FFmpegVideoPlayHWGL)
endif()
