LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

# 源代码
LOCAL_SRC_FILES := \
    main.cpp


# 导入库会自动设置
# SDL_PATH := ../SDL  # SDL
# LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include  # SDL
# LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -lOpenSLES -llog -landroid  # SDL

LOCAL_SHARED_LIBRARIES := SDL3

include $(BUILD_SHARED_LIBRARY)
