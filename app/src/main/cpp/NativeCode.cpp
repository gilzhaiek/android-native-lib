#include <jni.h>
#include <string>

extern "C"
JNIEXPORT jstring JNICALL
Java_com_protech_demonative_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from ProTech";
    return env->NewStringUTF(hello.c_str());
}
