package tests;

/*import org.mockito.Mockito;
import org.mockito.junit.MockitoJUnitRunner;
import org.junit.Test;
import org.junit.Before;
import org.junit.runner.RunWith;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertEquals;


import fr.ufc.l3info.oprog.*;

public class testATM {
    
	ATM atm = null;
    
	@Before 
	public void setUp() {
		atm = new ATM();
	}
    
	// Test an exception !
	@Test(expected=ATM.NullCardException.class)
	public void testInsertCard0() throws ATM.NullCardException {
		int r = atm.insertCard(null);
	}

	@Test
	public void testInsertCard1() throws ATM.NullCardException {
		Card mockedCard = Mockito.mock(Card.class);
		Mockito.when(mockedCard.isBlocked()).thenReturn(false);
		assertEquals(atm.insertCard(mockedCard),0);
		assertEquals(atm.insertCard(mockedCard),-1);
	}
	@Test
	public void testInsertCard2() throws ATM.NullCardException {
		Card mockedCard = Mockito.mock(Card.class);
		Mockito.when(mockedCard.isBlocked()).thenReturn(true);
		assertEquals(atm.insertCard(mockedCard),-2);
	}
	@Test
	public void testInputPin0() {
		assertEquals(atm.inputPin(0000), -1);
	}
	@Test
	public void testInputPin1() throws ATM.NullCardException {
		Card mockedCard = Mockito.mock(Card.class);
		Mockito.when(mockedCard.isBlocked()).thenReturn(false);
		atm.insertCard(mockedCard);
		Mockito.when(mockedCard.checkPin(0000)).thenReturn(true);
		assertEquals(atm.inputPin(0000), 0);
	}
	@Test
	public void testInputPin2() throws ATM.NullCardException {
		Card mockedCard = Mockito.mock(Card.class);
		Mockito.when(mockedCard.isBlocked()).thenReturn(false);
		atm.insertCard(mockedCard);
		Mockito.when(mockedCard.checkPin(0000)).thenReturn(false);
		assertEquals(atm.inputPin(0000), -2);
	}
	@Test
	public void testInputPin3() throws ATM.NullCardException {
		Card mockedCard = Mockito.mock(Card.class);
		atm.insertCard(mockedCard);
		Mockito.when(mockedCard.isBlocked()).thenReturn(true);
		Mockito.when(mockedCard.checkPin(0000)).thenReturn(false);
		assertEquals(atm.inputPin(0000), -3);
	}
}*/


// JUnit
import org.junit.Test;
import org.junit.Before;
import org.junit.runner.RunWith;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertEquals;
import static org.mockito.ArgumentMatchers.anyInt;

// Mockito
import org.mockito.Mockito;
import org.mockito.junit.MockitoJUnitRunner;

// Systeme sous test
import fr.ufc.l3info.oprog.*;


@RunWith(MockitoJUnitRunner.class)
public class testATM {

    private ATM atm;
    private Card mockedCard;
    private Account mockedAccount;
    
    @Before
    public void setUp() {
        atm = new ATM();

        mockedCard = Mockito.mock(Card.class);
        // comportement général : carte non bloquée, codes valides/invalides
        Mockito.when(mockedCard.isBlocked()).thenReturn(false);
        Mockito.when(mockedCard.checkPin(4321)).thenReturn(false);
        Mockito.when(mockedCard.checkPin(1234)).thenReturn(true);

        mockedAccount = Mockito.mock(Account.class);
        // comportement général : accepte tous les retraits
        Mockito.when(mockedAccount.canWithdraw(anyInt())).thenReturn(true);
        Mockito.when(mockedAccount.debit(anyInt())).thenReturn(true);
        Mockito.when(mockedCard.getAccount()).thenReturn(mockedAccount);

    }

    /** Insertion d'une carte null */
    @Test(expected=ATM.NullCardException.class)
    public void testInsertCard0() throws ATM.NullCardException {
        atm.insertCard(null);
    }

    /** Insertion d'une carte alors qu'une carte est déjà insérée. */
    @Test
    public void testInsertCard1() throws ATM.NullCardException {
        int r = atm.insertCard(mockedCard);
        assertEquals(0, r);
        r = atm.insertCard(mockedCard);
        assertEquals(-1, r);
    }

