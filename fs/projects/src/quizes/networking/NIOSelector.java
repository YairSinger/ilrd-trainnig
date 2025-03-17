package quizes.networking;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.*;
import java.nio.ByteBuffer;
import java.nio.channels.*;
import java.util.Iterator;
import java.util.Set;



public class NIOSelector {


    private static final String POISON_PILL = "POISON_PILL";
    private Selector selector;
    private ByteBuffer buffer;

    private ServerSocketChannel serverSocketTCP;


    private void initSelector() throws IOException {
        selector = Selector.open();
        //TCP channel
        serverSocketTCP = ServerSocketChannel.open();
        serverSocketTCP.bind(new InetSocketAddress("localhost", 5454));
        serverSocketTCP.configureBlocking(false);
        serverSocketTCP.register(selector, SelectionKey.OP_ACCEPT);

        //UDP Channel
        DatagramChannel channel = DatagramChannel.open();
        channel.socket().bind(new InetSocketAddress(9999));
        channel.configureBlocking(false);
        channel.register(selector,SelectionKey.OP_READ);

        buffer = ByteBuffer.allocate(256);

    }

    public void runSelector() throws IOException {
        BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
        boolean isRunning = true;
        while (isRunning) {

            if(selector.select(3000) == 0 ){
                if(input.ready() && input.readLine().trim().equals("exit")){
                    isRunning = false;
                }else {
                    System.out.println("selector is working");
                }
                continue;
            }

            Set<SelectionKey> selectedKeys = selector.selectedKeys();
            Iterator<SelectionKey> iter = selectedKeys.iterator();
            while (iter.hasNext()) {

                SelectionKey key = iter.next();

                if (key.isAcceptable()) {
                    register(selector, serverSocketTCP);
                }

                if (key.isReadable()) {

                    if(key.channel() instanceof DatagramChannel){
                        answerUDP(buffer,key);
                    }else {
                        answerTCP(buffer, key);
                    }
                }

                iter.remove();
            }
        }
        selector.close();
        return;
    }

    public NIOSelector() throws IOException {
        initSelector();
        runSelector();
    }

    public static void main(String[] args) throws IOException {
       NIOSelector selector1 = new NIOSelector();

    }

    private static void answerTCP(ByteBuffer buffer, SelectionKey key)
            throws IOException {

        SocketChannel client = (SocketChannel) key.channel();
        int r = client.read(buffer);
        if (r == -1 || new String(buffer.array()).trim().equals(POISON_PILL)) {
            client.close();
            buffer.clear();
            System.out.println("Not accepting client messages anymore");
        }
        else {
            String msg = new String(buffer.array());
            if (msg.substring(0,4).equals("ping")){
                buffer.clear();
                buffer.put("pong\n".getBytes());

            } else if (msg.substring(0,4).equals("pong")) {
                buffer.clear();
                buffer.put("ping\n".getBytes());

            }else {
                buffer.clear();
                buffer.put("error\n".getBytes());

            }
            buffer.flip();
            client.write(buffer);
            buffer.clear();

        }
    }

    private static void answerUDP(ByteBuffer buffer, SelectionKey key)
            throws IOException {

     DatagramChannel client = (DatagramChannel) key.channel();
     SocketAddress address = client.receive(buffer);
     String msg = new String(buffer.array());
     if (msg.substring(0,4).equals("ping")){
         buffer.clear();
         buffer.put("pong".getBytes());
     } else if (msg.substring(0,4).equals("pong")) {
         buffer.clear();
         buffer.put("ping".getBytes());
     }
     else {
         buffer.clear();
         buffer.put("error".getBytes());
     }
     buffer.flip();
    client.send(buffer,address);
    buffer.clear();
    }

    private static void register(Selector selector, ServerSocketChannel serverSocket)
            throws IOException {

        SocketChannel client = serverSocket.accept();
        client.configureBlocking(false);
        client.register(selector, SelectionKey.OP_READ);
    }

    public static Process start() throws IOException, InterruptedException {
        String javaHome = System.getProperty("java.home");
        String javaBin = javaHome + File.separator + "bin" + File.separator + "java";
        String classpath = System.getProperty("java.class.path");
        String className = EchoServer.class.getCanonicalName();

        ProcessBuilder builder = new ProcessBuilder(javaBin, "-cp", classpath, className);

        return builder.start();
    }

}

