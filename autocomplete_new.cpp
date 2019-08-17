#include<iostream>
#include<vector>
#include<fstream>
using namespace std;
vector<string>dic;
int idx=0;

struct trienode
{
	int index;
	trienode** children;
	trienode()
	{
		index=-1;
		children=new trienode*[26];
		for(int i=0;i<26;i++) children[i]=NULL;
	}
};

void insert(string s,trienode* head)
{
	trienode *current=head;   //temporary node = currrent
	for(int i=0;i<s.length();i++)
	{
		int val=s[i]-'a';
		if(current->children[val]==NULL)
		{
			current->children[val]=new trienode();
		}
		current=current->children[val];
	}
	dic.push_back(s);
	current->index=idx++;
}


void query1(trienode *head)
{
	if(head==NULL)
	return ;
	trienode *current=head;
	if(current->index>-1)  cout << dic[current->index] << std::endl;
	for(int i=0;i<26;i++)
	{
		if(current->children[i]!=NULL)
		query1(current->children[i]);
	}
}

void query(string s,trienode *head)
{
	trienode *current=head;
	for(int i=0;i<s.length();i++)
	{
		int val=s[i]-'a';
		if(current->children[val]==NULL)  //checking that if the word existed or not 
		{								//if not the adding it to dictonary
			insert(s,head);
			cout << "No suggestions " << endl;
			cout << "This Word is added to dictionary." << endl;
			return;
		}
		current=current->children[val];
	}
	query1(current);  //passing the control to print the values if existed
}
trienode* reading_file(trienode* head)
{
	fstream file;
	file.open("data1.txt");
	string s;
	while(file>>s)
	{ 
		insert(s,head);
	}
	file.close();
	return head;	
}
void adding_more_data(trienode* headx)
{
	cout<<"Enter the count of words to be added in dictionary: ";
	int n;
	cin>>n;
	
	cout<<"Enter the "<<n<<" words :\n";
	while(n--)
	{
		string s;
		cin>>s;
		insert(s,headx);
	}
}

int main() 
{
	trienode* head=new trienode();
	head=reading_file(head);
	
	cout<<"If you want to add more words then press 1 else 0";
	int x;
	cin>>x;
	
	if(x) 
	{
		adding_more_data(head);
	}
	
		int q;
		cout<<"Enter the number of queries you want : ";
		cin>>q;
	
		string s1;
		while(q--)
		{
			cin>>s1;
			query(s1,head);
		}
	
return 0;
}
