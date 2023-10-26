#include "BigInteger.h"


struct BigInteger initialize(char *s)
{
    int l=strlen(s);

    struct BigInteger A;
    A.length=l;

    A.L=(struct node*)malloc(sizeof(struct node));

    struct node *temp=A.L;

    int i=l-1;
    do
    {
        l-=1;
        temp->data=(int)(*(s+i)-48);
        if(l)
        {
            temp->next=(struct node*)malloc(sizeof(struct node));
            temp=temp->next;
        }
        i--;
    }while(l);

    temp->next=NULL;
    
    return A;
}



struct BigInteger rev(struct BigInteger A)
{
    struct node *curr=A.L, *next = A.L, *prev=NULL;

    while(curr)
    {
        next=curr->next;
        curr->next=prev;
        prev=curr;
        curr=next;
    }

    A.L=prev;

    return A;
}


struct BigInteger length(struct BigInteger A)
{
    int l=0;
    struct node *temp=A.L;

    while(temp)
    {
        l++;
        temp=temp->next;
    }

    A.length=l;
    return A;
}



void compare(struct BigInteger *A, struct BigInteger *B)
{
    if(A->L == NULL || B->L == NULL) return;

    if(A->length < B->length)
    {
        struct node *temp = A->L;
        A->L = B->L;
        B->L = temp; 
        int tempL=A->length;
        A->length=B->length;
        B->length=tempL;      
    }
}


void display(struct BigInteger A)
{
    if(!A.L)
    {
        printf("List is Empty!");
        return;
    }

    struct BigInteger temp=A;
    temp=rev(temp);

    struct node *tempNode=temp.L;

    while(tempNode!=NULL)
    {
        printf("%d",tempNode->data);
        tempNode=tempNode->next;
    }printf("\n");

    temp=rev(temp);
}



void free_list(struct node *head)
{
    struct node *temp;
    
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}


struct BigInteger remove1(struct BigInteger a)
{
    struct BigInteger x;
    x.L = a.L;

    x = rev(x);

    struct node *itr = x.L;

    while(itr && itr->data == 0 && itr->next)
    {
        struct node *tmp = itr;
        itr = itr->next;
        free(tmp);
    }

    x.L = itr;

    x = rev(x);

    return x;
}



int comp(struct BigInteger A, struct BigInteger B)
{
    if(A.length!=B.length)
    {
        return (A.length<B.length?1:0);
    }
    else
    {
        struct node *itr1=A.L, *itr2=B.L;

        while(itr1)
        {
            if(itr1->data < itr2->data)
            {
                return 1;
            }

            if(itr1->data > itr2->data)
            {
                return 0;
            }

            itr1=itr1->next;
            itr2=itr2->next;
        }
    }
    return 2;
}


struct node* addition(struct node *h, int d)
{
    struct node *temp=NULL;

    while(h)
    {
        if(temp==NULL)
        {
            temp=(struct node*)malloc(sizeof(struct node));
        }
        else
        {
            temp->next=(struct node*)malloc(sizeof(struct node));
            temp=temp->next;
        }

        temp->data=d;
        temp->next=NULL;

        h=h->next;
    }
    temp->next=NULL;
    return temp;
}



struct BigInteger add(struct BigInteger a, struct BigInteger b)
{
    if(a.L==NULL) return b;

    if(b.L==NULL) return a;

    compare(&a,&b);
    int c=0;

    struct BigInteger res; 
    res.L=NULL;

    struct node *sum=NULL;

    while(b.L!=NULL)
    {
        if(!res.L)
        {
            res.L=(struct node*)malloc(sizeof(struct node));
            sum=res.L;
        }
        else
        {
            sum->next=(struct node*)malloc(sizeof(struct node));
            sum=sum->next;
        }

        sum->data=(c + a.L->data + b.L->data)%10;
        c=(c + a.L->data + b.L->data)/10;

        a.L=a.L->next;
        b.L=b.L->next;
    }

    while(a.L!=NULL)
    {
        sum->next=(struct node*)malloc(sizeof(struct node));
        sum=sum->next;

        sum->data=(a.L->data + c)%10;

        c=(a.L->data + c)/10;
        a.L=a.L->next;
    }

    if(c!=0)
    {
        sum->next=(struct node*)malloc(sizeof(struct node));
        sum=sum->next;
        sum->data=c;
    }

    sum->next=NULL;
    return res;
}



struct BigInteger sub(struct BigInteger a, struct BigInteger b)
{
    if(comp(a, b)==1)
    {
        struct node *temp = a.L;
        a.L = b.L;
        b.L = temp; 
        int tempL=a.length;
        a.length=b.length;
        b.length=tempL; 
    }

    int bor=0;

    struct BigInteger res;
    res.L=NULL;

    struct node *sub=NULL, *prev=NULL;

    while(b.L!=NULL)
    {
        int v=a.L->data;
        if(!res.L)
        {
            res.L=(struct node*)malloc(sizeof(struct node));
            prev=sub;
            sub=res.L;
        }
        else
        {
            prev=sub;
            sub->next=(struct node*)malloc(sizeof(struct node));
            sub=sub->next;
        }

        if(bor==1) --v;

        if(v < b.L->data)
        {
            sub->data=(10+v)-b.L->data;
            bor=1;
        }
        else
        {
            sub->data=v - b.L->data;
            bor=0;
        }

        a.L=a.L->next;
        b.L=b.L->next;
    }
    
    while(a.L!=NULL)
    {
        int v=a.L->data;
        prev=sub;

        sub->next=(struct node*)malloc(sizeof(struct node));
        sub=sub->next;

        if(bor==1) --v;

        if(a.L->next==NULL && a.L->data==0)
        {
            free(sub);
            prev->next=NULL;
        }
        else if(v==-1)
        {
            sub->data=10+v;
            bor=1;
        }
        else
        {
            sub->data=v;
            bor=0;
        }

        a.L=a.L->next;
    }

    sub->next=NULL;

    return res;
}


struct BigInteger mul(struct BigInteger a, struct BigInteger b)
{
    struct BigInteger m=a;
    struct BigInteger res;
    res.L=NULL;

    int c=0,temp=c;

    while(b.L!=NULL)
    {
        int v=b.L->data;

        if(v==0)
        {
            m.L=addition(a.L, 0);
        }
        else
        {
            m.L=a.L;
        }

        if(v>0)
        {
            --v;
        }

        while(v--)
        {
            m=add(m, a);
        }

        temp=c;
        while(temp--)
        {
            struct node *new=(struct node*)malloc(sizeof(struct node));
            new->data=0;
            new->next=m.L;
            m.L=new;
        }

        c++;
        compare(&m, &res);

        res=add(m, res);

        b.L=b.L->next;
    }
    return res;
}


struct BigInteger div1(struct BigInteger A, struct BigInteger B)
{
    struct BigInteger C;
    C.L=(struct node*)malloc(sizeof(struct node));
    C.L->data=0;

    C.L->next=NULL;
    C.length=1;

    C=rev(C);

    struct BigInteger count;
    count.L=(struct node*)malloc(sizeof(struct node));
    count.L->data=1;

    count.L->next=NULL;
    count.length=1;

    struct BigInteger res=B;

    int l=0;

    while((comp(res=rev(res), A=rev(A))))
    {
        res=rev(res);
        A=rev(A);
        C=add(C,count);
        C=length(C);
        res=add(res, B);
        res=length(res);
    }

    res=rev(res);
    A=rev(A);

    return C;
}



struct BigInteger mod(struct BigInteger a, struct BigInteger b)
{
    struct BigInteger m=sub(a, mul(b, div1(a, b)));
    return m;
}