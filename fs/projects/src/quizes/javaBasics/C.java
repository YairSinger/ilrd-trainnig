//package quizes.javaBasics;
//
//class C {
//    private String s = "123";
//    class C1 {
//        private C c = new C();
//        private static String str = "hello world";
//        private void foo () {
//            s = "456";
//            System.out.println(str);
//        }
//    }
//    class C2 {
//        private C1 c1 = new C1();
//        private void foo2 () {
//            c1.c.s = "abc";
//        }
//    }
//
//    private static class C3 {
//        private int i = 3;
//        static void foo () {
//            this.i = 5;
//        }
//    }
//
//    void foo2 () {
//        static String s1 = "hello";
//    }
//}
//
//public class Main {
//    public static void main(String[] args) {
//        C.C2  c2 = new C().new C2();
//        C.C3  c3 = new C.C3();
//    }
//}
