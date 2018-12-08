# Enter your code here. Read input from STDIN. Print output to STDOUT

def f(n, m, grid):
    # create the answer array
    ans = [[0]*m for i in xrange(n)]

    height = [0]*m
    left   = [0]*m
    right  = [0]*m

    for i in xrange(n):

        # calculate height
        for j in xrange(m):
            height[j] += 1
            height[j] *= grid[i][j]

        # calculate left
        stack = [-1]
        for j in xrange(m):
            while stack[-1] >= 0 and height[stack[-1]] > height[j]:
                stack.pop()
            left[j] = stack[-1]
            stack.append(j)

        # calculate right
        stack = [m]
        for j in xrange(m-1,-1,-1):
            while stack[-1] < m and height[stack[-1]] >= height[j]:
                stack.pop()
            right[j] = stack[-1]
            stack.append(j)

        # initialize counter structure
        present = set()
        count = [0]*m
        def add(v):
            if v < 0: return
            if not count[v]: present.add(v)
            count[v] += 1
        def rem(v):
            if v < 0: return
            count[v] -= 1
            if not count[v]: present.remove(v)

        add(m-1)

        # calculate events
        mheight = max(height)
        events = [[] for h in xrange(mheight)]
        for j in xrange(m):
            if height[j] < mheight:
                events[height[j]].append(j)

        # process events by height
        for h in xrange(mheight):

            # process events
            for e in events[h]:
                l = left[e]
                r = right[e]
                rem(r - l - 2)
                add(r - e - 2)
                add(e - l - 2)

            #assert len(present)**2 <= 2*m

            # update ans
            for w in present:
                ans[h][w] += count[w]

    # need a final DP to finish everything
    for i in xrange(n):
        for j in xrange(m-1,0,-1):
            if j >= 2:
                ans[i][j-2] -= ans[i][j]
            ans[i][j-1] += 2*ans[i][j]
        ans

    return ans

if __name__ == '__main__':
    # take input
    n, m = map(int, raw_input().strip().split())
    grid = [map(int, raw_input()) for i in xrange(n)]

    # calculate answer
    # The function f above runs in O(n^2 sqrt(m)) time,
    # so transpose the grid if necessary
    # zip(*x) is a nice Pythonic way to transpose x
    if n > m:
        ans = zip(*f(m, n, zip(*grid)))
    else:
        ans = f(n, m, grid)

    # print answer
    for row in ans:
        print ' '.join(map(str, row))
