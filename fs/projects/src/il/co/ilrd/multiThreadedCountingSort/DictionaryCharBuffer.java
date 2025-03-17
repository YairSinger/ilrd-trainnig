package il.co.ilrd.multiThreadedCountingSort;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;

public class DictionaryCharBuffer {
   private char[] dictionaryChars;
    public DictionaryCharBuffer(){
        ArrayList<String> dictionary= new ArrayList<>();
        String filePath = "/usr/share/dict/words";

        try (BufferedReader reader = new BufferedReader(new FileReader(filePath))) {
            String line;
            int i = 1;
            while ((line = reader.readLine()) != null) {
                dictionary.add(line);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        dictionaryChars = dictionary.toString().replaceAll(",", "") .toCharArray();
    }

    public char[] getDictionaryChars() {
        return dictionaryChars;
    }

    public void setDictionaryChars(char[] dictionaryChars) {
        this.dictionaryChars = dictionaryChars;
    }

    public static void main(String[] args) {
        DictionaryCharBuffer buffer = new DictionaryCharBuffer();
        System.out.println(buffer.dictionaryChars);
    }
}
