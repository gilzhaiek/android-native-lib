package com.protech.mix;

public class SmartCalc {
    static {
        System.loadLibrary("smartcalc");
    }

    public native int addThis(int x, int y);

    public native long fibThis(long x, boolean fast);
}
