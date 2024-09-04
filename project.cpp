/* From Bank Company Side (Taken refrence from Siddhartha Bank) */
#include<iostream>
#include<iomanip>
#include<string.h>
#include<fstream>
using namespace std;
/* Creating Bank Account Class to Store Data of users for them to access*/
class BankAccountListUsers
{
protected:
	char FirstName[10],MidName[10],LastName[10],Address[12],In[12];
	char Password[10];
	long int phone_no;
	long double balance;
public:
	void input()
	{
		cout << "Enter full name of the new user: \n(If There's no Mid Name pls press x on it and enter)" << endl;
		cin >> FirstName >> MidName >>LastName;
		cout << "Enter Address of the New User:" << endl;
		cin >> Address;
		cout << "District Location:" << endl;
		cin >> In;
		cout << "Enter Password:\n(Atmost 10 digits)" << endl;
		cin >> Password;
		cout << "Enter Phone no.:" << endl;
		cin >> phone_no;
		cout << "Enter Balance For New User:" << endl;
		cin >> balance;
	}
	void output()
	{
		cout << "----------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << left << setw(15) << FirstName << setw(15) << MidName << setw(15) << LastName << setw(15) << Address << setw(15) << In << setw(15) << phone_no << setw(15) << Password << setw(15) << balance << endl;
	}
	long int getPhoneNo()
	{
		return phone_no;
	}
	int checkphone(long int r)
	{
		if (phone_no == r)
		{
			return 1;
		}
		else {
			return 0;
		}
	}
};

void WriteToFile()
{
	BankAccountListUsers B;
	int n;
	cout << "Enter the Number of Account Holders: " << endl;
	cin >> n;
	fstream fout;
	fout.open("AccountHolder.csv",ios::out | ios::app);
	for(int i = 0 ; i < n ; i++)
	{
		cout << "Enter the details for Account Holder"<< i+1 << endl;
		B.input();
		fout.write((char*)&B,sizeof(B));
	}
	fout.close();
}

void ReadFile()
{
	BankAccountListUsers B;
	fstream fin;
	fin.open("AccountHolder.csv",ios::in|ios::binary);
	cout << left << setw(15) << "First Name" << setw(15) << "Mid Name" << setw(15) << "Last Name" << setw(15) << "Address" << setw(15) << "District" << setw(15) << "Phone no." << setw(15) << "Password" << setw(15) << "Balance" << endl;
	while(fin.read((char*)&B,sizeof(B)))
	{
		B.output();
	}
	fin.close();
}

void Delete()
{
	BankAccountListUsers B;
	long int ph;
	cout << "Enter which data to delete" << endl;
	cin >> ph;
	int flag = 0;
	fstream fin,fout;
	fin.open("AccountHolder.csv",ios::in|ios::binary);
	fout.open("temp.csv",ios::out|ios::binary);
	int checkPhn = B.getPhoneNo();
	while (fin.read((char*)&B,sizeof(B))) {
		if(B.checkphone(ph))
		{flag = 1;}
		else {
			fout.write((char*)&B,sizeof(B));
		}
	}
	if(flag==0)
	{
		cout << "Record Not Found!!!!" << endl;
	}
	else {cout << "Record Deleted Successfully!!!" << endl;}
	fout.close();
	fin.close();
	remove("AccountHolder.csv");
	rename("temp.csv","AccountHolder.csv");
}
void Search()
{
	fstream fout;
	BankAccountListUsers B;
	long int ph;
	int flag = 0;
	cout << "Enter the Phone Number to search:" << endl;
	cin >> ph;
	fout.open("AccountHolder.csv",ios::in|ios::binary);
	while(fout.read((char*)&B,sizeof(B)))
	{
		if(B.checkphone(ph))
		{
			cout << left << setw(15) << "First Name" << setw(15) << "Mid Name" << setw(15) << "Last Name" << setw(15) << "Address" << setw(15) << "District" << setw(15) << "Phone no." << setw(15) << "Password" << setw(15) << "Balance" << endl;
			B.output();
			flag = 1;
			break;
		}
	}
	if( flag == 0 )
	{
		cout << "Couldn't Fined in the data sheet." << endl;
	}
	fout.close();
}

int main()
{
	int option;
	do{
		cout<<"Press the following button for to move that place: "
			<< "\n1. Write from start at AccountHolder(remove of old data):"
			<< "\n2. List of Data:\n"
			<< "3. Delete Data of User:\n" 
			<< "4. Search"
			<< endl;
		cin >> option;
		switch(option)
		{
			case 0:
				break;
			case 1:
				WriteToFile();
				break;
			case 2:
				ReadFile();
				break;
			case 3:
				Delete();
				break;
			case 4: Search();
				break;
			default:
				cout << "Enter from above option:" << endl;
				break;
		}
	} while(option!=0);
	return 0;
}
