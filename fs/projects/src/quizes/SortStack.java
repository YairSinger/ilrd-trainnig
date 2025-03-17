package quizes;

import java.util.Stack;

public class SortStack {

    public static void main(String[] args) {
        Stack<Integer> stack = new Stack<>();
        stack.push(200);
        stack.push(2);
        stack.push(4);
        stack.push(2);
        stack.push(0);
        stack.push(9);
        stack.push(500);

        sortStack(stack);
        for (Integer integer : stack) {
            System.out.println(integer);
        }
    }
    public static void sortStack(Stack<Integer> stack){
        Stack<Integer> aux = new Stack<>();
        Integer swappingInteger = null;

        aux.push(stack.pop());
        while(!stack.empty()){
            if (stack.peek() <= aux.peek()){
               aux.push(stack.pop());
            }
            else{
                swappingInteger = stack.pop();
                while(!aux.empty() && aux.peek() < swappingInteger ){
                    stack.push(aux.pop());
                }
                aux.push(swappingInteger);
            }
        }

        while(!aux.empty()){
            stack.push(aux.pop());
        }
    }
}
