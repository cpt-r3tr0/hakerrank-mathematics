from fractions import gcd
testcases = int(input())

for test in range(testcases):
    (strlen, K) = (int(x) for x in str(input()).split(" "))
    S = str(input())
    curcount = sum(1 for x in S[:K] if x == "1")
    ttotal = 0
    for i, x in enumerate(S[K:]):
        if x == "1":
            curcount += 1
        if S[i] == "1":
            curcount -= 1
            ttotal += 2*curcount+1
    for i in range(strlen-K,strlen):
        if S[i] == "1":
            curcount -= 1
            ttotal += 2*curcount+1

    gcdd = gcd(ttotal,strlen**2)
    print(str(ttotal//gcdd) + "/" + str(strlen**2//gcdd))
