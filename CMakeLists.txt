cmake_minimum_required(VERSION 3.10.2)
project("solar")

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 11)

# 라이브러리 생성 (libsolar.so)
add_library(
    solar
    SHARED
    main.cpp
    # 만약 ImGui 소스파일(.cpp)들도 같이 쓰신다면 여기에 추가해야 합니다.
    # 예: imgui.cpp, imgui_draw.cpp 등
)

# 안드로이드 기본 라이브러리 링크 (로그, 화면 렌더링용)
find_library(log-lib log)
find_library(EGL-lib EGL)
find_library(GLESv3-lib GLESv3)

target_link_libraries(
    solar
    ${log-lib}
    ${EGL-lib}
    ${GLESv3-lib}
)
