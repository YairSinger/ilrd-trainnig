//package quizes.quiz7;
//
//import java.io.IOException;
//
//class Base {
//    private int member1 = 1;
//    private int member2 = 2;
//    public Base()  {
//        System.out.println("Base Ctor");
//         print();
//    }
//    public void print() throws IOException {
//        System.out.println(member1 + " "+ member2);
//        throw new IOException();
//    }
//}
//
//class Derived extends Base {
//    private int member3 = 3;
//    private int member4 = 4;
//    public Derived() {
//        System.out.println("Derived Ctor");
//        print();
//    }
//    @Override
//    public void print() {
//        System.out.println(member3 + " " + member4);
//
//    }
//}
//
// class Test {
//    public static void main(String[] args){
//        Derived d = new Derived();
//    }
//}