package il.co.ilrd.genericFactory;

import org.junit.Test;
import org.junit.jupiter.api.DisplayName;

import java.util.function.Function;

import static org.junit.Assert.*;

class Animal implements Function<Integer, Animal> {
    Integer numOfLegs = 2;

    public Animal(Integer num) {
        this.numOfLegs = num;
    }
    public Animal() {

    }

    public Integer getNumOfLegs() {
        return numOfLegs;
    }

    @Override
    public Animal apply(Integer num) {
        return new Animal(num);
    }
}

class Dog extends Animal implements Function<Integer, Animal> {
    public Integer age;

    public Dog(Integer age) {
        this.age = age;
    }

    @Override
    public Animal apply(Integer num) {
        return (Animal) new Dog(num);
    }

    public static Animal printHellow(Integer num){

        for (int i = 0; i < num; i++) {
            System.out.println("hellow");

        }
        return null;
    }
    public Animal create(){
        return new Dog(5);
    }
}

class Cat extends Animal implements Function<Integer, Animal> {
    private long numOfLifes = 9;

    public Cat(long numOfLifes) {
        this.numOfLifes = numOfLifes;
    }

    @Override
    public Animal apply(Integer num) {
        return (Animal) new Cat(num);
    }



}


public class GenericFactoryTest {




    @Test
    @DisplayName("with object creation")
    public void testWithObjCreation(){

        GenericFactory<String,Animal,Integer> factory = new GenericFactory<>();
        Animal animal = new Animal();
        Dog dog = new Dog(8);
        factory.registerCreator("Animal",animal);
        factory.registerCreator("Dog",dog);

        Animal dogFromFactory = factory.createObject("Dog", 5);
        assertEquals(2,(dogFromFactory.getNumOfLegs().intValue()));
        assertEquals(5,((Dog)dogFromFactory).age.intValue());
        Animal animalFromFactory = factory.createObject("Animal", 4);
        assertEquals(4, animalFromFactory.getNumOfLegs().intValue());



    }


    @Test
    @DisplayName("with lambda")
    public void testWithLambda(){
        GenericFactory<String,Animal,Integer> factory = new GenericFactory<>();

        factory.registerCreator("Animal",(a)->new Animal(a));
        factory.registerCreator("Dog",(a)-> new Dog(a));

        Animal dogFromFactory = factory.createObject("Dog", 5);
        assertEquals(2,(dogFromFactory.getNumOfLegs().intValue()));
        assertEquals(5,((Dog)dogFromFactory).age.intValue());
        Animal animalFromFactory = factory.createObject("Animal", 4);
        assertEquals(4, animalFromFactory.getNumOfLegs().intValue());



    }

    @Test
    @DisplayName("with syntheticSuger")
    public void syntheticSuger(){
        GenericFactory<String,Animal,Integer> factory = new GenericFactory<>();

        factory.registerCreator("Animal",Animal::new);
        //factory.registerCreator("Animal",null);
        factory.registerCreator("Dog", Dog::new);

        Animal dogFromFactory = factory.createObject("Dog", 5);
        assertEquals(2,(dogFromFactory.getNumOfLegs().intValue()));
        assertEquals(5,((Dog)dogFromFactory).age.intValue());
        Animal animalFromFactory = factory.createObject("Animal", 4);
        assertEquals(4, animalFromFactory.getNumOfLegs().intValue());



    }

    @Test
    @DisplayName("AnonymousFunction")
    public void AnonymousFunction(){
        GenericFactory<String,Animal,Integer> factory = new GenericFactory<>();
        Function<Integer,Dog> dogCtr =(a) -> new Dog(a);
        Function<Integer,Cat> catCtr = (a) ->new Cat(a);
        factory.registerCreator("Dog", dogCtr);
        factory.registerCreator("Cat", dogCtr);

        Animal dogFromFactory = factory.createObject("Dog", 5);
        Animal catFromFactory = factory.createObject("Cat", 5);

        assertEquals(2,(dogFromFactory.getNumOfLegs().intValue()));
        assertEquals(5,((Dog)dogFromFactory).age.intValue());

    }

    @Test
    @DisplayName("staticMethod")
    public void staticMethod(){
        GenericFactory<String,Animal,Integer> factory = new GenericFactory<>();

        factory.registerCreator("Animal",Animal::new);
        factory.registerCreator("Dog", (Integer) -> Dog.printHellow(Integer));
        Animal dogFromFactory = factory.createObject("Dog", 5);
       assertNull(dogFromFactory);

    }

    @Test
    @DisplayName("syntheticSugerStaticMethod")
    public void syntheticSugerStaticMethod(){
        GenericFactory<String,Animal,Integer> factory = new GenericFactory<>();

        factory.registerCreator("Dog", Dog::new);
        Animal dogFromFactory = factory.createObject("Dog", 5);
        assertNull(dogFromFactory);

    }



    @Test
    @DisplayName("woInstance")
    public void woInstance(){
        GenericFactory<String,Animal,Integer> factory = new GenericFactory<>();
        Function<Animal,Animal> func = new Function<Animal, Animal>() {
            @Override
            public Animal apply(Animal animal) {
                return animal.apply(new Integer(3));
            }
        };

        factory.registerCreator(Dog.class.getName(),(func.compose(Dog::new)));
        Animal dogFromFactory = factory.createObject(Dog.class.getName());
        System.out.println(dogFromFactory);

   }

}