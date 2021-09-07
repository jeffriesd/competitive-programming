// problem: https://open.kattis.com/problems/10kindsofpeople

import java.util.Scanner;
import java.util.ArrayList;

public class People {

  public static class CellNode {
    public int row;
    public int cell;
    public CellNode next;

    public CellNode(int row, int cell, CellNode next) {
      this.row = row;
      this.cell = cell;
      this.next = next; 
    }
  }

  public static class HashTable {
    private CellNode [] table;			// Hash table - array of references to linked lists.
    private int size;						// Size of the hash table.

    /* Constructor 0 initializes the hash table of the required size. */
    public HashTable (int _size) {
      size = _size;
      table = new CellNode[size];
    }

    /* Insert a key into the hash table. This is inserted as the new head of the 
     * linked list at table[i], where i is the hash index ot the key.
     */
    public void insert(int row, int cell) {
      int i = hash(row, cell);
      table[i] = new CellNode(row, cell, table[i]);
    }

    /* Print the contents of the hash table. Loop through all array elements,
     * then loop through all the nodes in the linked list.
     */
    public void print() {
      for (int i = 0; i < size; i++) {
        for (CellNode curr = table[i]; curr != null; curr = curr.next) 
          System.out.println(curr.row + " " + curr.cell);
      }
    }

    public boolean find(int row, int cell) {
      int i = hash(row, cell);
      for (CellNode curr = table[i]; curr != null; curr = curr.next) {
        if (curr.row == row && curr.cell == cell) 
          return true;
      }
      return false;
    }

    /* hash an integer key k. This is along the lines of a universal hash function.
     * To make it theoretically correct, need to take mod a large prime first, before
     * doing mod m.
     */
    private int hash(int row, int cell) {
      int x = 2917;
      int hash = 0;
      int[] k = {row, cell};
      for (int i = 0; i < k.length; i++) {
        hash = ((hash * x) + k[i]) % size;
      }
      return hash;
    }
  }

  public static boolean [][] binary;  //true if 1 (allowed to move)
  public static boolean [][] decimal; //true if 0
  public static boolean [][] tabled;

  public static int [][] storedIn; //used to know where each cell was stored
  public static int tableNum = 0; //keep track of current table

  public static int goalRow, goalCol;
  public static int width, height;

  public static void backtrack(boolean[][] board, boolean[][] v,
      int row, int col, int tnum) {

    //table.insert(row, col);
    storedIn[row][col] = tnum;

    v[row][col] = true;
    tabled[row][col] = true;
    //up
    if (row > 0 && !v[row-1][col] && board[row-1][col]) {
      backtrack(board, v, row-1, col, tnum);
    }
    //down
    if (row < height - 1 && !v[row+1][col] && board[row+1][col]) {
      backtrack(board, v, row+1, col, tnum);
    }
    //left
    if (col > 0 && !v[row][col-1] && board[row][col-1]) {
      backtrack(board, v, row, col-1, tnum);
    }
    //right
    if (col < width - 1 && !v[row][col+1] && board[row][col+1]) {
      backtrack(board, v, row, col+1, tnum);
    }
  }

    public static void main(String[] args) {
      Scanner kb = new Scanner(System.in);
      height = kb.nextInt();
      width = kb.nextInt();
      binary = new boolean[height][width];
      decimal = new boolean[height][width];
      storedIn = new int[height][width];

      for (int r = 0; r < height; r++) {
        String row = kb.next();
        for (int c = 0; c < width; c++) {
          int k = row.charAt(c) - '0';
          //System.out.print(k);
          binary[r][c] = k == 0;
          decimal[r][c] = k == 1;
        }
        //System.out.println();
      }  
      //create hashtables
      tabled = new boolean[height][width];
      for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) { 
          if (!tabled[r][c]) {
            //System.out.println("Starting island at " + r + ", " + c);
            tabled[r][c] = true;
            //HashTable t = new HashTable(width*height);
            boolean[][] board;
            board = binary[r][c] ? binary : decimal;
            boolean[][] visited = new boolean[height][width];
            backtrack(board, visited, r, c, tableNum);
            storedIn[r][c] = tableNum;
            //tables.add(t);
            tableNum++;
          }
        }
      }

  
      int n = kb.nextInt();

      for (int i = 0; i < n; i++) {
        int r1 = kb.nextInt() - 1;
        int c1 = kb.nextInt() - 1;
        goalRow = kb.nextInt()- 1;
        goalCol = kb.nextInt() - 1;
        int t1 = storedIn[r1][c1];
        int t2 = storedIn[goalRow][goalCol];

        boolean bin = binary[r1][c1];

        if (bin) {
          if (t1 == t2) {
            System.out.println("binary");
          }
          else {
            System.out.println("neither");
          }
        }
        else if (t1 == t2) {
          System.out.println("decimal");
        }
        else {
          System.out.println("neither");
        } 
      }
         
    }
}
