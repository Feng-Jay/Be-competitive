#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;
void print_vector(vector<int> vec){
	cout << "{ ";
	for(int i = 0; i < vec.size() - 1; i++){
		cout << vec[i] << ", ";
	}

	cout << vec[vec.size() - 1] << " }" << endl;
}

int main()
{
	vector<int> vec{1,2,3};
	const vector<int> c_vec{1,2,3};
	vector<int> & ref = vec;
	const vector<int> & c_ref = vec;

	print_vector(vec);
	print_vector(c_vec);

	auto avec = c_vec;
	avec.push_back(5);
	print_vector(avec);
	print_vector(c_vec); //Ignore const

	auto aref= ref;
	aref.push_back(6);
	print_vector(aref);
	print_vector(ref);//Ignore &

	auto dou = c_ref;
	dou.push_back(7);
	print_vector(dou);
	print_vector(c_ref);//Ignore both

	

}