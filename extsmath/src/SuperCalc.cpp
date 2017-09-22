
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

jlong fibClean(jlong n) {
    if (n <= 0) {
        return 0;
    }

    if (n == 1) {
        return 1;
    }

    return fibClean(n - 1) + fibClean(n - 2);
}

void *fib_thread(void *pVoid) {
    jlong n = (jlong) pVoid;
    __android_log_print(ANDROID_LOG_DEBUG, "SuperCalc.cpp", "fib_thread(%lld)", (long long) n);
    jlong result = fibClean(n);
    __android_log_print(ANDROID_LOG_DEBUG, "SuperCalc.cpp", "fib_thread(%lld) = (%lld)",
                        (long long) n, (long long) result);
}

pthread_t p_fib_thread;

jlong SuperCalc::fibR(JNIEnv *env, jobject smartCalcInstance, jlong n) {
    __android_log_print(ANDROID_LOG_DEBUG, "SuperCalc.cpp", "fibR(%lld)", (long long) n);
    pthread_create(&p_fib_thread, NULL, fib_thread, (void *) n);
    __android_log_print(ANDROID_LOG_DEBUG, "SuperCalc.cpp", "fibR(%lld)", (long long) n);
    return 0;
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

