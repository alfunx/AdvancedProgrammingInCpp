import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;
import java.util.Vector;

public class Main {

	public static final int collectionSize = 500000000;
	public static final double nanoPerSec = 1000000000.0;

	private static <E> E findIf(Iterator<E> iter, IMatcher<E> matcher) {
		E element;

		while (iter.hasNext()) {
			element = iter.next();

			if (matcher.match(element))
				return element;
		}

		return null;
	}

	private static <E> void findElement(Collection<E> c, IMatcher<E> m) {
		long start = System.nanoTime();
		E element = findIf(c.iterator(), m);
		long end = System.nanoTime();

		if (element == null)
			System.out.println("Element not found.");
		else
			System.out.println("Element found: " + element);

		double duration = (end - start) / nanoPerSec;
		System.out.println("Time: " + duration + "s");
		System.out.println();
	}

	private static <E> void prepareCollection(Collection<E> c, E wrong, E correct) {
		for (int i = 1; i < collectionSize; ++i) {
			if (i % (collectionSize / 10) == 0)
				System.out.println(" > inserted: " + i);

			c.add(wrong);
		}
		c.add(correct);

		System.out.println("Collection ready.");
		System.out.println();
	}

	public static void main(String[] args) {
		final int find = 1;
		final int last = 1;
		final int wrong = 0;

		// Vector, slow
		Collection<Integer> collection = new Vector<>(collectionSize);

		// ArrayList, fast
		// Collection<Integer> collection = new ArrayList<>(collectionSize);

		prepareCollection(collection, wrong, last);

		IMatcher<Integer> matcher = (Integer i) -> find == i;

		for (int i = 0; i < 3; i++)
			findElement(collection, matcher);
	}

}
