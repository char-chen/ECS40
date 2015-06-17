#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

typedef map<char, short> CVmap;

class Word
{
public:
  string word;
  int value;
  bool operator<(const Word& rhs) const
  {
     return word < rhs.word;
  } //operator < for comparison in set<Word>
  
  Word(string w, const CVmap& letterValues) : word(w), value(0)
  {
    //wildcard appended at the end, with "word_c" format. 
    if (word.find('_') != string::npos)
    {
      if (*word.rbegin())
        value -= letterValues.at(*word.rbegin());
      
      word.erase(word.end() - 2, word.end());
    } //wildcard operation
    
    for (string::iterator itr = word.begin(); itr != word.end(); itr++)
      value += letterValues.at(*itr);
  } //Word
  
  bool operator==(const Word& rhs) const
  {
    return word == rhs.word;
  } //operator ==
}; //class Word

void createMap(CVmap& m, const short values[]);
void readWords(set<Word>& s, const CVmap& m);
void unscramble(const set<Word>& s, const CVmap& m, ifstream& f);
void getSubstrings(string target, set<string>& s);
 
int main(int argc, char **argv)
{
  set<Word> dictionary;
  CVmap letterVal;
  short values[26] = {1, 3, 3, 2, 1, 4, 2, 4, 2, 8,
  5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
  
  createMap(letterVal, values);
  readWords(dictionary, letterVal);
  
  ifstream scrambled(argv[1]);
  unscramble(dictionary, letterVal, scrambled);
  scrambled.close(); 
} //main

void createMap(CVmap& map, const short values[])
{
  for (char c = 'a'; c <= 'z'; c++, values++)
    map.insert(CVmap::value_type(c, *values));
} //createMap

void readWords(set<Word>& wordBank, const CVmap& letterValues)
{
  ifstream wordFile("words.txt");
  string str;
  
  while (getline(wordFile, str))
  {
    if (str.size() <= 7)
    {
      string::iterator itr; 
      
      for (itr = str.begin(); itr != str.end(); itr++)
        if (!islower(*itr))
          break;

      if (itr == str.end())
      {  
        Word w(str, letterValues);
        wordBank.insert(w);
      } //legal word
    } //check if legal
  } //store words
  
  wordFile.close();
} //readWords
 
void unscramble(const set<Word>& wordBank, const CVmap& m, ifstream& sbfile)
{
  string str;
  
  while (getline(sbfile, str))
  {
    int highVal = 0;
    set<Word> highest;
    set<string> subs; 
    getSubstrings(str, subs);
    
    for (set<string>::iterator itr = subs.begin(); itr != subs.end(); itr++)
    {
      Word word(*itr, m);
      set<Word>::iterator match = wordBank.find(word); 
        
      if (match != wordBank.end() && word.value >= highVal)
      {
        if (word.value > highVal)
          highest.clear();
          
        highVal = word.value;
        highest.insert(word);
      } //store highest valued words
    } //find each substring 
    
    cout << setw(2) << right << highVal << " " << str << ":";
      
    if (highVal > 0)
      for (set<Word>::iterator it = highest.begin(); it != highest.end(); it++)
       cout << " " << it->word;
    else //found
      cout << " No words found.";

    cout << endl;
  } //check combinations
} //scrabble

void getSubstrings(string target, set<string>& substrs)
{
  if (target.size() > 7)
    return;
   
  char wildcard = '\0';
  
  if (target.find(' ') != string::npos)
  {
    target.erase(remove(target.begin(), target.end(), ' '), target.end());
    target += wildcard = 'a';
  } //add wildcard
  
  do
  {
    string str = target;
    sort(str.begin(), str.end()); 
    
    do 
    {
      for (unsigned int i = 0; i < str.size(); i++)
        substrs.insert(str.substr(0, i + 1) + "_" + wildcard);
    } while (next_permutation(str.begin(), str.end()));
    
    if (wildcard)
      target.at(target.size() - 1) = ++wildcard;
  } while (wildcard && wildcard <= 'z');
} //getSubstring
