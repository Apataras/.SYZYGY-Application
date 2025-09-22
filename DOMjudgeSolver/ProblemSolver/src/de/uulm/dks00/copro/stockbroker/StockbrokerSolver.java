package de.uulm.dks00.copro.stockbroker;

import java.io.InputStream;
import java.io.PrintStream;
import java.util.Scanner;
import java.util.ServiceLoader;

import de.uulm.dks00.copro.ProblemSolver;
import de.uulm.dks00.copro.stockbroker.spi.StockbrokerSolverImpl;

public final class StockbrokerSolver extends ProblemSolver {
	
	private StockbrokerSolverImpl impl;
	
	public StockbrokerSolver() {
		super("stockbroker");
		this.impl = ServiceLoader.load(StockbrokerSolverImpl.class)
				.findFirst().get();
	}
	
	@Override public void solve(InputStream in, PrintStream out) {
		int d, p[];
		{
			@SuppressWarnings("resource")
			var sc = new Scanner(System.in);
			d = sc.nextInt();
			p = new int[d];
			for (int i = 0; i < d; i++)
				p[i] = sc.nextInt();
		}
		
		long max = impl.calcMax(d, p);
		
		out.println(max);
	}
}
