#include<iostream>
#include<string>
#include<iomanip>
#include<vector>
using namespace std;

class HugeInt{
	public:
		HugeInt(int i=0):number(i){type=0;}
		HugeInt(string s):str(s){type=1;}
		HugeInt operator+(HugeInt&);
		HugeInt operator-(HugeInt&);		
		friend ostream& operator<<(ostream &, const HugeInt&);
		friend istream& operator>>(istream &, HugeInt &);
		friend int WhoisBigger(HugeInt&, HugeInt&);
		friend int DoubleCheck(HugeInt&, HugeInt&, int);
		friend int CheckSize(HugeInt&, HugeInt&);
		friend HugeInt Minus(HugeInt&, HugeInt&);


		
	private:
		int number;
		string str;
		int type;//0 for number, 1 for string
};

int CheckSize(HugeInt& obj1, HugeInt& obj2){
		int BiggerSize;
		int Asize,Bsize;
		Asize=(obj1.str).size();
		Bsize=(obj2.str).size();
		BiggerSize=Asize;
		if(Bsize>Asize){BiggerSize=Bsize;}
		return BiggerSize;
}

int WhoisBigger(HugeInt& obj1, HugeInt& obj2){
	int action;
	if(obj1.str[0]!='-'){
		if(obj2.str[0]=='-'){action=1;}// +,-
		else if (obj2.str[0]!='-'){action=-1;}// +,+
	}
	else if(obj1.str[0]=='-'){
		if(obj2.str[0]!='-'){action=2;}// -,+
		else if(obj2.str[0]=='-'){action=-2;}// -,-
	}
	if(action==-1||action==-2){
		int status;
		status=action;
		action=DoubleCheck(obj1,obj2,status);
		return action;
	}
	else if(action==1){return action;}// +,-
	else if(action==2){return action;}// -,+
	return 0;
}

int DoubleCheck(HugeInt& obj1, HugeInt& obj2, int status){
	int answer;
	int Asize,Bsize;
		Asize=(obj1.str).size();
		Bsize=(obj2.str).size();
	if(status==-1){
		if(Asize>Bsize){answer=1;}
		else if(Asize<Bsize){answer=2;}
	}
	else if(status==-2){
		if(Asize>Bsize){answer=2;}
		else if(Asize<Bsize){answer=1;}
	}
	else{
		if(status==-1){
			int conti=1;
			answer=1;//a>b
			int j=0;
			while(j<=CheckSize(obj1,obj2)-1){
				if(obj1.str[j]>obj2.str[j]){
					answer=1;//a>b
					conti=0;
				}
				else if(obj1.str[j]<obj2.str[j]){
					answer=2;//a<b
					conti=0;
				}
				++j;
			}
		}
		else if(status==-2){
			int conti=1;
			answer=2;//a<b
			int j=1;
			while(j<=CheckSize(obj1,obj2)-1){
				if(obj1.str[j]>obj2.str[j]){
					answer=2;//a<b
					conti=0;
				}
				else if(obj1.str[j]<obj2.str[j]){
					answer=1;//a>b
					conti=0;
				}
				++j;
			}
		}
	}
	return answer;
}

HugeInt Minus(HugeInt& obj1, HugeInt& obj2){
	int BiggerSize;
	int Asize,Bsize;
	BiggerSize=CheckSize(obj1, obj2);
	Asize=(obj1.str).size();
	Bsize=(obj2.str).size();
	
	vector<int> vecA(BiggerSize-Asize);
	vector<int> vecB(BiggerSize-Bsize);
	
	char Ps;
	
	if(obj1.type==1){
		if(obj2.type==0){Ps='A';}//(1,0) means (string,int) Ps=A
		else if(obj2.type==1){Ps='B';}//(1,1) means (string,string) Ps=B
	}
	else if(obj1.type==0 && obj2.type==1){Ps='C';}//(0,1) means (int,string) Ps=C
	switch(Ps)
	{
	case 'A':
		for(int l=0;l<=BiggerSize-1;l++){
			vecA.push_back(obj1.str[l]-'0');
		}
		do{vecB.push_back((obj2.number)%10);}while((obj2.number)/=10);
		
		break;
	
	case 'B':
		for(int l=0;l<=BiggerSize-1;l++){
			vecA.push_back(obj1.str[l]-'0');
			vecB.push_back(obj2.str[l]-'0');
		}
		break;
	
	case 'C':
		for(int l=0;l<=BiggerSize-1;l++){
			vecB.push_back(obj2.str[l]-'0');
		}
		do{vecA.push_back((obj1.number)%10);}while((obj1.number)/=10);
		break;
	
	}
	
//	char Bigger;
	
	
}

HugeInt HugeInt::operator+(HugeInt& num){
/*type=1 先檢查size */
		HugeInt number2;
		number2.number=this->number + num.number;
		return number2;

}

HugeInt HugeInt::operator-(HugeInt& num){
	if((this->type)==0 && (num.type)==0){
	HugeInt number2;
	number2.number=this->number - num.number;
	return number2;
	}
/*	else{
		return Minus(*this,num);
	}*/
}

ostream& operator<<(ostream& out, const HugeInt& num) {
  out << num.number;
  return out;
}

istream& operator>>(istream& in, HugeInt &num){
	in >> num.number;
	return in;
}

int main(){
	HugeInt x;
	HugeInt y(28825252);
	//HugeInt z("314159265358979323846");
	HugeInt result;
	cin >> x;
	result = x+y;
	cout << x << "+" << y << " = " << result << endl;
	//result = z - x;
	cout << result << endl;
	return 0;
}
// CheckSize has some?

/*(Turn to vector)
HugeInt Minus(HugeInt& obj1, HugeInt& obj2){
	int BiggerSize;
	int Asize,Bsize;
	BiggerSize=CheckSize(obj1, obj2);
	Asize=(obj1.str).size();
	Bsize=(obj2.str).size();
	
	vector<int> vecA(BiggerSize-Asize);
	vector<int> vecB(BiggerSize-Bsize);
	
	char status;
	
	if(obj1.type==1){
		if(obj2.type==0){status='A';}//(1,0) means (string,int) status=A
		else if(obj2.type==1){status='B';}//(1,1) means (string,string) status=B
	}
	else if(obj1.type==0 && obj2.type==1){status='C';}//(0,1) means (int,string) status=C
	switch(status)
	{
	case 'A':
		for(int l=0;l<=BiggerSize-1;l++){
			vecA.push_back(obj1.str[l]-'0');
			vecB.push_back(obj2.num[l]);
		};
		break;
	
	case 'B':
		for(int l=0;l<=BiggerSize-1;l++){
			vecA.push_back(obj1.str[l]-'0');
			vecB.push_back(obj2.str[l]-'0');
		};
		break;
	
	case 'C':
		for(int l=0;l<=BiggerSize-1;l++){
			vecA.push_back(obj1.num[l]);
			vecB.push_back(obj2.str[l]-'0');
		};
		break;
	
	}
	
}
*/
