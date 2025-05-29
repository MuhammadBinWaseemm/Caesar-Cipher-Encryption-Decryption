#include<iostream>
#include<string>
using namespace std;
#define size 26
const string Z[size] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O",
                                 "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
int main()
{
	string x , y ,cal1,cal2;
	int k ;
	cout<<"\n\t\tEnter a text(only alphabets): ";
	getline(cin,x);
	cout<<"\n\t\tSet a key : ";
	cin>>k;
	k=k%26;
	for(char c:x)
	{
		cal1=c;
		cal2=toupper(c);
		for(int j=0 ; j<size ; j++)
		{
			if(cal1==" ")
			{
				y+=cal1;
				break;
			}
			if(cal1==Z[j] || cal2==Z[j])
			{
				cal1=Z[(j+k)%26];
				y+=cal1;
				break;
			}
		}
	}
	cout<<"\n\t\tEncryption : "<<y;
}