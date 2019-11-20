package bao.bon.appcontroller.Model;

public class Stability {
    public String stability_temp;
    public String stability_humi;

    public Stability() {
    }

    public Stability(String stability_temp, String stability_humi) {
        this.stability_temp = stability_temp;
        this.stability_humi = stability_humi;
    }

    public String getStability_temp() {
        return stability_temp;
    }

    public void setStability_temp(String stability_temp) {
        this.stability_temp = stability_temp;
    }

    public String getStability_humi() {
        return stability_humi;
    }

    public void setStability_humi(String stability_humi) {
        this.stability_humi = stability_humi;
    }
}
