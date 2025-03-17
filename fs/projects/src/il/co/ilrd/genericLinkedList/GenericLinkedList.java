//Project: GenericSinglyLinkedList
//Group: ilrd_fs149-150
//Writer: Yair Singer
//Reviewer: Isreal Weiss
//Date: 22.01.2024
//status: Approved

package il.co.ilrd.genericLinkedList;

import java.util.*;

public class GenericLinkedList<E> implements Iterable<E>{

    private volatile int listModCounter = 0;
    private Node<E> head = null;

    @Override
    public Iterator<E> iterator() {
       return new GenericLinkedListIterator();
    }

    public GenericLinkedList() {

    }

    public<T extends E> void pushFront(T data){
        ++listModCounter;
        head = new Node<>(data, head);
    }
    public E popFront(){
        ++listModCounter;
        E poped = head.getData();
        head = head.getNext();
        return  poped;
    }

    public int size(){
        int count = 0;
        for (E e : this) {
            ++count;
        }
        return count;
    }

    public boolean isEmpty(){
        return head == null;
    }

    public Iterator<E> find(E data){
        GenericLinkedListIterator runner =  new GenericLinkedListIterator();
        for (E e : this) {
            if(e.equals(data)){
                return runner;
            }
            runner.next();
        }
        return runner;
    }


    public static <E> GenericLinkedList<E> merge(GenericLinkedList<? extends E> list1, GenericLinkedList<? extends E> list2){
        GenericLinkedList<E> mergedList = new GenericLinkedList<>();
        for (E e : list1) {
            mergedList.pushFront(e);
        }
        for (E e : list2) {
            mergedList.pushFront(e);
        }
        return mergedList;

    }
    public static <E> GenericLinkedList<E> newReverse (GenericLinkedList<E> list){
        GenericLinkedList<E> reversed = new GenericLinkedList<>();

        for (E e : list) {
            reversed.pushFront(e);
        }
        return reversed;
    }

    public class GenericLinkedListIterator implements Iterator<E>{

        private Node<E> node = head;
        private final int modCounter = listModCounter;

        @Override
        public boolean hasNext() {
            return node != null;
        }

        @Override
        public E next() throws NoSuchElementException {
            if (modCounter != listModCounter){
                throw  new ConcurrentModificationException("Invalid List Iterator");
            }
            if (node == null){
                throw new NoSuchElementException("No Element");
            }
            E temp = (E) node.getData();
            node = node.getNext();
            return temp;
        }

    }

    private static class Node<T> {

        private T data;
        private Node<? extends T> next;

        public Node(T data, Node<? extends T> next) {
            this.data = data;
            this.next = next;

        }

        public T getData() {
            return data;
        }

        public Node getNext() {
            return next;
        }
    }

}
