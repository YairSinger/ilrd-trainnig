package quizes.networking;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class TCPClient {
    public static void main(String[] args) throws IOException {
        String hostName = "localhost";
        int portNumber = 5454;

        try (
                Socket kkSocket = new Socket(hostName, portNumber);
                PrintWriter outToSocket = new PrintWriter(kkSocket.getOutputStream(), true);
                BufferedReader inFromSocket = new BufferedReader(
                        new InputStreamReader(kkSocket.getInputStream()));
                BufferedReader inFromCLI = new BufferedReader(
                        new InputStreamReader(System.in));
        ){
            String inputLine = "";
            while (inputLine != null) {

               inputLine = inFromCLI.readLine();
                outToSocket.println(inputLine);
                System.out.println(inFromSocket.readLine());
            }
        }

    }
}
