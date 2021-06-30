#include<iostream>
using namespace std;
#include<fstream>
#include<vector>
#include<string>
#include<iomanip>

// Tags class to store frequency of each word 
struct Tags
{
	string word;
	int count;	
	Tags(string s)
	{
		word = s;
		count = 1;
	}
	bool isMatch(string w)
	{
		if(word==w)
		{
			count = count + 1;
			return true;
		}
		return false;
	}
};

// inputFile where tags are placed, outputFile where ranking of each tags will be saved.
// Note: In input file each line is a keyword tag. 
void readFile(const char * inputFile, const char * outputFile)
{
	vector<Tags> obj;
	ifstream ifs;
	ifs.open(inputFile);
	string str;
	while (std::getline(ifs, str)) 
	{
		int size = obj.size();
		if(size==0)
		{
			Tags t(str);
			obj.push_back(t);				
		}
		else
		{
			bool flag = false;
			int index = -1;
			for(int i=0;i<size;i++)
			{
				if(obj[i].isMatch(str)==true)
				{
					flag = true;
					index = i;	
				}	
			}
			if(flag==false)
			{
				Tags t(str);
				obj.push_back(t);
			}	
		}
	}
	int n = obj.size();
	for(int i=0;i<n;i++)
	{
		int max = i;
		for(int j=i+1;j<n;j++)
		{
			if(obj[max].count<obj[j].count)
			{
				max = j;
			}
		}
		Tags temp = obj[i];
		obj[i] = obj[max];
		obj[max] = temp;
	}
	ifs.close();
	ofstream ofs(outputFile);
	cout<<setw(30)<<left<<"Tags"<<"Ranking";
	ofs<<setw(30)<<left<<"Tags"<<"Ranking"<<"\n";
	for(int i=0;i<n;i++)
	{
		cout<<'\n'<<setw(30)<<left<<obj[i].word.data() << obj[i].count;	
		ofs<<setw(30)<<left<<obj[i].word.data() << obj[i].count;
		if(i!=n-1)
		{
			ofs<<"\n";	
		}	
	}	
	ofs.close();
}

int main()
{
	//tags.txt is a file where tags are placed line by line
	//rankTags.txt is a output file where ranking of each tag will be displayed
	readFile("tags.txt","rankTags.txt");
	return 0;
}
