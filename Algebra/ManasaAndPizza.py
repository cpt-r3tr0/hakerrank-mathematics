# Enter your code here. Read input from STDIN. Print output to STDOUT

d,u,v = 10**9+7,[6,-1,1,0],[0,1,-1,6]
def ml(l,r):
  (x,y,z,w),(h,i,j,k) = l,r
  return (x*h+z*i)%d,(y*h+w*i)%d,(x*j+z*k)%d,(y*j+w*k)%d
def slv(l,r):
  if r == 0:
    return 1,0,0,1
  if r & 1:
    return ml(slv(l,r-1),l)
  return slv(ml(l,l),r//2)
n = int(input())
l = list(map(int,input().split()))
a = [1,0,0,1]
for i in l:
  x,y = slv(u,i),slv(v,i)
  a = ml(a,(x[0]+y[0],x[1]+y[1],x[2]+y[2],x[3]+y[3]))
a = ml(a,v)
print((3*a[0]+a[1])%d)
