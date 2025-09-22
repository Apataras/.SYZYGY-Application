package de.uulm.dks00.copro.bestrelayteam.main;

import de.uulm.dks00.copro.bestrelayteam.BestRelayTeamSolver;

public final class Main {
	private Main() {}
	
	public static void main(String[] args) {
		var solver = new BestRelayTeamSolver();
		solver.solve(System.in, System.out);
	}
}
