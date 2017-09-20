package com.protech.mix;

import android.util.Log;

/**
 * Created by gilzhaiek on 2017-09-13.
 */

public class SmartCalcLogger implements SmartCalcListener {
    final int instCnt;

    public SmartCalcLogger(int instCnt) {
        this.instCnt = instCnt;
    }

    @Override
    public void onAdd(long result) {
        Log.d("SmartCalcLogger[" + instCnt + "]", "onAdd(" + result + ")");
    }

    @Override
    public void onFib(long result) {
        Log.d("SmartCalcLogger[" + instCnt + "]", "onFib(" + result + ")");
    }
}
