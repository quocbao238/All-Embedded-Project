package bao.bon.smartlight;

//import android.support.v7.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Switch;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

import bao.bon.smartlight.Model.ButtonModel;
import bao.bon.smartlight.Model.Sensor;

public class MainActivity extends AppCompatActivity {

    Switch swLight1, swLight2, swLight3, swLight4;
    TextView txtTemp, txtHumi;

    ButtonModel buttonModel;
    bao.bon.smartlight.Model.Sensor sensorModel;
    // Khai báo database
    FirebaseDatabase database;
    DatabaseReference databaseReference;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Ánh xạ
        initView();

        //Init Firebase
        database = FirebaseDatabase.getInstance();
        databaseReference = database.getReference("Controller");

        //Database Change
        databaseChange();

        btnChange();
    }

    private void initView() {
        swLight1 = findViewById(R.id.switchlight1);
        swLight2 = findViewById(R.id.switchlight2);
        swLight3 = findViewById(R.id.switchlight3);
        swLight4 = findViewById(R.id.switchlight4);
        txtTemp  = findViewById(R.id.txtTemp);
        txtHumi = findViewById(R.id.txtHumi);

    }


    /* handle button status */

    private void btnChange() {
        swLight1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (swLight1.isChecked()) {
                    databaseReference.child("Button").child("Btn1").setValue("0");
                } else {
                    databaseReference.child("Button").child("Btn1").setValue("1");
                }
            }
        });
        swLight2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (swLight2.isChecked()) {
                    databaseReference.child("Button").child("Btn2").setValue("0");
                } else {
                    databaseReference.child("Button").child("Btn2").setValue("1");
                }
            }
        });
        swLight3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (swLight3.isChecked()) {
                    databaseReference.child("Button").child("Btn3").setValue("0");
                } else {
                    databaseReference.child("Button").child("Btn3").setValue("1");
                }
            }
        });
        swLight4.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (swLight4.isChecked()) {
                    databaseReference.child("Button").child("Btn4").setValue("0");
                } else {
                    databaseReference.child("Button").child("Btn4").setValue("1");
                }
            }
        });

    }
    /* Funtion changedatabase from Firebase */
    private void databaseChange() {
        databaseReference.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
                showData(dataSnapshot);
                loadData();
            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {

            }
        });
    }
    /* Đọc dữ liệu từ database về */
    private void showData(DataSnapshot dataSnapshot) {
        /* Get value of Button0 */
        buttonModel = new ButtonModel();
        buttonModel.setBtn1(dataSnapshot.child("Button").child("Btn1").getValue().toString()); // Get Value Key : ButtonModel , Value of Btn1
        buttonModel.setBtn2(dataSnapshot.child("Button").child("Btn2").getValue().toString()); // Get Value Key : ButtonModel , Value of Btn1
        buttonModel.setBtn3(dataSnapshot.child("Button").child("Btn3").getValue().toString()); // Get Value Key : ButtonModel , Value of Btn1
        buttonModel.setBtn4(dataSnapshot.child("Button").child("Btn4").getValue().toString()); // Get Value Key : ButtonModel , Value of Btn1

        /* Get value Of Sensor */
        sensorModel = new Sensor();
        sensorModel.setSensor_humi(dataSnapshot.child("Sensor").child("Humi").getValue().toString()); // Get Value Key : ButtonModel , Value of Btn1
        sensorModel.setSensor_temp(dataSnapshot.child("Sensor").child("Temp").getValue().toString()); // Get Value Key : ButtonModel , Value of Btn1
    }
    /* Hiển thị dữ liệu lên màn hình */
    private void loadData() {
        txtTemp.setText(sensorModel.getSensor_temp() + "°C");
        txtHumi.setText(sensorModel.getSensor_humi() + "%");

        if (buttonModel.getBtn1().equals("0")) {
            swLight1.setChecked(true);
        } else if (buttonModel.getBtn1().equals("1")) {
            swLight1.setChecked(false);
        }

        if (buttonModel.getBtn2().equals("0")) {
            swLight2.setChecked(true);
        } else if (buttonModel.getBtn2().equals("1")) {
            swLight2.setChecked(false);
        }

        if (buttonModel.getBtn3().equals("0")) {
            swLight3.setChecked(true);
        } else if (buttonModel.getBtn3().equals("1")) {
            swLight3.setChecked(false);
        }

        if (buttonModel.getBtn4().equals("0")) {
            swLight4.setChecked(true);
        } else if (buttonModel.getBtn4().equals("1")) {
            swLight4.setChecked(false);
        }
    }
}
