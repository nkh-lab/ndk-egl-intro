cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Export ANativeActivity_onCreate(),
# Refer to: https://github.com/android-ndk/ndk/issues/381.
set(CMAKE_SHARED_LINKER_FLAGS
        "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")

add_library(native_app_glue STATIC
        #${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c
        native_app_glue/android_native_app_glue.c
        )
target_link_libraries(native_app_glue log)
target_include_directories(native_app_glue PUBLIC
        #${ANDROID_NDK}/sources/android/native_app_glue
        native_app_glue
        )

add_library(MainActivity SHARED MainActivity.cpp)
target_link_libraries(MainActivity
        android
        native_app_glue
        EGL
        GLESv1_CM
        )

