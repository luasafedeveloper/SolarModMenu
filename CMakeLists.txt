cmake_minimum_required(VERSION 3.10)
project(solar)

set(CMAKE_CXX_STANDARD 17)

# Dobby 라이브러리를 서브디렉토리로 통째로 빌드에 포함
add_subdirectory(dobby_lib)

# 내 모드 메뉴 라이브러리 설정
add_library(solar SHARED
    main.cpp
    imgui.cpp
    imgui_draw.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
)

# Dobby 헤더 경로 연결
target_include_directories(solar PRIVATE dobby_lib/include)

# Dobby와 안드로이드 시스템 라이브러리 링크
target_link_libraries(solar PRIVATE dobby log android)
