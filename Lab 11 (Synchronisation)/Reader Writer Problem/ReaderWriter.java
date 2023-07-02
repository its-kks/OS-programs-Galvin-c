import java.util.concurrent.Semaphore;
import java.util.*;

class Database {
    static int value;
    static Semaphore mutex = new Semaphore(1);
    static int readCount = 0;
    static Semaphore wrt = new Semaphore(1);
}

class Writer extends Thread {
    int id;
    Writer(int id){
        this.id=id;
    }
    public void run(){
        Random random=new Random();
        try {
            while (true) {
                Database.wrt.acquire();
                Database.value = random.nextInt(100);
                System.out.println("Writer "+id+" wrote "+Database.value);
                Database.wrt.release();
                Thread.sleep(1000);
            }
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}
class Reader extends Thread{
    int id;
    Reader(int id){
        this.id=id;
    }
    public void run(){
        try{
            while(true){
                Database.mutex.acquire();
                Database.readCount++;
                if(Database.readCount==1){
                    Database.wrt.acquire();//waiting if writer writing and preventing 
                    //writing while reading
                }
                Database.mutex.release();//other readers can enter while 
                //this reader is in critical section
                System.out.println("Reader "+id+" read "+Database.value);
                Database.mutex.acquire();
                Database.readCount--;
                if(Database.readCount==0){
                    Database.wrt.release();
                }
                Database.mutex.release();
                Thread.sleep(1000);
            }
        }
        catch(Exception e){
            System.out.println(e.getMessage());
        }   
    }
}
public class ReaderWriter {
    public static void main(String args[]){
        Scanner input=new Scanner(System.in);
        System.out.print("Enter no of readers:");
        int readNum=input.nextInt();
        System.out.print("Enter no of writers:");
        int writeNum=input.nextInt();
        Reader readerThread[]=new Reader[readNum];
        Writer writerThread[]=new Writer[writeNum];
        for(int i=0;i<readNum;i++){
            readerThread[i]=new Reader(i+1);
            readerThread[i].start();
        }
        for(int i=0;i<writeNum;i++){
            writerThread[i]=new Writer(i+1);
            writerThread[i].start();
        }
    }
}
