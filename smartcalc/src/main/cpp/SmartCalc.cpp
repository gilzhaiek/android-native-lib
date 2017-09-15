#include <jni.h>
#include <android/log.h>
#include <SuperCalc.h>

extern "C"
{
jobject gSmartCalcListener;
const char *kJavaSmartCalcClassPath = "com/protech/mix/SmartCalc";

static void nativeInit(JNIEnv *env, jobject object, jobject smartCalcListener) {
    gSmartCalcListener = env->NewGlobalRef(smartCalcListener);
}

static jint addNative(JNIEnv *env, jobject instance, jint x, jint y) {
    return x + y;
}

static void onResult(JNIEnv *env, jobject instance, jlong res) {
    jclass clazz = env->GetObjectClass(gSmartCalcListener);
    if (clazz != NULL) {
        jmethodID method = env->GetMethodID(clazz, "onFib", "(J)V");
        if (method != NULL) {
            env->CallVoidMethod(gSmartCalcListener, method, res);
        }
    }
}

static jlong fibNative(JNIEnv *env, jobject instance, jlong x, jboolean fast) {
    SuperCalc *superCalc = new SuperCalc();
    jlong res;
    if (fast) {
        res = superCalc->fibI(x);
    } else {
        res = superCalc->fibR(env, instance, x);
    }

    onResult(env, instance, res);

    return res;
}


static void onSProgress(JNIEnv *env, jclass smartCalcClazz, jlong progress) {
    jmethodID method = env->GetStaticMethodID(smartCalcClazz, "onSProgress", "(J)V");
    if (method != NULL) {
        env->CallStaticVoidMethod(smartCalcClazz, method, progress);
    }
}

/* Recursive implementation of the fibonacci algorithm (in a helper function) */
static jlong sFib(JNIEnv *env, jclass smartCalcClazz, jlong n) {
    onSProgress(env, smartCalcClazz, n);

    if (n <= 0) {
        return 0;
    }

    if (n == 1) {
        return 1;
    }

    return sFib(env, smartCalcClazz, n - 1) + sFib(env, smartCalcClazz, n - 2);
}

static jlong sFibNative(JNIEnv *env, jclass clazz, jlong x) {
    return sFib(env, clazz, x);
}

static JNINativeMethod methodTable[] = {
        {"init",       "(Lcom/protech/mix/SmartCalcListener;)V", (void *) nativeInit},
        {"addNative",  "(II)I",                                  (void *) addNative},
        {"fibNative",  "(JZ)J",                                  (void *) fibNative},
        {"sFibNative", "(J)J",                                   (void *) sFibNative},
};

jint JNI_OnLoad(JavaVM *aVm, void *aReserved) {
    JNIEnv *env;
    if (aVm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
        __android_log_print(ANDROID_LOG_ERROR, "SmartCalc.cpp", "Failed to get the environment");
        return -1;
    }

    jclass activityClass = env->FindClass(kJavaSmartCalcClassPath);
    if (!activityClass) {
        __android_log_print(ANDROID_LOG_ERROR, "SmartCalc.cpp", "failed to get %s class reference",
                            kJavaSmartCalcClassPath);
        return -1;
    }

    env->RegisterNatives(activityClass, methodTable, sizeof(methodTable) / sizeof(methodTable[0]));

    return JNI_VERSION_1_6;
}
}