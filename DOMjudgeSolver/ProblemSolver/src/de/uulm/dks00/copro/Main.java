package de.uulm.dks00.copro;

import java.util.Map;
import java.util.Scanner;
import java.util.ServiceLoader;
import java.util.ServiceLoader.Provider;
import java.util.function.Function;
import java.util.stream.Collectors;

public final class Main {
	private Main() {}
	
	private static final Map<String, ProblemSolver> SOLVERS;
	static {
		SOLVERS = ServiceLoader.load(ProblemSolver.class)
			.stream()
			.map(Provider::get)
			.collect(Collectors.toMap(ProblemSolver::getProblemID, Function.identity()));
	}
	public static void main(String[] args) {
		try (var sc = new Scanner(System.in)) {
			do {
				System.out.println("Select a problem");
				if (!sc.hasNext())
					break;
				String problem = sc.nextLine();
				if (problem.equals("none")) {
					break;
				}
				ProblemSolver solver = SOLVERS.get(problem);
				if (solver == null) {
					System.out.println("Unknown problem");
					continue;
				}
				solver.solve(System.in, System.out);
			} while (true);
		}
		System.out.println("Bye!");
	}
}
