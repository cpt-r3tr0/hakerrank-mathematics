#include<cstdio>
#include<algorithm>
#include<cstring>
#define rep(i,x,y) for(int i=x;i<=y;++i)
#define dep(i,x,y) for(int i=x;i>=y;--i)
using namespace std;
#define N 100005

struct bst{
	bst *l,*r,*fa;
	int size;

	inline void updata(){
		size=1+(l?l->size:0)+(r?r->size:0);
	}

	inline bool top(){return !fa || fa && fa->l!=this && fa->r!=this;}

	inline void zig(){
		bst *y=fa,*z=y->fa;
		y->l=r;
		if(r) r->fa=y;
		r=y;
		y->fa=this;
		fa=z;
		if(z && z->l==y) z->l=this;
		if(z && z->r==y) z->r=this;
		y->updata();
	}

	inline void zag(){
		bst *y=fa,*z=y->fa;
		y->r=l;
		if(l) l->fa=y;
		l=y;
		y->fa=this;
		fa=z;
		if(z && z->l==y) z->l=this;
		if(z && z->r==y) z->r=this;
		y->updata();
	}

}t[N];

void splay(bst *x){
	while(!x->top()){
		bst *y=x->fa,*z=y->fa;
		if(!y->top()){
			if(z->l==y){
				if(y->l==x) y->zig(),x->zig();
				else x->zag(),x->zig();
			}else{
				if(y->r==x) y->zag(),x->zag();
				else x->zig(),x->zag();
			}
		}else{
			if(y->l==x) x->zig();
			else x->zag();
		}
	}
	x->updata();
}

bst *access(bst *x){
	bst *y=NULL;
	for(;x;y=x,x=x->fa){
		splay(x);
		x->r=y;
		x->updata();
	}
	return y;
}

int n,m,x,y,son[N],Next[N<<1],ed[N<<1],w[N],f[N][30];

void dfs(int x,int fa){
	f[x][0]=fa;
	rep(i,1,20) f[x][i]=f[f[x][i-1]][i-1];
	for(int j=son[x];j;j=Next[j])
		if(ed[j]^fa){
			t[ed[j]].fa=t+x;
			dfs(ed[j],x);
		}
}

int jump(int x,int w){
	dep(i,20,0) if(1<<i<w){
		w-=1<<i;
		x=f[x][i];
	}
	x=f[x][0];
	if(!x)x=1;
	return x;
}

bst *Right(bst *x){while(x->r) x=x->r;return x;}

void reset_w(int x,int w){
	int p=jump(x,w);
	bst *y=t+x;
	access(y);
	splay(y);
	access(Right(y->l));
	splay(y);
	y->fa=t+p;
}

int main(){
	scanf("%d%d",&n,&m);
	rep(i,1,n) scanf("%d",w+i);
	rep(i,2,n){
		scanf("%d%d",&x,&y);
		Next[i]=son[x],son[x]=i,ed[i]=y;
		Next[i+n]=son[y],son[y]=i+n,ed[i+n]=x;
	}
	rep(i,1,n) t[i].size=1;
	dfs(1,0);
	rep(i,2,n)
		reset_w(i,w[i]);
	while(m--){
		int opt;
		scanf("%d%d",&opt,&x);
		if(opt==1){
			scanf("%d",&y);
			if(x^1) reset_w(x,y);
		}else{
			bst *v=access(t+x);
			printf("%d\n",v->size-1);
		}
	}
}
