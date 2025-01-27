package com.protech.mix;

import android.util.Log;

public class SmartCalc {
    static int instCount = 0;

    public enum FibType {
        FAST, SLOW
    }

    private long nativePtrSmartCalc;

    static {
        System.loadLibrary("smartcalc");
    }

    public SmartCalc() {
        instCount++;

        SmartCalcLogger smartCalcLogger = new SmartCalcLogger(instCount);
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

    public native long fibNative(long x, FibType fibType);

    public static native long sFibNative(long x);

    public long addThis(int x, int y) {
        return addNative(x, y);
    }

    public long fibThis(long x) {
        return fibNative(x, FibType.SLOW);
    }

    public void printEnum(String enumString) {
        if (enumString.equals(FibType.SLOW.name())) {
            Log.d("SmartCalc", "printMe(SLOW)");
        } else if (enumString.equals(FibType.FAST.name())) {
            Log.d("SmartCalc", "printMe(FAST)");
        }
    }
}
