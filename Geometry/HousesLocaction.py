# Enter your code here. Read input from STDIN. Print output to STDOUT


class Cercle:
    def __init__(self,o,r):
        self.o=o
        self.r=r
    def inter(self,other):
        if self.o==other.o:
            if self.r==other.r:
                return((self.o[0]-self.r,self.o[1]))
            else:
                return("Impossible!")
        else:
            d=(self.o[0]-other.o[0])**2+(self.o[1]-other.o[1])**2
            if d>(self.r+other.r)**2:
                return("Impossible!")
            elif d==(self.r+other.r)**2:
                v=((other.o[0]-self.o[0])/d**0.5,(other.o[1]-self.o[1])/d**0.5)
                return((self.o[0]+self.r*v[0],self.o[1]+self.r*v[1]))
            else:
                a=d**0.5/2+(self.r**2-other.r**2)/(2*d**0.5)
                h=(self.r**2-a*a)**0.5
                v=((other.o[0]-self.o[0])/d**0.5,(other.o[1]-self.o[1])/d**0.5)
                w=(v[1],-v[0])
                return(min((self.o[0]+a*v[0]+h*w[0],self.o[1]+a*v[1]+h*w[1]),(self.o[0]+a*v[0]-h*w[0],self.o[1]+a*v[1]-h*w[1])))

def f(x):
    y=str(round(100*x))
    if len(y)<3:
        y="0"*(3-len(y))+y
    return(y[:-2]+"."+y[-2:])

a,b=map(int,input().split())
x1,y1=map(int,input().split())
x0,y0=map(int,input().split())
x3,y3=map(int,input().split())
x2,y2=map(int,input().split())
C=Cercle((x0-(x1-x0)/(a*a-1),y0-(y1-y0)/(a*a-1)),((x0-x1)**2+(y0-y1)**2)**0.5*a/(a*a-1))
CC=Cercle((x2-(x3-x2)/(b*b-1),y2-(y3-y2)/(b*b-1)),((x2-x3)**2+(y2-y3)**2)**0.5*b/(b*b-1))

z=C.inter(CC)
if type(z)==tuple:
    z=f(z[0])+" "+f(z[1])
print(z)
