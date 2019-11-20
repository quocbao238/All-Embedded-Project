package bao.bon.appcontroller;

import android.content.Intent;
import android.support.annotation.NonNull;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;
import android.widget.Switch;
import android.widget.TextView;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

import bao.bon.appcontroller.Model.ButtonModel;
import bao.bon.appcontroller.Model.Dif;
import bao.bon.appcontroller.Model.Sensor;
import bao.bon.appcontroller.Model.Stability;

public class HomeAcitivity extends AppCompatActivity {

    Switch swTap, swSpray, swLight;
    ImageView imgSetting;
    TextView txtTemp, txtHumi , txtJson;
    ButtonModel buttonModel;
    Dif difModel;
    Sensor sensorModel;
    Stability stabilityModel;
    //Init firebase
    FirebaseDatabase database;
    DatabaseReference databaseReference;

    String temp, humi;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_home_acitivity);
        findId();

        //Init Firebase
        database = FirebaseDatabase.getInstance();
        databaseReference = database.getReference("Controller");

        //Database Change
        databaseChange();

        btnChange();

        imgSetting.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent stabilityItent = new Intent(HomeAcitivity.this, bao.bon.appcontroller.Stability.class);
                startActivity(stabilityItent);
            }
        });

    }

    private void btnChange() {

        swTap.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(swTap.isChecked()) {
                    databaseReference.child("Button").child("Btn1").setValue("0");
                }else{
                    databaseReference.child("Button").child("Btn1").setValue("1");
                }
            }
        });
        swSpray.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(swSpray.isChecked()) {
                    databaseReference.child("Button").child("Btn2").setValue("0");
                }else{
                    databaseReference.child("Button").child("Btn2").setValue("1");
                }
            }
        });

        swLight.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(swLight.isChecked()) {
                    databaseReference.child("Button").child("Btn3").setValue("0");
                }else{
                    databaseReference.child("Button").child("Btn3").setValue("1");
                }
            }
        });
    }

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

    private void loadData() {
        txtTemp.setText(sensorModel.getSensor_temp() +"°C");
        txtHumi.setText(sensorModel.getSensor_humi() +"%");
        if(buttonModel.getBtn1().equals("0")) {
            swTap.setChecked(true);
        }else if(buttonModel.getBtn1().equals("1")){
            swTap.setChecked(false);
        }

        if(buttonModel.getBtn2().equals("0")) {
            swSpray.setChecked(true);
        }else if(buttonModel.getBtn2().equals("1")){
            swSpray.setChecked(false);
        }

        if(buttonModel.getBtn3().equals("0")) {
            swLight.setChecked(true);
        }else if(buttonModel.getBtn3().equals("1")){
            swLight.setChecked(false);
        }

    }

    private void showData(DataSnapshot dataSnapshot) {
        buttonModel = new ButtonModel(); //Get value of Button0
        buttonModel.setBtn1(dataSnapshot.child("Button").child("Btn1").getValue().toString()); // Get Value Key : ButtonModel , Value of Btn1
        buttonModel.setBtn2(dataSnapshot.child("Button").child("Btn2").getValue().toString()); // Get Value Key : ButtonModel , Value of Btn1
        buttonModel.setBtn3(dataSnapshot.child("Button").child("Btn3").getValue().toString()); // Get Value Key : ButtonModel , Value of Btn1
        difModel = new Dif(); // Get Value Of Dif
        difModel.setDif_humi(dataSnapshot.child("Dif").child("Humi").getValue().toString()); // Get Value Key : ButtonModel , Value of Btn1
        difModel.setDif_temp(dataSnapshot.child("Dif").child("Temp").getValue().toString()); // Get Value Key : ButtonModel , Value of Btn1
        sensorModel = new Sensor(); //Get value Of Sensor
        sensorModel.setSensor_humi(dataSnapshot.child("Sensor").child("Humi").getValue().toString()); // Get Value Key : ButtonModel , Value of Btn1
        sensorModel.setSensor_temp(dataSnapshot.child("Sensor").child("Temp").getValue().toString()); // Get Value Key : ButtonModel , Value of Btn1
        stabilityModel = new Stability(); // Get value Of Stability
        stabilityModel.setStability_humi(dataSnapshot.child("Stability").child("Humi").getValue().toString()); // Get Value Key : ButtonModel , Value of Btn1
        stabilityModel.setStability_temp(dataSnapshot.child("Stability").child("Temp").getValue().toString()); // Get Value Key : ButtonModel , Value of Btn1
    }

    private void readJson(String data) {

    }

    private void findId() {
        swTap = findViewById(R.id.switchtapfaucetwater);
        swSpray = findViewById(R.id.switchmoispray);
        swLight = findViewById(R.id.switchlight);
        imgSetting = findViewById(R.id.imgSetting);
        txtTemp = findViewById(R.id.txtTemp);
        txtHumi = findViewById(R.id.txtHumi);
        txtJson = findViewById(R.id.textJson);
    }


}
