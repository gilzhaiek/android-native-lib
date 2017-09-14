#include <pthread.h>

#ifndef SUPER_CALC_H
#define SUPER_CALC_H

using namespace std;

class SuperCalc {
public :
    SuperCalc(jobject instance, jobject smartCalcListener);

    jlong fibR(jlong n);

    jlong fibI(jlong n);

private:
    jobject instance;
    jobject smartCalcListener;

    static void *fibWorker(void *param);

    pthread_t tPtr;
};

#endif