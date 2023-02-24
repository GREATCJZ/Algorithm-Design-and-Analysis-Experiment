#include <iostream>
using namespace std;
#define NOTPATH 999999

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
        head=tail=fence=NULL;
        rightcnt=leftcnt=0;
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

    Graph(int tempn=10){
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
        if(graph[a]->fence==graph[a]->tail){return getn();}
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
        //有向图和无向图
        if(Weight[ver2][ver1]==NOTPATH){
            graph[ver2]->append(ver1);
        }
        Weight[ver2][ver1]=wei;
        //n++;
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
        //有向图和无向图
        if(Weight[ver2][ver1]==NOTPATH){return false;}
        graph[ver2]->setPos(0);
        while (graph[ver2]->fence!=graph[ver2]->tail&&graph[ver2]->fence->next->element!=ver1){

        }
        if(graph[ver2]->fence->next==graph[ver2]->tail){return false;}
        graph[ver2]->remove(ver1);
        Weight[ver2][ver1]=NOTPATH;
        //n--;
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

//最小生成树
//Peim's Alogorithm
void AddEdgetoMST(int ver1,int ver2){
    cout<<"Add Edge to MST "<<ver1<<" "<<ver2<<endl;
    //一些action表示这条边被加进最小生成树了
}
void Peim(Graph* g,int* D,int start){
    g->setMark(start,true);
    int V[g->getn()];
    for(int i=0;i<g->getn()-1;i++){
        int ver= minVertex_Linear(g,D);
        g->setMark(ver, true);
        if(D[ver]==NOTPATH){return;}
        if(ver!=start){ AddEdgetoMST(V[ver],ver);}
        for(int w=g->first(ver);w<g->getn();w=g->next(ver,w)){
            if(D[w]>g->weight(ver,w)){
                D[w]=g->weight(ver,w);
                V[w]=ver;
            }
        }
    }
}

int main() {

    Graph* g=new Graph(6);

    g->setEdge(0,5,7); //AF 7
    g->setEdge(0,1,2); //AB 2
    g->setEdge(0,2,9); //AC 9
    g->setEdge(1,2,5); //BC 5
    g->setEdge(1,3,11); //BD 11
    g->setEdge(2,4,6); //CE 6
    g->setEdge(3,4,6); //DE 6
    g->setEdge(4,5,13); //EF 13
    //起始点A
    int d[6]={NOTPATH,2,9,NOTPATH,NOTPATH,7};
    Peim(g,d,0);

}
