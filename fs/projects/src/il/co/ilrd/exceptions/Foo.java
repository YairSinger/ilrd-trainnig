package il.co.ilrd.exceptions;

import java.io.IOException;

public class Foo {
    public static void func1() throws IOException{
        try {

            throw new MyException1();


        }
        catch (Exception e) {
//            NullPointerException erro = new NullPointerException();
//            e.initCause(erro);
            throw e;
        }
        finally {
            throw new MyException2();

        }
    }
    public static void  func2() throws IOException {
        throw new IOException("ygyug");
    }
    public static void  func3() throws MyException1 {
        throw new MyException1();
    }
    public static void  func4() throws MyException2 {
        throw new MyException2();
    }

    public static void main(String[] args) throws Exception {
//       byte[] arr = new byte[100];
//       arr[101] = 'c';
        ToDelete ref = new ToDelete();

        try {
            func1();

        }
        catch (Exception e){
            System.out.println(e);
        }



//        try {
//            Foo.func2();
//        }
//        catch (Exception e){
//            System.out.println("catch " + e);
//        }
//
//        try {
//            Foo.func3();
//        }
//        catch (Exception e){
//            System.out.println("catch " + e);
//        }
//
//        try {
//            Foo.func4();
//        }
//        catch (Exception e){
//            System.out.println(e);
//        }
    }
}
