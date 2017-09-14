package com.protech.mix;

public class SmartCalc {
    static {
        System.loadLibrary("smartcalc");
    }

    public SmartCalc() {
        SmartCalcLogger smartCalcLogger = new SmartCalcLogger();
        this.init(smartCalcLogger);
        System.gc();
    }

    public native void init(SmartCalcListener smartCalcListener);

    public native int addNative(int x, int y);

    public native long fibNative(long x, boolean fast);

    public long addThis(int x, int y) {
        return addNative(x, y);
    }

    public long fibThis(long x, boolean fast) {
        return fibNative(x, fast);
    }
}
