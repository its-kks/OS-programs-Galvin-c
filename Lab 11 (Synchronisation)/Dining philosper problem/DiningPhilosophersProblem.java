import java.util.*;
import java.util.concurrent.Semaphore;
class Forks{
    static Semaphore forks[];
    static Semaphore mutex=new Semaphore(1);
    static int N;
    static public void initialize(int n){
        N=n;
        forks=new Semaphore[n];
        for(int i=0;i<n;i++){
            forks[i]=new Semaphore(1);
        }
    }
}
class Philospher extends Thread{
    int id;
    //constructor
    public Philospher(int id){
        this.id = id;
    }
    public void think() throws Exception{
        System.out.println("Philospher "+id+" is thinking");
        Thread.sleep(1000);
    }
    public void eat() throws Exception{
        System.out.println("Philospher "+id+" is eating");
        Thread.sleep(1000);
    }
    public void run(){
        try{
            while(true){
                //puts current thread in sleep
                think();
                Forks.mutex.acquire();
                int left=id-1,right=(id-2+Forks.N)%Forks.N;
                //given chopstick count from 0 to N-1
                //1st philospher takes 0th and N-1 th chopstick
                Forks.forks[left].acquire();
                Forks.forks[right].acquire();
                eat();
                Forks.forks[left].release();
                Forks.forks[right].release();
                Forks.mutex.release();
            }
        }
        catch(Exception e){
            System.out.println(e.getMessage());
        }
    }
}
public class DiningPhilosophersProblem{
    public static void main(String args[]){
        Scanner input=new Scanner(System.in);
        System.out.print("Enter no of Philospers:");
        int num=input.nextInt();
        Forks.initialize(num);
        //make num number of threads
        Philospher philospher[]=new Philospher[num];
        for(int i=0;i<num;i++){
            philospher[i]=new Philospher(i+1);
            philospher[i].start();
        }
    }
}