import java.io.BufferedInputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Deque;
import java.util.LinkedList;
import java.util.Scanner;

// From https://www.tutorialcup.com/interview/tree/interval-tree.htm
public class IntervalTree {
	// class representing the node of interval tree
	static class Node {
		int l;
		int r;
		int v;
		int max;
		Node left, right;

		public Node(int l, int r, int v) {
			this.l = l;
			this.r = r;
			this.max = r;
			this.v = v;
		}

		@Override
		public String toString() {
			return "l " + l + " r " + r + " v " + v;
		}
	}

	// Function to insert an interval in interval tree
	public static Node insert(Node root, int l, int r, int v) {
		Deque<Node> stack = new LinkedList<>();
		stack.push(root);
		while (!stack.isEmpty()) {
			root = stack.pop();
			// Insert like normal BST, by considering root.l as the key element
			if (root == null) {
				return new Node(l, r, v);
			}
			if (l < root.l) {
				root.left = insert(root.left, l, r, v);
			} else if (l > root.l) {
				root.right = insert(root.right, l, r, v);
			} else {
				if (r < root.r) {
					root.left = insert(root.left, l, r, v);
				} else {
					root.right = insert(root.right, l, r, v);
				}
			}
			// If current node's max is less than r, then update max
			if (root.max < r) {
				root.max = r;
			}
			return root;
		}
//		// Insert like normal BST, by considering root.l as the key element
//		if (root == null) {
//			return new Node(l, r, v);
//		}
//		if (l < root.l) {
//			root.left = insert(root.left, l, r, v);
//		} else if (l > root.l) {
//			root.right = insert(root.right, l, r, v);
//		} else {
//			if (r < root.r) {
//				root.left = insert(root.left, l, r, v);
//			} else {
//				root.right = insert(root.right, l, r, v);
//			}
//		}
//		// If current node's max is less than r, then update max
//		if (root.max < r) {
//			root.max = r;
//		}
//		return root;
	}

	// From https://en.wikipedia.org/wiki/Interval_tree
	// Search for all intervals containing "p", starting with the
	// node "n" and adding matching intervals to the list "result"
	public static long search(Node n, int a) {
		// Don't search nodes that don't exist
		if (n == null)
			return 0L;

		// If p is to the right of the rightmost point of any interval
		// in this node and all children, there won't be any matches.
		if (a > n.max)
			return 0L;

		// Search left children
		long res = search(n.left, a);

		// Check this node
		if (n.l <= a && a <= n.r)
			res += n.v;

		// If p is to the left of the start of this interval,
		// then it can't be in any child to the right.
		if (a < n.l)
			return res;

		// Otherwise, search right children
		res += search(n.right, a);
		return res;
	}

	public static void main(String[] args) throws IOException {
		genLargeTest();
		var sc = new Scanner(System.in);
		int t = sc.nextInt();
		for (int i = 1; i <= t; i++) {
			int n = sc.nextInt();
			int k = sc.nextInt();

			long res = 0;
			Node root = null;
			for (int j = 0; j < k; j++) {
				char type = sc.next().charAt(0);
				if (type == 'q') {
					int a = sc.nextInt();
					res += search(root, a);
					res %= 1_000_000_007;
				} else if (type == 'i') {
					int l = sc.nextInt();
					int r = sc.nextInt();
					int v = sc.nextInt();
					root = insert(root, l, r, v);
					// System.out.println(root);
				}
			}

			System.out.printf("Case #%d: %d%n", i, res);
		}
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

}