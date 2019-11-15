public class factorielle{
	public static void main (String[] args){
		int valeur = 13;
		long result = 1;

		// code de factorielle
		for (int i = 1;i<=valeur;i++) {
			result *= i;
		}

		System.out.println("Factorielle de "+ valeur + " = "+ result);
	}
}