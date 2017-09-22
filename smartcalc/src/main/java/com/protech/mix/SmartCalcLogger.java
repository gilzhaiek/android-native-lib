package com.protech.mix;

import android.util.Log;

import java.util.IllegalFormatPrecisionException;

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
        if (result == 2) {
            Log.e("ERROR", "result is 2");
            throw new IllegalFormatPrecisionException(2);
        }
        Log.d("SmartCalcLogger[" + instCnt + "]", "onFib(" + result + ")");
    }
}

