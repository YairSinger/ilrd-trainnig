public class Rectangle extends Shape{
    private double width;
    private double length;

    public Rectangle(){
        width = 1.0;
        length = 1.0;
    }
    public Rectangle(double width, double length){
        this.width = width;
        this.length = length;
    }
    public Rectangle(double width, double length, String color, boolean filled){
        super(color,filled);
        this.width = width;
        this.length = length;
    }

    public double getLength() {
        return length;
    }

    public double getWidth() {
        return width;
    }

    public void setLength(double length) {
        this.length = length;
    }

    public void setWidth(double width) {
        this.width = width;
    }

    public double getArea(){
        return this.length * this.width;
    }

    public double getPerimeter(){
        return  2 * (this.width + this.length);
    }

    @Override
    public String toString() {
        return "Rectangle{" +
                "width=" + width +
                ", length=" + length +
                '}' + "  which is subclass of " + super.toString();
    }
}
