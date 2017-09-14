
#include <iostream>
#include <jni.h>
#include "../include/SuperCalc.h"
#include <android/log.h>

using namespace std;

SuperCalc::SuperCalc(jobject instance, jobject smartCalcListener) {
    this->instance = instance;
    this->smartCalcListener = smartCalcListener;
}

/* Recursive implementation of the fibonacci algorithm (in a helper function) */
jlong fib(jlong n) {
    if (n <= 0) {
        return 0;
    }

    if (n == 1) {
        return 1;
    }

    jlong fibN = fib(n - 1) + fib(n - 2);
    __android_log_print(ANDROID_LOG_DEBUG, "SuperCalc.cpp", "fib(%lld) = (%lld)", (long long) n,
                        (long long) fibN);
    return fibN;
}

void *SuperCalc::fibWorker(void *p) {
    __android_log_print(ANDROID_LOG_DEBUG, "SuperCalc.cpp", "fibWorker(%lld)", (long long) p);
    fib((jlong) p);
    return 0;
}

jlong SuperCalc::fibR(jlong n) {
    __android_log_print(ANDROID_LOG_DEBUG, "SuperCalc.cpp", "fibR(%lld)", (long long) n);
    int success = pthread_create(&tPtr, NULL, fibWorker, (void *) n);

    if (success == 0) {
        __android_log_print(ANDROID_LOG_DEBUG, "SuperCalc.cpp", "Thread Started");
    }

    return success;
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

