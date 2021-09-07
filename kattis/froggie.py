# problem: https://open.kattis.com/problems/froggie

SAFE = 0
CAR = 1
HIT = 2

class Lane(object):
  def __init__(self, width, offset, interval, speed, direction):
    self.lane = [0] * width
    self.width = width
    self.offset = offset
    self.interval = interval
    self.speed = speed
    self.direction = direction

    # build initial lane with only CAR and SAFE
    self.build_lane()

  def build_lane(self):
    for i in range(self.width):
      self.lane[i] = CAR if (i - offset) % interval == 0 else SAFE

  def update_lane(self):
    car_steps_left = 0
    first_car_index = -1
    for i, current in enumerate(self.lane):
      # if still in the path of a moving car, 
      # mark this cell
      if car_steps_left > 1:
        self.lane[i] = HIT
      elif car_steps_left == 0:
        # final position of this car
        self.lane[i] = CAR
      else: # car has finished its path

        if current == CAR:
          # is this the leftmost car?
          if first_car_index == -1:
            # calculate leftmost position after this car moves
            first_car_index = i + self.speed

          car_steps_left = self.speed
          # car at current position is moving out of the way
          self.lane[i] = SAFE
        else:
          self.lane[i] = SAFE
      
      # current car path is one step closer to completion
      car_steps_left -= 1
      
    # check for incoming car
    if first_car_index != -1 and first_car_index >= self.interval:
      # incoming car will be at self.interval - first_car_index
      new_leftmost = first_car_index - self.interval
      for i in range(self.interval - first_car_index):
        self.lane[i] = HIT
      self.lane[new_leftmost] = CAR

  def _squished(self, x_coord):
    # left to right lanes
    if self.direction == 1:
      return self.lane[x_coord] != SAFE
    
    # reversed lanes
    return self.lane[self.width - 1 - x_coord] != SAFE

  def squished(self, x_coord, time):
    # print("lane = o=%s, i=%s, s=%s" % (self.offset, self.interval, self.speed))
    if self.direction == -1:
      x_coord = self.width - 1 - x_coord

    # determine position of cars to froggie's left and right
    car_position = self.offset + (self.speed * time)
  
    # move it by intervals until right of froggie
    while car_position <= x_coord:
      car_position += self.interval
    # now move it back left (may have been way past froggie to begin with)
    while car_position >= x_coord:
      car_position -= self.interval
  
    left_car = car_position 
    right_car = car_position + self.interval

    # print("t =", time, ", x =", x_coord, ", lc =", left_car, ", rc =", right_car, end="")

    # check if left car is in froggie's way
    if left_car > 0 and left_car < self.width and left_car == x_coord:
      return True

    # check if right_car already passed over froggie's coordinate
    if right_car > 0 and right_car < self.width:
      r_prev = right_car - self.speed

      # print(", r_prev =", r_prev)

      if r_prev > 0 and x_coord > r_prev and x_coord <= right_car:
        return True
    else:
      print("")

    return False

def move_froggie(x, y, move):
  if move == "U":
    return (x, y+1)
  if move == "D":
    return (x, y-1)
  if move == "R":
    return (x+1, y)
  if move == "L":
    return (x-1, y) 

def simulate(grid, start, moves, length):
 
  frog_x = start 
  frog_y = -1
  t = 0 
  for step in moves:

    if frog_y >= length:
      return "safe"

    # check if frog was hit
    if frog_y != -1 and grid[frog_y].squished(frog_x, t):
      return "squish"
    
    # update car positions
    # for lane in grid:
    #   lane.update_lane()
    
    # update frog position
    frog_x, frog_y = move_froggie(frog_x, frog_y, step)

    t += 1

  # check if froggie escaped top lane
  return "safe" if frog_y >= length else "squish"

if __name__ == '__main__':
  l, w = map(int, input().split())

  grid = []

  possible = True

  for row in range(l):
    # top lane moves L -> R
    direction = 1 if row % 2 == 0 else -1

    offset, interval, speed = map(int, input().split())
    if interval <= speed:
      possible = False

    lane = Lane(w, offset, interval, speed, direction) 
    grid.insert(0, lane)

  frog_start, moves = input().split()
  frog_start = int(frog_start)

  if possible:
    print(simulate(grid, frog_start, moves, l))
  else:
    print("squish")
