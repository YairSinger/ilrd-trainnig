package il.co.ilrd.threadPool;

public enum Priority {
    LOW(1),
    MID(5),
    HIGH(10);
    private final int value;

    Priority(int value) {
        this.value = value;
    }

    public int getValue() {
        return value;
    }
}
