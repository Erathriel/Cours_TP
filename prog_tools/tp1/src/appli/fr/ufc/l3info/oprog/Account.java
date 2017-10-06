package fr.ufc.l3info.oprog;


/**
 *  Simplified class for a bank account.
 *  @author Frederic Dadeau (frederic.dadeau@univ-fcomte.fr)
 */
public class Account {
    
    /** Balance of the card */
    int balance;
    
    /** Constructor. Creates an account with the initial balance given in parameter. 
     *  @param initialBalance The initial balance of the account to be created.
     */
    public Account(int initialBalance) {
        balance = initialBalance;
    }
    
    /**
     *  Credits the card with the amount given in parameter. 
     *  @param  amount   the amount to credit the account with.
     */
    public void credit(int amount) {
        balance += amount;
    }
    
    /**
     *  Withdraws the amount in parameter from the account.
     *  @param  amount  the amount to withdraw from the account
     *  @return         true if the transaction succeeded, false otherwise.
     */
    public boolean debit(int amount) {
        if (this.canWithdraw(amount)) {
            balance -= amount;
            return true;
        }
        return false;
    }
    
    
    /**
     *  Checks if the amount in parameter can be withdrawn from the account. 
     *  @param amount   the amount to withdraw
     *  @return         true if the transaction can be performed, false otherwise.
     */
    public boolean canWithdraw(int amount) {
        return balance >= amount;
    }
    
}
