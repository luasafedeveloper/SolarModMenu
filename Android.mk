LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := modmenu
LOCAL_SRC_FILES := main.cpp
# 만약 imgui 관련 소스(.cpp)가 더 있다면 아래에 추가해줍니다.
# LOCAL_SRC_FILES += imgui.cpp imgui_draw.cpp imgui_tables.cpp imgui_widgets.cpp imgui_impl_android.cpp imgui_impl_opengl3.cpp

LOCAL_LDLIBS    := -llog -landroid -lEGL -lGLESv3

include $(BUILD_SHARED_LIBRARY)
