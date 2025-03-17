//Project: DynamicJarLoader
//Group: ilrd_fs149-150
//Writer: Yair Singer
//Reviewer: Yael
//Date: 04.03.2024
//status: Approved



package il.co.ilrd.jarLoader;

import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLClassLoader;
import java.util.*;
import java.util.jar.JarEntry;
import java.util.jar.JarFile;

public class DynamicJarLoader{
    private String absoluteFileName;
    private  final String interfaceName;

    public DynamicJarLoader(String interfaceName){
        this.interfaceName = interfaceName;

    }
    public Class<?>[] load( String absoluteFileName) {
        this.absoluteFileName = absoluteFileName;
        List<Class<?>> classToReturn = new ArrayList<>();
        URL[] urlArr;
        URLClassLoader loader;

        try (JarFile jarFile = new JarFile(absoluteFileName)){
            Objects.requireNonNull(jarFile);
            try {
                //get URL in jar  file protocol of complete file
                urlArr = new URL[]{new URL("jar:file:" + absoluteFileName + "!/")};
                loader = URLClassLoader.newInstance(urlArr);
                Enumeration<JarEntry> jarEntries = jarFile.entries();

                while (jarEntries.hasMoreElements()) {
                    JarEntry curr = jarEntries.nextElement();
                    if (curr.getName().endsWith(".class")) {
                        String className = adjustClassName(curr);
                        Class<?> classFetched = null;
                        try {
                            classFetched = loader.loadClass(className);
                        } catch (ClassNotFoundException e) {
                            //write to plug and play logger
                        }
                        if(doesClassIncludeInterface(classFetched)){
                            classToReturn.add(classFetched);
                        }
                    }
                }

            } catch (MalformedURLException e) {
                //write to plug and play logger
            }
        } catch (IOException e) {
            //write to plug and play logger
        }
       return classToReturn.toArray(new Class<?>[0]);
    }
    private String adjustClassName(JarEntry curr){
        String className = curr.getName().replace('/', '.');
        return className.substring(0, className.length() - ".class".length());
    }


    private boolean doesClassIncludeInterface(Class<?> curr){
        for (Class<?> aClass : curr.getInterfaces()) {
            if (aClass.getName().equals(interfaceName)) {
                return true;
            }
        }
        return false;
    }

    }


