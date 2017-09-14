#include <jni.h>
#include <SuperCalc.h>

extern "C" JNIEXPORT jint JNICALL Java_com_protech_mix_SmartCalc_addNative(
        JNIEnv *env, jobject instance, jobject smartCalcListener, jint x, jint y) {
    return x + y;
}

extern "C" JNIEXPORT jlong JNICALL Java_com_protech_mix_SmartCalc_fibNative(
        JNIEnv *env, jobject instance, jobject smartCalcListener, jlong x, jboolean fast) {
    SuperCalc *superCalc = new SuperCalc(instance, smartCalcListener);
    if (fast) {
        return superCalc->fibI(x);
    } else {
        return superCalc->fibR(x);
    }
}