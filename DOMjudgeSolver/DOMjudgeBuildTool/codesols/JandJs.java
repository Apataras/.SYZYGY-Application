import java.io.BufferedInputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;

public final class JandJs {
	private JandJs() {
	}

	private static void genLargeTest() throws IOException { Path tmp =
	  Files.createTempFile(null, null); try (var wr = Files.newBufferedWriter(tmp))
	  { int t = 5; wr.write("" + t + "\n"); for (int i = 0; i < t; i++) { int n =
	  1_000_000;// 1_000_000; 
	  int k = 100_000;// 100_000; 
	  wr.write(n + " " + k +
	  "\n"); int j = 0;for (; j < k/2; j++) { wr.write("i " + 1 + " " + n +
	  " 9999\n"); } for (; j < k; j++) { wr.write("q 2\n"); }} } System.setIn(new
	  BufferedInputStream(Files.newInputStream(tmp))); }

	public static void main(String[] args) throws IOException {
		final boolean tr = true;
		genLargeTest();
		try (var f = Files.newOutputStream(Paths.get("txt.txt"))) {
			System.in.transferTo(f);
		}
		
		if (tr)
			return;
		genLargeTest();
		@SuppressWarnings("resource")
		var sc = new Scanner(System.in);
		int t = sc.nextInt();
		for (int i = 1; i <= t; i++) {
			int n = sc.nextInt();
			int k = sc.nextInt();
			// sc.nextLine();
			/*
			 * int[] jjs = new int[n]; long res = 0; List<Integer> qs = new ArrayList<>();
			 * List<int[]>[] lrs = (List<int[]>[]) new List<?>[n];
			 *//*
				 * Node root = new Node(); root.l = 1; root.r = n; root.v = 0;
				 */
			long res = 0;
			List<int[]> lst = new ArrayList<>();
			List<Integer> qrs = new ArrayList<>();
			for (int j = 0; j < k; j++) {
				char type = sc.next().charAt(0);
				if (type == 'q') {
					int a = sc.nextInt();
					qrs.add(a);
					// qs.add(a);
					/*
					 * res += jjs[a-1]; res %= 1_000_000_007;
					 */
					/*
					 * res += calcQ(root, a); res %= 1_000_000_007;
					 */
				} else if (type == 'i') {
					int l = sc.nextInt();
					int r = sc.nextInt();
					int v = sc.nextInt();
					lst.add(new int[] { l, r, v });
					/// addNode(root, v, l, r, n);
					// lrs.add(new int[] {l, r, v});
					/*
					 * for (int m = l-1; m <= r-1; m++) { jjs[m] += v; jjs[m] %= 1_000_000_007; }
					 */
				}
			}

			for (int q : qrs) {
				for (int[] bnd : lst) {
					if (bnd[0] <= q && q <= bnd[1]) {
						res += bnd[2];
						res %= 1_000_000_007;
					}
				}
			}
			// System.out.println(root);

			System.out.printf("Case #%d: %d%n", i, res);
		}
	}

	static long calcQ(Node root, int a) {
		Node cur = root;
		long r = 0L;
		while (cur != null) {
			r += cur.v;
			r %= 1_000_000_007;
			if (cur.normal == null)
				break;

			if (a < cur.normal.l) {
				cur = cur.lower;
			} else if (a > cur.normal.r) {
				cur = cur.higher;
			} else {
				cur = cur.normal;
			}
		}
		return r;
	}

	static void addNode(Node root, int v, int l, int r, int n) {
		LinkedList<Node> stack = new LinkedList<>();
		stack.push(root);
		Node old = null;
		while (!stack.isEmpty()) {
			Node cur = stack.pop();
			if (old == cur) {
				System.err.println("AHHAHHH");
				break;
			}
			old = cur;
			if (cur.normal == null) {
				Node x = new Node();
				x.v = v;
				x.l = l;
				x.r = r;
				Node lower = new Node();
				lower.v = 0;
				lower.l = 0;
				lower.r = l - 1;
				Node higher = new Node();
				higher.v = 0;
				higher.l = r + 1;
				higher.r = n + 1;
				cur.lower = lower;
				cur.normal = x;
				cur.higher = higher;
				continue;
			}
			if (l <= cur.lower.r) {
				if (l <= cur.lower.l && r >= cur.lower.r) {
					cur.lower.v += v;
					cur.lower.v %= 1_000_000_007;
				} else {
					stack.push(cur.lower);
				}
				// addNode(cur.lower, v, l, r, cur.lower.r);
			}
			if ((l >= cur.normal.l && l <= cur.normal.r) || (r >= cur.normal.l && r <= cur.normal.r)
					|| (l < cur.normal.l && r > cur.normal.r)) {
				// n = cur.normal.r;
				if (l <= cur.normal.l && r >= cur.normal.r) {
					cur.normal.v += v;
					cur.normal.v %= 1_000_000_007;
				} else {
					stack.push(cur.normal);
				}
				// addNode(root.normal, v, l, r, root.normal.r);
			}
			if (r >= cur.higher.l) {
				// addNode(cur.higher, v, l, r, cur.higher.r);
				if (l <= cur.higher.l && r >= cur.higher.r) {
					cur.higher.v += v;
					cur.higher.v %= 1_000_000_007;
				} else {
					// n = cur.higher.r;
					stack.push(cur.higher);
				}
			}
		}
		// System.out.println(root);
	}

	static class Node {
		long v;
		int l, r;
		Node lower, normal, higher;
	}
}
