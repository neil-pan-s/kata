package demo.org.ichanging.nfc.util;

import android.content.Context;
import android.nfc.Tag;
import android.nfc.tech.IsoDep;
import android.util.Log;
import android.widget.Toast;

import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.text.SimpleDateFormat;
import java.util.Arrays;
import java.util.Date;

/**
 * Created by ChangingP on 2016/4/15.
 */
public class ApduUtil {

    private static final String TAG = "ApduUtil";

    //PPSE for Bank Card
    private static final String SELECT_APDU_PPSE = "2PAY.SYS.DDF01";

    // AID for Bank Card
    private static final String SELECT_APDU_AID = "A000000333010101";

    // "OK" status word sent in response to APDU command (0x9000)
    private static final byte[] APDU_OK_SW = {(byte) 0x90, (byte) 0x00};

    private static final int APDU_TIMEOUT = 3600;

    private IsoDep mIsoDep = null;

    public interface ApduCmdCallback {
        public void onCmdReceived(String response);
    }

    /**
     * Callback when a new tag is discovered by the system.
     *
     * <p>Communication with the card should take place here.
     *
     * @param tag Discovered tag
     */
    public void onTagDiscovered(Tag tag){

        Log.i(TAG, "======= Discovered Tag:" + tag + "==========");

        // Android's Host-based Card Emulation (HCE) feature implements the ISO-DEP (ISO 14443-4)
        // protocol.
        //
        // In order to communicate with a device using HCE, the discovered tag should be processed
        // using the IsoDep class.

        mIsoDep = IsoDep.get(tag);

        // Connect to the remote NFC device
        try {
            mIsoDep.connect();
        } catch (IOException e) {
            e.printStackTrace();
        }

        mIsoDep.setTimeout(APDU_TIMEOUT);

    }


