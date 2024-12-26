Compile all Java files:

javac -d bin files/*.java
javac -d bin streams/*.java

Run each program using the following command (replace <ClassName> with the actual class name, e.g., BasicFileReader):

java -cp bin files.<ClassName>
java -cp bin streams.<ClassName>
