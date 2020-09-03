


#include <iostream>
#include <stdio.h>
#include <cstring>
#include <queue>
#include <vector>
#include <fstream>
#include <string>
#include <memory.h>
#include <stack>
#include <limits.h>
#include <map>
#include <algorithm>
#include <set>
#include <thread>
#include <iterator>
#include <mutex>
#include <memory.h>
#include <unordered_map>
#include <ctime>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <chrono>
#include <fcntl.h>
//#include <bits/stdc++.h>
using namespace std;
#define N 2000002
#define M 100
#define REP(i, n) for (int i=0;i<int(n);++i)
#define REPV(i,n) for (int i = int(n)-1; i >=0; --i)
const int depth=2;
const int thread_num=100;
int e_num=0,e_b_num=0,num;
const int down=INT_MAX/5;
const int up=INT_MAX/3;
int head[N],tail[N];
int head_b[N],tail_b[N];
struct node1{
    int from=0;
    int to=0;
    int value=0;
}edge[N];
int time_dfs,time_bfs,find_way;
// mutex mtx;

char *index_id_c[N*2];
int index_id[N*2];
int index_id_len[N*2];

bool cmp_e(node1 a,node1 b){//排序逻辑
    if(a.from==b.from) return a.to<b.to;
    return a.from>b.from;
}

void add(int u,int v,int val){
    edge[e_num].from=u;
    edge[e_num].to=v;
    edge[e_num].value=val;
    e_num++;
}

struct node2{
    int from=0;//表示与第cnt条边同起点的上一条边的储存位置
    int to=0;
    int value=0;
}edge_b[N];

bool cmp_e_b(node2 a,node2 b){//排序逻辑
    if(a.from==b.from) return a.to<b.to;
    return a.from<b.from;
}

void add_b(int u,int v,int val){
    edge_b[e_b_num].from=u;
    edge_b[e_b_num].to=v;
    edge_b[e_b_num].value=val;
    e_b_num++;
}

struct node3
{
      int path[8];
};

unordered_map< int,  int> id_index;
vector<int> point [100];
int ret,ret3,ret4,ret5,ret6,ret7,size3,size4,size5,size6,size7;
mutex mtx;
bool notexsit[N*2];



 // char *ans3[N][30];

int tem[3][N];
int dic[N];

int v_size;
int G_num[N];
int G_b_num[N];
inline int digits10 (int n);
void read_data();
inline int myitoa(int num, char* str);
void search();
void tarjan(int node);
 // void write_ans();
void findPoint(int n,int num_t,bool *pre1,bool *pre2,bool *pre3,int *back_v);
void findPoint_1(int n);
void findPoint_2(int n);
void findPoint_3(int n);


inline int digits10 (int n) {
  if (n < 10) return 1;
  if (n < 100) return 2;
  if (n < 1000) return 3;
  if (n < 10000) return 4;
  if (n < 100000) return 5;
  if (n < 1000000) return 6;
  if (n < 10000000) return 7;
  if (n < 100000000) return 8;
  if (n < 1000000000) return 9;
  return 10;
}

inline int myitoa( int num, char* str)
{
    static const char index[201] = 
    "0001020304050607080910111213141516171819"
    "2021222324252627282930313233343536373839"
    "4041424344454647484950515253545556575859"
    "6061626364656667686970717273747576777879"
    "8081828384858687888990919293949596979899";
    uint32_t const length = digits10(num);
    uint32_t next = length-1;
    while(num>=100){
        auto const i = (num % 100)*2;
        num/=100;
        str[next]=index[i+1];
        str[next-1] =index[i];
        next-=2;
    }
    if (num<10){
        str[next]='0'+uint32_t(num);
    }
    else{
        auto i =uint32_t(num)*2;
        str[next]=index[i+1];
        str[next-1]=index[i];
    }
    return length;
}

bool exsit[1000001];
int num1,num2;

void map_1()
{
    sort(dic,dic+num);
    // for (int i=0;i<num2;i++)
    //   printf("%d ",dic[i]);
    //printf("good1\n");
    id_index[dic[0]]=num1;
    index_id_c[num1]=new char[16];
    index_id_len[num1]=myitoa(dic[0],index_id_c[num1]);
    num1++;
    for (int i = 1; i < num; i++){
        if (dic[i]!=dic[i-1]){
        num1++;
        id_index[dic[i]]=num1;
        index_id_c[num1]=new char[16];
        index_id_len[num1]=myitoa(dic[i],index_id_c[num1]);
      }
    }
}


