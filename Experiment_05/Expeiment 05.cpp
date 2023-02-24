#include <iostream>
#include <math.h>
#include <time.h>
#include <vector>
using namespace std;
#define NOTPATH 99999


template <class Elem> class listNode{
public:
    Elem element;
    listNode* next;
    listNode(Elem& e,listNode* n=NULL){
        element=e;
        next=n;
    }
    listNode(listNode* n=NULL){
        next=n;
    }
};

template <class Elem> class Linked_list{
public:
    listNode<Elem>* head;
    listNode<Elem>* tail;
    listNode<Elem>* fence;
    int rightcnt,leftcnt;
    Linked_list(){
        head=tail=fence=new listNode<Elem>(NULL);
        leftcnt=0;
        rightcnt=1;
    }
    void clear(){
        while(head!=tail) {
            fence=head;
            head = head->next;
            delete fence;
        }
        rightcnt=leftcnt=0;
    }
    bool insert(Elem& e){
        fence->next=new listNode<Elem>(e,fence->next);
        if (fence==tail){
            tail=fence->next;
        }
        rightcnt++;
        return true;
    }
    bool append(Elem& e){
        tail->next=new listNode<Elem>(e,tail->next);
        tail=tail->next;
        rightcnt++;
        return true;
    }
    bool remove(Elem& it){
        if(fence==tail){return false;}
        listNode<Elem>* temp=fence->next;
        fence->next=fence->next->next;
        it=temp->element;
        delete temp;
        rightcnt--;
        return true;
    }
    void setStart(){
        fence=head;
        rightcnt=leftcnt+rightcnt;
    }
    void setEnd(){
        fence=tail;
        leftcnt=leftcnt+rightcnt;
    }
    void prev(){
        if(fence==head){return;}
        listNode<Elem>* temp=head;
        while(temp->next!=fence){
            temp=temp->next;
        }
        fence=temp;
        leftcnt--;
        rightcnt++;
    }
    void next(){
        if (fence==tail){return;}
        fence= fence->next;
        leftcnt++;
        rightcnt--;
    }
    int leftLength(){
        //左边的匣子数
        return leftcnt;
    }
    int rightLength(){
        return rightcnt;
    }
    bool setPos(int pos){
        if(rightcnt+leftcnt<=pos){return false;}
        fence=head;
        rightcnt=leftcnt+rightcnt;
        leftcnt=0;
        while(pos--){
            fence=fence->next;
            leftcnt++;
            rightcnt--;
        }
        return true;
    }
    bool getValue(Elem& it){
        if(fence==tail){return false;}
        it=fence->next->element;
        return true;
    }
    void print(){
        listNode<Elem>* temp=head;
        cout<<"< ";
        while(temp!=fence){
            cout<<temp->next->element<<" ";
        }
        cout<<"| ";
        while(temp!=tail){
            cout<<temp->next->element<<" ";
        }
        cout<<">"<<endl;
    }
};
class Graph{
public:
    Linked_list<int>** graph;
    int n;
    int e;
    int** Weight;
    bool* Mark;

