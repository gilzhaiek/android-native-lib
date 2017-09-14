#include <jni.h>

extern "C"

JNIEXPORT jint JNICALL Java_com_protech_mix_SmartCalc_addThis(
        JNIEnv *env, jobject instance, jint x, jint y) {
    return x + y;
}

JNIEXPORT jlong JNICALL Java_com_protech_mix_SmartCalc_fibThis(
        JNIEnv *env, jobject instance, jlong x, jboolean fast) {
    return x + 1000;
//    SuperCalc *superCalc = new SuperCalc();
//    if (fast) {
//        return superCalc->fibI(x);
//    } else {
//        return superCalc->fibR(x);
//    }
}