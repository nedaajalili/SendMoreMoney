#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXW 9
#define MAXL 10

typedef struct{
    int val;
    char c;
}letter;

void readword(char *,char *,char *);
letter *allocation();
void letterOccur(letter*, char *, char *, char *, int *);
int findindex(letter *,char,int);
void test(letter*,int *, char *,char *,char *,int);
int checksol(letter *, char *,char *,char *,int);
int w2n(char *,letter *,int);
int solve(letter *,int *,int ,char *,char *,char *,int );
void display(letter *,int);

int main()
{
    char w1[MAXW],w2[MAXW],w3[MAXW];
    letter *letters;
    int usedletter=0;
    int mark[MAXL]={0};
    int cmd;
    readword(w1,w2,w3);
    printf("%s %s %s\n",w1, w2, w3);
    letters=allocation();
    letterOccur(letters,w1,w2,w3,&usedletter);
    printf("what do yo want to do? 1)test your own guess. 2)Let me solve it for you.\n");
    scanf("%d",&cmd);
    if(cmd==1){
        test(letters,mark,w1,w2,w3,usedletter);
    }else if(cmd==2){
        solve(letters,mark,0,w1,w2,w3,usedletter);
    }else{
        printf("wrong command!!");
    }
    return 0;
}
void readword(char *w1,char *w2,char *w3){
    printf("insert first word:\n");
    scanf("%s",w1);
    printf("insert second word:\n");
    scanf("%s",w2);
    printf("insert third word:\n");
    scanf("%s",w3);
    return;
}
letter *allocation(){
    int i;
    letter *letters=(letter *)malloc((MAXL)*sizeof(letter));
    if(letters==NULL){
        printf("error in allocating memory for letters!\n");
        exit(0);
    }
    for(i=0;i<MAXL;i++){
        letters[i].val=-1;
        letters[i].c='\0';
    }
    return letters;
}
void letterOccur(letter *letters, char *w1 ,char *w2, char *w3, int *usedletter){
    //all letters appear in my strings
    int i;
    for(i=0;i<strlen(w1);i++){
        if(findindex(letters,w1[i],*usedletter)==-1){
            letters[(*usedletter)++].c=w1[i];
        }
    }
    for(i=0;i<strlen(w2);i++){
        if(findindex(letters,w2[i],*usedletter)==-1){
            letters[(*usedletter)++].c=w2[i];
        }
    }for(i=0;i<strlen(w3);i++){
        if(findindex(letters,w3[i],*usedletter)==-1){
            letters[(*usedletter)++].c=w3[i];
        }
    }
}
int findindex(letter *letters,char find,int usedletter){
    int i;
    for(i=0;i<usedletter;i++)
        if(letters[i].c==find)
            return i;
        return -1;
}
void display(letter *letters,int usedletter){
    int i;
    for(i=0;i<usedletter;i++){
        printf("%c->%d\n",letters[i].c,letters[i].val);
    }
}
void test(letter *letters, int *mark,char *w1,char *w2,char *w3,int usedletter){
    int i,tmp;
    for(i=0;i<usedletter;i++){
        printf("you guess for %c value->",letters[i].c);
        scanf("%d",&tmp);
        mark[tmp]=1;
        letters[i].val=tmp;
    }
    if(checksol(letters,w1,w2,w3,usedletter)){
        printf("valid guess!");
    }else{
        printf("Not a valid guess!");
    }
}
int checksol(letter *letters, char *w1,char *w2,char *w3,int usedletter){
    int n1,n2,n3;
    n1=w2n(w1,letters,usedletter);
    n2=w2n(w2,letters,usedletter);
    n3=w2n(w3,letters,usedletter);
    if(n1==-1 || n2==-1 || n3==-1){
        return 0;
    }
    return ((n1+n2)==n3);
}
int w2n(char *w,letter *letters,int usedletter){
    int i,n=0;
    if(letters[findindex(letters,w[0],usedletter)].val==0)
        return -1;
    for(i=0;i<strlen(w);i++)//visit entire string,for each letter get value transform in to num
        n=n*10+letters[findindex(letters,w[i],usedletter)].val;

    return n;
}
int solve(letter *letters,int *mark,int pos,char *w1,char *w2,char *w3,int usedletter){
    int i,sol;
    if(pos>=usedletter){
        sol=checksol(letters,w1,w2,w3,usedletter);
        if(sol){
            display(letters,usedletter);
            return sol;
        }
    }
    for(i=0;i<MAXL;i++){
        if(mark[i]==0){
            mark[i]=1;
            letters[pos].val=i;
            if(solve(letters,mark,pos+1,w1,w2,w3,usedletter))
                return 1;
            mark[i]=0;
            letters[pos].val=-1;
        }
    }
    return 0;
}




