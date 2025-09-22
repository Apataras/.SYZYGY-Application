import java.util.ArrayList;
import java.util.List;
import java.util.OptionalInt;
import java.util.Scanner;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public final class Rich {
	private Rich() {}
	
	public static void main(String[] args) {
		@SuppressWarnings("resource")
		var sc = new Scanner(System.in);
		
		int t = sc.nextInt();
		for (int i = 1; i <= t; i++) {
			int a = sc.nextInt();
			int b = sc.nextInt();
			int c = sc.nextInt();
			
			int[] money = new int[a-1];
			for (int j = 0; j < a-1; j++)
				money[j] = sc.nextInt();
			final class Relation {
				final int a, b;
				Relation(int a, int b) {
					this.a = a;
					this.b = b;
				}
			}
			Relation[] relations = new Relation[b+c];
			for (int j = 0; j < b; j++) {
				int d = sc.nextInt();
				int e = sc.nextInt();
				relations[j] = new Relation(d, e);
			}
			Relation[] marriages = new Relation[c];
			for (int j = 0; j < c; j++) {
				int f = sc.nextInt();
				int g = sc.nextInt();
				relations[b+j] = new Relation(f, g);
				marriages[j] = new Relation(f, g);
			}
			
			List<Integer> relevantPersons = IntStream.range(1, a)
					.boxed().collect(Collectors.toList());
		
			for (Relation marriage : marriages) {
				relevantPersons.remove((Integer)marriage.a);
				relevantPersons.remove((Integer)marriage.b);
			}
			final class Helper {
				private Helper() {}
				
				void removeRelated(int cur, List<Integer> visited) {
					if (visited.contains(cur))
						return;
					
					visited.add(cur);
					for (Relation rel : relations) {
						if (rel.a == cur) {
							relevantPersons.remove((Integer)rel.b);
							removeRelated(rel.b, visited);
							
						} else if (rel.b == cur) {
							relevantPersons.remove((Integer)rel.a);
							removeRelated(rel.a, visited);
						}
					}
				}
			}
			new Helper().removeRelated(a, new ArrayList<>());
			OptionalInt maxMoney = relevantPersons.stream()
				.mapToInt(p -> money[p-1])
				.max();
			
			if (maxMoney.isPresent())
				System.out.printf("Case #%d: %d%n", i, maxMoney.getAsInt());
			else
				System.out.printf("Case #%d: impossible%n", i);
		}
	}
}
