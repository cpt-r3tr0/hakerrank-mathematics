# Enter your code here. Read input from STDIN. Print output to STDOUT

def tobinary(n):
  res=""
  while n>0:
    if n%2==0:
      res="0"+res
    else:
      res="1"+res
    n/=2
  return res

def calcstem(k,m):
  #calculate the number of 1s and the number of bits in the range with
  #stem k and m following bits.
  z=k.count("0")
  o=k.count("1")
  return (2*o+m)*2**m,2*(z+o+m)*2**m

def calcrange(a,b):
  #calculate the expected chance of getting a 1 and the expected number of 1s
  #per number in the range [a,b], and the number of numbers in the range
  alen=len(a)
  blen=len(b)
  if alen==blen:
    #the usual case
    #compare the initial digits to find the stem
    stem=""
    m=0
    for d in xrange(alen):
      if a[d]==b[d]:
        stem+=a[d]
      else:
        m=alen-d
        break
    if m==0 or (a[-m:]=="0"*m and b[-m:]=="1"*m):
      #we have the entire range of 2^m numbers with this stem
      numones,numbits=calcstem(stem,m)
      fracones=float(numones)/numbits
      expones=fracones*alen
      return fracones,expones,2**m
    else:
      #split the range in two and calculate each half
      frac1a,exp1a,numsa=calcrange(a,stem+"0"+"1"*(m-1))
      frac1b,exp1b,numsb=calcrange(stem+"1"+"0"*(m-1),b)
      fracones=(frac1a*numsa+frac1b*numsb)/(numsa+numsb)
      expones=(exp1a*numsa+exp1b*numsb)/(numsa+numsb)
      return fracones,expones,numsa+numsb
  else:
    #split the range by number of bits
    wfrac1=0.0
    wexp1=0.0
    tnums=0
    frac1,exp1,nums=calcrange(a,"1"*alen)
    wfrac1+=frac1*nums
    wexp1+=exp1*nums
    tnums+=nums
    for j in xrange(alen+1,blen):
      frac1,exp1,nums=calcrange("1"+"0"*(j-1),"1"*j)
      wfrac1+=frac1*nums
      wexp1+=exp1*nums
      tnums+=nums
    frac1,exp1,nums=calcrange("1"+"0"*(blen-1),b)
    wfrac1+=frac1*nums
    wexp1+=exp1*nums
    tnums+=nums
    return wfrac1/tnums,wexp1/tnums,tnums

t=input()
for j in xrange(t):
  a,b=map(int,raw_input().strip().split())
  res=calcrange(tobinary(a),tobinary(b))
  print "{:.5f} {:.5f}".format(res[0],res[1])
