// problem: https://open.kattis.com/problems/permutationencryption

import java.util.Scanner;
import java.util.ArrayList;
public class Permutation
{
  public static ArrayList<String> breakUp(String sentence, int size)
  {
    ArrayList<String> chunks = new ArrayList<String>();
    for (int i = 0; i < sentence.length(); i += size)
    {
      String chunk = "";
      try
      {
        chunk = sentence.substring(i, i + size);
      }
      catch (StringIndexOutOfBoundsException e)
      {
        chunk = sentence.substring(i);
      }
      while (chunk.length() < size)
      {
        chunk += " ";
      }
      chunks.add(chunk);
    }
    return chunks;
  }

  public static String permuteChunk(String chunk, String pattern)
  {
    String result = "";

    Scanner stringScanner = new Scanner(pattern);
    int chunk_size = stringScanner.nextInt();
    while (stringScanner.hasNextInt())
    {
      int index = stringScanner.nextInt();
      result += chunk.charAt(index-1);
    }
    return result;
  }

  public static String encryptSentence(String sentence, String pattern)
  {
    Scanner stringScanner = new Scanner(pattern);
    int chunk_size = stringScanner.nextInt();

    ArrayList<String> words = breakUp(sentence, chunk_size);
    String result = "'";
    for (String chunk : words)
    {
      String c = permuteChunk(chunk, pattern);
      result += c;
    }
    result += "'";
    return result;
  }


  public static void main(String[] args)
  {
    Scanner kb = new Scanner(System.in);
    while (kb.hasNextLine())
    {
      String s1 = "";
      String s2 = "";
      try
      {
        s1 = kb.nextLine();
        s2 = kb.nextLine();
        Scanner stringScanner = new Scanner(s1);
        if (stringScanner.hasNextInt())
          if (stringScanner.nextInt() == 0)
            System.exit(0);                

        String perm = encryptSentence(s2, s1);
        System.out.println(perm);
      } catch (Exception e)
      {
      }

    }
  }
}   
