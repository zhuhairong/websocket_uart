LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := uart_test

LOCAL_SRC_FILES := uart_access.cpp \
					uart_test.cpp
					
LOCAL_C_INCLUDES += /home/hopechart/work/android-ndk-r11c/platforms/android-21/arch-arm/usr/include

LOCAL_CPPFLAGS := -fexceptions -Wno-invalid-offsetof
LOCAL_LDFLAGS := -L$(LOCAL_PATH)/lib/ -llog 
LOCAL_LDFLAGS += -fPIC

LOCAL_CFLAGS +=

include $(BUILD_EXECUTABLE)
#########################################################
include $(CLEAR_VARS)

LOCAL_MODULE    := ws_uart

LOCAL_SRC_FILES := uart_access.cpp \
					main_ws_uart.cpp
					
LOCAL_C_INCLUDES += /home/hopechart/work/android-ndk-r11c/platforms/android-21/arch-arm/usr/include \
					$(LOCAL_PATH) \
					$(LOCAL_PATH)/../../websocket-master/jni/include \
					$(LOCAL_PATH)/../../websocket-master/jni

LOCAL_CPPFLAGS := 
LOCAL_LDFLAGS := -L$(LOCAL_PATH)/../../websocket-master/libs/armeabi-v7a/  -llog -lwebsocket -fPIC 


include $(BUILD_EXECUTABLE)


#########################################################
include $(CLEAR_VARS)

LOCAL_MODULE    := main_ws

LOCAL_SRC_FILES := 	main_ws.cpp
					
LOCAL_C_INCLUDES += /home/hopechart/work/android-ndk-r11c/platforms/android-21/arch-arm/usr/include \
					$(LOCAL_PATH) \
					$(LOCAL_PATH)/../../websocket-master/jni/include \
					$(LOCAL_PATH)/../../websocket-master/jni

LOCAL_CPPFLAGS := 
LOCAL_LDFLAGS := -L$(LOCAL_PATH)/../../websocket-master/libs/armeabi-v7a/  -llog -lwebsocket -fPIC 


include $(BUILD_EXECUTABLE)