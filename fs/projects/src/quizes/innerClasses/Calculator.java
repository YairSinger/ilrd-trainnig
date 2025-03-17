package quizes.innerClasses;

import java.util.HashMap;

public class Calculator {
        private  final HashMap<String, Operator> mapOperator = new HashMap<>();


        public Calculator() {
           addOperator("Addition",(a,b) -> a + b);
           Operator subtraction = new Operator() {
               @Override
               public int operate(int a, int b) {
                   return a - b;
               }
           };
           addOperator("Subtraction", subtraction);
           Multiplication multiplication = new Multiplication();
           addOperator("Multiplication", multiplication);
            class Division implements Operator{

               @Override
               public int operate(int a, int b) {
                   return a / b;
               }
           }
           Division div = new Division();
           addOperator("Division" , div);
        }

         interface Operator {
             int operate(int a, int b);
        }
        public void addOperator(String key,Operator o){
            mapOperator.put(key, o);
        }
        public int operate(String key, int a, int b) {
            return mapOperator.get(key).operate(a, b);
        }

        private static class Multiplication implements Calculator.Operator{


            @Override
            public int operate(int a, int b) {

                return a * b;
            }
        }
    }

