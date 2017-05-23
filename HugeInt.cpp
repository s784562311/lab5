#include<iostream>
#include<vector>
#include<string>
using namespace std;

class HugeInt{
	public:
		HugeInt();
		HugeInt(int);
		HugeInt(string);
		HugeInt(const HugeInt &);
		friend ostream& operator<<(ostream &, HugeInt);
		friend istream& operator>>(istream &, const HugeInt&);
		HugeInt& operator=(HugeInt);
		friend HugeInt operator+(HugeInt, HugeInt);
        friend HugeInt operator-(HugeInt, HugeInt);
		vector<int> data;

};

HugeInt::HugeInt(){
    data.push_back(0);
}

HugeInt::HugeInt(int num){
   while (num>0){
		data.push_back(num%10);
		num/=10;
	}
}

HugeInt::HugeInt(string str){
	data.clear();
	int size=str.size();
	for(int i=size-1;i>=0;--i){
		data.push_back(str[i]-'0');
	}
}

HugeInt::HugeInt(const HugeInt &num){
    this->data=num.data;
}

ostream& operator<<(ostream &out, HugeInt num){
	int size;
	size=num.data.size();
	for(int i=size-1;i>=0;--i){
		out << num.data[i];
	}
	return out;
}

istream& operator>>(istream &in,HugeInt &num){
	string str;
	in>>str;
	num.data.clear();
	int size=str.size();
	for(int i=size-1;i>=0;--i){
		num.data.push_back(str[i]-'0');
	}
	return in;
}

HugeInt& HugeInt::operator=(HugeInt num){
	this->data=num.data;
	return *this;
}

HugeInt operator+(HugeInt num1, HugeInt num2){
	int biggerSize;
	int sizeA,sizeB;
	sizeA=num1.data.size();
	sizeB=num2.data.size();
	biggerSize=sizeA;
	if(sizeB>sizeA){biggerSize=sizeB;}
	num1.data.resize(biggerSize);
	for(int i=0;i<sizeB;++i){
		num1.data[i]+=num2.data[i];
	}//plus
	for(int i=1;i<sizeA;++i){
		if(num1.data[i-1]>=10){
			num1.data[i-1]-10;
			num1.data[i]+1;
		}
	}
	if(num1.data.back()>=10){
		num1.data.back()-=10;
		num1.data.push_back(1);
	}
	return num1;
}

HugeInt operator-(HugeInt num1,HugeInt num2){
	int biggerSize;
	int sizeA,sizeB;
	int WhoBigger;

	sizeA=num1.data.size();
	sizeB=num2.data.size();
	if(sizeA>sizeB){WhoBigger=1;}
	else{WhoBigger=2;}
	biggerSize=sizeA;
	if(sizeB>sizeA){biggerSize=sizeB;}
	num1.data.resize(biggerSize);
	for(int i=0;i<biggerSize;++i){
		num1.data[i]-=num2.data[i];
	}
	if(WhoBigger==1){
	   for(int i=0;i<sizeA-1;++i){
	  	   if(num1.data[i]<0){
			   num1.data[i]+10;
			   num1.data[i+1]-1;
	   	   }
	   }
    }
    else if(WhoBigger==2){
    	for(int i=0;i<sizeA-1;++i){
	  	   if(num1.data[i]>0){
			   num1.data[i]-10;
			   num1.data[i+1]+1;
			   num1.data[i]*-1;
	       }
       }
       num1.data[sizeA-1]*-1;
   }
	if(num1.data.back()==0){
		num1.data.pop_back();
	}
	return num1;
}



int main()
{
HugeInt x;
HugeInt y(28825252);
HugeInt z("314159265358979323846");
HugeInt result;
cin >> x;
result = x+y;
cout << x << "+" << y << " = " << result << endl;
result = z - x;
cout << result << endl;
return 0;
}

