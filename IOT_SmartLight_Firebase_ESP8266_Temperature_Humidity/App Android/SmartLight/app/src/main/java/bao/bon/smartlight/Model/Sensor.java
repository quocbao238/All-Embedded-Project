package bao.bon.smartlight.Model;

public class Sensor {
    String sensor_temp;
    String sensor_humi;


    public Sensor(String sensor_temp) {
        this.sensor_temp = sensor_temp;
    }

    public Sensor() {
    }

    public Sensor(String sensor_temp, String sensor_humi) {
        this.sensor_temp = sensor_temp;
        this.sensor_humi = sensor_humi;
    }

    public String getSensor_temp() {
        return sensor_temp;
    }

    public void setSensor_temp(String sensor_temp) {
        this.sensor_temp = sensor_temp;
    }

    public String getSensor_humi() {
        return sensor_humi;
    }

    public void setSensor_humi(String sensor_humi) {
        this.sensor_humi = sensor_humi;
    }
}
