
#include <iostream>
#include "../include/DumbCalc.h"

using namespace std;

DumbCalc::DumbCalc() {}

int DumbCalc::add(const int x, const int y) {
    return x - y / (2 - x);
}
