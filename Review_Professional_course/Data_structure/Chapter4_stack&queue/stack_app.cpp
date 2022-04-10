#include "stack.h"
#include <string>
#include <cmath>
#include <sstream>
using std:: string;
using std:: ostringstream;

const int operators = 9;
const char pri[operators][operators] = { //运算符优先等级[栈顶][当前]
    /*          |------------当前运算符-----------| */
    /*          +     -     *     /     ^     !     (     )     \0 */
    /* -- + */ '>',  '>',  '<',  '<',  '<',  '<',  '<',  '>',  '>',    
    /* |  - */ '>',  '>',  '<',  '<',  '<',  '<',  '<',  '>',  '>',    
    /* 栈 * */ '>',  '>',  '>',  '>',  '<',  '<',  '<',  '>',  '>',    
    /* 顶 / */ '>',  '>',  '>',  '>',  '<',  '<',  '<',  '>',  '>',    
    /* 运 ^ */ '>',  '>',  '>',  '>',  '>',  '<',  '<',  '>',  '>',    
    /* 算 ! */ '>',  '>',  '>',  '>',  '>',  '>',  ' ',  '>',  '>',    
    /* 符 ( */ '<',  '<',  '<',  '<',  '<',  '<',  '<',  '=',  ' ',    
    /* |  ) */ ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',    
    /* --\0 */ '<',  '<',  '<',  '<',  '<',  '<',  '<',  ' ',  '='    
};
// 逆序输出
void convert(Stack<char>& s, long long n, int base){
    static char digit[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    while(n>0){
        int index = n%base;
        s.push(digit[index]);
        n /=base;
    }
}
// 括号匹配
bool parent(const char exp[], int lo, int hi){
    Stack<char> s;
    for(int i=lo; i< hi; ++i){
        switch(exp[i]){
            case '(': case '[': case '{': s.push(exp[i]); break;
            case ')': if (s.empty() || '('!=s.pop()) return false; break;
            case ']': if (s.empty() || '['!=s.pop()) return false; break;
            case '}': if (s.empty() || '{'!=s.pop()) return false; break;
            default: break;
        }
    }
    return s.empty();
    // switch case only process the )]} corresponding
    // not deal with the ([{ 's number problem.
    // only when stack is clear, is all checked.
}

// 求值计算
double readNumber(char*& S,Stack<double>& opnd)
{
    opnd.push(0);
    bool is_demical = false;
    double demical_base = 0.1;
    while(*S){
        if(isdigit(*S)){
            //如果是数字
            double previous = opnd.pop(); //先前读入的数字
            int now = *S - 0x30;  //该位
            if(!is_demical){
                previous = previous*10+now;
                opnd.push(previous);
            }else{
                previous = previous+now*demical_base;
                opnd.push(previous);
                demical_base*=0.1;
            }
            S++;
        }else if(*S =='.'){
            is_demical = true;
            demical_base = 0.1;
            S++;
        }else 
            break;
    }
    return opnd.top();
}

void append(string& RPN, double elem)
{
   ostringstream ss;
    ss << elem;
    RPN += ss.str();
}

void append(string& RPN, char elem){
    RPN += elem;
}

int get_index(char op)
{
    switch(op){
        case '+': return 0; break;
        case '-': return 1; break;
        case '*': return 2; break;
        case '/': return 3; break;
        case '^': return 4; break;
        case '!': return 5; break;
        case '(': return 6; break;
        case ')': return 7; break;
        case '\0': return 8; break;
        default: return -1; break;
    }
}

char order_between(char op1, char op2)
{
    int index1 = get_index(op1);
    int index2 = get_index(op2);
    if (index1 == index2 && index1 == -1) return 'f';
    return pri[index1][index2];
}

double calcu(char op, double number)
{
    double outcome = 1;
    if(op == '!'){
        int temp = (int)number;
        for(int i=2; i<=temp; ++i){
            outcome *=i;
        }
        return outcome;
    }
    std::cout<<"unimplemented op!"<<std::endl;
    exit(-1);
}

double calcu(double num1, char op, double num2)
{
    switch (op)
    {
    case '+': return num1+num2; break;
    case '-': return num1-num2; break;
    case '*': return num1*num2; break;
    case '/': return num1/num2; break;
    case '^': return std::pow(num1,num2);break;
    default: std::cout<<"unsupported op!\n"; exit(-1); break;
    }
}

double evaluate(char* S, string & RPN){
    // get the value, and transfer to RPN
    Stack<double> opnd; Stack<char> optr; // number, operator stack
    optr.push('\0'); // tricky way to deal with \0 in the string's end
    while(!optr.empty()){
        // std:: cout<<*S<<std::endl;
        if(isdigit(*S)){
            // std:: cout<<"test\n";
            readNumber(S, opnd);
            append(RPN, opnd.top());
        }else{
            switch(order_between(optr.top(),*S)){
                case '<': optr.push(*S); S++; break;
                case '=': optr.pop(); S++; break;
                case '>':{
                    char op=optr.pop(); append(RPN, op);
                    if(op=='!'){
                        double popnd = opnd.pop();
                        opnd.push(calcu(op,popnd));
                    }else{
                        double popnd2 = opnd.pop();
                        double popnd1 = opnd.pop();
                        opnd.push(calcu(popnd1,op,popnd2));
                    }
                    break;
                }
                default: exit(-1);
            }
        }
    }
    return opnd.pop();
}

struct Queen{
    int x,y;
    Queen(int xx=0, int yy=0):x(xx), y(yy){};
    bool operator==(Queen const& q)const{
        return (x==q.x)||(y==q.y)||(q.x-x== q.y -y) ||(q.x - x== y- q.y);
    }
    bool operator!=(Queen const& q)const{return !(*this==q);}
};

void show(Queen& q){
    std::cout<<q.x<<","<<q.y<<" ";
}

void (*poin)(Queen&) = show;

void nqueens(int N)
{
    int checks =0;
    int solutions = 0;
    Stack<Queen> solu; //存放解的stack
    Queen q(0,0); // init
    while((q.x >0) || (q.y <N)){
        
        // std:: cout<< solu.find(q)<<"\n";
        while(q.y < N && (0<= solu.find(q)))// find until get the aviable pos
        {
            q.y++;
            checks++;
        }
        // std::cout << q.x<<","<<q.y<<"\n";
        if (q.y < N){
            solu.push(q);    
            if(N<= solu.size()) {solutions++;
            solu.traverse(poin);
            std:: cout<<"\n";
            }
            // step into the next row
            q.x++;
            q.y=0;
        }
        else {
            q = solu.pop();
            q.y++;
        }
    }

    // output the ans
    std:: cout<<solutions;
}

//  maze problem

typedef enum{AVAILABLE, ROUTE, BACKTRACED, WALL} Status; // unit's status

typedef enum{UNKNOWN, EAST, SOUTH, WEST, NORTH, NO_WAY} ESWN; 

inline ESWN nextESWN(ESWN eswn){return ESWN(eswn+1);}

struct Cell
{
    int x,y;
    Status status;
    ESWN incoming, outgoing;
    /* data */
};

const int LABY_MAX = 13; // max range of maze

// Cell laby[LABY_MAX][LABY_MAX]; // 迷宫

inline Cell* neighbor(Cell* cell)
{
    // 找邻居
    switch (cell->outgoing)
    {
    case SOUTH: return cell+LABY_MAX; break;
    case EAST: return cell+1; break;
    case NORTH: return cell - LABY_MAX; break;
    case WEST: return cell -1; break;
    default: exit(-1);
    }
}

inline Cell* advance(Cell* cell)
{
    // 走一步
    Cell* next;
    switch (cell->outgoing)
    {
        case EAST: next = cell+1; next->incoming=WEST; break;
        case SOUTH: next=cell+LABY_MAX; next->incoming = NORTH; break;
        case WEST: next = cell -1; next->incoming = EAST; break;
        case NORTH: next = cell -LABY_MAX; next->incoming = SOUTH; break;
        default: exit(-1);
    }
    return next;
}

bool labyrinth1(Cell laby[LABY_MAX][LABY_MAX], Cell* s, Cell* t, Stack<Cell*>& path)
{
    if(AVAILABLE!=s->status || AVAILABLE != t->status) return false;
    // Stack<Cell*> path;
    // std::cout<<"test\n";
    s->incoming = UNKNOWN; s->status = ROUTE; path.push(s);
    // int counter =0;
    while(!path.empty()){
        // counter++;
        Cell* temp = path.top();
        // get the top one
        if(temp == t) return true;
        // if is the targer, return 
        temp ->outgoing = nextESWN(temp->outgoing);
        while(temp->outgoing<NO_WAY){
            // find a accessible neighbor
            if (neighbor(temp)->status == AVAILABLE) 
                break;
            temp->outgoing = nextESWN(temp->outgoing);
        }
        if(temp->outgoing >=NO_WAY){
            temp->status = BACKTRACED;
            temp = path.pop();
            // 所有方向都尝试过了
        }else{
            temp = advance(temp);
            path.push(temp);
            temp->outgoing = UNKNOWN;
            temp->status=ROUTE;
        }
    }
    // std::cout<<counter;
    return false;
}
bool labyrinth( Cell Laby[LABY_MAX][LABY_MAX], Cell* s, Cell* t, Stack<Cell*> &path) {
    if ( (AVAILABLE != s->status ) || (AVAILABLE != t->status) )
        return false; //退化情况

    //Stack<Cell*> path; //用栈记录通路

    s->incoming = UNKNOWN; //起点
    s->status = ROUTE;
    path.push(s);

    do { //从起点出发不断试探、回溯，直到抵达终点、或穷尽所有可能
        Cell* c = path.top(); //检查当前位置（栈顶）
        if (c == t) //若已抵达终点，则找到了一条通路，否则沿尚未试探的方向继续试探
            return true;

        while ( (c->outgoing = nextESWN(c->outgoing)) < NO_WAY ) //逐一检查所有方向
            if (AVAILABLE == neighbor(c)->status) //直到找到一个未尝试过的方向
                break;

        if ( NO_WAY <= c->outgoing ) { //若所有方向都已尝试过
            c->status = BACKTRACED; //则标记并且回溯
            c = path.pop();
        }
        else { //还有若尝试的，则向前试探一步
            path.push( c=advance(c) );
            c->outgoing = UNKNOWN;
            c->status = ROUTE;
        }
    } while (!path.empty());

    return false;
}


int main(){
    // Stack<char> s;
    // convert(s, 100, 16);
    // while(s.size()){
    //     std::cout<<s.pop();
    // }
    // std::cout<<"\n";
    // char exp[] ={'(','1','+','1',')'};
    // parent(exp,0, sizeof(exp)) ? std::cout<<"yes\n" : std::cout<<"nopppp\n";

    // test readnumber 
    // Stack<double> opnd;
    // std:: string rpn;
    // char* number ="1.024+1.024*(1+1)+2^3";
    // double outcome = evaluate(number,rpn);
    // std:: cout<<outcome<<std::endl;
    // std:: cout<< rpn;
    // std::cout<<readNumber(number, opnd)<< std::endl;
    // nqueens(4);

    // #define LABY_MAX 13 //最大迷宫尺寸
    Cell laby[LABY_MAX][LABY_MAX]; //迷宫，是一个二维数组
    std::cout << "test labyrinth:" << std::endl; //见P104 的 13X13 实例
    for (int i=0; i<LABY_MAX; i++) {
        for ( int j=0; j<LABY_MAX; j++) {
            laby[i][j].x = i;
            laby[i][j].y = j;
            laby[i][j].status = AVAILABLE;
            laby[i][j].incoming = UNKNOWN;
            laby[i][j].outgoing = UNKNOWN;
        }
    }
    for (int i=0; i<LABY_MAX; i++) {
        laby[0][i].status = WALL; //第一行
        laby[LABY_MAX-1][i].status = WALL; //最后一行

        laby[i][0].status = WALL; //第一列
        laby[i][LABY_MAX-1].status = WALL; //最后一列
    }
    laby[1][2].status = WALL;
    laby[1][3].status = WALL;
    laby[1][6].status = WALL;
    laby[2][1].status = WALL;
    laby[2][3].status = WALL;
    laby[2][4].status = WALL;
    laby[2][7].status = WALL;
    laby[2][9].status = WALL;
    laby[3][5].status = WALL;
    laby[3][6].status = WALL;
    laby[3][8].status = WALL;
    laby[4][5].status = WALL;
    laby[5][1].status = WALL;
    laby[5][5].status = WALL;
    laby[6][5].status = WALL;
    laby[7][2].status = WALL;
    laby[7][3].status = WALL;
    laby[7][6].status = WALL;
    laby[7][9].status = WALL;
    laby[8][1].status = WALL;
    laby[8][6].status = WALL;
    laby[9][3].status = WALL;
    laby[9][6].status = WALL;
    laby[9][7].status = WALL;
    laby[9][9].status = WALL;
    laby[10][10].status = WALL;
    laby[11][8].status = WALL;
    laby[11][10].status = WALL;
    laby[11][11].status = WALL;
    Cell* ss = &laby[4][9];
    Cell* tt = &laby[4][1];
    Stack<Cell*> path;

    if (labyrinth1( laby, ss, tt, path))
        std::cout << "has path ="   <<std:: endl;
    while (!path.empty()) {
        Cell* c = path.pop();
        std::cout << "(" << c->x << "," << c->y << ") <-- ";
    }
    std::cout << std::endl;

}