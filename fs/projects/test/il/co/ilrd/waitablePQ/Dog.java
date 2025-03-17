package il.co.ilrd.waitablePQ;

import java.util.Comparator;

public class Dog implements Comparator<Dog> {
    private int age = 5;

    public int getAge() {
        return age;
    }

    public Dog(int age) {
        this.age = age;
    }

    @Override
    public int compare(Dog o, Dog t1) {
        return ((Dog)o).age - ((Dog)t1).age;
    }


}
