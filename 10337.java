import java.util.Scanner;

class Main {
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    int numTestcases = in.nextInt();
    for (int i = 0; i < numTestcases; ++i) {
      Main main = new Main();
      int result = main.solveSingleCase(in);
      System.out.println(result);
      System.out.println();
    }
  }

  private int solveSingleCase(Scanner in) {
    final int numMiles = in.nextInt();
    final int numSteps = numMiles / 100;

    initAirspaceWind(numSteps, in);
    // The Cost-Matrix gets it's first column filled already.
    initAirspaceCost(numSteps);

    for (int currStep = 1; currStep < numSteps; ++currStep) {
      // Special case for currHeight == 0. We cannot get there by climbing.
      airspaceCost[currStep][0] = Math.min(holding(currStep, 0), sinking(currStep, 0));

      for (int currHeight = 1; currHeight < maxHeight; ++currHeight) {
        final int holdCost = holding(currStep, currHeight);
        final int sinkCost = sinking(currStep, currHeight);
        final int climbingCost = climbing(currStep, currHeight);

        final int fistMin = Math.min(holdCost, sinkCost);
        final int allMin = Math.min(fistMin, climbingCost);

        airspaceCost[currStep][currHeight] = allMin;
      }

      // Special case for currHeight == maxHeight. We cannot get the by sinking.
      airspaceCost[currStep][maxHeight] =
          Math.min(holding(currStep, maxHeight), climbing(currStep, maxHeight));
    }
    return airspaceCost[numSteps - 1][0];
  }

  private void initAirspaceWind(int numSteps, Scanner in) {
    airspaceWind = new int[numSteps][maxHeight + 1];
    for (int currHeight = maxHeight; currHeight >= 0; --currHeight) {
      for (int currStep = 0; currStep < numSteps; ++currStep) {
        airspaceWind[currStep][currHeight] = in.nextInt();
      }
    }
  }

  private void initAirspaceCost(int numSteps) {
    airspaceCost = new int[numSteps][maxHeight + 1];
    airspaceCost[0][0] = holding - airspaceWind[0][0];
    airspaceCost[0][1] = climbing - airspaceWind[0][0];
    for (int currHeight = 2; currHeight <= maxHeight; ++currHeight)
      airspaceCost[0][currHeight] = Integer.MAX_VALUE;
  }

  private int holding(int step, int height) {
    return calculateCost(airspaceCost[step - 1][height], holding, airspaceWind[step][height]);
  }

  private int sinking(int step, int height) {
    return calculateCost(
        airspaceCost[step - 1][height + 1], sinking, airspaceWind[step][height + 1]);
  }

  private int climbing(int step, int height) {
    return calculateCost(
        airspaceCost[step - 1][height - 1], climbing, airspaceWind[step][height - 1]);
  }

  private static int calculateCost(int prevValue, int actionCost, int wind) {
    if (prevValue == Integer.MAX_VALUE)
      return Integer.MAX_VALUE;
    else
      return prevValue + actionCost - wind;
  }

  private static final int maxHeight = 9;
  private static final int climbing = 60;
  private static final int holding = 30;
  private static final int sinking = 20;

  private int[][] airspaceWind;
  private int[][] airspaceCost;
}
