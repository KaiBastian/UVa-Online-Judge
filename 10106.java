import java.math.BigInteger;
import java.util.*;

//10106
class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        while (in.hasNextBigInteger())
        {
            BigInteger a = in.nextBigInteger();
            BigInteger b = in.nextBigInteger();
            BigInteger product = a.multiply(b);
            System.out.println(product.toString());
        }
    }
}
