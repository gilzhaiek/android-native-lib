package com.protech.mix;

import android.util.Log;

/**
 * Created by gilzhaiek on 2017-09-13.
 */

public class SmartCalcLogger implements SmartCalcListener {

    @Override
    public void onFib(long result) {
        Log.d("SmartCalcLogger", "onFib(" + result + ")");
    }
}
