import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;

public final class DiplomacyOld {
	private DiplomacyOld() {
	}

	private static void genLargeTest() throws IOException {
		Path tmp = Files.createTempFile(null, null);
		try (var wr = Files.newBufferedWriter(tmp)) {
			int t = 1;
			int n = 20_000;
			int m = 70_000;
			wr.write("" + t + "\n");
			wr.write(n + " " + m + "\n");
			while (m-- > 0) {
				int a = (int) (Math.random() * n + 1);
				int b;
				while ((b = (int) (Math.random() * n + 1)) == a)
					;
				wr.write((Math.random() >= 0.5 ? "F" : "A") + a + " " + b + "\n");
			}
		}
		System.setIn(new BufferedInputStream(Files.newInputStream(tmp)));
	}

	public static void main(String[] args) throws IOException {
		genLargeTest();
		Reader reader = new Reader();
		int t = reader.nextInt();
		for (int i = 1; i <= t; i++) {
			int n = reader.nextInt();
			int m = reader.nextInt();
			System.out.println(n);
			System.out.println(m);
			int[] alliances = new int[n];
			for (int j = 0; j < n; j++)
				alliances[j] = j;
			int[][] hates = new int[m][2];
			int h = 0;
			int[][] friends = new int[m][2];
			int f = 0;
			for (int j = 0; j < m; j++) {
				char c = (char) reader.read();
				int a = reader.nextInt();
				int b = reader.nextInt();
				if (c == 'F') {
					friends[f][0] = a-1;
					friends[f][1] = b-1;
					f++;
				} else {
					hates[h][0] = a-1;
					hates[h][1] = b-1;
					h++;
				}
			}

			final class Alliance {
				Collection<Integer> members = new ArrayList<>();

				void addMember(int c) {
					members.add(c);
				}

				void addMembers(Collection<Integer> cs) {
					members.addAll(cs);
				}

				@Override
				public String toString() {
					return "Alliance { " + members.toString() + " }";
				}
			}
			
			Alliance[] countryAllianceMapping = new Alliance[n];
			for (int[] fr : friends) {
				alliances[fr[1]] = alliances[fr[0]];
				/*
				var allA = countryAllianceMapping[fr[0]];
				var allB = countryAllianceMapping[fr[1]];
				if (allA != null && allB != null) {
					if (allA != allB) {
						if (allA.members.size() >= allB.members.size()) {
							allA.addMembers(allB.members);
							for (int c : allB.members)
								countryAllianceMapping[c] = allA;
						} else {
							allB.addMembers(allB.members);
							for (int c : allA.members)
								countryAllianceMapping[c] = allB;
						}
					}
				} else if (allA != null && allB == null) {
					allA.addMember(fr[1]);
					countryAllianceMapping[fr[1]] = allA;
				} else if (allA == null && allB != null) {
					allB.addMember(fr[0]);
					countryAllianceMapping[fr[0]] = allB;
				} else {
					Alliance all = new Alliance();
					all.addMember(fr[0]);
					all.addMember(fr[1]);
					countryAllianceMapping[fr[0]] = all;
					countryAllianceMapping[fr[1]] = all;
				}*/
			}

			for (int j = 0; j < h - 1; j++) {
				for (int k = j + 1; k < h; k++) {
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
					
					alliances[c2] = alliances[c1];

					/*
					Alliance allB = countryAllianceMapping[c1];
					Alliance allB2 = countryAllianceMapping[c2];
					if (allB == null && allB2 == null) {
						Alliance all = new Alliance();
						all.addMember(c1);
						all.addMember(c2);
						countryAllianceMapping[c1] = all;
						countryAllianceMapping[c2] = all;
					} else if (allB != null && allB2 == null) {
						allB.addMember(c2);
						countryAllianceMapping[c2] = allB;
					} else if (allB == null && allB2 != null) {
						allB2.addMember(c1);
						countryAllianceMapping[c1] = allB2;
					} else {
						if (allB.members.size() >= allB2.members.size()) {
							allB.addMembers(allB2.members);
							for (int c : allB2.members)
								countryAllianceMapping[c] = allB;
						} else {
							allB2.addMembers(allB.members);
							for (int c : allB.members)
								countryAllianceMapping[c] = allB2;
						}
					}*/
				}
			}/*
			Alliance leasAlliance = countryAllianceMapping[0];
			if (countryAllianceMapping[0] == null) {
				leasAlliance = new Alliance();
				leasAlliance.addMember(0);
			}*/
			int leasAllianceSize = (int)Arrays.stream(alliances).filter(x -> x == alliances[0]).count();
			boolean half = /*leasAlliance.members.size() > n*/ leasAllianceSize > n / 2;
			System.out.printf("Case #%d: %s%n", i, half ? "yes" : "no");
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
	/*
	 * 
	private static void genLargeTest() throws IOException {
		Path tmp = Files.createTempFile(null, null);
		try (var wr = Files.newBufferedWriter(tmp)) {
			int t = 20;
			wr.write("" + t + "\n");
			for (int i = 0; i < t; i++) {
			int n = 20_000;
			int m = 70_000;
			
			wr.write(n + " " + m + "\n");
			for (int j = 0; j < m; j++) {
				int a = (int) (Math.random() * n + 1);
				int b;
				while ((b = (int) (Math.random() * n + 1)) == a)
					;
				if (a >= n+1 || b >= n+1)
					System.out.println("HAHFHFHH");
				wr.write((Math.random() >= 0.95555 ? "F" : "A") + " " + a + " " + b + "\n");
			}
			
			}
			wr.flush();
		}
		System.setIn(new BufferedInputStream(Files.newInputStream(tmp)));
	}
	 */
}
