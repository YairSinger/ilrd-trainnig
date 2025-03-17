package il.co.ilrd.VM;

import org.junit.BeforeClass;
import org.junit.Test;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.DisplayName;

import java.util.ArrayList;
import java.util.List;

import static org.junit.Assert.*;

public class VMTest {

    static ArrayList<ProductProtoTypes> list = null;
    static ProductProtoTypes product = null;
    static VMDisplay output = null;
    static VM vm = null;

    @BeforeClass
    public static void initVMUtils(){
        list =  new ArrayList<ProductProtoTypes>();
        product = new UserProduct("Apple", 3);
        list.add(product);
        product = new UserProduct("Banana" , 2);
        list.add(product);
        product = new UserProduct("Milk", 7);
        list.add(product);
        product = new UserProduct("Candy", 1);
        output = new UserDisplay();
        vm = new VM (list, output);
    }
    @AfterEach
    public void resetVM(){
       vm.turnOff();
    }

    @Test
    public void turnOn() {
        try{
            Thread.sleep(2000);
        }catch(InterruptedException e){
            System.out.println(e);
        }
        vm.turnOn();
    }

    @Test
    @DisplayName("turnOff")
    public void turnOff() {
        try{
            Thread.sleep(2000);
        }catch(InterruptedException e){
            System.out.println(e);
        }
        vm.selectProduct("Apple");
        vm.insertCoin(6);
        vm.cancel();
        vm.turnOn();
        vm.turnOff();
    }

    @Test
    public void selectProduct() {
        try{
            Thread.sleep(2000);
        }catch(InterruptedException e){
            System.out.println(e);
        }
        System.out.println("\t\t selecting non existing product");
        vm.turnOn();
        vm.selectProduct("applle");
        System.out.println("\t\tselecting valid product");
        vm.selectProduct("Apple");
        System.out.println("\t\tselecting  second product wo cancel");
        vm.selectProduct("Banana");
        System.out.println("\t\tselecting  second product with cancel");
        vm.cancel();
        vm.selectProduct("Banana");
        System.out.println("\t\tselecting  when VM is off");
        vm.turnOff();
    }

    @Test
    public void insertCoin() {
        try{
            Thread.sleep(2000);
        }catch(InterruptedException e){
            System.out.println(e);
        }
        System.out.println("\t\t insert before selection");
        vm.turnOn();
        vm.insertCoin(5);

        System.out.println("\t\t selection and 2 inserts");
        vm.selectProduct("Banana");
        vm.insertCoin(1);
        vm.insertCoin(1);
        System.out.println("\t\t insert after received item wo new selection");
        vm.insertCoin(3);

        System.out.println("\t\t insert more than item price");
        vm.selectProduct("Banana");
        vm.insertCoin(3);
        System.out.println("\t\t insert after selection and turnoff");
        vm.selectProduct("Banana");
        vm.turnOff();
        vm.insertCoin(3);
    }

   @Test
    @DisplayName("timeout")
    public void timeout(){
       vm.turnOn();
       vm.insertCoin(5);
       System.out.println("waiting 10 sec");
       try{
           Thread.sleep(10000);
       }catch(InterruptedException e){
           System.out.println(e);
       }
       vm.selectProduct("Apple");
       vm.insertCoin(5);
    }


}