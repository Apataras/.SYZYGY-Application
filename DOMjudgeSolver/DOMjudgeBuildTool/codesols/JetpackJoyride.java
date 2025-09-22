import java.math.BigInteger;
import java.util.Scanner;

public final class JetpackJoyride {
	private JetpackJoyride() {}
	
	public static void main(String[] args) {
		var sc = new Scanner(System.in);
		int t = sc.nextInt();
		for (int i = 1; i <= t; i++) {
			BigInteger f = sc.nextBigInteger();
			sc.nextLine();
			
			BigInteger l = BigInteger.ONE, r = new BigInteger("D3C21BCECCEDA1000001", 16);
			while (l.compareTo(r) != 0) {
				BigInteger[] divRem = l.add(r).divideAndRemainder(BigInteger.TWO);
				BigInteger p = divRem[0].add(
						divRem[1].equals(BigInteger.ZERO) 
							? BigInteger.ZERO : BigInteger.ONE);
				BigInteger fuel = neededFuel(p);
				
				if (fuel.compareTo(f) > 0) {
					r = p.subtract(BigInteger.ONE);
				} else {
					l = p;
				}
			}
			System.out.printf("Case #%d: %d%n", i, l);
		}
	}
	// 1 + 2 + 3 + 4 = 4 * 5 / 2
	// (x - 1)^2 = (sum
		
	// l
	// fuel(p) = sum_1_k l^2 -2l + 1 = -2(k*(k+1)/2) + k where k = sum_1_p l = 
	// 		= 
	
	private static BigInteger neededFuel(BigInteger p) {
		// sum = p * (p+1) / 2
		p = p.subtract(BigInteger.ONE);
		return p.multiply(p.add(BigInteger.ONE)).multiply(BigInteger.TWO.multiply(p).add(BigInteger.ONE)).divide(BigInteger.valueOf(6L)) 
				.subtract(BigInteger.TWO.multiply(p.multiply(p.add(BigInteger.ONE)).divide(BigInteger.TWO)))
				.add(p);
	}
}
