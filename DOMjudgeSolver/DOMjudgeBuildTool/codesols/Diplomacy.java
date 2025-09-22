import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Scanner;

public final class Diplomacy {
	private Diplomacy() {
	}

	public static void main(String[] args) {
		@SuppressWarnings("resource")
		var sc = new Scanner(System.in);
		int t = sc.nextInt();
		for (int i = 1; i <= t; i++) {
			int n = sc.nextInt();
			int m = sc.nextInt();
			Relation[] relations = new Relation[m];
			for (int j = 0; j < m; j++) {
				char c = sc.next().charAt(0);
				int a = sc.nextInt();
				int b = sc.nextInt();
				if (c == 'F')
					relations[j] = new FriendRelation(a, b);
				else if (c == 'A')
					relations[j] = new HateRelation(a, b);
				else
					throw new AssertionError();
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

			private int hater; // country
			private List<Integer> countries = new ArrayList<>();

			public void addCountry(int country) {
				countries.add(country);
			}

			public int size() {
				return countries.size();
			}

			public boolean hasHater() {
				return hater != 0;
			}

			public int getHater() {
				return hater;
			}

			@Override
			public Iterator<Integer> iterator() {
				return countries.iterator();
			}

			@Override
			public String toString() {
				return "Alliance " + countries;
			}
		}
		final class AllianceHelper {
			private AllianceHelper() {
			}

			Alliance merge(Alliance a, Alliance b) {
				if (a == b)
					return a;
				Alliance bigger, smaller;
				if (a.size() >= b.size()) {
					bigger = a;
					smaller = b;
				} else {
					bigger = b;
					smaller = a;
				}
				for (int country : smaller)
					updateAlliance(country, bigger);
				return bigger;
			}

			private final Alliance[] cToAMap = new Alliance[n];
			{
				for (int i = 1; i <= n; i++) {
					Alliance newAll = new Alliance();
					newAll.addCountry(i);
					cToAMap[i - 1] = newAll;
				}
			}

			Alliance updateAlliance(int country, Alliance newAlliance) {
				Alliance oldAll = cToAMap[country - 1];
				cToAMap[country - 1] = newAlliance;
				newAlliance.addCountry(country);
				return oldAll;
			}

			Alliance getAlliance(int country) {
				return cToAMap[country - 1];
			}
		}
		AllianceHelper AllianceHelper = new AllianceHelper();

		for (Relation rel : relations) {
			if (rel instanceof FriendRelation /* :(fr */) {
				FriendRelation fr = (FriendRelation) rel;
				Alliance aAll = AllianceHelper.getAlliance(fr.a);
				Alliance bAll = AllianceHelper.getAlliance(fr.b);

				AllianceHelper.merge(aAll, bAll);
			}
		}
		for (Relation rel : relations) {
			if (rel instanceof HateRelation /* hr */) {
				HateRelation hr = (HateRelation) rel;
				Alliance aAll = AllianceHelper.getAlliance(hr.a);
				Alliance bAll = AllianceHelper.getAlliance(hr.b);

				if (bAll.hasHater())
					AllianceHelper.merge(aAll, AllianceHelper.getAlliance(bAll.getHater()));
				else
					bAll.hater = hr.a;
				if (aAll.hasHater())
					AllianceHelper.merge(bAll, AllianceHelper.getAlliance(aAll.getHater()));
				else
					aAll.hater = hr.b;
			}
		}

		Alliance leasAlliance = AllianceHelper.getAlliance(1);
		return leasAlliance.size() > n / 2;
	}

	interface Relation {
	}

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
