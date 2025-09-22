package de.uulm.dks00.copro.stockbroker.main;

import de.uulm.dks00.copro.stockbroker.StockbrokerSolver;

public final class Main {
	private Main() {}
	
	public static void main(String[] args) {
		var solver = new StockbrokerSolver();
		solver.solve(System.in, System.out);
	}
}
