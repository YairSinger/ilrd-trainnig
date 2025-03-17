package quizes.firstNonDuplicate;

public class MyNode{

    private  Long value;
     private Long prev;
     private Long Next;

     public MyNode(Long date, Long prev, Long next) {
         this.value = date;
         this.prev = prev;
         Next = next;
     }

    public Long getValue() {
        return value;
    }

    public Long getPrev() {
        return prev;
    }

    public Long getNext() {
        return Next;
    }



    public void setPrev(Long prev) {
        this.prev = prev;
    }

    public void setNext(Long next) {
        Next = next;
    }
    public void setValue(Long value) {
        this.value = value;
    }
}
