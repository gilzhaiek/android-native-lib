package com.protech.mix;

import android.util.Log;

public class SmartCalc {
    static {
        System.loadLibrary("smartcalc");
    }

    public SmartCalc() {
        SmartCalcLogger smartCalcLogger = new SmartCalcLogger();
        this.init(smartCalcLogger);
        System.gc();
    }

    // Make sure this will be called from Native Code
    private void onProgress(long x) {
        Log.d("SmartCalc", "onProgress(" + x + ")");
    }

    // Make sure this will be called from Native Code
    private static void onSProgress(long x) {
        Log.d("SmartCalc", "Static onProgress(" + x + ")");
    }

    public native void init(SmartCalcListener smartCalcListener);

    public native int addNative(int x, int y);

    public native long fibNative(long x, boolean fast);

    public static native long sFibNative(long x);

    public long addThis(int x, int y) {
        return addNative(x, y);
    }

    public long fibThis(long x, boolean fast) {
        return sFibNative(x);
    }
}
