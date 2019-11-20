package bao.bon.appcontroller;

import android.support.annotation.NonNull;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

import org.w3c.dom.Text;

import bao.bon.appcontroller.Model.Dif;
import bao.bon.appcontroller.Model.Sensor;

public class Stability extends AppCompatActivity {

    EditText edtTemp,edtHumi,edtDifTemp,edtDifHumi;
    TextView btnSave;
    Dif difModel;
    bao.bon.appcontroller.Model.Stability stabilityModel;
    FirebaseDatabase database;
    DatabaseReference databaseReference;



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_stability);
        findId();

        database = FirebaseDatabase.getInstance();
        databaseReference = database.getReference("Controller");

        databaseChange();

        btnSave.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                senData();
                Toast.makeText(Stability.this, "Data Send", Toast.LENGTH_SHORT).show();
                finish();
            }
        });
    }

    private void databaseChange() {
        databaseReference.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
                showData(dataSnapshot);

            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {

            }
        });
    }

    private void senData() {
        databaseReference.child("Dif").child("Humi").setValue(edtDifHumi.getText().toString() );
        databaseReference.child("Dif").child("Temp").setValue(edtDifTemp.getText().toString());
        databaseReference.child("Stability").child("Humi").setValue(edtHumi.getText().toString());
        databaseReference.child("Stability").child("Temp").setValue(edtTemp.getText().toString());
    }

    private void findId() {
        edtTemp = findViewById(R.id.edt_StaTemp);
        edtHumi = findViewById(R.id.edt_StaHumi);
        edtDifHumi = findViewById(R.id.edt_difHumi);
        edtDifTemp = findViewById(R.id.edt_difTemp);
        btnSave = findViewById(R.id.btnSave);
    }

    private void showData(DataSnapshot dataSnapshot) {
        difModel = new Dif(); // Get Value Of Dif
        difModel.setDif_humi(dataSnapshot.child("Dif").child("Humi").getValue().toString()); // Get Value Key : ButtonModel , Value of Btn1
        difModel.setDif_temp(dataSnapshot.child("Dif").child("Temp").getValue().toString()); // Get Value Key : ButtonModel , Value of Btn1
        stabilityModel = new bao.bon.appcontroller.Model.Stability(); // Get value Of Stability
        stabilityModel.setStability_humi(dataSnapshot.child("Stability").child("Humi").getValue().toString()); // Get Value Key : ButtonModel , Value of Btn1
        stabilityModel.setStability_temp(dataSnapshot.child("Stability").child("Temp").getValue().toString()); // Get Value Key

        edtTemp.setText(stabilityModel.getStability_temp());
        edtHumi.setText(stabilityModel.getStability_humi());
        edtDifHumi.setText(difModel.getDif_humi());
        edtDifTemp.setText(difModel.getDif_temp());
    }
}
