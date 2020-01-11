#include<iostream>
#include<fstream>
#include<string>
#include<vector>


std::string genOriginalSentence(
		const std::string& original, 
		std::string::size_type& sentinel,
		const std::string& word, 
		const std::string& note
	);

// return index of colon.
int getColonIndex(const std::string& str)
{
	const int len = str.length();
	for(int i=0; i<len; i++)
	{
		if(str[i] == ':')
			return i;
	}
	return -1;
}

void writeln(std::fstream& out, std::string& str)
{
	out << str << std::endl;
}

int main()
{
	std::fstream raw("script.txt");
	std::string tmp;
	std::string title, name;
	if(!raw.is_open())
	{
		std::cout << "bad!" << std::endl;
	}
	raw >> title;
	raw >> name;
	raw.get();

	std::string word, note;
	std::vector<std::string> original, translation;
	std::vector<std::string> originalHTML;
	std::string p("<p>");
	while(getline(raw, tmp))
	{
		if(tmp.empty())	//end of segment
		{
			p += "</p>\n";
			originalHTML.push_back(p);
			p = "<p>";
			std::cout << "=====================该段结束==================" << std::endl;
			continue;
		}
		if(tmp == "end")
		{
			originalHTML.push_back(p);
			std::cout << "=================原文结束=================" << std::endl;
			break;
		}

		original.push_back(tmp);
		std::string sentence(tmp);
		std::cout << tmp  << std::endl;
		getline(raw, tmp);

		if(tmp == "[")  //this sentence has note
		{
			std::string::size_type sentinel = 0;
			std::cout << "Note begin ------------------" << std::endl;
			
			// process note
			while(getline(raw, tmp))
			{
				if(tmp == "]")
					break;

				int ind = getColonIndex(tmp);
				word = tmp.substr(0, ind);
				note = tmp.substr(ind+1, tmp.length());
				std::cout << word << "  " << note << std::endl;

				// append note
				p += genOriginalSentence(sentence, sentinel, word, note);			
				std::cout << "Has benn writed!" << std::endl;
			}

			if(sentinel < sentence.length())
			{
				p += sentence.substr(sentinel);
			}
			std::cout << "Note end --------------------" << std::endl;
		}
		getline(raw, tmp);
		translation.push_back(tmp);
		std::cout << tmp << std::endl;
	}
	std::fstream outTest("test_p.txt", std::ios::out);
	if(!outTest.is_open())
	{
		std::cout << "bad!" << std::endl;
	}
	for(auto s : originalHTML)
		outTest << s;
	raw.close();
	outTest.close();
	return 0;
}

std::string genOriginalSentence(
		const std::string& original, 
		std::string::size_type& sentinel,
		const std::string& word, 
		const std::string& note
	)
{
	std::string ans;
	std::string::size_type pos = original.find(word, sentinel);
	if(pos != original.npos)
	{
		if(pos > sentinel)
		{
			ans += original.substr(sentinel, pos-sentinel);
		}

		ans += ("<span class=\"tooltip\">" 
			   + word
			   + "<span class=\"tooltiptext\">"
			   + word + ":" + note
			   + "</span></span>");
		sentinel = pos + word.length();
		std::cout << "Sentinel = " << sentinel << std::endl;
	}
	return ans;
}























