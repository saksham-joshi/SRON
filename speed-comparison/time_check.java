
public class time_check {
    public static void main(String[] args) {
        long startTime = System.nanoTime();

        for(int i = 0 ; i < 10000 ; ++i){
            System.out.println(i);
        }

        long endTime = System.nanoTime();
        long elapsedTime = endTime - startTime;

        System.out.println("Time taken by Java: " + ((double)elapsedTime/1000000000) + " seconds");
    }
}