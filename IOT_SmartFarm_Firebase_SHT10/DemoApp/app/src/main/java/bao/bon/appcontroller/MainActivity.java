package bao.bon.appcontroller;

import android.content.Intent;
import android.support.annotation.NonNull;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.auth.AuthResult;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;
import com.rengwuxian.materialedittext.MaterialEditText;

public class MainActivity extends AppCompatActivity {

    TextView btnLogin, btnSignUp;
    MaterialEditText edtUser, edtPassword;

    private FirebaseAuth mAuth;
    String TAG = "FirebaseActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        findId();
        //Check Auth Firebase
        mAuth = FirebaseAuth.getInstance();
        btnLogin.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String email = edtUser.getText().toString();
                String password = edtPassword.getText().toString();

                if (email.isEmpty() && password.isEmpty()) {
                    Toast.makeText(MainActivity.this, "Vui lòng nhập Email & Password", Toast.LENGTH_SHORT).show();
                }else {
                    mAuth.signInWithEmailAndPassword(email, password)
                            .addOnCompleteListener(MainActivity.this, new OnCompleteListener<AuthResult>() {
                                @Override
                                public void onComplete(@NonNull Task<AuthResult> task) {
                                    if (task.isSuccessful()) {
                                        FirebaseUser user = mAuth.getCurrentUser();
//                                    updateUI(user);
                                        Toast.makeText(MainActivity.this, "Login Sucessful", Toast.LENGTH_SHORT).show();
                                        Intent intentHome = new Intent(MainActivity.this,HomeAcitivity.class);
                                        startActivity(intentHome);
                                    } else {
                                        Toast.makeText(MainActivity.this, "Login Faild !!!", Toast.LENGTH_SHORT).show();
//                                    updateUI(null);
                                    }
                                }
                            });
                }
            }
        });
        btnSignUp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent signUp_Intent = new Intent(MainActivity.this,SignUp.class);
                startActivity(signUp_Intent);
            }
        });
    }

    private void findId() {
        btnLogin = findViewById(R.id.btnLogin);
        btnSignUp = findViewById(R.id.btnSignUp);
        edtUser =   findViewById(R.id.edtUser);
        edtPassword = findViewById(R.id.edtPassword);
    }

    @Override
    protected void onStart() {
        super.onStart();
        FirebaseUser user = mAuth.getCurrentUser();
//        updateUI(user);
    }

}
