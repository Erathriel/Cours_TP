package fr.ufc.l3info.oprog;

/**
 *  Class describing the automated teller machine.
 *  @author Frederic Dadeau (frederic.dadeau@univ-fcomte.fr)
 */
public class ATM {

    /** Possible states of the ATM */
    enum STATES {
            /** Waiting for a card */
            idle,
            /** Waiting for pin input */
            input_pin,
            /** Waiting for the withdrawl amount */
            input_amount,
            /** Waiting for the card to be taken back */
            card_ejected,
            /** Waiting for the bills to be taken */
            bills_ejected
    }
    
    /** Current withdrawal request */
    private int currentRequest;
    
    /** Current state of the ATM */
    private STATES state;
    
    /** Current card inserted in the ATM */
    private Card card;
    
    /** Bills that are made available for the client */
    private int[] bills;
    
    
    /**
     *  Class constructor, initializes the ATM with a given amount of money. Starts the ATM in the idle state.
     */
    public ATM() {
        state = STATES.idle;
        card = null;
        bills = null;
        currentRequest = 0;
    }
    
    /**
     *  Insert card and checks that the card is valid. Only applicable when the ATM is in the idle state. Upon correct execution, expects the user to input his pin code.
     *  @param     c the card inserted in the ATM
     *  @return    0 if the inserted card is valid. -1 if a card is already in the ATM, -2 if the card is blocked, it is then ejected.
     *  @exception NullCardException    Exception thrown if parameter c is null
     */
    public int insertCard(Card c) throws NullCardException {
        if (c == null) {
            throw new NullCardException();
        }
        if (state != STATES.idle) {
            return -1;
        }
        card = c;
        if (card.isBlocked()) {
            state = STATES.card_ejected;
            return -2;
        }
        state = STATES.input_pin;
        return 0;
    }
    
    
    /**
     *  Tries to identify the card holder by checking his pin. If he authenticates with success, expects then the user to choose the amount he wants to withdraw.
     *  @param      p   the pin code to check
     *  @return     0   if the card holder is authenticated,
     *              -1  if the ATM is in the wrong state,
     *              -2  if the authentication failed, 
     *              -3  if the card was blocked and is now ejected.
     */
    public int inputPin(int p) {
        if (state != STATES.input_pin) {
            return -1;
        }
        if (card.checkPin(p)) {
            state = STATES.input_amount;
            return 0;
        }
        if (card.isBlocked()) {
            state = STATES.card_ejected;
            return -3;
        }
        return -2;
        
    }

    /** 
     *  Selects the amount to withdraw. If the amount is correct, the ATM ejects the card.
     *  @param a    the amount to withdraw. Possible values are 0 (cancel), 20, 30, 40, 50, 80, 100.
     *  @return 0 if the selected amount is valid, -1 if the ATM is not in the appropriate state, -2 if the amount is not in the list of the possible values, -3 if the amount is more than the balance of card's account.
     */
    public int chooseAmount(int a) {
        if (state != STATES.input_amount) {
            return -1;
        }
        if (a != 0 && a != 20 && a != 30 && a != 40 && a != 50 && a != 80 && a != 100) {
            return -2;
        }
        if (a == 0 || card.getAccount().canWithdraw(a)) {
            currentRequest = a;
            state = STATES.card_ejected;
            return 0;
        }
        return -3;
    }
    
    /**
     *  Takes back the card when it has been ejected. If a transaction was initiated, the bills are then ejected. Otherwise the ATM goes back to the idle state.
     *  @return     the card that was ejected. null if the ATM was in the wrong state.
     */
    public Card takeCard() {
        Card r = card;
        if (state != STATES.card_ejected) {
            return null;
        }
        Account acc = card.getAccount();
        card = null;
        if (currentRequest > 0) {
            acc.debit(currentRequest);
            prepareBills();
            state = STATES.bills_ejected;
        }
        else {
            state = STATES.idle;
        }
        return r;
    }
    
    
    /** 
     *  Prepare the bills. Computes the number of bills of each kind to be given to the client.
     */
    private void prepareBills() {
        int nb10 = 0;
        int nb20 = 0;
        int nb50 = 0;
        if (currentRequest >= 50) {
            nb50 = currentRequest / 50;
            currentRequest = currentRequest % 50;
        }
        if (currentRequest >= 20) {
            nb20 = currentRequest / 20;
            currentRequest = currentRequest % 20;
        }
        if (currentRequest >= 10) {
            nb10 = 1;
        }
        else {
            nb10 = 0;
        }
        bills = new int[nb50 + nb20 + nb10];
        for (int i=0; i < nb50; i++) {
            bills[i] = 50;
        }
        for (int i=0; i < nb20; i++) {
            bills[nb50+i] = 20;
        }
        for (int i=0; i < nb10; i++) {
            bills[nb50+nb20+i] = 10;
        }
        currentRequest = 0;
    }
    
    
    /** 
     *  The user takes the bills from the ATM. Upon successful execution, the ATM goes back to the idle state.
     *  @return     An array of bill amounts. null if the ATM is in the wrong state
     */
    public int[] takeBills() {
        if (state != STATES.bills_ejected) {
            return null;
        }
        int[] r = bills;
        bills = null;
        state = STATES.idle;
        return r;
    }
    
    
    /**
     *  Nested class for null values used when inserting card.
     */
    public class NullCardException extends Exception {
        public NullCardException() {
            super("Tried to insert a null card");
        }
    }
}



