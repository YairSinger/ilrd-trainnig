import java.util.Arrays;

public class ClassInfo {
    public static void main(String[] args) throws ClassNotFoundException {
        String classStr = args[0];

        Class<?> curClass = Class.forName(classStr);

        System.out.println("Class name is: " + curClass.getName());
        System.out.println("Class interfaces are : " + Arrays.toString(curClass.getInterfaces()));
        System.out.println("is interface : " + curClass.isInterface());
        System.out.println("Superclass is: " + curClass.getSuperclass());

    }
}
