#include <jni.h>
#include "../include/DumbCalc.h"

extern "C"
JNIEXPORT jint JNICALL
Java_com_protech_demonative_MainActivity_addThis(JNIEnv *env, jobject instance,
                                                 jint x, jint y) {
    DumbCalc *dumbCalc = new DumbCalc();
    return dumbCalc->add(env, x, y);
}

