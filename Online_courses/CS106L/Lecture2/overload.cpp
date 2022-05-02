#include <iostream>
#include <string>

int div_2(int x){
	return x/2;
}

double div_2(double x){
	return x/2;
}

int main(int argc, char const *argv[])
{
	/* code */
	std:: cout<< div_2(3) <<" "<<div_2(3.0)<<std::endl; 
	std:: pair<int, std:: string> numSuffix(1,"st");
	std:: cout << numSuffix.first << numSuffix.second;
 	return 0;
}