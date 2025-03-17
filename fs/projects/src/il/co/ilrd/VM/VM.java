//Project: Vending Machine
//Group: ilrd_fs149-150
//Writer: Yair Singer
//Reviewer: Yuval Nemrower
//Date: 8.01.2024
//Status: Approved


package il.co.ilrd.VM;

import java.sql.Timestamp;
import java.util.ArrayList;

public class VM {
    private VmState state;
    private double coinBalance;
    private double insertedCoin;
    private String productName;
    private ArrayList<ProductProtoTypes> list;
    private ProductProtoTypes selectedProduct;
    private  VMDisplay display;
    private boolean timeOutRunningFlag;

    private Timestamp lastInputTime;
    private VMTimeoutThread vmTimeoutThread;

    public VM(ArrayList<ProductProtoTypes> list, VMDisplay d){
        this.list = list;
        display = d;
        coinBalance = 0;
        insertedCoin = 0;
        productName = null;
        selectedProduct = null;
        state  = VmState.OFF;
        lastInputTime = new Timestamp(System.currentTimeMillis());
        timeOutRunningFlag = false;
    }
    public void turnOn(){
        lastInputTime.setTime(System.currentTimeMillis());
        timeOutRunningFlag = true;
        state.turnOn(this);
    }
    public void turnOff(){
        timeOutRunningFlag = false;
        lastInputTime.setTime(System.currentTimeMillis());
        state.turnOff(this);
    }
    public void selectProduct(String productName){

        this.productName = productName;
        lastInputTime.setTime(System.currentTimeMillis());
        state.selectProduct(this);
    }
    public void insertCoin(double coin){
       insertedCoin = coin;
        lastInputTime.setTime(System.currentTimeMillis());
       state.insertCoin(this);
    }
    public void cancel(){
       lastInputTime.setTime(System.currentTimeMillis());
       state.cancel(this);
    }

    public enum VmState{
        OFF{
            @Override
            public void turnOn(VM vm){
                vm.state = WAIT4SELECTION;
                vm.vmTimeoutThread = vm.new VMTimeoutThread();
                vm.vmTimeoutThread.start();
                vm.display.output("Please select item");
            }
            @Override
            public void  selectProduct(VM vm){}

            @Override
            public void insertCoin(VM vm){}
            @Override
            public void cancel(VM vm){

            }
        },
        WAIT4SELECTION{
            @Override
            public void turnOn(VM vm){
                vm.display.output("Please select item");
            }
            @Override
            public void selectProduct(VM vm){

                for (ProductProtoTypes product : vm.list) {
                    if(product.getName().equals(vm.productName)){

                        vm.selectedProduct = product;
                        vm.display.output(vm.productName + " was selected item price: " + product.getPrice());
                        vm.productName = null;
                        vm.state = VmState.WAIT4COINS;
                        return;
                    }
                }
                vm.display.output("Item is not in VM, select other item");

            }
            @Override
            public void insertCoin(VM vm){
                vm.display.output(vm.insertedCoin +" returned. Please choose item");
            }
            @Override
            public void cancel(VM vm){
                vm.selectedProduct = null;
                vm.display.output("Please select item");
            }
        },
        WAIT4COINS{
            @Override
            public void turnOn(VM vm){
                vm.display.output("Please insert money");
            }
            @Override
            public void selectProduct(VM vm){
                vm.display.output("Product is already selected, cancel or insert money");
            }
            @Override
            public void insertCoin(VM vm){
                vm.coinBalance += vm.insertedCoin;
                vm.insertedCoin = 0;
                if (vm.selectedProduct != null && vm.coinBalance >= vm.selectedProduct.getPrice()){
                        vm.coinBalance -= vm.selectedProduct.getPrice();
                        vm.display.output("item: " + vm.selectedProduct.getName() + " received");
                        if (vm.coinBalance > 0){
                            vm.display.output("change returned " + vm.coinBalance + " received");
                            vm.coinBalance = 0;
                        }
                        vm.state = WAIT4SELECTION;
                }
                else{
                    vm.display.output("selected item price is: " + vm.selectedProduct.getPrice() + "balance is : " + vm.coinBalance );
                }
            }

            @Override
            public void cancel(VM vm){
                if (vm.coinBalance > 0){
                    vm.display.output("change returned " + vm.selectedProduct + "received");
                    vm.coinBalance = 0;
                }
                vm.selectedProduct = null;
                vm.state = WAIT4SELECTION;
            }
            @Override
            public void vmTimeOut(VM vm){
                if (System.currentTimeMillis() - vm.lastInputTime.getTime() > 8000)
                {
                    vm.display.output("VM TimeOut");
                    vm.lastInputTime.setTime(System.currentTimeMillis());
                    vm.cancel();
                }
            }
        };
        public void turnOff(VM vm){
            vm.state = OFF;
        }
        public abstract void turnOn(VM vm);
        public abstract void selectProduct(VM vm);
        public abstract void insertCoin(VM vm);
        public abstract void cancel(VM vm);

        public void vmTimeOut(VM vm){
            //empty
        }
     }

    private  class VMTimeoutThread extends Thread{

        @Override
        public void run(){
          while(timeOutRunningFlag){
            try{
                Thread.sleep(1000);
            }catch(InterruptedException e){
                System.out.println(e);
            }
            state.vmTimeOut(VM.this);

        }
       }

    }
}

