import de.uulm.dks00.copro.ProblemSolver;
import de.uulm.dks00.copro.stockbroker.MinMaxStockbrokerSolverImpl;
import de.uulm.dks00.copro.stockbroker.StockbrokerSolver;
import de.uulm.dks00.copro.stockbroker.spi.StockbrokerSolverImpl;
import de.uulm.dks00.copro.bestrelayteam.BestRelayTeamSolver;
import de.uulm.dks00.copro.bestrelayteam.SimpleBestRelayTeamSolverImpl;
import de.uulm.dks00.copro.bestrelayteam.spi.BestRelayTeamSolverImpl;

module de.uulm.dks00.copro {
	exports de.uulm.dks00.copro;
	exports de.uulm.dks00.copro.stockbroker;
	exports de.uulm.dks00.copro.stockbroker.main;
	exports de.uulm.dks00.copro.stockbroker.spi;
	exports de.uulm.dks00.copro.bestrelayteam;
	exports de.uulm.dks00.copro.bestrelayteam.main;
	exports de.uulm.dks00.copro.bestrelayteam.spi;
	
	uses ProblemSolver;
	uses StockbrokerSolverImpl;
	uses BestRelayTeamSolverImpl;
	provides ProblemSolver with
		StockbrokerSolver,
		BestRelayTeamSolver;
	provides StockbrokerSolverImpl with
		MinMaxStockbrokerSolverImpl;
	provides BestRelayTeamSolverImpl with
		SimpleBestRelayTeamSolverImpl;
}