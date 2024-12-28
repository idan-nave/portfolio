package journal;

import java.io.IOException;
import java.nio.file.*;
import java.nio.file.attribute.BasicFileAttributes;

public class FileHandler {

    // Create a file
    public static void createFile(String filePath) {
        Path path = Paths.get(filePath);
        try {
            // If the file does not exist, create it
            if (Files.notExists(path)) {
                Files.createFile(path);
                System.out.println("File created: " + filePath);
            } else {
                System.out.println("File already exists: " + filePath);
            }
        } catch (IOException e) {
            System.out.println("Error creating file: " + e.getMessage());
        }
    }

    // Create a directory
    public static void createDirectory(String dirPath) {
        Path path = Paths.get(dirPath);
        try {
            // If the directory does not exist, create it
            if (Files.notExists(path)) {
                Files.createDirectory(path);
                System.out.println("Directory created: " + dirPath);
            } else {
                System.out.println("Directory already exists: " + dirPath);
            }
        } catch (IOException e) {
            System.out.println("Error creating directory: " + e.getMessage());
        }
    }

    // Delete a file
    public static void deleteFile(String filePath) {
        Path path = Paths.get(filePath);
        try {
            // Delete the file if it exists
            if (Files.exists(path)) {
                Files.delete(path);
                System.out.println("File deleted: " + filePath);
            } else {
                System.out.println("File does not exist: " + filePath);
            }
        } catch (IOException e) {
            System.out.println("Error deleting file: " + e.getMessage());
        }
    }

    // Delete an empty directory
    public static void deleteEmptyDirectory(String dirPath) {
        Path path = Paths.get(dirPath);
        try {
            // Check if the directory is empty before deleting
            if (Files.exists(path) && Files.isDirectory(path)) {
                try (DirectoryStream<Path> stream = Files.newDirectoryStream(path)) {
                    if (!stream.iterator().hasNext()) {
                        Files.delete(path);
                        System.out.println("Directory deleted: " + dirPath);
                    } else {
                        System.out.println("Directory is not empty: " + dirPath);
                    }
                }
            } else {
                System.out.println("Directory does not exist: " + dirPath);
            }
        } catch (IOException e) {
            System.out.println("Error deleting directory: " + e.getMessage());
        }
    }

    // Delete a directory and all its contents (files and subdirectories)
    public static void deleteDirectoryRecursively(String dirPath) {
        Path path = Paths.get(dirPath);
        try {
            // Check if the directory exists
            if (Files.exists(path) && Files.isDirectory(path)) {
                // Use Files.walkFileTree to recursively delete contents
                Files.walkFileTree(path, new SimpleFileVisitor<Path>() {
                    // Visit each file/directory in the tree
                    @Override
                    public FileVisitResult visitFile(Path file, BasicFileAttributes attrs) throws IOException {
                        Files.delete(file); // Delete file
                        return FileVisitResult.CONTINUE;
                    }

                    // Visit each directory in the tree
                    @Override
                    public FileVisitResult postVisitDirectory(Path dir, IOException exc) throws IOException {
                        Files.delete(dir); // Delete directory after contents are deleted
                        return FileVisitResult.CONTINUE;
                    }
                });
                System.out.println("Directory and its contents deleted: " + dirPath);
            } else {
                System.out.println("Directory does not exist: " + dirPath);
            }
        } catch (IOException e) {
            System.out.println("Error deleting directory: " + e.getMessage());
        }
    }

    // Rename a directory using only the current path and a new title
    public static void renameDirectory(String pathStr, String newTitle) {
        Path oldPath = Paths.get(pathStr);
        Path parentDir = oldPath.getParent(); // Get the parent directory of the original path
        Path newPath = parentDir.resolve(newTitle); // Create the new path with the new title

        try {
            if (Files.exists(oldPath)) {
                Files.move(oldPath, newPath, StandardCopyOption.REPLACE_EXISTING);
                System.out.println("Directory renamed from " + oldPath + " to " + newPath);
            } else {
                System.out.println("The source directory does not exist: " + oldPath);
            }
        } catch (IOException e) {
            System.out.println("Error renaming directory: " + e.getMessage());
        }
    }

    // Rename a file using only the current path and a new title
    public static void renameFile(String pathStr, String newTitle) {
        Path oldPath = Paths.get(pathStr);
        Path parentDir = oldPath.getParent(); // Get the parent directory of the original path
        Path newPath = parentDir.resolve(newTitle); // Create the new path with the new title

        try {
            if (Files.exists(oldPath)) {
                Files.move(oldPath, newPath, StandardCopyOption.REPLACE_EXISTING);
                System.out.println("File renamed from " + oldPath + " to " + newPath);
            } else {
                System.out.println("The source file does not exist: " + oldPath);
            }
        } catch (IOException e) {
            System.out.println("Error renaming file: " + e.getMessage());
        }
    }
}
