package quizes.networking;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.Arrays;

public class UDPServer {
    public UDPServer() throws IOException {

        try (
                DatagramSocket socket = new DatagramSocket(55556);) {
            byte[] bufOut = new byte[10];
            byte[] bufIn = new byte[10];
            byte[] ping = {112, 105, 110, 103, 0, 0, 0, 0, 0, 0};
            byte[] pong = {112, 111, 110, 103, 0, 0, 0, 0, 0, 0};

            while (true) {
                String inputLine = "";
                DatagramPacket packetin = new DatagramPacket(bufIn, bufIn.length);
                socket.receive(packetin);
                InetAddress adr = packetin.getAddress();
                int portReceived = packetin.getPort();
                System.out.println("port " + portReceived);


                if (Arrays.equals(bufIn, ping)) {
                    System.out.println("Server received ping");
                    DatagramPacket packetOut = new DatagramPacket("pong".getBytes(), "pong".length(), adr, portReceived);
                    socket.send(packetOut);
                } else if (Arrays.equals(bufIn, pong)) {
                    System.out.println("Server received pong");
                    DatagramPacket packetOut = new DatagramPacket("ping".getBytes(), "ping".length(), adr, portReceived);
                    socket.send(packetOut);
                } else {
                    System.out.println("Server received " + bufIn);
                    DatagramPacket packetOut = new DatagramPacket("error".getBytes(), "error".length(), adr, portReceived);
                    socket.send(packetOut);

                }
            }
        }
    }

    public static void main(String[] args) throws IOException {
        UDPServer client = new UDPServer();
    }
}
