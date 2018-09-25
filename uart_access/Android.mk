LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional

LOCAL_SRC_FILES := \
					uart_access.cpp \

LOCAL_C_INCLUDES += $(KERNEL_HEADERS) \
					$(LOCAL_PATH)
					
LOCAL_SHARED_LIBRARIES:= libcutils libstdc++ libc libdl libutils liblog

LOCAL_MODULE:= libuart_access_min

include $(BUILD_SHARED_LIBRARY)
#BUILD_STATIC_LIBRARY     BUILD_EXECUTABLE

#/////////////////////////////////////////////////////////////////////////////////////LOCAL_PATH:= $(call my-dir)




include $(CLEAR_VARS)
LOCAL_MODULE = libwebsocket
LOCAL_PREBUILT_LIBS := ../websocket-master/libs/armeabi-v7a/libwebsocket.so

LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE = libevent
LOCAL_PREBUILT_LIBS := $(LOCAL_PATH)/../libevent-master/libs/armeabi-v7a/libevent.so

LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)
#/////////////////////////////////////////////////////////////////////////////////////
include $(CLEAR_VARS)

LOCAL_SHARED_LIBRARIES := libwebsocket \
						libcutils \
						libstdc++ \
						libc libdl \
						libutils \
						liblog \
						libuart_access_min \
						libevent

LOCAL_SRC_FILES := main_ws_uart.cpp

LOCAL_C_INCLUDES := $(KERNEL_HEADERS) \
					$(LOCAL_PATH) \
					$(LOCAL_PATH)/../websocket-master/jni/include \
					$(LOCAL_PATH)/../websocket-master/jni

LOCAL_MODULE_TAGS := optional
LOCAL_MODULE := ws_uart

LOCAL_LDFLAGS +=$(LOCAL_PATH)/../websocket-master/obj/local/armeabi-v7a/libwebsocket.a 
				

include $(BUILD_EXECUTABLE)

