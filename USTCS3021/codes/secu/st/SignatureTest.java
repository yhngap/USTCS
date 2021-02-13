/**
 * @version 1.00 1997-09-10
 * @author Cay Horstmann
 */

import java.security.*;

public class SignatureTest
{  public static void main(String[] args)
   {  try
      {
	 // get a KeyPairGenerator object and 
	 // initialize it with a random number
	 KeyPairGenerator keygen
            = KeyPairGenerator.getInstance("DSA");
         SecureRandom secrand = new SecureRandom();
         keygen.initialize(512, secrand);

	// generate a pair of keys
         KeyPair keys1 = keygen.generateKeyPair();
         PublicKey pubkey1 = keys1.getPublic();
         PrivateKey privkey1 = keys1.getPrivate();

	// generate another pair of keys
         KeyPair keys2 = keygen.generateKeyPair();
         PublicKey pubkey2 = keys2.getPublic();
         PrivateKey privkey2 = keys2.getPrivate();

	// sign a message with private key 1
         Signature signalg = Signature.getInstance("DSA");
         signalg.initSign(privkey1);
         String message
            = "Pay authors a bonus of $20,000.";
         signalg.update(message.getBytes());
         byte[] signature = signalg.sign();


	// verify the signature with public key 1, should pass 
         Signature verifyalg = Signature.getInstance("DSA");
         verifyalg.initVerify(pubkey1);
         verifyalg.update(message.getBytes());
         if (!verifyalg.verify(signature))
            System.out.println("Wrong key or message  tampered ");
	 else
            System.out.println("Correct key and message not tampered ");

	// verify with public key 2. should fail
         verifyalg.initVerify(pubkey2);
         verifyalg.update(message.getBytes());
         if (!verifyalg.verify(signature))
            System.out.println("Wrong key or message  tampered ");
	 else
            System.out.println("Correct key and message not tampered ");

	// modify message.  Should fail verification
	 message = message+".";
         verifyalg.initVerify(pubkey1);
         verifyalg.update(message.getBytes());
         if (!verifyalg.verify(signature))
            System.out.println("Wrong key or message  tampered ");
	else 
            System.out.println("Correct key and message not tampered ");

      }
      catch(Exception e)
      {  System.out.println("Error " + e);
      }
   }
}
