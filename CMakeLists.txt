cmake_minimum_required(VERSION 3.10)
project(solar)

set(CMAKE_CXX_STANDARD 17)

# 현재 디렉토리와 하위 폴더들을 헤더 검색 경로에 포함시킵니다.
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# 빌드할 소스 파일 목록
add_library(solar SHARED
    main.cpp
    imgui.cpp
    imgui_draw.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
    dobby.cpp
)

# 안드로이드 빌드 시 필요한 라이브러리 링크
target_link_libraries(solar PRIVATE log android)
