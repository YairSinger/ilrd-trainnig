package quizes.networking;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.Arrays;


public class UDPClient {

    public UDPClient() throws IOException {
        try(

    BufferedReader inFromCLI = new BufferedReader(
            new InputStreamReader(System.in));
    DatagramSocket socket = new DatagramSocket();) {

            byte[] bufOut;
            byte[] bufIn = new byte[10];
            byte[] ping = {112, 105, 110, 103, 0, 0, 0, 0, 0, 0};
            byte[] pong = {112, 111, 110, 103, 0, 0, 0, 0, 0, 0};

            String inputLine = "";
            while (inputLine != null) {
                inputLine = inFromCLI.readLine();
                bufOut = inputLine.getBytes();
                DatagramPacket packetOut = new DatagramPacket(bufOut, bufOut.length, InetAddress.getByName("localhost"), 9999);
                socket.send(packetOut);

                DatagramPacket packetin = new DatagramPacket(bufIn, bufIn.length);
                socket.receive(packetin);

                String recivedMsg = new String(packetin.getData(), 0,packetin.getLength());
                if (recivedMsg.equals("pong")) {
                    System.out.println("received pong from server");
                } else if (recivedMsg.equals("ping")) {
                    System.out.println("received ping");
                } else {
                    String msg = new String(bufIn);
                    System.out.println(msg);
                    System.out.println("error");
                }
            }
        }
    }

    public static void main(String[] args) throws IOException {
        UDPClient client = new UDPClient();
    }

}
