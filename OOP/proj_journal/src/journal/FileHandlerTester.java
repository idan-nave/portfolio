package journal;

public class FileHandlerTester {

    // Main method to test the FilesDirsManager class
    public static void main(String[] args) {
        FileHandler.createDirectory("exampleFullDir");
        FileHandler.createDirectory("exampleEmptyDir");
        FileHandler.createFile("./exampleFullDir/example1.txt");
        FileHandler.createFile("./exampleFullDir/example2.txt");
        FileHandler.renameFile("./exampleFullDir/example2.txt", "./exampleFullDir/example2Renamed.txt");
        FileHandler.deleteFile("./exampleFullDir/example2Renamed.txt");
        FileHandler.deleteDirectoryRecursively("exampleFullDir");
        FileHandler.deleteEmptyDirectory("exampleEmptyDir");
    }
}
