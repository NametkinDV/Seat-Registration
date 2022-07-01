#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


void reserve(ofstream &out, vector<string> &row, const int &num_row, int goal, int count) // Разрешение бронирования
{
  out << "Passengers can take seats:";
  while (count-- != 0) // Пока не будут помечены все забронированные места
    {
      row[num_row][goal] = 'X';
      out << " " << num_row+1;

      switch(goal)
	{
	case 0: out << "A"; break;
	case 1: out << "B"; break;
	case 2: out << "C"; break;
	  
	case 4: out << "D"; break;
	case 5: out << "E"; break;
	case 6: out << "F"; break;
	}

       ++goal;
    }
  out << endl;

  for (string &i : row)
    out << i << endl;
}


void changes(vector<string> &raw, const int &num_row, int goal, int count) // Закрепление брони
{
  while (count-- != 0) // Пока не будут помечены все забронированные места
    {
      raw[num_row][goal] = '#';
      ++goal;
    }
}


void find(ofstream &out, vector<string> &row, const int &size_row, const int &count, const string &side, const string &prefers) // Проверка мест
{
  for (int r = 0; r < size_row; ++r) // Итерация рядов
    {
      int start_count = 6; // Крайнее правое место
      
      if (side == "right") // Места по правой стороне
	{
	  if (prefers == "window") // Места по правой стороне у окна
	    {
	      int goal = start_count;
	      
	      for (int s = 0; s < count; ++s)
		{
		  if (row[r][start_count] == '#') break;
		  else start_count--;
		}
	      
	      if (start_count == goal - count) // Если запрошеные места присутствуют
		{
		  reserve(out, row, r, (goal-count)+1, count);
		  changes(row, r, (goal-count)+1, count);
		  return;
		}
	    }
	  
	  else if (prefers == "aisle") // Места по правой стороне у прохода
	    {
	      start_count -= 2;
	      int goal = start_count;
	      
	      for (int s = 0; s < count; ++s)
		{
		  if (row[r][start_count] == '#') break;
		  else start_count++;
		}
	      
	      if (start_count == goal + count) // Если запрошеные места присутствуют
		{
		  reserve(out, row, r, goal, count);
		  changes(row, r, goal, count);
		  return;
		}
	    }
	}
      
      else if (side == "left") // Места по левой стороне
	{
	  start_count -= 3;
	  
	  if (prefers == "aisle") // Места по левой стороне у прохода
	    {
	      int goal = start_count;
	      
	      for (int s = 0; s < count; ++s)
		{
		  if (row[r][start_count] == '#') break;
		  else start_count--;
		}
	      
	      if (start_count == goal - count) // Если запрошеные места присутствуют
		{
		  reserve(out, row, r, goal-count, count);
		  changes(row, r, goal-count, count);
		  return;
		}
	    }
	  
	  else if (prefers == "window") // Места по левой стороне у окна
	    {
	      start_count -= 3;
	      int goal = start_count;
	      
	      for (int s = 0; s < count; ++s)
		{
		  if (row[r][start_count] == '#') break;
		  else start_count++;
		}
	      
	      if (start_count == goal + count) // Если запрошеные места присутствуют
		{
		  reserve(out, row, r, goal, count);
		  changes(row, r, goal, count);
		  return;
		}
	    }
	}     
    }
  out << "Cannot fulfill passengers requirements" << endl; // Если запрошеные места отстутствуют
}


int main()
{
  int size_row, size_goals;
  vector<string> row;
  
  ifstream input_file("input.txt");
  ofstream output_file("output.txt");
  
  if (!input_file.good())
    {
      return 0;
    }
  
  input_file >> size_row;
  
  for (short i = 0; i < size_row; ++i) // Считывание рядов из файла
    {
      string temp_str;
      input_file >> temp_str;
      row.push_back(temp_str);
    }
  
  input_file >> size_goals;
  
  
  for(short i = 0; i < size_goals; ++i) // Считывание запросов на бронирование из файла
    {  
      int count;
      string side, prefers;
      
      input_file >> count;
      input_file >> side;
      input_file >> prefers;
      
      find(output_file, row, size_row, count, side, prefers);   
    }
  
  return 0;
}
