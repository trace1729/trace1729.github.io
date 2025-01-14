adb push hello.txt /sdcard/manjaro/
adb ls /system/bin
adb shell getprop ro.product.model
adb shell dumpsys battery
adb shell wm size
adb shell dumpsys window displays
adb shell getprop ro.build.version.release
adb shell pm uninstall --user 0 cn.HONOR.qinxuan
adb shell pm list packages -s | grep 'huawei' > package.txt
