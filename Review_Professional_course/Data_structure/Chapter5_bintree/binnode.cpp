#include "binnode.h"
template <typename T>
inline int stature(BinNodePosi(T) p){return (p)? (p)->height : -1;}


// quick ways
template <typename T>
inline bool Isroot(BinNode<T> const& x){return !((x).parent);}

template <typename T>
inline bool IsLChild(BinNode<T> const& x){return !Isroot(x) && (&(x) == (x).parent->lc);}

template <typename T>
inline bool IsRChild(BinNode<T> const& x){return !Isroot(x) && (&(x) == (x).parent->rc);}

template <typename T>
inline bool HasParent(BinNode<T> const& x) { return !Isroot(x);}

template <typename T>
inline bool HasLChild(BinNode<T> const& x) { return x.lc; }

template <typename T>
inline bool HasRChild(BinNode<T> const& x) { return x.rc; }

template <typename T>
inline bool HasChild(BinNode<T> const& x){ return HasLChild(x)||HasRChild(x);}

template <typename T>
inline bool HasBothChild(BinNode<T> const& x){return HasLChild(x)&&HasRChild(x);}

template <typename T>
inline bool IsLeaf(BinNode<T> const& x) {return !HasChild(x);}

template <typename T>
inline BinNodePosi(T) sibling(BinNode<T> const& x) {return IsLChild(x) ? x.parent->rc : x.parent->lc; }

template <typename T>
inline BinNodePosi(T) uncle(BinNode<T> const& x){ return IsLChild(*(x.parent)) ? x.parent->parent->rc : x.parent->parent->lc; }

template <typename T>
inline BinNodePosi(T) FromParentTo(BinNode<T> const & x){
    // if is root, return NULL
    // else return the pointer
    return Isroot(x) ? NULL : (IsLChild(x)? x.parent->lc : x.parent->rc);
}

template <typename T>
BinNodePosi(T) BinNode<T>::insertAsLC(T const& e){
    return lc = new BinNode(e, this);
}
template <typename T>
BinNodePosi(T) BinNode<T>::insertAsRC(T const& e){
    return rc = new BinNode(e, this);
}

template <typename T>
BinNodePosi(T) BinNode<T>::succ(){
    BinNodePosi(T) s = this;
    if(HasRChild(*s)){
        s = rc;
        while(HasLChild(*s)) s= s->lc;
    }else{
        while(IsRChild(*s)) s = s->parent;
        s = s->parent;
    }
    return s;
}
// recursive traverse. 
template <typename T, typename VST>
void travpre_R(BinNodePosi(T)x, VST& visit)
{
    if(!x) return;
    visit(x);
    travpre_R(x->lc, visit);
    travpre_R(x->rc, visit);
}

template <typename T, typename VST>
void travpost_R(BinNodePosi(T)x, VST& visit)
{
    if(!x) return;
    travpost_R(x->lc,visit);
    travpost_R(x->rc, visit);
    visit(x);
}

template <typename T, typename VST>
void travin_R(BinNodePosi(T) x, VST& visit)
{
    if(!x) return ;
    travin_R(x->lc, visit);
    visit(x);
    travin_R(x->rc, visit);
}

template <typename T, typename VST>
void travpre_v1(BinNodePosi(T)x, VST& visit)
{
    Stack<BinNodePosi(T)> temp;
    temp.push(x); 
    while(!temp.empty()){
        BinNodePosi(T) t = temp.pop();
        visit(t);
        if(HasRChild(*t)){
            temp.push(t->rc);
        }else if(HasLChild(*t)){
            temp.push(t->lc);
        }
    }
}
template <typename T, typename VST>
void travpre_v2(BinNodePosi(T)x, VST& visit){
    // more common version
    // 每次都相当于, 对于一棵树根节点的所有最左边子树的根节点过一遍
    // 然后再对每棵左子树的右子树重复上述过程
    Stack<BinNodePosi(T)> temp;
    temp.push(x); // push root
    while(!temp.empty()){
        x = temp.pop();
        while(x){
            visit(x);
            if(HasRChild(*x))
                temp.push(x->rc);
            x= x->lc;
        }
    }
}

