# problem: https://open.kattis.com/problems/2048

import sys
def padzeros(row):
    while row.__len__() < 4:
        row.append(0)

def get_row(board, index):
    return board[index]

def get_col(board, index):
    col = [board[i][index] for i in range(4)]
    return col

def put_row(board, row, index):
    board[index] = row

def put_col(board, col, index):
    row_index = 0
    for item in col:
        board[row_index][index] = item
        row_index += 1 

def compress(row, dir):
    """
    compress a row
    :param row: row index from 0-3
    :param dir: right or left
    :return:
    """
    # while can_shift(row, dir) or can_combine(row):
    shift(row, dir)
    combine(row, dir)
    shift(row, dir)


def pos_zero(row):
    pos_indices = []
    zero_indices = []
    index = 0
    for i in row:
        if i == 0:
            zero_indices.append(index)
        else:
            pos_indices.append(index)
        index += 1

    return pos_indices, zero_indices

def can_combine(row):

    for i in range(row.__len__()-1):
        element = row[i]
        offset = 1
        next = 0
        while next == 0 and i+offset < row.__len__():
            next = row[i+offset]
            offset += 1
        if element != 0 and element == next:
            return True
    return False

def can_shift(row, dir):
    pos_indices, zero_indices = pos_zero(row)
    if zero_indices.__len__() == 0 or \
            pos_indices.__len__() == 0:
        return False
    if dir == "left":

        return min(zero_indices) < max(pos_indices)

    elif dir =="right":

        return max(zero_indices) > min(pos_indices)

def shift(row, dir):

    new_row = []
    pos, zero = pos_zero(row)

    if dir == "left":
        for index in pos:
            new_row.append(row[index])
        for z in zero:
            new_row.append(0)

    elif dir == "right":
        for z in zero:
            new_row.append(0)
        for index in pos:
            new_row.append(row[index])

    for i in range(row.__len__()):
        row[i] = new_row[i]

def combine(row, dir):

    if dir == "left":
        for i in range(row.__len__()-1):
            if row[i] != 0 and row[i] == row[i+1]:
                row[i] *= 2
                row[i+1] = 0
    if dir == "right":
        for i in range(row.__len__()-1, 0, -1):
            if row[i] != 0 and row[i] == row[i-1]:
                row[i-1] = 0
                row[i] *= 2
            # break

def print_board(board):
    for row in board:
        for cell in row:
            print(cell, end=" ")
        print()

def makeMove(gameboard, move):

    if move == 0:
        #left
        for row in gameboard:
            compress(row, "left")

    elif move == 1:
        #up
        for i in range(gameboard.__len__()):
            col = get_col(gameboard, i)
            compress(col, "left")
            put_col(gameboard, col, i)

    elif move == 2:
        #right
        for row in gameboard:
            compress(row, "right")
    elif move == 3:
        #down
        for i in range(gameboard.__len__()):
            col = get_col(gameboard, i)
            compress(col, "right")
            put_col(gameboard, col, i)

def make_board(lines):
    board = []
    for l in lines:
        row = []
        nums = l.split(" ")
        for num in nums:
            row.append(int(num))
        board.append(row)

    return board

def main():

    line1 = None
    line2 = None
    line3 = None
    line4 = None
    i = 0
    move = 0
    for input in sys.stdin:
        if i == 0:
            line1 = input
        elif i == 1:
            line2 = input
        elif i == 2:
            line3 = input
        elif i == 3:
            line4 = input

        elif i == 4:
            move = int(input)
            lines = [line1, line2, line3, line4]
            board = make_board(lines)
            makeMove(board, move)
            print_board(board)

        i = (i + 1) % 5




if __name__ == '__main__':
    main()
