package de.uulm.dks00.copro.bestrelayteam;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

import de.uulm.dks00.copro.bestrelayteam.BestRelayTeamSolver.Runner;
import de.uulm.dks00.copro.bestrelayteam.BestRelayTeamSolver.Team;
import de.uulm.dks00.copro.bestrelayteam.spi.BestRelayTeamSolverImpl;

public class SimpleBestRelayTeamSolverImpl implements BestRelayTeamSolverImpl {

	@Override
	public Team calcBestTeam(int n, Runner[] runners) {
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
		
		return new Team(
				new Runner[] {
						best,
						secondLegRunners.get(0),
						secondLegRunners.get(1),
						secondLegRunners.get(2)
				},
				bestT
		);
	}
}
