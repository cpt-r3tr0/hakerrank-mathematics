# Enter your code here. Read input from STDIN. Print output to STDOUT

n = int(input())
block_belt = list(int(i) for i in input().split())
current_score = best_score = block_value_sum = 0
for i, val in enumerate(block_belt):
    block_value_sum+=val
    current_score+=(i+1)*val
best_score = current_score
for i in block_belt:
    current_score -= block_value_sum
    current_score += n * i
    best_score = max(best_score, current_score)
print(best_score)
