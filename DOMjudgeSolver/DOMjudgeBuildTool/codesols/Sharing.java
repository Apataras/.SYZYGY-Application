import java.util.Scanner;

public final class Sharing {
	private Sharing() {}
	
	static X x;
	static ThreadLocal<?> tl;
	static Object got;
	public static void main(String[] args) {
		Thread a = new Thread(() -> {
			try {
				Thread.sleep(2000L);
			} catch (InterruptedException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
			x = new X();
			tl = x.t;
			got = tl.get();
			try {
				Thread.sleep(5000L);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		});
		Thread b = new Thread(() -> {
			try {
				Thread.sleep(3000L);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			x.x(tl, got);
		});
		
		a.start();
		b.start();
	}
	static class X {
		ThreadLocal<Long> t = ThreadLocal.withInitial(() -> Thread.currentThread().getId());
	
		void x(ThreadLocal<?> x, Object got) {
			System.out.println(x == t);
			System.out.println(x.get() == t.get());
			System.out.println(x.get() == got);
		}
	}
}
