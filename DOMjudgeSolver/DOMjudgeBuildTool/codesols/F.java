import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.Scanner;

public class F {

	public static void main(String[] args) {
		class Runner {
			
			private final String name;
			private final double firstLeg, secondLag;
			
			private Runner(String name, double firstLeg, double secondLag) {
				this.name = name;
				this.firstLeg = firstLeg;
				this.secondLag = secondLag;
			}
			
			public double getFirstLeg() {
				return firstLeg;
			}
			public double getSecondLag() {
				return secondLag;
			}
			public String getName() {
				return name;
			}
		}
		class Team {
			
			private final Runner[] runners;
			private final double time;
			
			public Team(Runner[] runners, double time) {
				this.runners = runners;
				this.time = time;
			}

			public double getTime() {
				return time;
			}
			public Runner[] getRunners() {
				return runners;
			}
		}
		int n;
		Runner[] runners;
		{
			@SuppressWarnings("resource")
			var sc = new Scanner(System.in);
			n = sc.nextInt();
			runners = new Runner[n];
			sc.nextLine();
			for (int i = 0; i < n; i++) {
				String[] tmp = sc.nextLine().split(" ");
				runners[i] = new Runner(tmp[0], Double.parseDouble(tmp[1]), Double.parseDouble(tmp[2]));
			}
		}
		
		Comparator<Runner> sndLegComp = Comparator.comparingDouble(Runner::getSecondLag);
		List<Runner> secondLegRunners = new ArrayList<>();
		for (var runner : runners)
			secondLegRunners.add(runner);
		Collections.sort(secondLegRunners, sndLegComp);
		Runner best = null;
		double bestT = Double.MAX_VALUE;
		for (int i = 0; i < runners.length; i++) {
			int j = 0;
			double time = runners[i].getFirstLeg() 
					+ (secondLegRunners.get(j) != runners[i] ? secondLegRunners.get(j++) : secondLegRunners.get(-1+(j+=2))).getSecondLag()
					+ (secondLegRunners.get(j) != runners[i] ? secondLegRunners.get(j++) : secondLegRunners.get(-1+(j+=2))).getSecondLag()
					+ (secondLegRunners.get(j) != runners[i] ? secondLegRunners.get(j++) : secondLegRunners.get(-1+(j+=2))).getSecondLag();
			if (time < bestT) {
				bestT = time;
				best = runners[i];
			}
		}
		secondLegRunners.remove(best);
		Collections.sort(secondLegRunners, sndLegComp);
		
		Team bestTeam = new Team(
				new Runner[] {
						best,
						secondLegRunners.get(0),
						secondLegRunners.get(1),
						secondLegRunners.get(2)
				},
				bestT
		);
		
		System.out.println(bestTeam.getTime());
		for (var runner : bestTeam.getRunners())
			System.out.println(runner.getName());
	}
}
