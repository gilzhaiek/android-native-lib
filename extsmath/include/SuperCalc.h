
#ifndef SUPER_CALC_H
#define SUPER_CALC_H

using namespace std;

class SuperCalc {
public :
    SuperCalc();

    jlong fibR(JNIEnv *env, jobject smartCalcInstance, jlong n);

    jlong fibI(jlong n);
};

#endif