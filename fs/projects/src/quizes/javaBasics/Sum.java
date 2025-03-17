package quizes.javaBasics;

class Sum {
    public int sumOf(int n) {
        Integer sum = 0;
        for (Integer i = 1; i <= n; ++i) {
            sum += i;
        }
        return sum;
    }
}
