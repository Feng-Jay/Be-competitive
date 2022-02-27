#include <string>
#include <iostream>
#include <cmath> //gives us pow and sqrt!

using std::string; using std::cout;
using std::cin; using std::pow;
using std::sqrt; using std::endl;

//want: a function names quadratic that will take in 3 doubles and return
//a combination of: does a solution exist, and if so, what is it?
std::pair<bool, double*> quadratic(double a, double b, double c) 
{
	 double roots[2]={0,0};
	double test = pow(b,2) - 4 * a * c;
	if (test < 0){
		return std::make_pair(false, roots);
	}else{
		roots[0] = (-1*b + sqrt(test))/(2*a);
		roots[1] = (-1*b - sqrt(test))/(2*a);
		// cout << "In function roots: "<< roots[0]<<","<<roots[1]
		// <<endl;
		// cout << &roots[0] <<endl;
		// cout << &roots[1] <<endl;
		return std::make_pair(true, roots);
	} 
	//get radical, test if negative, return indicating no roots
	//otherwise get roots and return
	
}

int main(){
	//get 3 doubles (ax^2 + bx + c)
	double a, b, c;
	cout << "Give me 3 coefficients!!!: " << endl;

	//This line gets 3 numbers from user input and stores them in a, b and c 
	//we will learn more about cin on Thursday
	cin >> a >> b >> c;
	// cout <<"test"<<endl;
	// cout << a << b << c;
	//get roots if they exist
	//some call to quadratic function!
	std::pair<bool, double*> outcome; 
	// outcome.second = new double[2];
	// outcome.second = {0,0};
	 outcome = quadratic(a,b,c);
	// cout << &outcome.second[0]<<endl;
	// cout << &outcome.second[1]<<endl;
	// cout << outcome.second[0] <<" " << outcome.second[1]<<endl;
	bool exists = outcome.first;
	double* roots = outcome.second;
	if(exists){
		std:: cout << "roots exist" << std::endl;
		std:: cout << roots[0] << " " << roots[1]<< std::endl;
	}else{
		std:: cout << "roots not exist"<< std::endl;
	}
	return 0;
}