package de.uulm.dks00.copro.bestrelayteam.spi;

import de.uulm.dks00.copro.bestrelayteam.BestRelayTeamSolver.Runner;
import de.uulm.dks00.copro.bestrelayteam.BestRelayTeamSolver.Team;

public interface BestRelayTeamSolverImpl {

	Team calcBestTeam(int n, Runner[] runners);
}
