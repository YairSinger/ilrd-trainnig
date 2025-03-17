package quizes.firstNonDuplicate;

//import javax.xml.soap.Node;
import java.util.HashMap;
import java.util.Map;


public class FirstNonDuplicate {
    private Map<Long, MyNode> map = new HashMap<>();

    public FirstNonDuplicate() {
        map.put(0L, new MyNode(0L,0L,0L)); //start dummy

    }

    public void input(long n){

        if(!map.containsKey(n)){
            putIn(n);
        }else if (map.get(n).getValue() != null){
                removeAndFixlist(n);
        }
    }

    private void removeAndFixlist (long n){
        Long next = map.get(n).getNext();
        Long prev = map.get(n).getPrev();
        map.get(prev).setNext(next);
        map.get(next).setPrev(prev);
        map.get(n).setValue(null);
    }

    private void putIn(long n){
        Long oldLast = map.get(0L).getNext();
        map.get(0L).setNext(n);
        map.put(n,new MyNode(n,0L,oldLast));
        map.get(oldLast).setPrev(n);
    }

    public long output(){
        return map.get(0L).getPrev();
    }

    public static void main(String[] args) {
        FirstNonDuplicate test = new FirstNonDuplicate();
        long[] arr = {1,2,2,3,3,4,1,1,1,4,5};
        long[] res = {1,1,1,1,1,1,4,4,4,0,5};
        for (int i = 0; i < 11; i++) {
            test.input(arr[i]);
            if (test.output() != res[i]){
                System.out.println("failed test");
                System.out.println("resulted :" + test.output() + " expected: " + res[i]);
            }else System.out.println("passed i :" + i);
        }
    }
}
