public class Ex1 {

    int instanceVar = 0;
    static int classField1 = 2;
    {
        System.out.println("instance block before constructor super");
    }
    static {
        System.out.println("static block before constructor super");
    }
    public Ex1()
    {
        System.out.println("Ex1 constructor super");
        System.out.println("Ex1 super classField1 is: " + classField1);
        System.out.println("Ex1 super instanceVar is: " + instanceVar);
    }

    {
        System.out.println("instance block after constructor super");
    }

    static {
        System.out.println("static block before constructor super");
    }
}

 class Ex1Subclass extends Ex1 {
    public static void main(String[] args) {

        System.out.println("Hello world! subclass");
        Ex1Subclass ex1Subclass = new Ex1Subclass();
    }
    int instanceVar = 0;
    static int classField1 = 2;
    {
        System.out.println("instance block before constructor sub");
    }
    static {
        System.out.println("static block before constructor sub");
    }
    public Ex1Subclass()
    {
        System.out.println("Ex1 constructor sub");
        System.out.println("Ex1 sub classField1 is: " + classField1);
        System.out.println("Ex1 sub instanceVar is: " + instanceVar);
    }

    {
        System.out.println("instance block after constructor sub");
    }

    static {
        System.out.println("static block before constructor sub");
    }
}