    public void onClose()
    {
        try {
            if(mIsoDep != null) {
                mIsoDep.close();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    //QPBOC Trans
    public void onReadCard(Context context)
    {
        byte[] status = new byte[2];
        byte[] resp = null;
        byte[] cmd = null;

        cmd = BuildSelectApdu(ByteArrayToHexString(SELECT_APDU_PPSE.getBytes()));
        resp = ApduComm(cmd, status);
        Log.i(TAG, "======================= Select PPSE - Return [" + String.format("%02X%02x",status[0],status[1]) +"]======================");

        cmd = BuildSelectApdu(SELECT_APDU_AID);
        resp = ApduComm(cmd, status);
        Log.i(TAG, "======================= Select AID - Return [" + String.format("%02X%02x",status[0],status[1]) +"]======================");

        cmd = BuildGPOApdu("000000000001", "440945C0", 00);
        resp = ApduComm(cmd, status);
        Log.i(TAG, "======================= GPO - Return [" + String.format("%02X%02x",status[0],status[1]) +"]======================");

        //取电子现金余额
        cmd = BuildGetDataApdu("9F79");
        resp = ApduComm(cmd, status);
        Log.i(TAG, "======================= GET 9F79 - Return [" + String.format("%02X%02x",status[0],status[1]) +"]======================");
        Log.i(TAG, ByteArrayToHexString(resp));

        //GPO 获取应用文件定位器（AFL）
        // 10 05 07 01
        // 18 01 02 00
        cmd = BuildReadRecordApdu(0x10,0x05);
        resp = ApduComm(cmd, status);
        Log.i(TAG, "======================= Read Record SFI = 10 Index = 0x05 - Return [" + String.format("%02X%02x",status[0],status[1]) +"]======================");

        cmd = BuildReadRecordApdu(0x10, 0x06);
        resp = ApduComm(cmd, status);
        Log.i(TAG, "======================= Read Record SFI = 10 Index = 0x06 - Return [" + String.format("%02X%02x",status[0],status[1]) +"]======================");

        cmd = BuildReadRecordApdu(0x10, 0x07);
        resp = ApduComm(cmd, status);
        Log.i(TAG, "======================= Read Record SFI = 10 Index = 0x07 - Return [" + String.format("%02X%02x",status[0],status[1]) +"]======================");

        cmd = BuildReadRecordApdu(0x18, 0x01);
        resp = ApduComm(cmd, status);
        Log.i(TAG, "======================= Read Record SFI = 18 Index = 0x01 - Return [" + String.format("%02X%02x",status[0],status[1]) +"]======================");

        cmd = BuildReadRecordApdu(0x18, 0x02);
        resp = ApduComm(cmd, status);
        Log.i(TAG, "======================= Read Record SFI = 18 Index = 0x02 - Return [" + String.format("%02X%02x",status[0],status[1]) +"]======================");

        //取电子现金余额
        cmd = BuildGetDataApdu("9F79");
        resp = ApduComm(cmd, status);
        Log.i(TAG, "======================= GET 9F79 - Return [" + String.format("%02X%02x",status[0],status[1]) +"]======================");
        Log.i(TAG, ByteArrayToHexString(resp));

        Toast.makeText(context,"电子现金余额:" + ByteArrayToHexString(resp).substring(6),Toast.LENGTH_LONG).show();
    }

    /**
     * Apdu Communication
     *
     * Communication with the card should take place here.
     *
     * @param cmd  Apdu Command to Card
     * @param sw   2 byte status word
     */
    public byte[] ApduComm(byte[] cmd,byte[] sw)
    {
        if (mIsoDep != null)
        {
            try
            {

                Log.i(TAG, "ApduSend: [" + ByteArrayToHexString(cmd) + "]");

                byte[] result = mIsoDep.transceive(cmd);

                Log.i(TAG, "ApduRecv: [" + ByteArrayToHexString(result) + "]");

                // If AID is successfully selected, 0x9000 is returned as the status word (last 2
                // bytes of the result) by convention. Everything before the status word is
                // optional payload, which is used here to hold the account number.
                int resultLength = result.length;

                sw[0] = result[resultLength - 2];
                sw[1] = result[resultLength - 1];

                byte[] payload = Arrays.copyOf(result, resultLength - 2);

                if (Arrays.equals(APDU_OK_SW, sw)) {

                    return payload;

                }


            } catch (IOException e) {
                Log.e(TAG, "Error Communicating With Card: " + e.toString());
            }
        }
        return null;
    }


    /**
     * Build APDU for SELECT AID command. This command indicates which service a reader is
     * interested in communicating with. See ISO 7816-4.
     *
     * @param aid Application ID (AID) to select
     * @return APDU for SELECT AID/PSE/PPSE command
     */
    public static byte[] BuildSelectApdu(String aid) {
        // Format: [CLASS | INSTRUCTION | PARAMETER 1 | PARAMETER 2 | LENGTH | DATA]
        return HexStringToByteArray("00A40400" + String.format("%02X", aid.length() / 2) + aid);
    }


    /**
     * Build APDU for READ_RECORD command. See ISO 7816-4.
     *
     * @return APDU for READ_RECORD command
     */
    public static byte[] BuildReadRecordApdu(int sfi,int index) {
        // Format: [CLASS | INSTRUCTION | PARAMETER 1 | PARAMETER 2 | LENGTH | DATA]

        return HexStringToByteArray(
                "00B2" +
                String.format("%02X",index) +         //P1 记录号
                String.format("%02X",sfi | 0x04) +    //P2 SFI号
                "00"
        );
    }

    /**
     * Build APDU for GPO command. See ISO 7816-4.
     *
     * @return APDU for GPO command
     */
    public static byte[] BuildGPOApdu(String amt,String random,int transType) {
        // Format: [CLASS | INSTRUCTION | PARAMETER 1 | PARAMETER 2 | LENGTH | DATA]

        String yyMMdd =new SimpleDateFormat("yyMMdd").format(new Date());
        String trans = String.format("%02d",transType);

        return HexStringToByteArray(
                "80A8000023" +
                "8321" +        // PDOL标签 长度
                "36000080" +    //9F66 04  终端交易属性
                amt +           //9F02 06  授权金额 eg.000000000001
                "000000000000"+ //9F03 06  其他金额
                "0156" +        //9F1A 02 终端国家代码
                "0000000000" +  //95 05 终端验证结果 TVR
                "0156" +        //5F2A 02 交易货币代码
                yyMMdd +        //9A 03 交易日期
                trans +	        //9C 01 交易类型 eg.00
                random +        //9F37 04 终端不可预知数 eg.440945C0
                "00"            //R-APDU期待长度
        );
    }

    /**
     * Build APDU for GET_DATA command. This command indicates which service a reader is
     * interested in communicating with. See ISO 7816-4.
     *
     * @param tag Emv/PBOC Tag
     * @return APDU for command
     */
    public static byte[] BuildGetDataApdu(String tag) {
        // Format: [CLASS | INSTRUCTION | PARAMETER 1 | PARAMETER 2 | LENGTH | DATA]
        return HexStringToByteArray("80CA" + tag + "00");
    }


    /**
     * Utility method to convert a byte array to a hexadecimal string.
     *
     * @param bytes Bytes to convert
     * @return String, containing hexadecimal representation.
     */
    public static String ByteArrayToHexString(byte[] bytes) {
        final char[] hexArray = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
        char[] hexChars = new char[bytes.length * 2]; // Each byte has two hex characters (nibbles)
        int v;
        for (int j = 0; j < bytes.length; j++) {
            v = bytes[j] & 0xFF; // Cast bytes[j] to int, treating as unsigned value
            hexChars[j * 2] = hexArray[v >>> 4]; // Select hex character from upper nibble
            hexChars[j * 2 + 1] = hexArray[v & 0x0F]; // Select hex character from lower nibble
        }
        return new String(hexChars);
    }

    /**
     * Utility method to convert a hexadecimal string to a byte string.
     *
     * <p>Behavior with input strings containing non-hexadecimal characters is undefined.
     *
     * @param s String containing hexadecimal characters to convert
     * @return Byte array generated from input
     * @throws java.lang.IllegalArgumentException if input length is incorrect
     */
    public static byte[] HexStringToByteArray(String s) throws IllegalArgumentException {
        int len = s.length();
        if (len % 2 == 1) {
            throw new IllegalArgumentException("Hex string must have even number of characters");
        }
        byte[] data = new byte[len / 2]; // Allocate 1 byte per 2 hex characters
        for (int i = 0; i < len; i += 2) {
            // Convert each character into a integer (base-16), then bit-shift into place
            data[i / 2] = (byte) ((Character.digit(s.charAt(i), 16) << 4)
                    + Character.digit(s.charAt(i+1), 16));
        }
        return data;
    }


}
