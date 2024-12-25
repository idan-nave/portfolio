package calc;

import org.junit.Test;
import static org.junit.Assert.*;

public class ArithmeticOperatorsTest {

//     expected: The first argument (10 + 5) is the expected value that we anticipate.
//     actual: The second argument (15) is the actual value that the test will compare to the expected value.

    @Test
    public void testArithmeticOperations() {
        assertEquals(10 + 5, 15);
        assertEquals(10 - 5, 5);
        assertEquals(10 * 5, 50);
        assertEquals(10 / 5, 2);
        assertEquals(10 % 5, 0);
    }

    @Test
    public void testComparisonOperators() {
        int d = 8;
        int e = 10;
        assertFalse(d == e);
        assertTrue(d != e);
        assertFalse(d > e);
        assertTrue(d < e);
        assertFalse(d >= e);
        assertTrue(d <= e);
    }
}
