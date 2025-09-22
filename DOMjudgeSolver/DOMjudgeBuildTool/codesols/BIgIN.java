import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Random;

import static java.lang.Math.min;
public class BIgIN {

	public static void main(String[] args) throws FileNotFoundException {
		System.setOut(new PrintStream(new FileOutputStream(new File("bigwords.txt"))));
		int t = 20;
		System.out.println(t);
		for (int i = 0; i < t; i++) {
			int n = 1_000_000;
			for (int j = 0; j < 3; j++) {
				char[] xx = genRandomArray(n);
				System.out.println(new String(xx));
			}
			
		}
	}
	private static char[] genRandomArray(int n) {
		var ran = new Random();
		char[] a = new char[n];
		for (int i = 0; i < n; i++) {
			int x = ran.nextInt(27);
			a[i] = (char) (x < 26 ? x + 'a' : '?');
		}
		return a;
	}
	private static String genField(int n, int m) {
		char[][] field = new char[n][m];
		for (char[] row : field)
			Arrays.fill(row, '.');
		for (int r = 0; r < n; r+=2) {
			for (int c = 0; c < m; c+=2) {
				field[r][c] = 'B';
				field[r][c+1] = 'W';
				field[r+1][c] = 'W';
			}
		}
		
		
		var sb = new StringBuilder();
		for (char[] row : field) {
			for (char ch : row) sb.append(ch);
			sb.append('\n');
		}
		return sb.toString();
	}
	
	
	/*static int id = 1;
	public static void main(String[] args) throws FileNotFoundException {
		System.setOut(new PrintStream(new FileOutputStream(new File("guards.txt"))));
		build_building(id);
	}
	static int n = 10_000;
	static void build_building(int prev) {
		
	}*/
	/*static void build_building(int prev) {
		if (n == 2) {
			System.out.println("2 1 0");
			int a = prev;
			int b = ++id;
			System.out.println(a + " " + b);
			return;
		}
		System.out.println("2 1 1");
		n -= 2;
		int a = prev;
		int b = ++id;
		System.out.println(a + " " + b);
		int next = ++id;
		System.out.println(b + " " + next);
		build_building(next);
	}*/
}
