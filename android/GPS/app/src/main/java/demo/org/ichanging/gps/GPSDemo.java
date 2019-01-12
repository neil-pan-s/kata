package demo.org.ichanging.gps;

import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.location.Criteria;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.location.LocationProvider;
import android.os.Build;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.List;
import java.util.jar.Manifest;

public class GPSDemo extends AppCompatActivity {

    Toast toast;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_gps_demo);

        final LocationManager lm = (LocationManager) getSystemService(Context.LOCATION_SERVICE);
        List<String> allProviders = lm.getAllProviders();

        String all = "";
        for (String name:allProviders)
        {
            all += "\nName: " + name;
        }

        toast = Toast.makeText(this, all, Toast.LENGTH_SHORT);
        toast.show();

        LocationProvider gps = lm.getProvider(LocationManager.GPS_PROVIDER);

//        //创建一个Location Provider 过滤条件
//        Criteria cri = new Criteria();
//        //要求免费
//        cri.setCostAllowed(false);
//        //能提供高度信息
//        cri.setAltitudeRequired(true);
//        //能提供方向信息
//        cri.setBearingRequired(true);
//
//        List<String> criProviders = lm.getProviders(cri,false);


        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M)
        {
            if (GPSDemo.this.checkSelfPermission(android.Manifest.permission.ACCESS_FINE_LOCATION) == PackageManager.PERMISSION_GRANTED)
            {

                // ...
            } else {
                return;
            }
        }

        //取最后一次定位信息
        Location location = lm.getLastKnownLocation(LocationManager.GPS_PROVIDER);
        printLocation(location);

        //从GPS获取信息 3秒或移动8米+ 触发更新
        lm.requestLocationUpdates(LocationManager.GPS_PROVIDER, 3000, 8, new LocationListener() {
            @Override
            public void onLocationChanged(Location location) {
                printLocation(location);
            }

            @Override
            public void onStatusChanged(String provider, int status, Bundle extras) {

            }

            @Override
            public void onProviderEnabled(String provider) {

                toast.setText("GPS TurnOn");
                toast.show();
            }

            @Override
            public void onProviderDisabled(String provider) {
                toast.setText("GPS TurnOff");
                toast.show();
            }
        });


        //临近警告
        double longitude = 113.9260140000;
        double latitude = 22.7370520000;
        //半径 5公里
        float radius = 5000;

        Intent intent = new Intent(this,ProximityAlertReciever.class);
        PendingIntent pi = PendingIntent.getBroadcast(this,-1,intent,0);
        lm.addProximityAlert(latitude,longitude,radius,-1,pi);

    }

    private void printLocation(Location location)
    {
        if(location != null) {
            StringBuilder sb = new StringBuilder();
            sb.append("经度:" + location.getLongitude());
            sb.append("纬度:" + location.getLatitude());
            sb.append("高度:" + location.getAltitude());
            sb.append("速度:" + location.getSpeed());
            sb.append("方向:" + location.getBearing());

            System.out.println("==========" + sb.toString() + "===========");

            toast.setText(sb.toString());
            toast.show();

        }else{
            System.out.println("Error: Location is Null");
        }
    }




}
