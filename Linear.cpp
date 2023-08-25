#include<iostream>
#include<cmath>
#include<string>
using namespace std;
int findLCM(int a, int b){
	a = abs(a);
	b = abs(b);
    if(a == 0 || b == 0)
    return 0;
    int greater = max(a, b);
    int smallest = min(a, b);
    for (int i = greater; ; i += greater) {
        if (i % smallest  == 0)
            return i;
}
}
class Fraction{
	int numerator, denomerator;
	public:
		Fraction(){
			numerator = 0;
			denomerator = 1;
		}
		Fraction(int a, int b=1){
			numerator = a;
			denomerator = b;
		}
		void input(){
			cin>>numerator;
		}
		void print(){
			cout<<numerator;
		    if(denomerator ==1 || numerator == 0)
		    cout<<" ";
		    else{
		    	cout<<"/"<<denomerator;
			}
		}
		void setNum(int a){
			numerator = a;
		}
		void setDenom(int a){
			if(a < 0)
			numerator = -numerator;
			denomerator = abs(a);
		}
		int getNum(){
			return numerator;
		}
		int getDenom(){
			return denomerator;
		}
		void reduce(){
			int limit = min(abs(numerator), abs(denomerator));
			
			for(int i=2; i<=limit; i++){
				if(numerator%i == 0 and denomerator%i == 0){
					numerator /= i;
					denomerator /=i;
				}
			}
		if(denomerator < 0)
			numerator = -numerator;
			denomerator = abs(denomerator);
		}
		Fraction operator+(Fraction& f){
			int lcm = findLCM(denomerator, f.getDenom());
			int numer = (lcm/denomerator)*numerator + (lcm/f.getDenom())*f.getNum();
			Fraction result(numer, lcm);
			result.reduce();
			return result;		
		}
		Fraction operator-(Fraction& f){
			int lcm = findLCM(denomerator, f.getDenom());
			int numer = (lcm/denomerator)*numerator - (lcm/f.getDenom())*f.getNum();
			Fraction result(numer, lcm);
			result.reduce();
			return result;		
		}
		Fraction operator*(Fraction& f){
			Fraction result(numerator*f.getNum(), denomerator*f.getDenom());
			result.reduce();
			return result;
		}
		Fraction operator/(Fraction& f){
			Fraction result(numerator*f.getDenom(), denomerator*f.getNum());
			result.reduce();
			return result;
		}
		Fraction operator*(int a){
			Fraction result(numerator*a);
			result.reduce();
				return result;
		}
		Fraction operator+(int a){
			Fraction result(numerator + a*denomerator, denomerator);
			result.reduce();
				return result;
		}
		Fraction operator-(int a){
			Fraction result(numerator - a*denomerator, denomerator);
			result.reduce();
			return result;
		}
		Fraction operator/(int a){
			Fraction result(numerator, denomerator*a);
			return result;
		}
};
Fraction findLCM(Fraction& f1, Fraction& f2){
	Fraction result(abs(f1.getNum()*f2.getNum()), abs(f1.getDenom()*f2.getDenom()));
	result.reduce();
	return result;
}
void Eligible(int& i, int& j, int rows, int cols ,Fraction** array){
	for(int k = 0; k<rows; k++){
		if(k == i)
		continue;  // if row k is equal to row i then do not check in it
		
		int l = 0;
			//checking if row k has same number of leading zeros as row i
		for( ; l<j; l++){
			if(array[k][l].getNum() !=0)
			break;
		}
	
		Fraction lcm = findLCM(array[i][j], array[k][l]);
		if(l != j || lcm.getNum() == 0){
			continue;
		}
		Fraction a = lcm/array[i][j], b = lcm/array[k][l];
		int sign = (array[i][j].getNum()*array[k][l].getNum() >=0)?-1:1;
			for(int m = 0; m<cols; m++){
				Fraction v = array[i][m]*a, x = array[k][m]*b*sign;
				array[i][m] = v + x;
			}
			break;
	}
}
void echelon(int rows, int cols, Fraction** array){
    for(int i = 1; i<rows; i++){ //Start from row 2 because it will have the first zero
    	for(int j = 0; j<rows; j++){ //Second row has one zero, thired has two and so on
    		 Eligible(i, j, rows, cols, array);
		}
	}
	
	for(int i = 0; i<rows; i++){
			if(array[i][i].getNum()!=1){
				Fraction divisor = array[i][i];
				for(int k = 0; k<cols; k++){
					array[i][k] = array[i][k]/divisor;
				}
			}
		
	}
	
	
}
int main(){
	int no = 0;
	cout<<"Enter the number of variables: "<<endl;
	cin>>no;
    Fraction** matrix = new Fraction*[no];
    for(int i = 0; i<no; i++)
    matrix[i] = new Fraction[no+1];
    
  for(int i=0; i<no; i++){
  	for(int j=0; j<no+1; j++)
  	matrix[i][j].input();
  }
    
    echelon(no, no+1, matrix);
    cout<<"\nMatrix: "<<endl;
    
     for(int i=0; i<no; i++){
  	for(int j=0; j<no+1; j++){
  		matrix[i][j].print();
	  cout<<" ";
	  }
  	
  	cout<<endl;
  }
    
    for(int i = no-1; i>=0; i--)
    delete matrix[i];
    
    delete[] matrix;
    
}
