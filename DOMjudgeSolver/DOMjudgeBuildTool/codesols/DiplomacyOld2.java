import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.IOException;

public final class DiplomacyOld2 {
	private DiplomacyOld2() {
	}

	public static void main(String[] args) throws IOException {
		var reader = new Reader();
		int t = reader.nextInt();
		/*
		 * @SuppressWarnings("resource") var sc = new Scanner(System.in);
		 */
		// int t = sc.nextInt();
		// sc.nextLine();
		for (int i = 1; i <= t; i++) {
			// var ws = sc.nextLine().split(" ");
			int n = reader.nextInt();// Integer.parseInt(ws[0]);
			int[] alliances = new int[n];
			int[][] roots = new int[n][n + 1];
			for (int j = 0; j < n; j++) {
				alliances[j] = j;
				roots[j][0] = 1;
				roots[j][1] = j;
			}
			int m = reader.nextInt();// Integer.parseInt(ws[1]);
			int[][] hates = new int[m][2];
			int h = 0;
			for (int j = 0; j < m; j++) {
				byte c;
				while ((c = reader.read()) <= ' ')
					;
				// ws = sc.nextLine().split(" ");
				// char c = (char)reader.read();//s[0].charAt(0);
				int a = reader.nextInt()-1;// Integer.parseInt(ws[1])-1;
				int b = reader.nextInt()-1;// Integer.parseInt(ws[2])-1;
				if (c == 'F') {
					if (alliances[b] == alliances[a])
						continue;
					int size = roots[alliances[b]][0];
					int r = alliances[b];
					for (int k = 0; k < size; k++) {
						int old = roots[alliances[b]][k + 1];
						alliances[old] = alliances[a];
						roots[alliances[a]][roots[alliances[a]][0] + 1] = old;
						roots[alliances[a]][0]++;
					}
					roots[r][0] = 0;
				} else {
					hates[h][0] = a;
					hates[h][1] = b;
					h++;
				}
			}

			int cnt = 0;
			for (int j = 0; j < h - 1; j++) {
				for (int k = j + 1; k < h; k++) {
					cnt++;
					int c1, c2;
					if (hates[j][0] == hates[k][0]) {
						if (hates[j][1] == hates[k][1])
							continue;
						c1 = hates[j][1];
						c2 = hates[k][1];
					} else if (hates[j][0] == hates[k][1]) {
						if (hates[j][1] == hates[k][0])
							continue;
						c1 = hates[j][1];
						c2 = hates[k][0];
					} else if (hates[j][1] == hates[k][0]) {
						c1 = hates[j][0];
						c2 = hates[k][1];
					} else if (hates[j][1] == hates[k][1]) {
						c1 = hates[j][0];
						c2 = hates[k][0];
					} else {
						continue;
					}

					if (alliances[c2] == alliances[c1])
						continue;
					int size = roots[alliances[c2]][0];
					int r = alliances[c2];
					for (int l = 0; l < size; l++) {
						int old = roots[alliances[c2]][l + 1];
						alliances[old] = alliances[c1];
						roots[alliances[c1]][roots[alliances[c1]][0] + 1] = old;
						roots[alliances[c1]][0]++;
					}
					roots[r][0] = 0;
				}
			}

			System.out.println(cnt);
			int leasAllianceSize = roots[alliances[0]][0];
			System.out.printf("Case #%d: %s%n", i, leasAllianceSize > n/2 ? "yes" : "no");
		}
	}

	// from
	// https://www.geeksforgeeks.org/fast-io-in-java-in-competitive-programming/
	static class Reader {
		final private int BUFFER_SIZE = 1 << 16;
		private DataInputStream din;
		private byte[] buffer;
		private int bufferPointer, bytesRead;

		public Reader() {
			din = new DataInputStream(System.in);
			buffer = new byte[BUFFER_SIZE];
			bufferPointer = bytesRead = 0;
		}

		public Reader(String file_name) throws IOException {
			din = new DataInputStream(new FileInputStream(file_name));
			buffer = new byte[BUFFER_SIZE];
			bufferPointer = bytesRead = 0;
		}

		public String readLine() throws IOException {
			byte[] buf = new byte[64]; // line length
			int cnt = 0, c;
			while ((c = read()) != -1) {
				if (c == '\n') {
					if (cnt != 0) {
						break;
					} else {
						continue;
					}
				}
				buf[cnt++] = (byte) c;
			}
			return new String(buf, 0, cnt);
		}

		public int nextInt() throws IOException {
			int ret = 0;
			byte c = read();
			while (c <= ' ') {
				c = read();
			}
			boolean neg = (c == '-');
			if (neg)
				c = read();
			do {
				ret = ret * 10 + c - '0';
			} while ((c = read()) >= '0' && c <= '9');

			if (neg)
				return -ret;
			return ret;
		}

		public long nextLong() throws IOException {
			long ret = 0;
			byte c = read();
			while (c <= ' ')
				c = read();
			boolean neg = (c == '-');
			if (neg)
				c = read();
			do {
				ret = ret * 10 + c - '0';
			} while ((c = read()) >= '0' && c <= '9');
			if (neg)
				return -ret;
			return ret;
		}

		public double nextDouble() throws IOException {
			double ret = 0, div = 1;
			byte c = read();
			while (c <= ' ')
				c = read();
			boolean neg = (c == '-');
			if (neg)
				c = read();

			do {
				ret = ret * 10 + c - '0';
			} while ((c = read()) >= '0' && c <= '9');

			if (c == '.') {
				while ((c = read()) >= '0' && c <= '9') {
					ret += (c - '0') / (div *= 10);
				}
			}

			if (neg)
				return -ret;
			return ret;
		}

		private void fillBuffer() throws IOException {
			bytesRead = din.read(buffer, bufferPointer = 0, BUFFER_SIZE);
			if (bytesRead == -1)
				buffer[0] = -1;
		}

		private byte read() throws IOException {
			if (bufferPointer == bytesRead)
				fillBuffer();
			return buffer[bufferPointer++];
		}

		public void close() throws IOException {
			if (din == null)
				return;
			din.close();
		}
	}
}
