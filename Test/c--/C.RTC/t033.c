int f1();
_IA *f2();
static int a=1;
static int b=2;
static _IA *c;
static _RA *d;
typedef struct _X X;
struct _X {
int b;
int a;
};
static X *e;
static void f3(){
((*_ICA(c,1,__FILE__,__LINE__))=(b=((a*b)+(*_ICA((*_RCA(d,(5+(((X*)_CP(e,__FILE__,__LINE__))->a)),__FILE__,__LINE__)),(((((*_ICA(c,4,__FILE__,__LINE__))+5)+(*_ICA(c,6,__FILE__,__LINE__)))+f1())+b),__FILE__,__LINE__)))));
}
