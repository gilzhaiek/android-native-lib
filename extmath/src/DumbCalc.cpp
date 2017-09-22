
#include <iostream>
#include <android/log.h>
#include <jni.h>
#include "../include/DumbCalc.h"

using namespace std;

static void ThrowExceptionByClassName(JNIEnv *env, const char *name, const char *message) {
    jclass clazz = env->FindClass(name);
    if (clazz != NULL) {
        env->ThrowNew(clazz, message);
        env->DeleteLocalRef(clazz);
    }
}

DumbCalc::DumbCalc() {}

int DumbCalc::add(JNIEnv *env, const int x, const int y) {
    __android_log_print(ANDROID_LOG_DEBUG, "DumbCalc", "x=%d y=%d", x, y);
    if (2 == x) {
        ThrowExceptionByClassName(env, "java/lang/IllegalArgumentException",
                                  "x can't be equal to 2");
        return 0;
    }
    int res = x - y / (2 - x);
    return res;
}
