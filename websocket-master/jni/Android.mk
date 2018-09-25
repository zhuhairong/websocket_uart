LOCAL_PATH := $(call my-dir)


include $(CLEAR_VARS)
LOCAL_MODULE	:= websocket_server


LOCAL_LDLIBS	+= -llog -lz
LOCAL_CPPFLAGS	+= -fexceptions

LOCAL_C_INCLUDES := include \
					$(LOCAL_PATH)

WEB_SOCKET_FILES := websock.c base64.c sha1.c  frames.c default_callbacks.c api.c sha1.h base64.h utf.c util.c 

LOCAL_SRC_FILES	:= $(WEB_SOCKET_FILES) conv.c uart_access.cpp main.c 
#main_ws_uart.cpp


LOCAL_LDFLAGS += ../../libevent-master/libs/$(TARGET_ARCH_ABI)/libevent.so 

#include $(BUILD_SHARED_LIBRARY)
#include $(BUILD_STATIC_LIBRARY)
include $(BUILD_EXECUTABLE)

###################################




include $(CLEAR_VARS)
LOCAL_MODULE	:= vircom


LOCAL_LDLIBS	+= -llog -lz

LOCAL_C_INCLUDES := include \
					$(LOCAL_PATH)

LOCAL_SRC_FILES	:= vircom.c 
#main_ws_uart.cpp

#include $(BUILD_SHARED_LIBRARY)
#include $(BUILD_STATIC_LIBRARY)
include $(BUILD_EXECUTABLE)
############# install ##############
#include $(CLEAR_VARS)

#DEST_PATH	:= /data/local/tmp

#all:
#	adb push $(LOCAL_PATH)\..\libs\x86\websocket $(DEST_PATH)
#	adb shell "chmod 777 $(DEST_PATH)/websocket"
