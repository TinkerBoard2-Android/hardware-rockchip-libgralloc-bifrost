LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := android.hardware.graphics.allocator@3.0-service
LOCAL_INIT_RC := android.hardware.graphics.allocator@3.0-service.rc
LOCAL_MODULE_CLASS := EXECUTABLES
LOCAL_MODULE_RELATIVE_PATH := hw
LOCAL_PROPRIETARY_MODULE := true
LOCAL_SHARED_LIBRARIES := libhidlbase liblog libhidltransport libutils
LOCAL_SHARED_LIBRARIES += android.hardware.graphics.allocator@3.0

LOCAL_SRC_FILES := service.cpp

include $(BUILD_EXECUTABLE)