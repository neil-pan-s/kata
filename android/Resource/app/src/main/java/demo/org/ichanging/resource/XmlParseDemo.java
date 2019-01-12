package demo.org.ichanging.resource;

import android.content.res.XmlResourceParser;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.Toast;

import org.xmlpull.v1.XmlPullParserException;

import java.io.IOException;

public class XmlParseDemo extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_xml_parse_demo);

        XmlResourceParser xmlResourceParser = getResources().getXml(R.xml.books);

        try
        {
            StringBuilder sb = new StringBuilder("");
            while(xmlResourceParser.getEventType() != XmlResourceParser.END_DOCUMENT)
            {
                if(xmlResourceParser.getEventType() == XmlResourceParser.START_TAG)
                {
                        String tagName = xmlResourceParser.getName();
                        if(tagName.equals("book"))
                        {
                            //根据属性名获取属性值
                            String bookPrice = xmlResourceParser.getAttributeValue(null,"price");
                            sb.append("Price: " + bookPrice);

                            //根据索引获取属性值
                            String bookPDate = xmlResourceParser.getAttributeValue(1);
                            sb.append("Publish Date: " + bookPDate);
                            sb.append("Book Name: " + xmlResourceParser.nextText() + "\n");
                        }
                }
                xmlResourceParser.next();
            }

            Toast.makeText(this,sb,Toast.LENGTH_LONG).show();

        } catch (XmlPullParserException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }


    }
}
