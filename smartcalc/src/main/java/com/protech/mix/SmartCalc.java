package com.protech.mix;

public class SmartCalc {
    SmartCalcListener smartCalcListener;

    static {
        System.loadLibrary("smartcalc");
    }

    public SmartCalc(SmartCalcListener smartCalcListener) {
        this.smartCalcListener = smartCalcListener;
    }

    public native int addNative(SmartCalcListener smartCalcListener, int x, int y);

    public native long fibNative(SmartCalcListener smartCalcListener, long x, boolean fast);

    public long addThis(int x, int y) {
        SmartCalcLogger smartCalcLogger = new SmartCalcLogger();
        return addNative(smartCalcLogger, x, y);
    }

    public long fibThis(long x, boolean fast) {
        SmartCalcLogger smartCalcLogger = new SmartCalcLogger();
        return fibNative(smartCalcLogger, x, fast);
    }

    private void onNativeResult(long result) {
        this.smartCalcListener.onFib(result);
    }
}
