package tests;

import org.junit.Test;
import org.junit.Before;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertEquals;


import fr.ufc.l3info.oprog.*;

public class testAccount {
    
    Account accountUnderTest = null;
    
    @Before 
    public void setUp() {
        accountUnderTest = new Account(1000);
    }
    
    @Test
    public void testCredit1() {
        assertFalse(accountUnderTest.canWithdraw(1200));
        accountUnderTest.credit(200);
        assertTrue(accountUnderTest.canWithdraw(1200));
    }
    
    @Test
    public void testDebit1() {
        boolean ok = accountUnderTest.debit(500);
        assertTrue(ok);
    }

    @Test
    public void testDebit2() {
        boolean ok = accountUnderTest.debit(1000);
        assertEquals(ok, true);
    }

    @Test
    public void testDebit3() {
        boolean nok = accountUnderTest.debit(1001);
        assertEquals(nok, false);
    }

}
