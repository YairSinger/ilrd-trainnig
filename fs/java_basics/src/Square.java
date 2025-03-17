public class Square extends Rectangle {
    public Square(){
        super(1.0,1.0);
    }
    public Square(double side){
        super(side,side);
    }

    public Square(double side, String color, boolean filled){
        super(side, side, color,filled);
    }

    @Override
    public void setLength(double length) {
        super.setLength(length);
        super.setWidth(length);
    }

    @Override
    public void setWidth(double width) {
        super.setWidth(width);
        super.setLength(width);
    }

    public double getSide(){
        return super.getLength();
    }

    public void setSide(double side){
        super.setLength(side);
        super.setWidth(side);
    }
    @Override
    public String toString() {
        return "Square{" +
                "side=" + super.getWidth() +
                '}' + "  which is subclass of " + super.toString();
    }
}
