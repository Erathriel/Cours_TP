package fr.ufc.l3info.oprog;


/**
 *  Simplified interface of a credit card.
 *  @author Frederic Dadeau (frederic.dadeau@univ-fcomte.fr)
 */
public interface Card {
    

    /**
     *  Retrieves the bank account associated to the card.
     *  @return the account associated to the card.
     */
    public Account getAccount();
    
    /** 
     *  Indicates whether the card is blocked or not.
     *  @return true if the card is blocked, false otherwise.
     */
    public boolean isBlocked();
    
    /** 
     *  Checks the current pin of the card vs. the one in parameter.
     *  @param p the pin to check
     *  @return true if the pin are equal, false otherwise.
     */
    public boolean checkPin(int p);
    
}
