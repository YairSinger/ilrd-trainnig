package il.co.ilrd.reflection;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.util.Arrays;

public class ObjectAnalyzer {
    private Object obj;
    private  Class objClass;

    public ObjectAnalyzer(Object obj) {
        this.obj = obj;
        this.objClass = this.obj.getClass();
    }

    public void printAncestor() throws InstantiationException, IllegalAccessException, NoSuchMethodException, InvocationTargetException {
        System.out.println("Ancestor: " + this.objClass.getSuperclass().getName());
    }


    public void classModifiers(){
        int modifiersResult = 0;
        modifiersResult = objClass.getModifiers();
        System.out.println("Modifiers: " + Modifier.toString(modifiersResult));
    }

    public void classInterfaces(){
        System.out.println("Interfaces: " +Arrays.toString(objClass.getInterfaces()));
    }
    public void classMembers(){
        System.out.println("Members: " + Arrays.toString(objClass.getFields()));
        System.out.println("Methods: " + Arrays.toString(objClass.getMethods()));
    }

    public Object newInstanceAnalyzer() throws InvocationTargetException, InstantiationException, IllegalAccessException {
        Constructor[] ctor = objClass.getConstructors();
       return  ctor[0].newInstance();
    }
    public void callInstanceMethod(Object obj, String methodName) throws NoSuchMethodException, InvocationTargetException, IllegalAccessException {
        Method f1 = objClass.getMethod(methodName);
        f1.invoke(obj);
    }

}

