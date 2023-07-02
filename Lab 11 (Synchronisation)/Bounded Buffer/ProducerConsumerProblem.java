import java.util.*;
import java.util.concurrent.Semaphore;

class Buffer{
    //static so can be accesed without creating object
    static Stack<Integer> buffer=new Stack<>();
    static Semaphore mutex=new Semaphore(1);
    static Semaphore empty=new Semaphore(10);//max size allowed 10
    static Semaphore full=new Semaphore(0);
}
class Producer extends Thread{
    @Override
    public void run(){
        Random random=new Random();
        try{
            while(true){
                //generate random item
                int item=random.nextInt(100);
                Buffer.empty.acquire();//wait(empty) <- wait until empty
                Buffer.mutex.acquire();//wait(mutex) <- acquire lock no simutaneous production and consumption
                Buffer.buffer.push(item);
                System.out.println("Produced:"+item);
                Buffer.mutex.release();
                Buffer.full.release();
                Thread.sleep(1000);
            }
        }
        catch(Exception e){
            System.out.println(e.getMessage());
        }
    }
}
class Consumer extends Thread{
    @Override
    public void run(){
        try{
            while(true){
                Buffer.full.acquire();//wait(full) <- wait until some produced
                Buffer.mutex.acquire();//wait(mutex) <- acquire lock no simutaneous production and consumption
                int item=Buffer.buffer.pop();
                System.out.println("Consumed:"+item);
                Buffer.mutex.release();
                Buffer.empty.release();
                Thread.sleep(1000);
            }
        }
        catch(Exception e){
            System.out.println(e.getMessage());
        }
    }
}
public class ProducerConsumerProblem {
    public static void main(String args[]){
        Producer producerThread=new Producer();
        Consumer consumerThread=new Consumer();
        //threads started
        producerThread.start();
        producerThread.setPriority(1);
        consumerThread.start();
        consumerThread.setPriority(8);
    }
}
