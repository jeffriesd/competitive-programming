# problem: https://open.kattis.com/problems/touchscreenkeyboard

import sys
class WordRank:
    def __init__(self, word, dist):
        self.word = word
        self.dist = dist
 

def letter_to_index(letter):
    alphabet = "abcdefghijklmnopqrstuvwxyz"
    return alphabet.index(letter)

def all_distances():
  alphabet = "abcdefghijklmnopqrstuvwxyz"
  distances = []
  for a in alphabet:
    a_distances = []
    for b in alphabet:
      a_distances.append(ab_dist(a, b))
    distances.append(a_distances)
  return distances

def letter_xy(letter):
    line1 = "qwertyuiop"
    line2 = "asdfghjkl"
    line3 = "zxcvbnm"

    if line1.__contains__(letter):
        return 0, line1.index(letter)
    elif line2.__contains__(letter):
        return 1, line2.index(letter)
    elif line3.__contains__(letter):
        return 2, line3.index(letter)

def ab_dist(a, b):
    if a == b:
        return 0
    ax, ay = letter_xy(a)
    bx, by = letter_xy(b)
    
    return abs(ax - bx) + abs(ay - by)

def word_dist(w1, w2):
    tot_dist = 0
    if w1 == w2:
        return 0
 
    for i in range(w1.__len__()):
      c1 = w1[i]
      c2 = w2[i]
      if c1 == c2:
        continue
      else:
        dist = ab_dist(c1, c2)
        tot_dist += dist     
    
    return tot_dist

def rank_words(orig, words):   
      
    ranked_words = []
    dist_arr = rank_array(orig)
    olen = orig.__len__()
    for i in range(words.__len__()):
        wi = words[i]
        d = 0
        for c in range(olen):
            ci = wi[c]
            d += int(dist_arr[orig[c]][ci])
        w = WordRank(wi, d)
        if ranked_words.__len__() == 0:
            ranked_words.append(w)
            continue
        insert = 0
        for rw in ranked_words:
            #print("w=%s, wd=%s, rw=%s, rd=%s, insert=%s" % (wi, d, rw.word, rw.dist, insert))
            if rw.dist > d or \
               rw.dist == d and wi < rw.word:
                ranked_words.insert(insert, w)
                break
            elif insert == ranked_words.__len__()-1:
                ranked_words.append(w)
                break
            insert += 1

    for r in ranked_words:
        print(r.word[0:-1], r.dist)

def rank_array(orig):
  alphabet = "abcdefghijklmnopqrstuvwxyz"
  arr = {}
  num_keys = 0
  for letter in orig:
    if num_keys == 26:
      break
    if letter not in arr.keys():
      row = {}
      for a in alphabet:
        row[a] = (ab_dist(letter, a))
      arr[letter] = row
      num_keys += 1
  return arr


def main():
    line_i = 0
    num_cases = 0
    num_to_check = 0
    orig_word = ""
    to_rank = []
    for line in sys.stdin:
        if line_i == 0:
            num_cases = int(line)
        elif num_cases > 0 and num_to_check == 0:
            words = []
            word, num_check = line.split(" ")
            num_to_check = int(num_check)
            orig_word = word
            num_cases -= 1
            to_rank.append((orig_word, words))
        elif num_to_check > 0:
            words.append(line)
            num_to_check -= 1
        if num_cases == 0 and num_to_check == 0:
            for o, words in to_rank:
                rank_words(o, words)
        line_i += 1
main()
