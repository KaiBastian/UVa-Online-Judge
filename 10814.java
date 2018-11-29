import java.math.BigInteger;
import java.util.Scanner;

public class Main {
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    int cases = in.nextInt();
    for (int c = 0; c < cases; ++c) {
      Main m = new Main();
      m.parseSingleCase(in);
      m.solveSingleCase();
      m.printSingleCase();
    }
  }

  private void parseSingleCase(Scanner in) {
    numerator = in.nextBigInteger();
    in.next();
    denumerator = in.nextBigInteger();
  }

  private void solveSingleCase() {
    final BigInteger gcd = numerator.gcd(denumerator);
    reducedNumerator = numerator.divide(gcd);
    reducedDenumerator = denumerator.divide(gcd);
  }

  private void printSingleCase() {
    System.out.print(reducedNumerator);
    System.out.print(" / ");
    System.out.println(reducedDenumerator);
  }

  private BigInteger numerator;
  private BigInteger denumerator;

  private BigInteger reducedNumerator;
  private BigInteger reducedDenumerator;
}
