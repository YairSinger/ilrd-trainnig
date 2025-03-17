package quizes.io;

import java.io.*;

public class IO {
    public static void main(String[] args) throws IOException {
        FileReader fileReader = new FileReader("/home/yair/git/fs/java_basics/databases_usecases.txt");
//        char[] buffer = new char[200];
//        fileReader.read(buffer ,4 ,150);
//        System.out.println(buffer);
 //       fileReader.close();

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String s = reader.readLine();
        reader.close();

        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        PrintStream ps = new PrintStream(baos);
// IMPORTANT: Save the old System.out!
        PrintStream old = System.out;
// Tell Java to use your special stream
        System.setOut(ps);
        System.out.println(s);
        System.out.flush();
        System.setOut(old);
// Show what happened
        System.out.println("Here: " + baos);



//        StringBuilder stringBuilder = new StringBuilder();
//        char[] buffer = new char[100];
//       reader.read(buffer);
//       reader.close();
//       byte[] byteBuffer = buffer.toString().getBytes();
//       ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
 //      outputStream.write(byteBuffer,90,0);

       // System.out.println(buffer);



    }
}