void map_2(){
//printf("good2\n");
for (int i=0;i<=1000000;i++){
  if (exsit[i]){
    id_index[i]=num1;
    index_id_c[num1]=new char[16];
    index_id_len[num1]=myitoa(i,index_id_c[num1]);
    num1++;
  }
}
}


void read_data(){
   char *data = NULL;
   // int fd = open("data/test_data_1900.txt",00);
   // int fd = open("/data/test_data.txt",00);
   int fd = open("/huawei_com/test_data_1900.txt",00);
   // int fd = open("test_data.txt",00);
   // struct stat sb;
   long size = lseek(fd, 0, SEEK_END);
   data = (char *) mmap( NULL, size,PROT_READ, MAP_PRIVATE, fd, 0 );
   bool flag=0;
   num=0;
   num1=1;
   int int_num = 0;
   bool start_node = true;
   bool second_node = false;
   for (int i = 0; data[i] != '\0'; ++i){
       if (data[i] >= '0'&& data[i] <= '9'){
           int_num *= 10;
           int_num += data[i] - '0';
       }
       if (data[i] == ',' && start_node)
       {
            tem[num].a= int_num;
           dic[num] = int_num;
           start_node = false;
           second_node = true;
           int_num = 0;

       }else if (data[i] == ',' && second_node)
       {
           tem[num].b= int_num;
           second_node = false;
           int_num = 0;

       }else if (data[i]== '\n'){
           tem[num].c= int_num;
           start_node = true;
           int_num = 0;
           num++;
       }
   }
    if(flag==1||num<10000) map_1();
    else map_2();
    v_size=num1;
     // printf("%d \n",v_size );
    for(int i=0;i<num;i++){
        a=id_index[tem[0][i]];
        b=id_index[tem[1][i]];
        if(a==0||b==0) continue;
        c=tem[2][i];
        G_b_num[b]++;
        add_b(b,a,c);
        add(a,b,c);
    }
}



