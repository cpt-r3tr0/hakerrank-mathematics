#!/bin/python
def solve_test():
    NMk = [int(s) for s in raw_input().split()]

    junction_map = []
    for N in range(NMk[0]):
        junction_map.append([])

    for M in range(NMk[1]):
        add_junction(junction_map, [int(s) for s in raw_input().split()])

    zombie_map = []
    for N in range(NMk[0]):
        zombie_map.append([float(s) for s in raw_input().split()][0])

    zombie_map = move_zombies(zombie_map, junction_map, NMk[2])

    zombie_map.sort(reverse=True)
    return zombie_map[0:5]

def add_junction(jmap, arr):
    jmap[arr[0]].append(arr[1])
    jmap[arr[1]].append(arr[0])

def move_zombies(zmap, jmap, k):
    if k <= 0:
        return zmap

    newmap = []
    for i in range(len(zmap)):
        newmap.append(0)

    for i in range(len(zmap)):
        dif = zmap[i]/len(jmap[i])
        for junction in jmap[i]:
            newmap[junction] += dif

    if small_diff(zmap, newmap):
        return newmap
    return move_zombies(newmap, jmap, k-1)
def small_diff(a, b):
    for i in range(len(a)):
        if abs(a[i] - b[i]) > 0.01:
            return False
    return True
num_tests = raw_input()
for test in range(int(num_tests)):
    thing = solve_test()
    print "%d %d %d %d %d" % tuple([int(round(i)) for i in thing])
