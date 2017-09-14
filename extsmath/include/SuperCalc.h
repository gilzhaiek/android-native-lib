#ifndef SUPER_CALC_H
#define SUPER_CALC_H

class SuperCalc {
public :
    SuperCalc();

    jlong fib(jlong n);

    jlong fibR(const jlong n);

    jlong fibI(const jlong n);
};

#endif