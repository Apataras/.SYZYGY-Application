import java.util.Scanner;

public class Test {

	public static void main(String[] args) {
		@SuppressWarnings("resource")
		var sc = new Scanner(System.in);
		int t = Integer.parseInt(sc.nextLine());
		for (int i = 1; i <= t; i++) {
			String line = sc.nextLine();
			Rod root = Rod.parseRod(line);
			System.out.printf("Case #%d: %d%n", i, calcMinChanges(root));
		}
	}

	private static int calcMinChanges(Rod root) {
		final class CalcHelper {
			private CalcHelper() {
			}

			// record Result(...) :(
			final class Result {
				double weight;
				int minChanges;

				Result(double weight, int minChanges) {
					this.weight = weight;
					this.minChanges = minChanges;
				}
			}
			Result bringIntoEquilibrium(Rod cur) {
				if (cur.isLeaf())
					return new Result(cur.weight, 0);
				Result rl = bringIntoEquilibrium(cur.left);
				Result rr = bringIntoEquilibrium(cur.right);
				int minChangesL = calcMinChanges(rl.weight, cur.right) + rl.minChanges;
				int minChangesR = calcMinChanges(rr.weight, cur.left) + rr.minChanges;
				return minChangesL <= minChangesR ? new Result(2 * rl.weight, minChangesL)
						: new Result(2 * rr.weight, minChangesR);
			}
			private int calcMinChanges(double targetWeight, Rod cur) {
				if (cur.isLeaf())
					return cur.weight == targetWeight ? 0 : 1;
				return calcMinChanges(targetWeight / 2, cur.left) + calcMinChanges(targetWeight / 2, cur.right);
			}
		}
		return new CalcHelper().bringIntoEquilibrium(root).minChanges;
	}

	static final class Rod {
		double weight = -1d;
		Rod left, right;

		Rod(double weight, Rod left, Rod right) {
			this.weight = weight;
			this.left = left;
			this.right = right;
		}
		
		@Override
		public String toString() {
			return weight + " " + left + " " + right;
		}

		boolean isLeaf() {
			return weight != -1d;
		}
		boolean isTree() {
			return weight == -1d;
		}

		public static Rod parseRod(String s) {
			int m = s.indexOf(',');
			if (m == -1)
				return new Rod(Integer.parseInt(s), null, null);
			int c = 0;
			int i;
			for (i = 1; i < s.length(); i++) {
				if (s.charAt(i) == '[')
					c++;
				else if (s.charAt(i) == ']')
					c--;
				if (c == 0 && s.charAt(i) == ',')
					break;
			}
			return new Rod(-1D, parseRod(s.substring(1, i)), parseRod(s.substring(i + 1, s.length() - 1)));
		}
	}
}
