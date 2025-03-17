package il.co.ilrd.singly_linked_list;

public class SinglyLinkedList {
    private class Node {

        private Object data;
        private Node next;

        private Node(Object data, Node next){
            this.data = data;
            this.next = next;
        }

    }

    private class ListIteratorImp implements ListIterator {

        private Node curr;

        private ListIteratorImp(Node node){
            curr = node;
        }
        private ListIteratorImp(){
            curr = null;
        }

        @Override
        public boolean hasNext(){
            return curr != null;
        }


        @Override
        public Object next(){
            Object temp = curr.data;
            curr = curr.next;
            return temp;
        }

    }

    public Node head;

    public void pushFront(Object data){
        head = new Node(data, head);
    }

    public Object popFront(){

        Object poped = head.data;
        head = head.next;
        return poped;

    }

    public int size(){
        int count = 0;
        ListIterator runner = begin();
        while (runner.hasNext()){
            ++count;
            runner.next();
        }
        return count;
    }

    public boolean isEmpty(){
        return head == null;
    }

    public ListIterator begin(){

        return new ListIteratorImp(head);
    }


    public ListIterator find(Object data){
        ListIterator runner =  begin();
        ListIterator runnerPrev =  new ListIteratorImp();
        while (runner.hasNext() && data.equals((runner.next())) ){
            runnerPrev.next();
        }
        return runnerPrev;
    }

}