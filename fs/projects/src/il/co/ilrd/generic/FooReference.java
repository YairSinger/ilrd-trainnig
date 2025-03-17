package il.co.ilrd.generic;

public class FooReference<T> {
    private T reference;

    public FooReference(T reference) {
        this.reference = reference;
    }

    public FooReference() {}
    public void set(T t) { this.reference = t; }
    public T get() { return reference; }
}
