DLX重复覆盖对于当前矩阵的处理是，将当前列去掉，并将选作当前列的解的行能够覆盖到的列全部去掉。因为不需要每列仅由一个1去覆盖，因此不必要把能够覆盖某一列的所有行全部去掉。因此remove和resume函数的写法将会有所不同（具体可参考下面我写的代码）

第二个区别是，由于矩阵密度下降会变慢（因为去掉的少了），因此要加上一个强剪枝。这个剪枝利用的思想是A*搜索中的估价函数。即，对于当前的递归深度K下的矩阵，估计其最好情况下（即最少还需要多少步）才能出解。也就是，如果将能够覆盖当前列的所有行全部选中，去掉这些行能够覆盖到的列，将这个操作作为一层深度。重复此操作直到所有列全部出解的深度是多少。如果当前深度加上这个估价函数返回值，其和已然不能更优（也就是已经超过当前最优解），则直接返回，不必再搜。（具体可参考下面我写的代码）
1.模板

    #include<cstdio>  
    #define N 2011  
    #define M 102011  
    int U[M],D[M],L[M],R[M],C[M],X[M];//x代表M所属的行，c代表M所属的列，U，D，L，R为一个元素的上下左右指针  
    int H[N],S[N],Q[N];//H是水平循环链表的头指针，S代表每一列的元素个数，Q存储一个可能结果  
      
    int size,n,m;  
    void remove(int c)  
    {  
        R[L[c]]=R[c],L[R[c]]=L[c];  
        for(int i=D[c]; i!=c; i=D[i])  
            for(int j=R[i]; j!=i; j=R[j])  
                U[D[j]]=U[j],D[U[j]]=D[j],--S[C[j]];  
    }  
    void resume(int c)  
    {  
        R[L[c]]=L[R[c]]=c;  
        for(int i=U[c]; i!=c; i=U[i])  
            for(int j=L[i]; j!=i; j=L[j])  
                ++S[C[U[D[j]]=D[U[j]]=j]];  
    }  
    bool Dance(int k)  
    {  
        int i,j,tmp,c;  
        if(!R[0])  
        {  
            printf("%d",k);  
            for(i=0; i<k; ++i)printf(" %d",X[Q[i]]);  
            puts("");  
            return 1;  
        }  
        for(tmp=N,i=R[0]; i; i=R[i])  
            if(S[i]<tmp)tmp=S[c=i];  
        remove(c);  
        for(i=D[c]; i!=c; i=D[i])  
        {  
            Q[k]=i;  
            for(j=R[i]; j!=i; j=R[j])remove(C[j]);  
            if(Dance(k+1))return 1;  
            for(j=L[i]; j!=i; j=L[j])resume(C[j]);//在这里我遵循的原则是先删除的后还原，后删除的先还原。  
        }  
        resume(c);  
        return 0;  
    }  
    void Link(int r,int c)  
    {  
        ++S[C[size]=c];  
        D[size]=D[c];  
        U[D[c]]=size;  
        U[size]=c;  
        D[c]=size;  
        if(H[r]<0)H[r]=L[size]=R[size]=size;  
        else  
        {  
            R[size]=R[H[r]];  
            L[R[H[r]]]=size;  
            L[size]=H[r];  
            R[H[r]]=size;  
        }  
        X[size++]=r;  
    }  
    int main()  
    {  
        int i,j,num;  
        while(scanf("%d%d",&n,&m)!=EOF)  
        {  
            for(i=0; i<=m; ++i)  
            {  
                S[i]=0;  
                D[i]=U[i]=i;  
                L[i+1]=i;  
                R[i]=i+1;  
            }  
            R[m]=0;  
            L[0]=m;  
            size=m+1;  
            for(i=1; i<=n; ++i)  
            {  
                H[i]=-1;  
                scanf("%d",&num);  
                while(num--)scanf("%d",&j),Link(i,j);  
            }  
            if(!Dance(0))puts("NO");  
        }  
        return 0;  
    }  
2.
建图还是坑了我一下午。。。。终于把数独搞定了(囧)

