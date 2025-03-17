package il.co.ilrd.SinglyLinkedList;

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
        Node newNode = new Node(data, head);
        head = newNode;
    }

    public Object popFront(){
        if (isEmpty()){
            return null;
        }
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
        ListIteratorImp runner = (ListIteratorImp) begin();

        while (runner.hasNext()){

            if(data.equals(runner.curr.data)){
               return runner;
            }
            runner.next();
        }
        return runner;
    }

}
