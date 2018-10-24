adb connect 127.0.0.1:7555
adb push libs/x86/websocket_server /system/bin
adb push libs/x86/vircom /system/bin
adb push index.html /sdcard/