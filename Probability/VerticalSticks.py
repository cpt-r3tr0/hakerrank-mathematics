#!/bin/python3
from collections import Counter

def main():
  t = int(input())

  for _ in range(t):
    n = int(input())
    sticks = [int(i) for i in input().split()]
    print("%.2f" % expected_len(sticks))

def expected_len(sticks):
  expected = 0
  length = len(sticks)
  count = 0

  s = Counter(sticks)

  for stick in sorted(s, reverse=True):
    count += s[stick]
    expected += s[stick] * (length + 1) / (count + 1)

  return expected

if __name__ == '__main__':
  main()
