// problem: https://open.kattis.com/problems/baloni

import java.util.Scanner;

public class Baloni {

  
  public static void main(String[] args) {
    Scanner kb = new Scanner(System.in);

    while (kb.hasNext()) {
      int numBalloons = kb.nextInt();
      HashTable table = new HashTable(numBalloons);   
      int arrows = 0;
      for (int i = 0; i < numBalloons; i++) {
        int height = kb.nextInt();
        if (! table.find(height)) {
          table.insert(height-1);
          arrows += 1;
        }
        else {
          table.remove(height);
          table.insert(height-1);
        }
         
      }
      System.out.println(arrows);   
    } 

  }

  
  public static class HashTable {
    public Node [] table;
    public int size;

    public HashTable(int size) {
      this.size = size;
      table = new Node[size];
    }

    public void insert(int k) {
      int index = hash(k);
      
      table[index] = new Node(k, table[index]);
    }
    
    public boolean find(int k) {
      int index = hash(k);
      Node head = table[index];
      
      for (Node cur = head; cur != null; cur = cur.next) {
        if (cur.key == k) {
          return true;
        }      
      }
      return false;
    }
    
    public void remove(int k) {
      if (find(k)) {
        int i = hash(k);
        Node head = table[i];
        if (head.key == k) {
          table[i] = head.next;
        }
        else {
          for (Node cur = head; cur != null; cur = cur.next) {
            
            if (cur.next.key == k) {
              cur.next = cur.next.next;
            }
          }     
        } 
      }
    }
  
    public int hash(int k) {
      return (2917 * k + 101923) % size;
    }
  }
  
  public static class Node {
    public int key;
    public Node next;

    public Node(int key, Node next) {
      this.key = key;
      this.next = next;
    }
  }
}
