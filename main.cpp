#include <jni.h>
#include <string>
#include <pthread.h>
#include <android/log.h>
#include <unistd.h>
#include <sys/mman.h>
#include <dlfcn.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include "imgui.h"
#include "dobby.h" // Dobby 후킹 라이브러리 헤더

bool bAimbot = false;
bool bESP = false;
bool bSkinChanger = false;
bool bTranslation = false;
bool showMenu = true;
bool g_Initialized = false;

typedef EGLBoolean (*orig_eglSwapBuffers_t)(EGLDisplay dpy, EGLSurface surface);
orig_eglSwapBuffers_t orig_eglSwapBuffers = nullptr;

void DrawSolarMenu() {
    if (!showMenu) return;

    ImGui::SetNextWindowSize(ImVec2(350, 300), ImGuiCond_FirstUseEver);
    
    ImGui::Begin("Solar v1.0 - Mod Menu", &showMenu, ImGuiWindowFlags_None);

    ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.8f, 1.0f), "Solar Mobile Panel");
    ImGui::Separator();

    ImGui::Checkbox("Aimbot", &bAimbot);
    ImGui::Checkbox("ESP (Box & Line)", &bESP);
    ImGui::Checkbox("Skin Changer", &bSkinChanger);
    ImGui::Checkbox("Chat Translation", &bTranslation);

    ImGui::Separator();
    
    if (ImGui::Button("Hide Menu", ImVec2(-1, 30))) {
        showMenu = false;
    }

    ImGui::End();
}

EGLBoolean hooked_eglSwapBuffers(EGLDisplay dpy, EGLSurface surface) {
    if (!g_Initialized) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui::StyleColorsDark();
        g_Initialized = true;
    }

    ImGui::NewFrame();
    DrawSolarMenu();
    ImGui::Render();

    return orig_eglSwapBuffers(dpy, surface);
}

void* hack_thread(void* arg) {
    void* handle = nullptr;
    while (!handle) {
        handle = dlopen("libEGL.so", RTLD_NOLOAD);
        sleep(1);
    }
    
    // Dobby를 이용해 화면 렌더링 함수를 가로채는 핵심 코드
    void* eglSwapBuffers_addr = dlsym(handle, "eglSwapBuffers");
    if (eglSwapBuffers_addr) {
        DobbyHook(eglSwapBuffers_addr, (void*)hooked_eglSwapBuffers, (void**)&orig_eglSwapBuffers);
    }
    
    return nullptr;
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    pthread_t thread;
    pthread_create(&thread, nullptr, hack_thread, nullptr);
    return JNI_VERSION_1_6;
}
