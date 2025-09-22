package de.uulm.dks00.copro.stockbroker;

import de.uulm.dks00.copro.stockbroker.spi.StockbrokerSolverImpl;

public class MinMaxStockbrokerSolverImpl implements StockbrokerSolverImpl {

	@Override
	public long calcMax(int d, int[] p) {
		final class Person {
            private final String name;
            private long money;
            private int stocks = 0; // invariant: 0 <= stocks <= 100_000
            
            public Person(String name, long money) {
                this.name = name;
                this.money = money;
            }
            
            public void buy(int amount, int price) {
                money -= amount * price;
                stocks += amount;
            }
            public void sell(int amount, int price) {
                money += amount * price;
                stocks -= amount;
            }
            public void sellAll(int price) { sell(this.stocks, price); }
            
            public int getStocks() { return stocks; }
            public long getMoney() { return money; }
            @SuppressWarnings("unused")
			public String getName() { return name; }
            
            @Override public String toString() {
                return String.format("%s { money=%d, stocks=%d }", name, money, stocks);
            }
        } Person gina = new Person("Gina", /*money=*/100L); // Gina starts with 100$
        
        int simTill = d;
        while (--simTill > 0 && p[simTill] <= p[simTill-1]);
        /*simulation:*/ for (int i = 0; i < simTill; i++) {
            int currentPrice = p[i], 
                futurePrice = p[i+1];
            if (currentPrice > futurePrice) {
                gina.sellAll(currentPrice);
            } else if (currentPrice < futurePrice) {
                // buy as much as possible
                final int MAX_STOCKS = 100_000;
                int amount = (int)Math.min(gina.getMoney() / currentPrice, MAX_STOCKS-gina.getStocks());
                gina.buy(amount, currentPrice);
            } else ; // Keep stocks
        }
        if (gina.getStocks() != 0) {
            int lastPrice = p[simTill];
            gina.sellAll(lastPrice);
        }
        return gina.getMoney();
	}
}