具体细节我加了注释
[html] view plaincopy

    #include<cstdio>  
    #define inf 1e8  
    #define M 9*9*9*9*9*4+100  
    #define N 9*9*9+100   
    int U[M],D[M],L[M],R[M],C[M],X[M];//x代表M所属的行，c代表M所属的列，U，D，L，R为一个元素的上下左右指针  
    int H[N],S[N],Q[N];//H是水平循环链表的头指针，S代表每一列的元素个数，Q存储一个可能结果  
    char map[100];  
    bool v[N];  
    int size;  
    void remove(int c)  
    {  
        R[L[c]]=R[c],L[R[c]]=L[c];  
        for(int i=D[c]; i!=c; i=D[i])  
            for(int j=R[i]; j!=i; j=R[j])  
                U[D[j]]=U[j],D[U[j]]=D[j],--S[C[j]];  
    }  
    void resume(int c)  
    {  
        R[L[c]]=L[R[c]]=c;  
        for(int i=U[c]; i!=c; i=U[i])  
            for(int j=L[i]; j!=i; j=L[j])  
                ++S[C[U[D[j]]=D[U[j]]=j]];  
    }  
    bool Dance(int k)  
    {  
        int i,j,tmp,c;  
        if(!R[0])  
        {  
            for(i=0;i<k;i++)       
                map[X[Q[i]]/9]=X[Q[i]]%9+1+'0';  
            for(i=0;i<81;++i)  
                printf("%c",map[i]);  
            puts("");  
            return 1;  
        }  
        for(tmp=inf,i=R[0];i;i=R[i])  
            if(S[i]<tmp)tmp=S[c=i];  
        remove(c);  
        for(i=D[c]; i!=c; i=D[i])  
        {  
            Q[k]=i;  
            for(j=R[i]; j!=i; j=R[j])remove(C[j]);  
            if(Dance(k+1))return 1;  
            for(j=L[i]; j!=i; j=L[j])resume(C[j]);//在这里我遵循的原则是先删除的后还原，后删除的先还原。  
        }  
        resume(c);  
        return 0;  
    }  
    void Link(int r,int c)  
    {  
        ++S[C[size]=c];  
        D[size]=D[c];  
        U[D[c]]=size;  
        U[size]=c;  
        D[c]=size;  
        if(H[r]<0)H[r]=L[size]=R[size]=size;  
        else  
        {  
            R[size]=R[H[r]];  
            L[R[H[r]]]=size;  
            L[size]=H[r];  
            R[H[r]]=size;  
        }  
        X[size++]=r;  
    }  
    void prepare(int m)  
    {  
        int i,j,num;  
        for(i=0; i<=m; ++i)   //注意列下标是从1开始到m.  
        {  
            S[i]=0;  
            D[i]=U[i]=i;  
            L[i+1]=i;  
            R[i]=i+1;  
        }  
        R[m]=0;  
        L[0]=m;  
        size=m+1;  
        for(i=0;i<=N;++i)  
            H[i]=-1;  
    }  
    void cal(int &r,int &cx,int &cy,int &cg,int &ck,int i,int j,int k){  
        r=(i*9+j)*9+k-1;            //第几行（行）  
        cg=i*9+j+1;                //第几个格子（列）       这里必须从1开始（我在这里WA了多次）  
        cx=81+i*9+k;              //第i行上的k（列）  
        cy=81*2+j*9+k;           //第j列上的k（列）  
        ck=81*3+(i/3*3+j/3)*9+k;//第某个宫上的k（列）  
    }  
    int main(){  
        int i,j,k;  
        int tx,ty;  
        int r,cx,cy,cg,ck;  
        while(scanf("%s",map) && map[0]!='e'){  
            prepare(9*9*4);  
            for(i=1;i<=N;++i)v[i]=0;  
              
            for(i=0;i<=80;i++){  
                if(map[i]=='.'){  
                    for(j=1;j<=9;j++){  
                        tx=i/9;ty=i%9;    //要得到行列坐标还是i循环从0开始比较好  
                        cal(r,cx,cy,cg,ck,tx,ty,j);  
                        Link(r,cx);Link(r,cy);Link(r,cg);Link(r,ck);  
                    }  
                }  
                else{  
                    tx=i/9;ty=i%9;  
                    cal(r,cx,cy,cg,ck,tx,ty,map[i]-'0');  
                    Link(r,cx);Link(r,cy);Link(r,cg);Link(r,ck);  
                }  
            }  
            Dance(0);  
        }  
    }  

还有我的建图还是太麻烦了

还有更快的。
[html] view plaincopy

    for(i=1;i<=N;++i)v[i]=0;  
            
    for(k=0,i=0;i<9;++i)  
                
        for(j=0;j<9;++j,++k)  
                
            if(map[k]>'0'&&map[k]<='9'){  
                    
                cal(r,c1,c2,c3,c4,i,j,map[k]-'0');  
                    
                Link(r,c1),Link(r,c2),Link(r,c3),Link(r,c4);  
                    
                v[c2]=v[c3]=v[c4]=1;  
                
            }  
            
    for(i=0;i<9;++i)  
                
        for(j=0;j<9;++j)  
                    
            for(k=1;k<=9;++k){  
      
                            cal(r,c1,c2,c3,c4,i,j,k);  
                        
                if(v[c2]||v[c3]||v[c4])continue;  
                        
                Link(r,c1),Link(r,c2),Link(r,c3),Link(r,c4);  
                    
            }  

这里v数组记录了已经选好的列（对应是数独里填好的数字），然后处理‘.’时就可以剪去一些节点（是通过九格宫）。

 

反正总之用dancing links解决EXACT COVER问题还是比较高效的。
