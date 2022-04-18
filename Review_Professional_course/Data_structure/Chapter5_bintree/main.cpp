#include "bintree.h"

template<typename T>
class VST{
public:
    void operator() (BinNodePosi(T) temp){
        std::cout<<temp->data<<" ";
    }
};

int main()
{
    Bintree<int> my_tree;
    VST<int> visit;
    my_tree.insertAsRoot(123);
    my_tree.insertAsLC(my_tree.root(),111);
    my_tree.insertAsRC(my_tree.root(),222);
    Bintree<int> attach;
    Bintree<int>* btp = &attach;
    attach.insertAsRoot(666);
    attach.insertAsLC(attach.root(),777);
    attach.insertAsRC(attach.root(),888);
    my_tree.attachAsLC(my_tree.root()->lc,btp);
    int num = my_tree.remove(my_tree.root()->lc->lc);
    std::cout<<"delete: "<<num<<std::endl;
    // btp = new Bintree<int>;
    // btp = my_tree.secede(my_tree.root()->lc->lc);
    // btp = NULL;
    // std:: cout<<btp;
    // std::cout<<my_tree.root()->rc<<std::endl;
    // std:: cout<<"IN\n";
    // std::cout<<my_tree.size()<<std::endl;
    // my_tree.travIn(visit);
    // std::cout<<"\n";
    // (*btp).travIn(visit);
    // std::cout<<"\n";
    // std:: cout<<"Pre\n";
    // my_tree.travPre(visit);
    // std::cout<<"\n";
    // btp->travPre(visit);
    // std::cout<<"\n";
    // std:: cout<<"Post\n";
    // my_tree.travPost(visit);
    // std::cout<<"\n";
    // btp->travPost(visit);
    // std::cout<<"\n";
    // std:: cout<<"level\n";
    // my_tree.travLevel(visit);
    // std::cout<<"level done\n";
    // std::cout<<"\nfsafasf\n";
    // btp->travLevel(visit);
    // std::cout<<"\n";
    return 0;
}