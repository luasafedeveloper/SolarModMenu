cmake_minimum_required(VERSION 3.10)
project(solar)

set(CMAKE_CXX_STANDARD 17)

# 빌드할 소스 파일 목록에 ImGui와 Dobby 파일들을 추가합니다.
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
