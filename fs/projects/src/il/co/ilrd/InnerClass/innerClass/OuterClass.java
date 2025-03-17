package il.co.ilrd.InnerClass.innerClass;

public class OuterClass {
    private  int x;
    public static void main(String[] args) {
        OuterClass objOut = new OuterClass(5);
        InnerClass objInn = new InnerClass(objOut);

        objInn.printHello();

    }

    public OuterClass(int x) {
        this.x = x;
    }

    public static void printOuter(){
        System.out.println("printOuter");

    }
    public static class InnerClass{
        private OuterClass outer;

        public InnerClass(OuterClass outer) {
            this.outer = outer;
        }

        public void printHello(){
            OuterClass.printOuter();

            System.out.println("Hello");
            System.out.println("x = " + outer.x);
        }
    }

}

interface Age {
    int x = 21;
    void getAge();
}

// Main class
class AnonymousDemo {

    // Main driver method
    public static void main(String[] args)
    {
        Age oj1 = new Age() {
            @Override public void getAge()
            {
                System.out.print("Anonymous num age " + x);
            }
        };

        oj1.getAge();
    }
}

