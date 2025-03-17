package quizes.networking;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;


public class TCPServer {


    public static void main(String[] args) throws IOException {
        int portNumber = Integer.parseInt(args[0]);

        try (
                ServerSocket serverSocket = new ServerSocket(portNumber);
                Socket clientSocket = serverSocket.accept();
                PrintWriter out =
                        new PrintWriter(clientSocket.getOutputStream(), true);
                BufferedReader in = new BufferedReader(
                        new InputStreamReader(clientSocket.getInputStream()));
        ) {
            while (true) {
                String inputLine = in.readLine();
                if (inputLine.equals("ping")) {
                    System.out.println("Server received ping");
                    out.println("pong");
                } else if (inputLine.equals("pong")) {
                    System.out.println("Server received pong");
                    out.println("ping");
                } else {
                    System.out.println("Server received error");
                    out.println("error");
                }
            }

        }
    }
}




