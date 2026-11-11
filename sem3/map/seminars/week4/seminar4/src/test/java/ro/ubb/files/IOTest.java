package ro.ubb.files;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.io.TempDir;

import java.io.*;
import java.nio.charset.StandardCharsets;

import static org.junit.jupiter.api.Assertions.*;


//    @Test
//    void test() throws IOException {
//        OutputStream outPutStream = new FileOutputStream("test.out");
//        try {
//
//        } finally {
//            outPutStream.close();
//        }
//    }

//    @Test
//    void test() throws IOException {
//        try (OutputStream outPutStream = new FileOutputStream("test.out");
//             InputStream inputStream = new FileInputStream("test.in")) {
//
//        }
//    }

    //    @Test
//    void test() throws IOException {
//        try (OutputStream outPutStream = new ByteArrayOutputStream()) {
//            outPutStream.write('a');
//            assertEquals("a", outPutStream.toString());
//            outPutStream.write("Hello".getBytes(StandardCharsets.UTF_8));
//        }
//    }
//    @Test
//    void test() throws IOException {
//        try (FileWriter fileWriter = new FileWriter("test.out")) {
//            fileWriter.write("Test!");
//        }
//    }
//
//    @Test
//    void test(@TempDir File tempDir) throws IOException {
//        File file = new File(tempDir, "test.txt");
//        try (FileOutputStream outputStream = new FileOutputStream("test.out");
//             ByteArrayOutputStream outputStream1 = new ByteArrayOutputStream();
//             PrintWriter fileWriter = new PrintWriter(new BufferedWriter(new FileWriter(file)))
//
//    }

public class IOTest {
    @Test
    void testCopy() throws IOException {
        try (FileReader fileReader = new FileReader("gradlew");
            FileWriter fileWrite = new FileWriter("test.out");) {
            int nextChar;

            while((nextChar = fileReader.read()) != -1){
                fileWrite.write(nextChar);
            }
        }
    }

}