    Graph(int tempn=7,int type=0){
        n=tempn;
        e =0;
        graph=new Linked_list<int>*[n];
        for(int i=0;i<n;i++){
            graph[i]=new Linked_list<int>();
        }
        Weight=new int*[n];
        for(int i=0;i<n;i++){
            Weight[i]=new int[n];
            for(int k=0;k<n;k++){
                if(i==k){Weight[i][k]=0;}
                else{Weight[i][k]=NOTPATH;}
            }
        }
        Mark=new bool[n];
        for(int i=0;i<n;i++){
            Mark[i]= false;
        }
        if(type==0) {
            setEdge(0, 1, 2);
            setEdge(0, 2, 3);
            setEdge(0, 3, 4);
            setEdge(1, 2, 3);
            setEdge(1, 4, 2);
            setEdge(2, 4, 2);
            setEdge(2, 5, 2);
            setEdge(3, 5, 2);
            setEdge(4, 5, 1);
            setEdge(4, 6, 3);
            setEdge(5, 6, 5);
        }
        if(type==1){
            setEdge(1, 0, 2);
            setEdge(2, 0, 3);
            setEdge(3, 0, 4);
            setEdge(2, 1, 3);
            setEdge(4, 1, 2);
            setEdge(4, 2, 2);
            setEdge(5, 2, 2);
            setEdge(5, 3, 2);
            setEdge(5, 4, 1);
            setEdge(6, 4, 3);
            setEdge(6, 5, 5);
        }

    }
    ~Graph(){
        delete Weight;
        delete Mark;
        delete graph;
    }
    int getn(){return n;}
    int gete(){return e;}
    int first(int a){
        if(graph[a]->head==graph[a]->tail){return getn();}
        graph[a]->setPos(0);
        int result;
        graph[a]->getValue(result);
        return result;
    }
    int next(int a,int b){
        graph[a]->setPos(0);
        while(graph[a]->fence!=graph[a]->tail&&graph[a]->fence->next->element!=b) {
            graph[a]->next();
        }
        if(graph[a]->fence==graph[a]->tail||graph[a]->fence->next==graph[a]->tail){return getn();}
        graph[a]->next();
        int result;
        graph[a]->getValue(result);
        return result;
    }
    void setEdge(int ver1,int ver2,int wei){
        if(Weight[ver1][ver2]==NOTPATH){
            graph[ver1]->append(ver2);
        }
        Weight[ver1][ver2]=wei;
        e++;
//        有向图和无向图
//        if(Weight[ver2][ver1]==NOTPATH){
//            graph[ver2]->append(ver1);
//        }
//        Weight[ver2][ver1]=wei;
//        //e++;
    }
    bool delEdge(int ver1,int ver2){
        if(Weight[ver1][ver2]==NOTPATH){return false;}
        graph[ver1]->setPos(0);
        while (graph[ver1]->fence!=graph[ver1]->tail&&graph[ver1]->fence->next->element!=ver2){

        }
        if(graph[ver1]->fence->next==graph[ver1]->tail){return false;}
        graph[ver1]->remove(ver2);
        Weight[ver1][ver2]=NOTPATH;
        e--;
//        //有向图和无向图
//        if(Weight[ver2][ver1]==NOTPATH){return false;}
//        graph[ver2]->setPos(0);
//        while (graph[ver2]->fence!=graph[ver2]->tail&&graph[ver2]->fence->next->element!=ver1){
//
//        }
//        if(graph[ver2]->fence->next==graph[ver2]->tail){return false;}
//        graph[ver2]->remove(ver1);
//        Weight[ver2][ver1]=NOTPATH;
//        //e--;
        return true;
    }
    int weight(int ver1,int ver2){
        return Weight[ver1][ver2];
    }
    bool getMark(int ver){return Mark[ver];}
    void setMark(int ver,bool flag=true){
        Mark[ver]=flag;
    }
};
struct Dynamic{
    int m;
    vector<int> D_Path;
};

Dynamic F_minPath(int node){
    Dynamic d;
    if(node==6){d.D_Path.push_back(6);d.m=0;return d;}
    int m=99999;
    for (int w=global_g->first(node);w<global_g->getn();w=global_g->next(node,w)){
        Dynamic temp_d= F_minPath(w);
        if(m>(temp_d.m+global_g->weight(node,w))){
            d.D_Path.clear();
            d.D_Path.assign(temp_d.D_Path.begin(),temp_d.D_Path.end());
            m=temp_d.m+global_g->weight(node,w);
        }
    }
    d.D_Path.push_back(node);
    d.m=m;
    return d;
}

Graph* global_g2=new Graph(7,1);

Dynamic B_minPath(int node){
    Dynamic d;
    if(node==0){d.D_Path.push_back(0);d.m=0;return d;}
    int m=99999;
    for (int w=global_g2->first(node);w<global_g2->getn();w=global_g2->next(node,w)){
        Dynamic temp_d= B_minPath(w);
        if(m>(temp_d.m+global_g2->weight(node,w))){
            d.D_Path.clear();
            d.D_Path.assign(temp_d.D_Path.begin(),temp_d.D_Path.end());
            m=temp_d.m+global_g2->weight(node,w);
        }
    }
    d.D_Path.push_back(node);
    d.m=m;
    return d;
}

int main(){
    Dynamic F;
    beginTime=clock();
    F=F_minPath(0);
    endTime=clock();
    cout<<F.m<<endl;
    for (int i=0;i<F.D_Path.size();i++){
        cout<<F.D_Path[F.D_Path.size()-1-i]<<" ";
    }
    cout<<endl<<"Forward Dynamic Programming-Time using: "<<(double)((endTime-beginTime)/CLOCKS_PER_SEC)<<endl;

    Dynamic B;
    beginTime=clock();
    B=B_minPath(6);
    endTime=clock();
    cout<<B.m<<endl;
    for (int i=0;i<B.D_Path.size();i++){
        cout<<B.D_Path[i]<<" ";
    }
    cout<<endl<<"Backward Dynamic Programming-Time using: "<<(double)((endTime-beginTime)/CLOCKS_PER_SEC)<<endl;

}