    /** Insertion d'une carte bloquée */
    @Test
    public void testInsertCard2() throws ATM.NullCardException {
        // definition du comportement voulu : isBlocked doit retourner true
        Mockito.when(mockedCard.isBlocked()).thenReturn(true);
        int r = atm.insertCard(mockedCard);
        assertEquals(-2, r);
    }

    /** Saisie d'un code pin correct pour une carte bloquée */
    @Test
    public void testInsertCard3() throws ATM.NullCardException {
        // insert la carte
        int r = atm.insertCard(mockedCard);
        assertEquals(0, r);
        // definition du comportement voulu : isBlocked doit retourner true
        Mockito.when(mockedCard.isBlocked()).thenReturn(true);
        // tape le code PIN
        r = atm.inputPin(4321);
        assertEquals(-3, r);
    }
    
    /** Saisie d'un code pin au mauvais moment du cycle de l'ATM */
    @Test
    public void testInputPin0() {
        int r = atm.inputPin(1234);
        assertEquals(-1, r);
    }

    /** Saisie d'un code pin correct */
    @Test
    public void testInputPin1() throws ATM.NullCardException {
        int r = atm.insertCard(mockedCard);
        assertEquals(0, r);
        r = atm.inputPin(1234);
        assertEquals(0, r);
    }

    /** Saisie d'un code pin incorrect */
    @Test
    public void testInputPin2() throws ATM.NullCardException {
        int r = atm.insertCard(mockedCard);
        assertEquals(0, r);
        r = atm.inputPin(4321);
        assertEquals(-2, r);
    }

    /** Demande de retrait au mauvais moment du cycle de l'ATM */
    @Test
    public void testChooseAmount0() {
        int r = atm.chooseAmount(10);
        assertEquals(-1, r);
    }

    /** Demande de retrait d'une somme invalide, puis annulation et
     *  récupération de la carte et non-récupération de billets.
     */
    @Test
    public void testChooseAmount1() throws ATM.NullCardException {
        int r = atm.insertCard(mockedCard);
        assertEquals(0, r);
        r = atm.inputPin(1234);
        assertEquals(0, r);
        r = atm.chooseAmount(10);
        assertEquals(-2, r);
        r = atm.chooseAmount(0);
        assertEquals(0, r);
        Card c = atm.takeCard();
        assertEquals(mockedCard, c);
        int[] b = atm.takeBills();
        assertEquals(null, b);
    }
    
    @Test
    public void testChooseAmount2() throws ATM.NullCardException {
        testChooseAmountPUT(20);
    }
    @Test
    public void testChooseAmount3() throws ATM.NullCardException {
        testChooseAmountPUT(30);
    }
    @Test
    public void testChooseAmount4() throws ATM.NullCardException {
        testChooseAmountPUT(40);
    }
    @Test
    public void testChooseAmount5() throws ATM.NullCardException {
        testChooseAmountPUT(50);
    }
    @Test
    public void testChooseAmount6() throws ATM.NullCardException {
        testChooseAmountPUT(80);
    }
    @Test
    public void testChooseAmount7() throws ATM.NullCardException {
        testChooseAmountPUT(100);
    }

    /** Demande de retrait d'une somme non autorisée */
    @Test
    public void testChooseAmount8() throws ATM.NullCardException {
        Mockito.when(mockedAccount.canWithdraw(anyInt())).thenReturn(false);
        int r = atm.insertCard(mockedCard);
        assertEquals(0, r);
        r = atm.inputPin(1234);
        assertEquals(0, r);
        r = atm.chooseAmount(20);
        assertEquals(-3, r);
    }

    /**
     * Test unitaire paramétré par le montant à retirer.
     * PUT = Paramaterized Unit Test
     * Réalise une séquence valide jusqu'à la récupération de l'argent. 
     */
    private void testChooseAmountPUT(int a) throws ATM.NullCardException {
        int r = atm.insertCard(mockedCard);
        assertEquals(0, r);
        r = atm.inputPin(1234);
        assertEquals(0, r);
        r = atm.chooseAmount(a);
        assertEquals(0, r);
        Card c = atm.takeCard();
        assertEquals(mockedCard, c);
        int[] b = atm.takeBills();
        assertFalse(b == null);
        int total = 0;
        for (int i=0; i < b.length; i++) {
            total += b[i];
        }
        assertEquals(a, total);
    }

    /** Tentative de reprendre la carte sans même l'avoir insérée */
    @Test
    public void testChooseTakeCard0() {
        Card r = atm.takeCard();
        assertEquals(null, r);
    }

}











