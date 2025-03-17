import il.co.ilrd.SinglyLinkedList.SinglyLinkedList;

//project: SinglyLinkedList
//Writer: Yair Singer
//Reviewer: Oron Shifman
//date: 03.01.2024
package il.co.ilrd.SinglyLinkedList;

public class TestSinglyLinkedList {
   public static void main(String[] args) {
    SinglyLinkedList sll = new SinglyLinkedList();
    int failsCounter = 0;

    if(!sll.isEmpty() || sll.size() != 0){
        ++failsCounter;
        System.out.println("Failed. isEmpty:" + sll.isEmpty() + "sll.size :" + sll.size());
    }
    sll.pushFront(5);
   if(sll.isEmpty() || sll.size() != 1){
       ++failsCounter;
       System.out.println("Failed after insert. isEmpty:" + sll.isEmpty() + "sll.size :" + sll.size());
   }
   sll.pushFront(10);
   if(sll.isEmpty() || sll.size() != 2){
       ++failsCounter;
       System.out.println("Failed after insert. isEmpty:" + sll.isEmpty() + "sll.size :" + sll.size());
   }

   sll.pushFront(7);
   if(sll.isEmpty() || sll.size() != 3){
       ++failsCounter;
       System.out.println("Failed after insert. isEmpty:" + sll.isEmpty() + "sll.size :" + sll.size());
   }
   Object pop = sll.popFront();
   if (!pop.equals(7) || pop.equals(5)){
       ++failsCounter;
       System.out.println("poped value isnt last pushed");
   }
   if( sll.size() != 2){
       ++failsCounter;
       System.out.println("Failed after pop. size:" + sll.size() + " vs 2 expected");
   }
   sll.popFront();
   sll.popFront();
   if(!sll.isEmpty() || sll.size() != 0){
       ++failsCounter;
       System.out.println("Failed.to empty list");
   }
   if (null != sll.popFront()){
       System.out.println("failed to pop from empty sll");
   }

   sll.pushFront(1);
   sll.pushFront(2);
   sll.pushFront(10);
   sll.pushFront(15);
   
   ListIterator iterator =  sll.find(2);
   Object foundData = iterator.next();
   if (!foundData.equals(2)){
       ++failsCounter;
       System.out.println("Failed to find. found :" + foundData);
   }

   iterator = sll.find(0);
   if (iterator.hasNext()){
       ++failsCounter;
       System.out.println("Failed to find object that is not in list");
   }



   if(failsCounter == 0){
       System.out.println("Sll PASSED Tests");
   }
   }

}
