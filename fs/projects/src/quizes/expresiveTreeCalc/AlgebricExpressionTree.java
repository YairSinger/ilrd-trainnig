package quizes.expresiveTreeCalc;

import il.co.ilrd.genericFactory.GenericFactory;
import quizes.innerClasses.Calculator;

import java.util.ArrayList;
import java.util.HashMap;

public class AlgebricExpressionTree {
    private static HashMap<Character, Operator> calculator = new HashMap<>();
    private static GenericFactory<Boolean,Expression,String> factory = new GenericFactory<>();
    private FullExpression fullExpression;
    private interface Expression{
       double calculate();
       boolean isOperand(String str);
    }
    private interface Operator{
        public double operate(double a,double b);
    }

    public static void initCalculator(){
        calculator.put(new Character('+'),(a,b)-> a+b);
        calculator.put(new Character('-'),(a,b)-> a-b);
        calculator.put(new Character('*'),(a,b)-> a*b);
        calculator.put(new Character('/'),(a,b)-> {
            if ((b) == 0){
                throw new IllegalArgumentException("divided by " + (b));
            }
            return a/b;

        });
    }

    public static void initFactory(){
        factory.registerCreator(false, FullExpression::new);
        factory.registerCreator(true, Operand::new);
    }

    static {
        initCalculator();
        initFactory();
    }

    public AlgebricExpressionTree(FullExpression expressionToEvaluate) {
        fullExpression = expressionToEvaluate;
    }
    public double calculate() {
        return fullExpression.calculate();
    }
   static public class FullExpression implements Expression{
        private Character operator;
        private Expression[] operands= new Expression[2];

        public FullExpression(String inputExpression) {
           //implement all the parsing logic here
            operator = inputExpression.charAt(1);
            operands[0] = factory.createObject(((Expression)this).isOperand(inputExpression.substring(0)), inputExpression.substring(0));
            operands[1] = factory.createObject(((Expression)this).isOperand(inputExpression.substring(2)), inputExpression.substring(2));
        }

        public FullExpression(Character operator,Expression leftChild, Expression rightChild) {
            this.operator = operator;
            operands[0] = leftChild;
            operands[1] = rightChild;

        }
        @Override
        public double calculate() {
            return calculator.get(operator).operate(operands[0].calculate(),operands[1].calculate());
        }

        @Override
        public boolean isOperand(String str) {
            return false;
        }
    }

    public static class Operand implements Expression{
        private double operand;

        public Operand(String str) {
            operand = Double.parseDouble(str);
        }


        @Override
        public double calculate() {
            return operand;
        }

        @Override
        public boolean isOperand(String str) {
            return true;
        }
    }

}

class  Test{
    public static void main(String[] args) {
        AlgebricExpressionTree.FullExpression plus1 =   new AlgebricExpressionTree.FullExpression('+',
                                                        new AlgebricExpressionTree.Operand("5"),
                                                        new AlgebricExpressionTree.Operand("9"));
        AlgebricExpressionTree.FullExpression multi =   new AlgebricExpressionTree.FullExpression('*',
                                                        plus1,
                                                        new AlgebricExpressionTree.Operand("2"));
        AlgebricExpressionTree.FullExpression plus2 = new AlgebricExpressionTree.FullExpression('+', multi, new AlgebricExpressionTree.Operand("3"));

        AlgebricExpressionTree algExpTree = new AlgebricExpressionTree(plus2);

        System.out.println("algExpTree resulted : " +algExpTree.calculate() + " while 31 was expected");
    }
}