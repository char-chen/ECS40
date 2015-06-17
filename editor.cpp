#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

void readText(vector<string>& v, ifstream& file);
void readCommands(vector<string>& v, ifstream& file);
void insert(vector<string>& v, string command);
void replace(vector<string>& v, string command);
void find(vector<string>& v, string command);
void deleteLine(vector<string>& v, string command);
void erase(vector<string>& v, string command);
void copyPaste(vector<string>& v, string command);
void move(vector<string>& v, string command);
void save(const vector<string>& v, ofstream& file);

int main(int argc, char **argv)
{
  vector<string> text;
  
  ifstream source(argv[1]);
  readText(text, source);
  
  ifstream commands(argv[2]);
  readCommands(text, commands);
  
  ofstream results(argv[3]);
  save(text, results); 
} //main

void readText(vector<string>& v, ifstream& sourceFile)
{
  string line;
  
  if (sourceFile) 
    while (getline(sourceFile, line))
      v.push_back(line += "\n");
  
  sourceFile.close();
} //readText

void readCommands(vector<string>& v, ifstream& commandFile)
{
  string command;
   
  while (getline(commandFile, command))
  {
    string::iterator itr = command.begin();
    command = command.substr(2);
    
    if (*itr == 'I')
      insert(v, command);
    else //Replace
      if (*itr == 'R')
        replace(v, command);
    else //Find
      if (*itr == 'F')
        find(v, command);
    else //Delete
      if (*itr == 'D')
        deleteLine(v, command);
    else //Erase
      if (*itr == 'E')
        erase(v, command);
    else //Copy and Paste
      if (*itr == 'C')
        copyPaste(v, command);
    else //Move
      if (*itr == 'M')
        move(v, command);
  } //extract commands
} //readCommands

void insert(vector<string>& v, string command)
{
  istringstream iss(command);
  int line_number, position;
  string str;
  iss >> line_number >> position;
  vector<string>::iterator itr = v.begin() + line_number;
  getline(iss, str);
  str.erase(str.begin());
  itr->insert(position, str);
} //insert

void replace(vector<string>& v, string command)
{
  istringstream iss(command);
  int line_number, start_position, end_position;
  string str;
  iss >> line_number >> start_position >> end_position;
  vector<string>::iterator itr = v.begin() + line_number;
  getline(iss, str);
  str.erase(str.begin());
  itr->replace(start_position, end_position - start_position, str); 
} //replace

void find(vector<string>& v, string command)
{
  cout << command << " ";
  int line = 0;
  
  for (vector<string>::iterator itr = v.begin(); itr != v.end(); itr++, line++)
    if (itr->find(command) != string::npos)
      cout << line << " ";
  
  cout << endl;
} //find

void deleteLine(vector<string>& v, string command)
{
  istringstream iss(command);
  int start_line, end_line;
  iss >> start_line >> end_line;
  v.erase(v.begin() + start_line, v.begin() + end_line + 1);
} //deleteLine

void erase(vector<string>& v, string command)
{
  for (vector<string>::iterator itr = v.begin(); itr != v.end(); itr++)
  {
    if (itr->find(command) != string::npos)
    {
      itr->erase(itr->find(command), command.size());
        
      if (*itr == "\n")
        v.erase(itr);
    } //found
  } //traverse text
} //erase

void copyPaste(vector<string>& v, string command)
{
  istringstream iss(command);
  int start_line, end_line, dest;
  iss >> start_line >> end_line >> dest;
  v.insert(v.begin() + dest, v.begin() + start_line, v.begin() + end_line + 1);
} //copyPaste

void move(vector<string>& v, string command)
{
  istringstream iss(command);
  int start_line, end_line, dest, final_dest;
  iss >> start_line >> end_line >> dest;
  
  if (dest > start_line) 
    final_dest = dest - (end_line - start_line + 1);
  else //final line to insert
    final_dest = dest;

  vector<string> tmp(v.begin() + start_line, v.begin() + end_line + 1);
  v.erase(v.begin() + start_line, v.begin() + end_line + 1);
  v.insert(v.begin() + final_dest, tmp.begin(), tmp.end());
} //move

void save(const vector<string>& v, ofstream& outf)
{
  for (vector<string>::const_iterator itr = v.begin(); itr != v.end(); itr++)
    outf << *itr;

  outf.close();
} //save text
