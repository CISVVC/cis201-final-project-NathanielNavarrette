#include<iostream>
#include<locale>
#include<fstream>
#include<vector>
#include<string>
#include<iomanip>
#include<ctype.h>

class WORDCOUNT
{
public:
	void readWord(std::string input);
	void readLineNum(int line_number);
	std::string getWord();
	std::vector<int> getLineNums();

private:
	std::string word;
	std::vector<int> lineNumbers;
	bool checkExist(std::string);
	std::string removeItems(std::string clean_up);
};

void WORDCOUNT::readWord(std::string input)
{
	word = input;
}

void WORDCOUNT::readLineNum(int line_number)
{
	lineNumbers.push_back(line_number);
}

std::vector<int> WORDCOUNT::getLineNums()
{
	return lineNumbers;
}

std::string WORDCOUNT::getWord()
{
	return word;
}

int wordLength(std::string line, int word_number)
{
	std::string tmp = line;
        int count =1;
	int word_length =0;
        for(int j=0; j<tmp.length()-1;j++)
        {
                if(count == word_number)
                {
                        int go_through = j;
                        while(tmp[go_through] != 32 || tmp[go_through] == '\0' || tmp[go_through] == '\0')
                        {
                                word_length++;
                                go_through++;
                        }
                        return word_length;
                        break;
                }
                if(tmp[j] == 32)
                        count++;
        }
}

std::string getWord(std::string line, int word_number) 
{
	std::string tmp = line;
	int count =1;	
/*
	if(wordLength(line, word_number) > 0)
	{
*/
		std::string temp_string(wordLength(line, word_number), ' ');
	

	for(int j=0; j<tmp.length()-1;j++)
	{
		if(count == word_number)
		{
			int pos_count =0;
			int go_through = j;
			while(tmp[go_through] != 32)
			{
				temp_string[pos_count] = tmp[go_through];
				pos_count++;
				go_through++;
			}
			return temp_string;
			break;
		}
		if(tmp[j] == 32)
			count++;
	}
/*
	}else{
		std::string empty ="";
		return empty;
	}
*/
}

int countLineWords(std::string line)
{
	int word_count =0;
	for(int i =0; i<line.length()+1;i++)
		if(line[i] == 32 || line[i] == '\n')
			word_count++;

	return word_count;
		

}

int countFileWords(std::string file_name)
{
	std::ifstream input;
    	input.open(file_name.c_str());
	int word_count =0;
	

	if( input.is_open())
    	{
        	while(1)
        	{
            		char c;
            		input.get(c);
            		if(input.eof())
                		break;
			if(c == 32 || c == '\n')
				word_count++;
        	}
    	}else{
        std::cout << "File is not open for reading" << std::endl;
    	}

	return word_count;
}

int countLines(std::string file_name)
{
	std::ifstream input;
    	input.open(file_name.c_str());
	int line_num =0;
	

	if( input.is_open())
    	{
        	while(1)
        	{
            		char c;
            		input.get(c);
            		if(input.eof())
                		break;
			if(c == '\n')
				line_num++;
        	}
    	}else{
        std::cout << "File is not open for reading" << std::endl;
    	}

	return line_num;
}

//fill a vector up with the file line by line
std::vector<std::string> fillVector(std::string file_name)
{
	int linecount = countLines(file_name);
	std::vector<std::string> fill(linecount);
	std::ifstream my_input;
	my_input.open(file_name.c_str());

	for(int i=0;i<linecount;i++)
		getline(my_input, fill.at(i));	

	return fill;
}

std::vector<std::string> fillWords(std::vector<std::string> linevec)
{
	std::vector<std::string> tmp;
	for(int i=0;i<linevec.size();i++)
	{
		for(int j=0;j<countLineWords(linevec.at(i));j++)
		{
//			std::cout << getWord(linevec.at(i), j+1) << std::endl;
			tmp.push_back(getWord(linevec.at(i), j+1));
		}

	}

	return tmp;

}

void upperToLower(char &to_lower)
{
	if(to_lower >64 && to_lower < 91)
		to_lower+=32;
}

bool checkPunc(char check)
{
	for(int i=32;i<127;i++)
	{
		if(check == char(i))
			return false;
		if(i == 64)
			i = 90;
		if(i == 96)
			i = 122;
	}
	return true;
}

std::vector<std::string> cleanUp(std::vector<std::string> &clean)
{
	std::vector<std::string> return_me;

	for(int i=0; i<clean.size();i++)
	{
		std::string cleantmp, tmp2;
		cleantmp = clean.at(i);
		for(int j=0;j<cleantmp.length();j++)
		{
			upperToLower( cleantmp[j]);
			if(checkPunc(cleantmp[j]))
				tmp2.push_back( cleantmp[j]);
		}
		
		return_me.push_back(tmp2);
	}	
	return return_me;

}

int main()
{
	//This vector will contain all the information for studets, be sperated by each student id number;
	std::ifstream input;
    	std::string filename= "Alice.txt";
    	input.open(filename.c_str());
	
	//declare the vectors here
	std::vector<std::string> wordstmp;
	std::vector<std::string> linestmp;
	std::vector<std::string> cleanWords;
	std::vector<std::string> cleanLines;

	//vector to store the the file number (first vector) and store the line numbers (second vector)
	//std::vector<std::vector< std::string > > test;

	//Go through the classes.txt file and count the lines (number of classes there are) 
	
	//Function that goes through a file and fills it (by lines) with strings
	linestmp = fillVector(filename);	

	for(int i=0;i<linestmp.size();i++)
	{
		for(int j=0;j<countLineWords(linestmp.at(i));j++)
			wordstmp.push_back( getWord(linestmp.at(i), j+1) );
		wordstmp.push_back("cake.");
	}

	cleanLines = cleanUp(linestmp);	


	cleanWords = cleanUp(wordstmp);

	for(int i=0;i<cleanWords.size();i++)
		std::cout << i << std::setw(16) << cleanWords.at(i) << std::endl;

	

	return 0;
}
