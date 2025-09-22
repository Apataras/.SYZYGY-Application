package de.uulm.dks00.copro.bestrelayteam;

import java.io.InputStream;
import java.io.PrintStream;
import java.util.Scanner;
import java.util.ServiceLoader;

import de.uulm.dks00.copro.ProblemSolver;
import de.uulm.dks00.copro.bestrelayteam.spi.BestRelayTeamSolverImpl;

public class BestRelayTeamSolver extends ProblemSolver {

	private final BestRelayTeamSolverImpl impl;
	
	public BestRelayTeamSolver() {
		super("bestrelayteam");
		impl = ServiceLoader.load(BestRelayTeamSolverImpl.class)
				.findFirst().get();
	}

	@Override
	public void solve(InputStream in, PrintStream out) {
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
		
		Team bestTeam = impl.calcBestTeam(n, runners);
		out.println(bestTeam.getTime());
		for (var runner : bestTeam.getRunners())
			out.println(runner.getName());
	}
	
	public static class Runner {
	
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
	public static class Team {
		
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
}
