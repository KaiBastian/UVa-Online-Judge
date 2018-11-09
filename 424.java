import java.math.BigInteger;
import java.util.*;

//424
class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        BigInteger sum = BigInteger.ZERO;
        while (true)
        {
            BigInteger currInt = in.nextBigInteger();
            if (currInt.equals(BigInteger.ZERO))
                break;

            sum = sum.add(currInt);
        } 

        System.out.println(sum.toString());
    }
}
