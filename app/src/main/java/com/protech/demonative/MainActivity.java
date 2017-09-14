package com.protech.demonative;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import com.protech.mix.SmartCalc;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {
    static {
        System.loadLibrary("app-native");
    }

    TextView tvResult;
    Button btnCalcDumb, btnCalcSmart, btnFibSmart;
    EditText etX, etY;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        ((TextView) findViewById(R.id.tv_hello_native)).setText(stringFromJNI());

        tvResult = (TextView) findViewById(R.id.tv_result);
        etX = (EditText) findViewById(R.id.et_x);
        etY = (EditText) findViewById(R.id.et_y);
        btnCalcDumb = (Button) findViewById(R.id.btn_dumb_add);
        btnCalcDumb.setOnClickListener(this);
        btnCalcSmart = (Button) findViewById(R.id.btn_smart_add);
        btnCalcSmart.setOnClickListener(this);
        btnFibSmart = (Button) findViewById(R.id.btn_smart_fib);
        btnFibSmart.setOnClickListener(this);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native int addThis(int x, int y);

    @Override
    public void onClick(View view) {
        try {
            int x = Integer.valueOf(etX.getText().toString());
            if (view == btnFibSmart) {
                SmartCalc smartCalc = new SmartCalc();
                tvResult.setText(String.valueOf(smartCalc.fibThis((long) x, false)));
            } else {
                int y = Integer.valueOf(etY.getText().toString());
                if (view == btnCalcDumb) {
                    tvResult.setText(String.valueOf(addThis(x, y)));
                } else {
                    SmartCalc smartCalc = new SmartCalc();
                    tvResult.setText(String.valueOf(smartCalc.addThis(x, y)));
                }
            }
        } catch (NumberFormatException e) {
            tvResult.setText("NumberFormatException");
        }
    }
}
