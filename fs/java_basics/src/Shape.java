public abstract class Shape {

    private String color;
    private boolean filled;
    public Shape(){
        color = "green";
        filled = true;
    }

    public Shape(String color, boolean filled)
    {
        this.color = color;
        this.filled = filled;
    }

    public String getColor() {
        return color;
    }

    public boolean getFilled(){
        if (filled) return true;
        else return false;
    }
    public void setColor(String color) {
        this.color = color;
    }

    public boolean isFilled() {
        return filled;
    }

    public abstract double getArea();
    public abstract double getPerimeter();

    @Override
    public String toString() {
        return "A Shape with{" +
                " color of " + color + '\'' +
                ",and filled=" + filled +
                '}';
    }
}
