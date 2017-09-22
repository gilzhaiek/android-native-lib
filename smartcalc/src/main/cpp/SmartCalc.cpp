#include <jni.h>
#include <android/log.h>
#include <SuperCalc.h>
#include <cstring>

extern "C"
{
//jobject gSmartCalcListener;
const char *kJavaSmartCalcClassPath = "com/protech/mix/SmartCalc";

jfieldID nativePtrSmartCalcField;
jmethodID smartCalcListenerAddId;
jmethodID smartCalcListenerFibId;
jmethodID smartCalcPrintEnumId;

enum FibType {
    FAST = 0,
    SLOW = 1,
};

static void nativeInit(JNIEnv *env, jobject smartCalcInst, jobject smartCalcListener) {
    jclass clazz = env->GetObjectClass(smartCalcInst);
    if (clazz != NULL) {
        nativePtrSmartCalcField = env->GetFieldID(clazz, "nativePtrSmartCalc", "J");
        jobject lgSmartCalcListener = env->NewGlobalRef(smartCalcListener);
        env->SetLongField(smartCalcInst, nativePtrSmartCalcField, (jlong) lgSmartCalcListener);

        smartCalcPrintEnumId = env->GetMethodID(clazz, "printEnum", "(Ljava/lang/String;)V");

        jclass smartCalcListenerClazz = env->GetObjectClass(lgSmartCalcListener);
        if (smartCalcListenerClazz != NULL) {
            smartCalcListenerAddId = env->GetMethodID(smartCalcListenerClazz, "onAdd", "(J)V");
            smartCalcListenerFibId = env->GetMethodID(smartCalcListenerClazz, "onFib", "(J)V");
        }
    }
}

static jobject getSmartCalcListener(JNIEnv *env, jobject instance) {
    return (jobject) env->GetLongField(instance, nativePtrSmartCalcField);
}

static void onAdd(JNIEnv *env, jobject instance, jlong res) {
    if (smartCalcListenerAddId != NULL) {
        env->CallVoidMethod(getSmartCalcListener(env, instance), smartCalcListenerAddId, res);
    }
}

static void onFib(JNIEnv *env, jobject instance, jlong res) {
    if (smartCalcListenerAddId != NULL) {
        env->CallVoidMethod(getSmartCalcListener(env, instance), smartCalcListenerFibId, res);
    }
}

static jint addNative(JNIEnv *env, jobject instance, jint x, jint y) {
    jint sum = (x + y);
    onAdd(env, instance, sum);
    return sum / (2 - sum);
}

static jlong fibNative(JNIEnv *env, jobject instance, jlong x, jobject enumFibType) {
    SuperCalc *superCalc = new SuperCalc();
    jlong res;
    jclass fibTypeClazz = env->GetObjectClass(enumFibType);
    jmethodID getNameMethod = env->GetMethodID(fibTypeClazz, "name", "()Ljava/lang/String;");
    jstring value = (jstring) env->CallObjectMethod(enumFibType, getNameMethod);
    const char *valueNative = env->GetStringUTFChars(value, 0);
    __android_log_print(ANDROID_LOG_DEBUG, "SmartCalc.cpp", "fibNative %s", valueNative);
    if (strcmp(valueNative, "FAST") == 0) {
        __android_log_print(ANDROID_LOG_DEBUG, "SmartCalc.cpp", "fibNative - fast");
        if (smartCalcPrintEnumId != NULL) {
            env->CallVoidMethod(instance, smartCalcPrintEnumId, res);
        }
        res = superCalc->fibI(x);
    } else {
        __android_log_print(ANDROID_LOG_DEBUG, "SmartCalc.cpp", "fibNative - slow");
        res = superCalc->fibR(env, instance, x);
    }

    onFib(env, instance, res);

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
        {"init",       "(Lcom/protech/mix/SmartCalcListener;)V",  (void *) nativeInit},
        {"addNative",  "(II)I",                                   (void *) addNative},
        {"fibNative",  "(JLcom/protech/mix/SmartCalc$FibType;)J", (void *) fibNative},
        {"sFibNative", "(J)J",                                    (void *) sFibNative},
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
