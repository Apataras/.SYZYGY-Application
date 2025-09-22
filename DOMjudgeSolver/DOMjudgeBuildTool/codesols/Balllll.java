import java.util.Arrays;
import java.util.Comparator;
import java.util.HashMap;
import java.util.PriorityQueue;
import java.util.Scanner;

public final class Balllll {
	private Balllll() {}
	
	public static void main(String[] args) {
		var sc = new Scanner(System.in);
		int t = sc.nextInt();
		for (int i = 1; i <= t; i++) {
			int N = sc.nextInt();
			long B = sc.nextLong();
			long[] a = new long[N];
			for (int j = 0; j < N; j++)
				a[j] = sc.nextLong();
			
			long sum = Arrays.stream(a).sum();
			double[] prod = new double[N];
			for (int j = 0; j < N; j++)
				prod[j] = (double)a[j] / sum;
			
			long[] b = new long[N];
			class X implements Comparable<X> { double d; int q;
			
				public int compareTo(X o) {
					
					return Double.compare(d, o.d);
				};
			}
			X[] ds = new X[N];
			long rem = B;
			for (int j = 0; j < N; j++) {
				b[j] = (long)(prod[j] * (B-N)) + 1;
				System.out.println(b[j]);
				rem -= b[j];
				X x = new X();
				x.q = j;
				x.d = -((double)a[j] / b[j]);
				ds[j] = x;
			}
			//System.out.println(Arrays.toString(b));
			
			/*class {
				int i;
				long x;
			}*/
			PriorityQueue<X> pq = new PriorityQueue<>(
					Arrays.asList(ds)
			);
			System.out.println("kfk"+rem);
			while (rem --> 0) {
				X x = pq.poll();
				b[x.q]++;
				//System.out.println("KKKK" + x.d);
				x.d = -((double)a[x.q] / b[x.q]);
				//System.out.println("x");
				//System.out.println(x.d);
				pq.add(x);
			}
			X y = pq.poll();//a[maxI] / (long)(prod[maxI] * B);
			//System.out.println(Arrays.toString(b));
			//System.out.println(y.q);
			System.out.printf("Case #%d: %d%n", i, 
					(int)Math.ceil((double)a[y.q]/b[y.q]));
		}
	}
}
