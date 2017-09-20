
#include <iostream>
#include <jni.h>
#include "../include/SuperCalc.h"
#include <android/log.h>

using namespace std;

SuperCalc::SuperCalc() {
}

static void onProgress(JNIEnv *env, jobject instance, jlong progress) {
    jclass clazz = env->GetObjectClass(instance);
    if (clazz != NULL) {
        jmethodID method = env->GetMethodID(clazz, "onProgress", "(J)V");
        if (method != NULL) {
            env->CallVoidMethod(instance, method, progress);
        }
    }
}

/* Recursive implementation of the fibonacci algorithm (in a helper function) */
jlong fib(JNIEnv *env, jobject smartCalcInstance, jlong n) {
    onProgress(env, smartCalcInstance, n);

    if (n <= 0) {
        return 0;
    }

    if (n == 1) {
        return 1;
    }

    return fib(env, smartCalcInstance, n - 1) + fib(env, smartCalcInstance, n - 2);
}

jlong SuperCalc::fibR(JNIEnv *env, jobject smartCalcInstance, jlong n) {
    __android_log_print(ANDROID_LOG_DEBUG, "SuperCalc.cpp", "fibR(%lld)", (long long) n);
    jlong result = fib(env, smartCalcInstance, n);
    return result;
}

jlong SuperCalc::fibI(const jlong n) {
    jlong previous = -1;
    jlong result = 1;
    jlong i;
    __android_log_print(ANDROID_LOG_DEBUG, "SuperCalc.cpp", "fibI(%lld)", (long long) n);
    for (i = 0; i <= n; i++) {
        jlong sum = result + previous;
        previous = result;
        result = sum;
    }
    return result;
}

