#include "listNode.h"

template <typename T> class List{
    private:
        int _size; // size 
        ListNodePosi(T) header; // head node
        ListNodePosi(T) tailer; // tail node
    protected:
        void init();// init when list is created
        int clear();
        void copyNodes(ListNodePosi(T), int);// copy n elems from p
        void merge(ListNodePosi(T)&, int, List<T>&, ListNodePosi(T), int);
        void mergesort(ListNodePosi(T)&, int); // mergesort to begin at p, n elems
        void selectionsort(ListNodePosi(T), int);
        void insertionsort(ListNodePosi(T), int);
    public:
        // constructor
        List(){init()};
        List(List<T> const& L); // copy L
        List(List<T> const& L, Rank n, int n);// copy start from L's r to r+n-1
        List(ListNodePosi(T) p, int n);// copy from p to p+n

        // destructor
        ~List(); // release all the nodes

        // read-only interface
        Rank size() const{return _size;}

        bool empty() const{return _size <=0;}

        T& operator[] (Rank r) const; // reload to support access by rank

        ListNodePosi(T) first() const{return header->succ;} // first node's p
        ListNodePosi(T) last() const {return tailer->pred;} // last node's p

        bool valid(ListNodePosi(T) p) //judge position p is illeagle?
        {return p && (header != p) && (tailer != p);}

        int disordered() const;
        // 倒序查找, 总能找到秩最大的那一个对应元素.
        ListNodePosi(T) find(T const& e) const{
            return find(e, _size, tailer);
        }
        ListNodePosi(T) find(T const&3, int n, ListNodePosi(T) p) const;

        ListNodePosi(T) search(T const& e) const
        {return search(e, _size, tailer);}
        ListNodePosi(T) search(T const& e, int n, ListNodePosi(T) p) const;

        ListNodePosi(T) selectmax(ListNodePosi(T) p, int n);
        ListNodePosi(T) selectmax(){return selectmax(header->succ, _size);}

        // writable function
        ListNodePosi(T) insertAsFirst(T const& e);
        ListNodePosi(T) insertAsLast(T const& e);

        ListNodePosi(T) insertA(ListNodePosi(T) p, T const& e);
        ListNodePosi(T) insertB(ListNodePosi(T) p, T const& e);

        T remove(ListNodePosi(T) p); // delete p's node, return it

        void merge(List<T>& L){merge(first(),size, L, L.first(), L._size);}
        void sort(ListNodePosi(T) p, int n);
        void sort() {sort(first(), _size);}

        int deduplicate();
        int uniquify();
        void reverse();

        // travel
        void traverse(void(*)(T&));
        template<typename VST>
        void traverse(VST&);
}