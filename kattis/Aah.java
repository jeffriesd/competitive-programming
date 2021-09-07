// problem: https://open.kattis.com/problems/aaah


import java.util.Scanner;
public class Aah
{
    
    public static void main(String[] args)
    {
        Scanner kb = new Scanner(System.in);
        
        while (kb.hasNextLine())
        {
            String s1 = kb.nextLine();
            String s2 = kb.nextLine();
            String out = s1.length() >= s2.length() ? "go" :"no";
            System.out.println(out);
        }
    }


}
