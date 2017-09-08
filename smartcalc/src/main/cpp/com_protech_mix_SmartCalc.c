#include "com_protech_mix_SmartCalc.h"

JNIEXPORT jint JNICALL Java_com_protech_mix_SmartCalc_addThis
        (JNIEnv *env, jobject instance, jint x, jint y) {
    return x + y;
}