# problem: https://open.kattis.com/problems/funhouse 

import sys

class Path:
  def __init__(self, board, start_row, start_col):
    self.board = board
    self.s_row = start_row
    self.s_col = start_col
    self.row = self.s_row
    self.col = self.s_col
    self.width = len(board[0])
    self.height = len(board)
    
    if start_col == 0:
      self.dx = 1
      self.dy = 0
      self.dir = "r"
    elif start_col == self.width - 1:
      self.dx = -1
      self.dy = 0
      self.dir = "l"
    elif start_row == 0:
      self.dx = 0
      self.dy = 1
      self.dir = "d"
    else:
      self.dx = 0
      self.dy = -1  
      self.dir = "u" 

  def set_dir(self, d):
    if d == "r":
      self.dx = 1
      self.dy = 0
      self.dir = "r"
    elif d == "l": 
      self.dx = -1
      self.dy = 0
      self.dir = "l"
    elif d == "d": 
      self.dx = 0
      self.dy = 1
      self.dir = "d"
    elif d == "u":
      self.dx = 0
      self.dy = -1  
      self.dir = "u" 

  def move(self):
    """
    moving up and hit / : go right
    moving up and hit \ : go left
    
    moving down and hit / : go left
    moving down and hit \ : go right
    
    moving left and hit / : go down
    moving left and hit \ : go up
  
    moving right and hit / : go up
    moving right and hit \ : go down
    """ 
    self.col += self.dx
    self.row += self.dy
    
    if self.done():
      #print("moved %s into %s, %s" % (self.dir, self.row, self.col))
      self.board[self.row] = self.board[self.row][:self.col] + "&" \
                        + self.board[self.row][self.col+1:]
      
    
    char = self.board[self.row][self.col]
    if char == "/":
      if self.dir == "u":
        self.set_dir("r")
      elif self.dir == "d":
        self.set_dir("l")
      elif self.dir == "l":
        self.set_dir("d")
      elif self.dir == "r":   
        self.set_dir("u")
    elif char == "\\":
      if self.dir == "u":
        self.set_dir("l")
      elif self.dir == "d":
        self.set_dir("r")
      elif self.dir == "l":
        self.set_dir("u")
      elif self.dir == "r":   
        self.set_dir("d")

  def done(self):
    start = self.row == self.s_row and self.col == self.s_col
    wall = self.row == 0 or self.col == 0 \
            or self.row == self.height - 1 \
            or self.col == self.width - 1
    return not start and wall
  
  def print(self):
    for r in self.board:
      print(r) 
    
def __main__():
  
  house = 1 
  for line in sys.stdin:
    w, h = [int(x) for x in line.split(" ")]
    if [w, h] == [0, 0]:
      exit(0)
    board = []
    for r in range(h):
      row = input()
      if "*" in row:
        entr_r = r
        entr_c = row.index("*")
      board.append(row)
    print("HOUSE %i" % house)
    path = Path(board, entr_r, entr_c)
    while not path.done():
      path.move()
    path.print() 
    house += 1
    

__main__()
