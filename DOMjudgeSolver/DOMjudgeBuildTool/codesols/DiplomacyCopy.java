import java.io.BufferedInputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;
import java.util.List;
import java.util.Scanner;

import javax.sound.midi.SysexMessage;

public final class DiplomacyCopy {
	private DiplomacyCopy() {}
	private static void genLargeTest() throws IOException {
		Path tmp = Files.createTempFile(null, null);
		try (var wr = Files.newBufferedWriter(tmp)) {
			int t = 20;
			wr.write("" + t + "\n");
			for (int i = 0; i < t; i++) {
				int n = 20_000;
				int m = 70_000;
				wr.write(n + " " + m + "\n");
				while (m-- > 0) {
					int a = (int) (Math.random() * n + 1);
					int b;
					while ((b = (int) (Math.random() * n + 1)) == a)
						;
					wr.write((Math.random() >= 2 ? "F" : "A") + " " + a + " " + b + "\n");
				}
			}
		}
		System.setIn(new BufferedInputStream(Files.newInputStream(tmp)));
	}
	public static void main(String[] args) throws IOException {
		genLargeTest();
		@SuppressWarnings("resource")
		var sc = new Scanner(System.in);
		int t = sc.nextInt();
		for (int i = 1; i <= t; i++) {
			int n = sc.nextInt();
			int m = sc.nextInt();
			
			//System.out.println(n + " " + m);
			
			Relation[] relations = new Relation[m];
			//sc.nextLine();
			for (int j = 0; j < m; j++) {
				//var tmp = sc.nextLine().split(" ");
				//System.out.println(tmp[0]);
				//System.out.println(tmp[1]);
				
				char c = sc.next().charAt(0);
				int a = sc.nextInt();//.parseInt(tmp[1]);
				int b = sc.nextInt();//.parseInt(tmp[2]);
				//System.out.println(c);
				if (c == 'F')
					relations[j] = new FriendRelation(a, b);
				else if (c == 'A')
					relations[j] = new HateRelation(a, b);
				else throw new AssertionError();
			}
			
			boolean result = canGatherHalfOfAllCountries(n, m, relations);
			if (result)
				System.out.println("Case #" + i + ": yes");
			else
				System.out.println("Case #" + i + ": no");
		}
	}
	static boolean canGatherHalfOfAllCountries(int n, int m, Relation[] relations) {		
		
		final class Alliance implements Iterable<Integer> {
			//static final Alliance EMPTY_ALLIANCE = new Alliance();
			
			static Alliance[] cToAMap; // BUG?: = new Alliance[n];
			
			private List<Integer> countries = new ArrayList<>();
			
			public void addCountry(int country) {
				countries.add(country);
			}
			
			public int size() {
				return countries.size();
			}
			
			@Override public Iterator<Integer> iterator() {
				return countries.iterator();
			}
			
			@Override
			public String toString() {
				return "Alliance " + countries;
			}
		}
		final class AllianceHelper {
			private AllianceHelper() {}
			
			Alliance merge(Alliance a, Alliance b) {
				if (a == b)
					return a;
				Alliance bigger, smaller;
				if (a.size() >= b.size()) {
					bigger = a; smaller = b;
				} else {
					bigger = b; smaller = a;
				}
				for (int country : smaller)
					updateAlliance(country, bigger);
				return bigger;
			}
			
			Alliance updateAlliance(int country, Alliance newAlliance) {
				Alliance oldAll = Alliance.cToAMap[country-1];
				Alliance.cToAMap[country-1] = newAlliance;
				newAlliance.addCountry(country);
				return oldAll;
			}
			Alliance getAlliance(int country) {
				return Alliance.cToAMap[country-1];
			}
		} AllianceHelper AllianceHelper = new AllianceHelper();
		Alliance.cToAMap = new Alliance[n];
		for (int i = 1; i <= n; i++) {
			Alliance newAll = new Alliance();
			newAll.addCountry(i);
			Alliance.cToAMap[i-1] = newAll;
		}
		Alliance[] hate = new Alliance[n];
		/*
		 * Exception in thread "main" java.lang.VerifyError: Bad local variable type
Exception Details:
  Location:
    Diplomacy$1Alliance.<clinit>()V @4: iload_0
  Reason:
    Type top (current frame, locals[0]) is not assignable to integer
  Current Frame:
    bci: @4
    flags: { }
    locals: { }
    stack: { uninitialized 0, uninitialized 0 }
  Bytecode:
    0000000: bb00 0159 1ab7 0012 b300 161a bd00 01b3
    0000010: 0018 b200 18b2 0016 b800 1ab1          

	at Diplomacy.canGatherHalfOfAllCountries(Diplomacy.java:87)
	at Diplomacy.main(Diplomacy.java:30)
		 */
		//System.out.println(Arrays.toString(Alliance.cToAMap));
		for (Relation rel : relations) {
			//System.out.println(rel);
			if (rel instanceof FriendRelation fr) {
				Alliance aAll = AllianceHelper.getAlliance(fr.a);
				Alliance bAll = AllianceHelper.getAlliance(fr.b);
				/*if (aAll == Alliance.EMPTY_ALLIANCE
						&& bAll == Alliance.EMPTY_ALLIANCE) {
					Alliance newAll = new Alliance();
					AllianceHelper.updateAlliance(fr.a, newAll);
					AllianceHelper.updateAlliance(fr.b, newAll);
					continue;
				}*/
				AllianceHelper.merge(aAll, bAll);
			} else if (rel instanceof HateRelation hr) {
				Alliance aAll = AllianceHelper.getAlliance(hr.a);
				Alliance bAll = AllianceHelper.getAlliance(hr.b);
				/*if (hate[hr.b] == Alliance.EMPTY_ALLIANCE
						&& aAll == Alliance.EMPTY_ALLIANCE) {
					Alliance all;
					if (aAll != Alliance.EMPTY_ALLIANCE)
						all = aAll;
					else {
						Alliance newAll = new Alliance();
						AllianceHelper.updateAlliance(hr.a, all);
						all = newAll;
					}
					hate[hr.b] = all;
				}
				if (hate[hr.a] == Alliance.EMPTY_ALLIANCE) {
					Alliance newAll = new Alliance();
					AllianceHelper.updateAlliance(hr.a, newAll);
					hate[hr.a] = newAll;
				}*/
				if (hate[hr.b-1] != null)
					hate[hr.b-1] = AllianceHelper.merge(aAll, hate[hr.b-1]);
				else hate[hr.b-1] = aAll;
				if (hate[hr.a-1] != null)
					hate[hr.a-1] = AllianceHelper.merge(bAll, hate[hr.a-1]);
				else hate[hr.a-1] = bAll;
			} else throw new AssertionError();
		}
		
		//System.out.println(Arrays.toString(Alliance.cToAMap));
		Alliance leasAlliance = AllianceHelper.getAlliance(1);
		System.out.println(leasAlliance);
		return leasAlliance.size() > n/2;
	}
	
	interface Relation {}
	static final class FriendRelation implements Relation {
		int a;
		int b;
		FriendRelation(int a, int b) {
			this.a = a;
			this.b = b;
		}
	}
	static final class HateRelation implements Relation {
		int a;
		int b;
		HateRelation(int a, int b) {
			this.a = a;
			this.b = b;
		}
	}
}
