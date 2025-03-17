package quizes;

class A<T extends Number> {
    public void foo (Object o) {}
    public void foo (T t) {}
}