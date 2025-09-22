package de.uulm.dks00.copro;

import java.io.InputStream;
import java.io.PrintStream;

public abstract class ProblemSolver {
	
	private final String problemID;
	
	protected ProblemSolver(String problemID) {
		this.problemID = problemID;
	}
	
	public abstract void solve(InputStream in, PrintStream out);
	
	public String getProblemID() { return problemID; }
	
	@Override public String toString() {
		return problemID + "-solver";
	}
}
