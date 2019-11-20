package bao.bon.appcontroller.Model;

public class Dif {
    public String dif_humi;
    public String dif_temp;

    public Dif() {
    }

    public Dif(String dif_humi, String dif_temp) {
        this.dif_humi = dif_humi;
        this.dif_temp = dif_temp;
    }

    public String getDif_humi() {
        return dif_humi;
    }

    public void setDif_humi(String dif_humi) {
        this.dif_humi = dif_humi;
    }

    public String getDif_temp() {
        return dif_temp;
    }

    public void setDif_temp(String dif_temp) {
        this.dif_temp = dif_temp;
    }
}
