#ifndef DUMB_CALC_H
#define DUMB_CALC_H

class DumbCalc {
public :
    DumbCalc();

    int add(JNIEnv *env, const int x, const int y);
};

#endif