void mytopo() {
  int  v,a,b,c;
    queue<int> q;
    for (int i = 0; i < v_size; i++) {
        if (0 == G_b_num[i])
        {
          notexsit[i]=1;
          head_b[i]=-1;
          head[i]=-1;
            q.push(i);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for(int i=head_b[u];edge_b[i].from==u&&i<e_b_num;++i){
        v=edge_b[i].to;
            if (0 == --G_b_num[v])
                q.push(v);
        }
    }
    
    for (int i = 0; i < v_size; i++) {
        if (G_b_num[i] == 0) {
            // G_b[i].clear();
            notexsit[i]=1;
           head_b[i]=-1;
          head[i]=-1;
        }
    }

}


inline bool check(int x, int y) {
   if (y<=down) if(x>5*y)  return true;
    if (x<=up) if(y>x+x+x ) return true;
   return false;
}


//thread1
void dfs2_0();
void dfs3_0(int &p1);
void dfs4_0(int &p2,int &v3);
void dfs5_0(int &p2,int &v4);


struct pre_path_2
{
  int from;
    int to[2];
    int s_val,e_val;//e means edge touching with  
}pre_edge_2[thread_num][N/thread_num];



int head_pre_2[thread_num][N];
int pre_num_2[thread_num];
int head_pre_3[thread_num][N];
int pre_num_3[thread_num];
node3 record_0[thread_num];


struct pre_path_3
{
    int from;
    int to[3];
    int s_val,e_val;
}pre_edge_3[thread_num][N/thread_num];


bool cmp_pre_2(pre_path_2 a,pre_path_2 b){//排序逻辑
    if(a.from==b.from) {
      if(a.to[0]== b.to[0])return  a.to[1]< b.to[1];
      return a.to[0]< b.to[0];
    }
    return a.from<b.from;
}


bool cmp_pre_3(pre_path_3 a,pre_path_3 b){//排序逻辑
    if(a.from==b.from) {
      if(a.to[0]== b.to[0]) {
         if(a.to[1]== b.to[1])return  a.to[2]< b.to[2];
        return  a.to[1]< b.to[1];
      }
      return a.to[0]< b.to[0];
    }
    return a.from<b.from;
}



void add_pre_path_2(int u,int p1,int s_val, int e_val,int num_t){
    pre_edge_2[num_t][pre_num_2[num_t]].to[0]=p1;//第cnt条边的终点是v
    pre_edge_2[num_t][pre_num_2[num_t]].from=u;//head[i]表示以i起点的最后一条边的储存位置
    pre_edge_2[num_t][pre_num_2[num_t]].s_val=s_val;
    pre_edge_2[num_t][pre_num_2[num_t]].e_val=e_val;
    pre_num_2[num_t]++;//head[];
}


void add_pre_path_3(int u,int p1,int p2, int s_val, int e_val,int num_t){
    pre_edge_3[num_t][pre_num_3[num_t]].to[0]=p1;//第cnt条边的终点是v
    pre_edge_3[num_t][pre_num_3[num_t]].to[1]=p2;//第cnt条边的终点是v
    pre_edge_3[num_t][pre_num_3[num_t]].from=u;//head[i]表示以i起点的最后一条边的储存位置
    pre_edge_3[num_t][pre_num_3[num_t]].s_val=s_val;
    pre_edge_3[num_t][pre_num_3[num_t]].e_val=e_val;
    pre_num_3[num_t]++;//head[];
}


int size3_0[thread_num];
int ret3_0[thread_num];
int size4_0[thread_num],ret4_0[thread_num];
int size5_0[thread_num],ret5_0[thread_num];
int size6_0[thread_num],ret6_0[thread_num];
int size7_0[thread_num],ret7_0[thread_num];
char *answer3_0[thread_num];
char *answer4_0[thread_num];
char *answer5_0[thread_num];
char *answer6_0[thread_num];
char *answer7_0[thread_num];
char *ans3_pointer_0[thread_num];
char *ans4_pointer_0[thread_num];
char *ans5_pointer_0[thread_num];
char *ans6_pointer_0[thread_num];
char *ans7_pointer_0[thread_num];


void addpath3_0(int num_t,int point_0){
    char *start=answer3_0[num_t];
    ret3_0[num_t]+=1;
    memcpy(answer3_0[num_t],index_id_c[point_0],index_id_len[point_0]);
    answer3_0[num_t]+=index_id_len[point_0];
    *answer3_0[num_t]=','; answer3_0[num_t]+=1;
    memcpy(answer3_0[num_t],index_id_c[record_0[num_t].path[0]],index_id_len[record_0[num_t].path[0]]);
    answer3_0[num_t]+=index_id_len[record_0[num_t].path[0]];
    *answer3_0[num_t]=','; answer3_0[num_t]+=1;
    memcpy(answer3_0[num_t],index_id_c[record_0[num_t].path[1]],index_id_len[record_0[num_t].path[1]]);
    answer3_0[num_t]+=index_id_len[record_0[num_t].path[1]];
    *answer3_0[num_t]='\n'; answer3_0[num_t]+=1;
    size3_0[num_t]+=answer3_0[num_t]-start;
}


void addpath4_0(int num_t,int point_0){
    char *start=answer4_0[num_t];
    ret4_0[num_t]+=1;
    memcpy(answer4_0[num_t],index_id_c[point_0],index_id_len[point_0]);
    answer4_0[num_t]+=index_id_len[point_0];
    *answer4_0[num_t]=','; answer4_0[num_t]+=1;
    memcpy(answer4_0[num_t],index_id_c[record_0[num_t].path[0]],index_id_len[record_0[num_t].path[0]]);
    answer4_0[num_t]+=index_id_len[record_0[num_t].path[0]];
    *answer4_0[num_t]=','; answer4_0[num_t]+=1;
    memcpy(answer4_0[num_t],index_id_c[record_0[num_t].path[1]],index_id_len[record_0[num_t].path[1]]);
    answer4_0[num_t]+=index_id_len[record_0[num_t].path[1]];
    *answer4_0[num_t]=','; answer4_0[num_t]+=1;
    memcpy(answer4_0[num_t],index_id_c[record_0[num_t].path[2]],index_id_len[record_0[num_t].path[2]]);
    answer4_0[num_t]+=index_id_len[record_0[num_t].path[2]];
    *answer4_0[num_t]='\n'; answer4_0[num_t]+=1;
    size4_0[num_t]+=answer4_0[num_t]-start;
}

void addpath5_0(int num_t,int point_0){
    char *start=answer5_0[num_t];
    ret5_0[num_t]+=1;
    memcpy(answer5_0[num_t],index_id_c[point_0],index_id_len[point_0]);
    answer5_0[num_t]+=index_id_len[point_0];
    *answer5_0[num_t]=','; answer5_0[num_t]+=1;
    memcpy(answer5_0[num_t],index_id_c[record_0[num_t].path[0]],index_id_len[record_0[num_t].path[0]]);
    answer5_0[num_t]+=index_id_len[record_0[num_t].path[0]];
    *answer5_0[num_t]=','; answer5_0[num_t]+=1;
    memcpy(answer5_0[num_t],index_id_c[record_0[num_t].path[1]],index_id_len[record_0[num_t].path[1]]);
    answer5_0[num_t]+=index_id_len[record_0[num_t].path[1]];
    *answer5_0[num_t]=','; answer5_0[num_t]+=1;
    memcpy(answer5_0[num_t],index_id_c[record_0[num_t].path[2]],index_id_len[record_0[num_t].path[2]]);
    answer5_0[num_t]+=index_id_len[record_0[num_t].path[2]];
    *answer5_0[num_t]=','; answer5_0[num_t]+=1;
    memcpy(answer5_0[num_t],index_id_c[record_0[num_t].path[3]],index_id_len[record_0[num_t].path[3]]);
    answer5_0[num_t]+=index_id_len[record_0[num_t].path[3]];
    *answer5_0[num_t]='\n'; answer5_0[num_t]+=1;
    size5_0[num_t]+=answer5_0[num_t]-start;
}


void addpath6_0(int num_t,int point_0){
    char *start=answer6_0[num_t];
    ret6_0[num_t]+=1;
    memcpy(answer6_0[num_t],index_id_c[point_0],index_id_len[point_0]);
    answer6_0[num_t]+=index_id_len[point_0];
    *answer6_0[num_t]=','; answer6_0[num_t]+=1;
    memcpy(answer6_0[num_t],index_id_c[record_0[num_t].path[0]],index_id_len[record_0[num_t].path[0]]);
    answer6_0[num_t]+=index_id_len[record_0[num_t].path[0]];
    *answer6_0[num_t]=','; answer6_0[num_t]+=1;
    memcpy(answer6_0[num_t],index_id_c[record_0[num_t].path[1]],index_id_len[record_0[num_t].path[1]]);
    answer6_0[num_t]+=index_id_len[record_0[num_t].path[1]];
    *answer6_0[num_t]=','; answer6_0[num_t]+=1;
    memcpy(answer6_0[num_t],index_id_c[record_0[num_t].path[2]],index_id_len[record_0[num_t].path[2]]);
    answer6_0[num_t]+=index_id_len[record_0[num_t].path[2]];
    *answer6_0[num_t]=','; answer6_0[num_t]+=1;
    memcpy(answer6_0[num_t],index_id_c[record_0[num_t].path[3]],index_id_len[record_0[num_t].path[3]]);
    answer6_0[num_t]+=index_id_len[record_0[num_t].path[3]];
    *answer6_0[num_t]=','; answer6_0[num_t]+=1;
    memcpy(answer6_0[num_t],index_id_c[record_0[num_t].path[4]],index_id_len[record_0[num_t].path[4]]);
    answer6_0[num_t]+=index_id_len[record_0[num_t].path[4]];
    *answer6_0[num_t]='\n'; answer6_0[num_t]+=1;
    size6_0[num_t]+=answer6_0[num_t]-start;
}


void addpath7_0(int num_t,int point_0){
     char *start=answer7_0[num_t];
     ret7_0[num_t]+=1;
     memcpy(answer7_0[num_t],index_id_c[point_0],index_id_len[point_0]);
     answer7_0[num_t]+=index_id_len[point_0];
     *answer7_0[num_t]=','; answer7_0[num_t]+=1;
     memcpy(answer7_0[num_t],index_id_c[record_0[num_t].path[0]],index_id_len[record_0[num_t].path[0]]);
     answer7_0[num_t]+=index_id_len[record_0[num_t].path[0]];
     *answer7_0[num_t]=','; answer7_0[num_t]+=1;
     memcpy(answer7_0[num_t],index_id_c[record_0[num_t].path[1]],index_id_len[record_0[num_t].path[1]]);
     answer7_0[num_t]+=index_id_len[record_0[num_t].path[1]];
     *answer7_0[num_t]=','; answer7_0[num_t]+=1;
     memcpy(answer7_0[num_t],index_id_c[record_0[num_t].path[2]],index_id_len[record_0[num_t].path[2]]);
     answer7_0[num_t]+=index_id_len[record_0[num_t].path[2]];
     *answer7_0[num_t]=','; answer7_0[num_t]+=1;
     memcpy(answer7_0[num_t],index_id_c[record_0[num_t].path[3]],index_id_len[record_0[num_t].path[3]]);
     answer7_0[num_t]+=index_id_len[record_0[num_t].path[3]];
     *answer7_0[num_t]=','; answer7_0[num_t]+=1;
     memcpy(answer7_0[num_t],index_id_c[record_0[num_t].path[4]],index_id_len[record_0[num_t].path[4]]);
     answer7_0[num_t]+=index_id_len[record_0[num_t].path[4]];
     *answer7_0[num_t]=','; answer7_0[num_t]+=1;
     memcpy(answer7_0[num_t],index_id_c[record_0[num_t].path[5]],index_id_len[record_0[num_t].path[5]]);
     answer7_0[num_t]+=index_id_len[record_0[num_t].path[5]];
     *answer7_0[num_t]='\n'; answer7_0[num_t]+=1;
     size7_0[num_t]+=answer7_0[num_t]-start;
}



int n_t;
void find_thread(){
   int vsize=v_size+1; 
   bool vis[vsize];
   bool pre1[vsize],pre2[vsize],pre3[vsize];
   int back_v[vsize];
   int num_t;
   while(1){
     auto start = chrono::steady_clock::now();

   mtx.lock();
      num_t=n_t;
   n_t++;
   mtx.unlock();
        if (num_t<100)
          REP(i,point[num_t].size()){
                          findPoint(point[num_t][i],num_t,pre1,pre2,pre3,back_v);
          }
   
   else return;

 auto end = chrono::steady_clock::now();
 auto diff = end - start;
 cout << "DFS Time  " << chrono::duration <double> (diff).count() << " s" << endl;
}
}
// char check_f[10000][10000];

void findPoint(int n,int num_t,bool *pre1,bool *pre2,bool *pre3,int *back_v)
{
    int v2,v1,v3,v4,p1,p2,p3,p4;
    int vsize=v_size+1;
    int point_0=n;
    pre_num_2[num_t]=0;
    pre_num_3[num_t]=0;
    memset(pre1, 0, (vsize)*sizeof(bool));
    memset(pre2, 0, (vsize)*sizeof(bool));
    memset(pre3, 0, (vsize)*sizeof(bool));
    for(int i1=head_b[point_0];i1<tail_b[point_0];++i1){
         p1=edge_b[i1].to;
         v1=edge_b[i1].value;
         if (p1<=point_0) continue;
         pre1[p1]=1;
         back_v[p1]=v1;
        for(int i2=head_b[p1];i2<tail_b[p1];++i2){
            p2=edge_b[i2].to;
            if (p2<point_0) continue;
            v2=edge_b[i2].value;
            if (check(v2,v1))  continue;
            pre2[p2]=true;
            add_pre_path_2(p2,p1,v1,v2,num_t);
            for(int i3=head_b[p2];i3<tail_b[p2];++i3){
                p3=edge_b[i3].to;
                if (p3<point_0) continue;
                if (p3==p1) continue;
                v3=edge_b[i3].value;
                if (check(v3,v2))  continue;
                pre3[p3]=true;
                add_pre_path_3(p3,p2,p1,v1,v3,num_t);
            }
        }
    }
    sort(pre_edge_2[num_t],pre_edge_2[num_t]+pre_num_2[num_t],cmp_pre_2);
    head_pre_2[num_t][pre_edge_2[num_t][0].from]=0;
    for(int i=1;i<pre_num_2[num_t];i++){
    if(pre_edge_2[num_t][i].from!=pre_edge_2[num_t][i-1].from)//确定起点为Vi的第一条边的位置
        head_pre_2[num_t][pre_edge_2[num_t][i].from]=i;
}
    sort(pre_edge_3[num_t],pre_edge_3[num_t]+pre_num_3[num_t],cmp_pre_3);
    head_pre_3[num_t][pre_edge_3[num_t][0].from]=0;
    for(int i=1;i<pre_num_3[num_t];i++){
    if(pre_edge_3[num_t][i].from!=pre_edge_3[num_t][i-1].from)//确定起点为Vi的第一条边的位置
        head_pre_3[num_t][pre_edge_3[num_t][i].from]=i;
}

    for(int i1=head[point_0];i1<tail[point_0];++i1){
        int p1=edge[i1].to;
        int v1_0=edge[i1].value;
        if (p1<=point_0) continue;
        record_0[num_t].path[0]=p1;
        for(int i2=head[p1];i2<tail[p1];++i2){
           int p2=edge[i2].to;
           if (p2<=point_0) continue;
           v2=edge[i2].value;
           if (check(v1_0,v2))  continue;
           record_0[num_t].path[1]=p2;
           if(pre1[p2]==1){
             if (!(check(v2,back_v[p2])||check(back_v[p2],v1_0)) )     addpath3_0(num_t,point_0);
          }
            for(int i3=head[p2];i3<tail[p2];++i3){
               p3=edge[i3].to;
               if (p3<=point_0) continue;
               if (p3==p1) continue;
               v3=edge[i3].value;
               if (check(v2,v3)) continue;
               record_0[num_t].path[2]=p3;
               if(pre1[p3]==1){
               if (!(check(v3,back_v[p3])||check(back_v[p3],v1_0)) )
               addpath4_0(num_t,point_0);
               }
                for(int i4=head[p3];i4<tail[p3];++i4){
                   p4=edge[i4].to;
                   if (p4<=point_0) continue;
                   if (p4==p1||p4==p2) continue;
                   if (pre1[p4]==0 && pre2[p4]==0 && pre3[p4]==0) continue;
                   v4=edge[i4].value;
                   if (check(v3,v4)) continue;
                   record_0[num_t].path[3]=p4;
                   if(pre1[p4]==1)  {if (!(check(v4,back_v[p4])||check(back_v[p4],v1_0)))  addpath5_0(num_t,point_0);}
                   if(pre2[p4]==1){
                    for(int i=head_pre_2[num_t][p4];pre_edge_2[num_t][i].from==p4&&i<pre_num_2[num_t];++i){
                       int p5=pre_edge_2[num_t][i].to[0];
                       if(p5==p1||p5==p2||p5==p3) continue;
                       if (check(v4,pre_edge_2[num_t][i].e_val)||check(pre_edge_2[num_t][i].s_val,v1_0)) continue;
                       record_0[num_t].path[4]=pre_edge_2[num_t][i].to[0];
                       addpath6_0(num_t,point_0);
                       }
                       }
                       if(pre3[p4]==1){
                            for(int i=head_pre_3[num_t][p4];pre_edge_3[num_t][i].from==p4&&i<pre_num_3[num_t];++i){
                               int p5=pre_edge_3[num_t][i].to[0];
                               int p6=pre_edge_3[num_t][i].to[1];
                               if(p6==p1||p2==p6||p6==p3) continue;
                               if(p5==p1||p5==p2||p5==p3) continue;
                               if (check(v4,pre_edge_3[num_t][i].e_val)||check(pre_edge_3[num_t][i].s_val,v1_0)) continue;
                               record_0[num_t].path[4]=pre_edge_3[num_t][i].to[0];
                               record_0[num_t].path[5]=pre_edge_3[num_t][i].to[1];
                               addpath7_0(num_t,point_0);
                               }
                               }
        }
    }
}
}
}



void search(){
    thread task[4];
    for(int i=0;i<4;i++){
        task[i]=thread(find_thread);
    }
    for(int i=0;i<4;i++){
    if (task[i].joinable())  task[i].join();
    }
}

void write_ans()
{
      FILE *fd = fopen("/huawei_com/sample.out", "w");
    // FILE *fd = fopen("/projects/student/result.txt", "w");   
     fprintf(fd, "%d\n", ret);
     for(int i=0;i<thread_num;i++)
     fwrite(ans3_pointer_0[i],1,size3_0[i],fd);
     for(int i=0;i<thread_num;i++)
     fwrite(ans4_pointer_0[i],1,size4_0[i],fd);
     for(int i=0;i<thread_num;i++)
     fwrite(ans5_pointer_0[i],1,size5_0[i],fd);
     for(int i=0;i<thread_num;i++)
     fwrite(ans6_pointer_0[i],1,size6_0[i],fd);
     for(int i=0;i<thread_num;i++)
     fwrite(ans7_pointer_0[i],1,size7_0[i],fd);
     fclose(fd);
}

void validation()
{
    ifstream ansFile("/huawei_com/sample.out");
    ifstream resultFile("ans_2");
    bool same = true;
    int wrong=0;
    while (not ansFile.eof() and not resultFile.eof())
    {
        string l1, l2;   
        getline(ansFile, l1);
        getline(resultFile, l2); 
        if (l1 != l2)
        {
          wrong++;
            same = false;
            cout << endl << l1 << endl << l2 << endl;
            if(wrong>10) break;
        }
    }
    if (not ansFile.eof() or not resultFile.eof()) same = false;
    ansFile.close();
    resultFile.close();
    if (same) cout << "Validation: right\n";
    else cout << "Validation: wrong\n";
}


int main()
{
    //printf("start\n");
    memset(head,-1,N*sizeof(int));
    memset(head_b,-1,N*sizeof(int));
	read_data();
    sort(edge_b,edge_b+e_b_num,cmp_e_b);
    //printf("!!!\n");
    head_b[edge_b[0].from]=0;
    for (int i = 1; i < e_b_num+1; ++i)
    {
    if(edge_b[i].from!=edge_b[i-1].from){
        head_b[edge_b[i].from]=i;
        tail_b[edge_b[i-1].from]=i;
    }
    }
    tail[edge_b[e_b_num-1].from]=e_b_num;
    mytopo() ;
    sort(edge,edge+e_num,cmp_e);
    head[edge[0].from]=0;

    for(int i=1;i<e_num+1;i++){
        if(edge[i].from!=edge[i-1].from){
            head[edge[i].from]=i;
            tail[edge[i-1].from]=i;
        }
    }
             tail[edge[e_num-1].from]=e_num;
    // for(int p1=0;p1<=num;p1++){
    //                   for(int i2=head[p1];edge[i2].from==p1&&i2<num+1;++i2){
    //             printf("%d %d %d\n",edge[i2].from,edge[i2].to,edge[i2].value );
    //             }}
    //           printf("!!!\n");

    int cnt=0;
    for(int i=0;i<v_size;i=i+1){
       if (notexsit[i]==0) {
        cnt++;
      }
    }
    cnt=cnt/100;
    int cut=1,cnt2=0;
    for (int i=0;i<v_size;i++){
    if (notexsit[i]==0){
      if(cnt2>cnt*cut && cut<99)   cut++;
        point[cut-1].emplace_back(i);
      cnt2++;
    }
    }
    for(int i=0;i<thread_num;i++){
        answer3_0[i]=new char[40*1024*1024];
        answer4_0[i]=new char[80*1024*1024];
        answer5_0[i]=new char[80*1024*1024];
        answer6_0[i]=new char[120*1024*1024];
        answer7_0[i]=new char[200*1024*1024];
        ans3_pointer_0[i]=answer3_0[i];
        ans4_pointer_0[i]=answer4_0[i];
        ans5_pointer_0[i]=answer5_0[i];
        ans6_pointer_0[i]=answer6_0[i];
        ans7_pointer_0[i]=answer7_0[i];
    }

    auto start = chrono::steady_clock::now();
    //printf("searching %d\n",v_size);
    search();
    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    time_t t2 =clock();
    //printf("%d dfs_time=%d bfs_time=%d find_way=%d\n",ret,time_dfs,time_bfs,find_way);
    //cout << "DFS Time  " << chrono::duration <double> (diff).count() << " s" << endl;
    for (int i=0;i<thread_num;i++)
    ret+=(ret3_0[i]+ret4_0[i]+ret5_0[i]+ret6_0[i]+ret7_0[i]);
    //printf("ret=%d\n",ret );
    write_ans();
    time_t t3 =clock();
    //cout << "writing Time : " <<(double)(t3 - t2) / CLOCKS_PER_SEC<< "s" << endl;
    validation();
    return 0;
}


