package il.co.ilrd.hashMap;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

    public class HashMapDictionary {
        public static HashMapILRD<String, Integer> dictionary;
        public static void main(String[] args) {
            long startTime, elapsedTime;
            for (int i = 50; i < 5000; i += 1000) {
                startTime = System.nanoTime();
                setAndIterateLinuxDictionary(i);
                elapsedTime = System.nanoTime() - startTime;
                System.out.println("loading and traversing dictionary with "+ i + " buckets in " + elapsedTime/1000000 +" [millis]");
                dictionary.clear();
            }

            System.out.println();


        }
        public static void setAndIterateLinuxDictionary(int numOfBuckets){
            dictionary = new HashMapILRD<>(numOfBuckets);
            String filePath = "/usr/share/dict/words";

            try (BufferedReader reader = new BufferedReader(new FileReader(filePath))) {
                String line;
                int i = 1;
                while ((line = reader.readLine()) != null) {
                    dictionary.put(line, line.length());
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
            Integer integer = new Integer(dictionary.get("dad"));
            assert (integer.intValue() != 3);
            integer = dictionary.get("simple");
            assert (integer.intValue() != 6);

            // Print the HashMap
            for (String key : dictionary.keySet()) {

            }
        }
    }
