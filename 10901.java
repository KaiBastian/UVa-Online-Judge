import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.TreeMap;

public class Main {
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    int cases = in.nextInt();
    for (int c = 0; c < cases; ++c) {
      Main m = new Main();
      m.parseSingleCase(in);
      m.solveSingleCase();
      final boolean isLastCase = (c + 1) == cases;
      m.printSingleCase(isLastCase);
    }
  }

  public Main() {
    this.time = 0;
    this.ferriedCars = new TreeMap<Integer, Integer>();
    this.queues = new ArrayList<ArrayDeque<Car>>(2);
    this.queues.add(new ArrayDeque<Car>());
    this.queues.add(new ArrayDeque<Car>());
  }

  private class Car {
    public Car(int id, int arrivalTime) {
      this.id = id;
      this.arrivalTime = arrivalTime;
    }
    public int id;
    public int arrivalTime;
  }

  private void parseSingleCase(Scanner in) {
    ferryCapacity = in.nextInt();
    tripTime = in.nextInt();
    final int numCars = in.nextInt();
    for (int i = 0; i < numCars; ++i) {
      final int arrivalTime = in.nextInt();
      final String side = in.next();
      final int sideInt = side.equals("left") ? 0 : 1;
      queues.get(sideInt).add(new Car(i, arrivalTime));
    }
  }

  private void solveSingleCase() {
    while (true) {
      if (areCarsReady()) {
        ferryOver();
      } else {
        if (areWeDone()) {
          return;
        } else {
          waitForCars();
        }
      }
    }
  }

  private void printSingleCase(boolean isLastCase) {
    for (Integer i : ferriedCars.values()) System.out.println(i);
    if (!isLastCase)
      System.out.println();
  }

  private boolean areCarsReady() {
    if (!queues.get(0).isEmpty() && queues.get(0).getFirst().arrivalTime <= time)
      return true;
    if (!queues.get(1).isEmpty() && queues.get(1).getFirst().arrivalTime <= time)
      return true;
    return false;
  }

  private void ferryOver() {
    moveAvailabeCars();
    time += tripTime;
    ferryPosition = ferryPosition == 0 ? 1 : 0;
  }

  private void moveAvailabeCars() {
    int numberOfShippedCars = 0;
    ArrayDeque<Car> departingSideQueue = queues.get(ferryPosition);
    while (!departingSideQueue.isEmpty() && departingSideQueue.getFirst().arrivalTime <= time
        && numberOfShippedCars < ferryCapacity) {
      numberOfShippedCars++;
      ferriedCars.put(departingSideQueue.getFirst().id, time + tripTime);
      departingSideQueue.removeFirst();
    }
  }

  private boolean areWeDone() {
    return (queues.get(0).size() + queues.get(1).size()) == 0;
  }

  private void waitForCars() {
    int nextEventTime = Integer.MAX_VALUE;
    if (!queues.get(0).isEmpty()) {
      nextEventTime = queues.get(0).getFirst().arrivalTime;
    }
    if (!queues.get(1).isEmpty()) {
      final int thisQueueNextEvent = queues.get(1).getFirst().arrivalTime;
      nextEventTime = Math.min(nextEventTime, thisQueueNextEvent);
    }
    time = nextEventTime;
  }

  private int ferryCapacity;
  private int tripTime;
  private int ferryPosition;
  private int time;
  private TreeMap<Integer, Integer> ferriedCars;
  private ArrayList<ArrayDeque<Car>> queues;
}