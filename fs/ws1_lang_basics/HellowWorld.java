class HelloWorld {
    public static void main(String[] args) {
    	MySecondClass a = new MySecondClass();
        MySecondClass.foo1();
        a.foo2();
        int x = 1;
        {
            int x = 2;
        }
    }
}