template <typename T, typename VST>
void travIn_v1(BinNodePosi(T)x, VST& visit){
    Stack<BinNodePosi(T)> temp;
    while(true){
        while(x){
            temp.push(x);
            x= x->lc;
        }
        if (temp.empty()) break;
        x = temp.pop();
        visit(x);
        x = x->rc;
    }
}

template <typename T, typename VST>
void travIn_v2(BinNodePosi(T)x, VST& visit){
    Stack<BinNodePosi(T)> temp;
    while(true){
        if(x){
            temp.push(x);
            x = x->lc;
        }else if (!temp.empty()){
            x = temp.pop();
            visit(x);
            x = x->rc;
        }else break;
    }
}
template <typename T, typename VST>
void travIn_v3(BinNodePosi(T)x, VST& visit){
    // do not need extra storage space
    // but need call the succ many times. time complexity grows
    bool backtrace = false;
    while(true){
        if(!backtrace && HasLChild(*x))
            x =x->lc;
        // deep into the "leftest" node
        else{
            visit(x);
            if(HasRChild(*x)){
                // if has rchild, re deep into the "leftest"
                x = x->rc;
                backtrace = false;
            }else{
                // else, it is still the same level
                // do not need deep into, because this level has not been visited yet.
                if(!(x=x->succ())) break; // get to the end
                backtrace = true;
            }
        }
    }
}
template <typename T, typename VST>
void travIn_v4(BinNodePosi(T)x, VST& visit){
    while(true){
        if(HasLChild(*x))   x = x->lc; 
        // if have left-child-tree, deep in
        else{
            visit(x);
            // or visir this node.
            while(!HasRChild(*x)){
                if(!(x=x->succ())) return;
                else visit(x);
            }
            x = x->rc;
        }
    }
}

template <typename T, typename VST>
void travpost_v1(BinNodePosi(T)x, VST& visit){
    Stack<BinNodePosi(T)> temp;
    if(x) temp.push(x);
    while ((!temp.empty()))
    {
        if(temp.top()!=x->parent){
            // 就只能是x的右兄弟咯
            while(BinNodePosi(T) t = temp.top()){
                if(HasLChild(*t)){
                    if(HasRChild(*t)) temp.push(t->rc);
                    temp.push(t->lc);
                }else{
                    temp.push(t->rc);
                }
            }
            temp.pop();
        }
        x = temp.pop();
        visit(x);
    }
    
}

template <typename T>
template<typename VST>
void BinNode<T>::travPre(VST& visit){
    switch (std:: rand()%2){
        case 0: travpre_v1(this, visit); break;
        case 1: travpre_v2(this, visit); break;
        default: travpre_R(this, visit); break;
    }
}

template <typename T>
template <typename VST>
void BinNode<T>::travIn(VST& visit)
{
    switch (std::rand()%5)
    {
    case 1: travIn_v1(this, visit); break;
    case 2: travIn_v2(this, visit); break;
    case 3: travIn_v3(this, visit); break;
    case 4: travIn_v4(this, visit); break;
    default: travin_R(this, visit); break;
    }
}

template <typename T>
template<typename VST>
void BinNode<T>::travPost(VST& visit)
{
    travpost_v1(this, visit);
}

template <typename T>
template <typename VST>
void BinNode<T>::travLevel(VST& visit)
{
    Queue<BinNodePosi(T)> q;
    q.enqueue(this);
    while(!q.empty()){
        BinNodePosi(T) x= q.dequeue();
        visit(x);
        if(HasLChild(*x)) q.enqueue(x->lc);
        if(HasRChild(*x)) q.enqueue(x->rc);
    }
    // std::cout<<"level done\n";
}

template <typename T>
int BinNode<T>::size()
{
    int outcome =1;
    BinNodePosi(T) temp = this;
    bool backtrace = false;
    while(true){
        if(!backtrace && HasLChild(*temp)){
            temp = temp->lc;
            outcome++;
        }else{
            if(HasRChild(*temp)){
                temp = temp->rc;
                backtrace = false;
                outcome++;
            }else{
                if(!(temp=temp->succ())) break;
                backtrace = true;
            }
        }
    }
    return outcome;
}