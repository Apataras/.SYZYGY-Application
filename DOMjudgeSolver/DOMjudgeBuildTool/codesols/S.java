import java.util.Arrays;
import java.util.Scanner;
import java.util.function.DoubleFunction;
import java.util.function.DoubleUnaryOperator;
import java.util.function.Function;

public final class S {

	public static void main(String[] args) {
		var sc = new Scanner(System.in);
		int t = sc.nextInt();
		for (int i = 1; i <= t; i++) {
			int n = sc.nextInt();
			double[] x = new double[n];
			double[] y = new double[n];
			for (int j = 0; j < n; j++) {
				x[j] = sc.nextDouble();
				y[j] = sc.nextDouble();
			}
			double m = minRadius(n, x, y, n);
			
		}
	}
	// Return minimum distance required so that
    // aleast k point lie inside the circle.
    static double minRadius(int k, double[] x, double[] y,
                                          int n)
    {
        double[] dis = new double[n];
     
        // Finding distance between of each
        // point from origin
        for (int i = 0; i < n; i++)
            dis[i] = x[i] * x[i] + y[i] * y[i];
     
        // Sorting the distance
        Arrays.sort(dis);
     
        return dis[k - 1];
    }
}
