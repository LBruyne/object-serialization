#ifndef _SERIALIZE_BIN_H_
#define _SERIALIZE_BIN_H_
#define _CRT_SECURE_NO_WARNINGS

#include "global.h"
using namespace std;

namespace serial2bin
{
	//arithmetic types and pair
	template<class T>
	void serialize(T object, std::string filename)
	{
		std::fstream file;
		file.open(filename, std::ios::out | std::ios::binary);
		file.write((char*)(&object), sizeof(object));
		file.flush();
		file.close();
	}
	template<class T>
	void deserialize(T &object, std::string filename)
	{
		object = T();
		std::fstream file;
		file.open(filename, std::ios::in | std::ios::binary);
		file.read((char*)(&object), sizeof(object));
		file.close();
	}

	//string
	//string_write to write in the file
	static ostream& write(ostream& file, std::string& str) 
	{
		int size = str.size();
		file.write((char*)(&size), sizeof(size));
		file.write(str.c_str(), str.size());
		return file;
	}
	//string_const_write is for set<>
	static ostream& write(ostream& file, const std::string& str)
	{
		int size = str.size();
		file.write((char*)(&size), sizeof(size));	//store the size of the string first
		file.write(str.c_str(), str.size());
		return file;
	}
	//serialize for string
	void serialize(string str, std::string filename)
	{
		std::fstream file;
		file.open(filename, std::ios::out | std::ios::binary);
		write(file, str);
		file.close();
	}
	//string_read is used to read the binary data
	static istream& read(istream& file, std::string& str) 
	{
		int size = 0;
		file.read((char*)(&size), sizeof(size));	//read the size of the string firsr
		str.resize(size);
		file.read(const_cast<char*> (str.c_str()), size);
		return file;
	}
	//deserialize for string
	void deserialize(string &str, std::string filename)
	{
		std::fstream file;
		file.open(filename, std::ios::in | std::ios::binary);
		read(file, str);
		file.close();
	}
	
	//vector
	//vector_write is used to write the data into the file
	template <class T>
	static ostream& write(ostream& file, vector<T>& v)
	{
		int size = v.size();
		file.write((char*)(&size), sizeof(size));	//write the size of the vector first
		for (auto& item : v)
			file.write((char*)(&item), sizeof(item));
		return file;
	}
	//vector<string>_write
	static ostream& write(ostream& file, vector<string>& v)
	{
		int size = v.size();
		file.write((char*)(&size), sizeof(size));
		for (auto& item : v)
			write(file, item);
		return file;
	}
	//serialize for vector
	template<class T>
	void serialize(vector<T>& v, std::string filename)
	{
		std::ofstream file;
		file.open(filename, std::ios::out | std::ios::binary);
		write(file, v);
		file.close();
	}
	template<class T>
	void serialize(vector<vector<T>>& v, std::string filename)
	{
		std::ofstream file;
		file.open(filename, std::ios::out | std::ios::binary);
		int size = v.size();
		file.write((char *)(&size), sizeof(size));
		for (auto vec : v)
			write(file, vec);
		file.close();
	}
	//vector_read is used to read the binary data
	template<class T>
	static istream& read(istream& file, vector<T>& v)
	{
		int i;
		int size;
		if (file.eof());
		else
		{
			file.read((char*)(&size), sizeof(size));	//read the size of the vector first
			for (i = 0; i < size; i++)
			{
				T object;
				file.read((char*)(&object), sizeof(object));	//read the members one by one
				v.push_back(object);
			}
		}
		return file;
	}
	//vector<string>_read is used to read the string data
	static istream& read(istream& file, vector<string>& v)
	{
		int i;
		int size;
		v.clear();
		if (file.eof());
		else
		{
			file.read((char*)(&size), sizeof(size));
			for (i = 0; i < size; i++)
			{
				string object;
				read(file, object);
				v.push_back(object);
			}
		}
		return file;
	}
	//deserialize for vector
	template<class T>
	void deserialize(vector<T>& v, std::string filename)
	{
		std::ifstream file;
		file.open(filename, std::ios::in | std::ios::binary);
		read(file, v);
		file.clear();
	}
	template<class T>
	void deserialize(vector<vector<T>>& v, std::string filename)
	{
		std::ifstream file;
		file.open(filename, std::ios::in | std::ios::binary);
		int size;
		file.read((char *)(&size), sizeof(size));
		for (int i = 0;i < size;i++)
		{
			vector<T> vec;
			read(file, vec);
			v.push_back(vec);
		}
		file.clear();
	}

	//list
	//list_write is to write the list(except string) data
	template <class T>
	static ostream& write(ostream& file, list<T>& l)
	{
		int size = l.size();
		file.write((char*)(&size), sizeof(size));
		for (auto& item : l)
			file.write((char*)(&item), sizeof(item));
		return file;
	}
	//list<string>_write is to write the list<string> data
	static ostream& write(ostream& file, list<string>& l)
	{
		int size = l.size();
		file.write((char*)(&size), sizeof(size));
		for (auto& item : l)
			write(file, item);
		return file;
	}
	//serialize for list
	template<class T>
	void serialize(list<T>& l, std::string filename)
	{
		std::ofstream file;
		file.open(filename, std::ios::out | std::ios::binary);
		write(file, l);
		file.close();
	}
	//list<string>_read 
	static istream& read(istream& file, list<string>& l)
	{
		int i;
		int size;
		l.clear();
		if (file.eof());
		else
		{
			file.read((char*)(&size), sizeof(size));
			for (i = 0; i < size; i++)
			{
				string object;
				read(file, object);		//use string_read to read the string type data
				l.push_back(object);
			}
		}
		return file;
	}
	//list_read
	template<class T>
	static istream& read(istream& file, list<T>& l)
	{
		int i;
		int size;
		l.clear();	//clear the initial data
		if (file.eof());
		else
		{
			file.read((char*)(&size), sizeof(size));	//store the size of the list first
			for (i = 0; i < size; i++)
			{
				T object;
				file.read((char*)(&object), sizeof(object));
				l.push_back(object);
			}
		}
		return file;
	}
	//deseriliaze for list
	template<class T>
	void deserialize(list<T>& l, std::string filename)
	{
		std::ifstream file;
		file.open(filename, std::ios::in | std::ios::binary);
		read(file, l);
		file.clear();
	}

	//set
	//set_write almost the same as others
	template <class T>
	static ostream& write(ostream& file, set<T>& s)
	{
		int size = s.size();
		file.write((char*)(&size), sizeof(size));
		for (auto& item : s)
			file.write((char*)(&item), sizeof(item));
		return file;
	}
	//set<string>_write
	static ostream& write(ostream& file, set<string>& s)
	{
		int size = s.size();
		file.write((char*)(&size), sizeof(size));
		for (auto& item : s)
			write(file, item);
		return file;
	}
	//serialize for set
	template<class T>
	void serialize(set<T>& s, std::string filename)
	{
		std::ofstream file;
		file.open(filename, std::ios::out | std::ios::binary);
		write(file, s);
		file.close();
	}
	//set<string>_read 
	static istream& read(istream& file, set<string>& s)
	{
		int i;
		int size;
		s.clear();
		if (file.eof());
		else
		{
			file.read((char*)(&size), sizeof(size));
			for (i = 0; i < size; i++)
			{
				string object;
				read(file, object);
				s.insert(object);//set.insert
			}
		}
		return file;
	}
	//set_read almost the same as others
	template<class T>
	static istream& read(istream& file, set<T>& s)
	{
		int i;
		int size;
		s.clear();
		if (file.eof());
		else
		{
			file.read((char*)(&size), sizeof(size));
			for (i = 0; i < size; i++)
			{
				T object;
				file.read((char*)(&object), sizeof(object));
				s.insert(object);
			}
		}
		return file;
	}
	//deserialize for set
	template<class T>
	void deserialize(set<T>& s, std::string filename)
	{
		std::ifstream file;
		file.open(filename, std::ios::in | std::ios::binary);
		read(file, s);
		file.clear();
	}
	
	//map
	//map_write is to write the map_data
	template <class K, class V>
	static ostream& write(ostream& file, map<K, V>& m)
	{
		int size = m.size();	//store the size first
		file.write((char*)(&size), sizeof(size));
		for (auto& item : m)
		{
			file.write((char*)(&item.first), sizeof(item.first));
			file.write((char*)(&item.second), sizeof(item.second));
		}
		return file;
	}
	//belows are three stype of map<string>,almost the same
	template <class K>
	static ostream& write(ostream& file, map<K, string>& m)
	{
		int size = m.size();
		file.write((char*)(&size), sizeof(size));
		for (auto& item : m)
		{
			file.write((char*)(&item.first), sizeof(item.first));
			write(file, item.second);
		}
		return file;
	}
	template <class V>
	static ostream& write(ostream& file, map<string, V>& m)
	{
		int size = m.size();
		file.write((char*)(&size), sizeof(size));
		for (auto& item : m)
		{
			write(file, item.first);
			file.write((char*)(&item.second), sizeof(item.second));
		}
		return file;
	}
	static ostream& write(ostream& file, map<string, string>& m)
	{
		int size = m.size();
		file.write((char*)(&size), sizeof(size));
		for (auto& item : m)
		{
			write(file, item.first);
			write(file, item.second);
		}
		return file;
	}
	//serialize for map
	template<class K, class V>
	void serialize(map<K, V>& m, std::string filename)
	{
		std::ofstream file;
		file.open(filename, std::ios::out | std::ios::binary);
		write(file, m);
		file.close();
	}
	//map_read
	template<class K, class V>
	static istream& read(istream& file, map<K, V>& m)
	{
		int i;
		int size;
		m.clear();
		if (file.eof());
		else
		{
			file.read((char*)(&size), sizeof(size));
			for (i = 0; i < size; i++)
			{
				K k;
				V v;
				file.read((char*)(&k), sizeof(k));
				file.read((char*)(&v), sizeof(v));
				m[k] = v;
			}
		}
		return file;
	}
	//belows are three type of map<string>, almost the same, only change the positioin
	template<class K>
	static istream& read(istream& file, map<K, string>& m)
	{
		int i;
		int size;
		m.clear();
		if (file.eof());
		else
		{
			file.read((char*)(&size), sizeof(size));
			for (i = 0; i < size; i++)
			{
				K k;
				string v;
				file.read((char*)(&k), sizeof(k));
				read(file, v);
				m[k] = v;
			}
		}
		return file;
	}
	template< class V>
	static istream& read(istream& file, map<string, V>& m)
	{
		int i;
		int size;
		m.clear();
		if (file.eof());
		else
		{
			file.read((char*)(&size), sizeof(size));
			for (i = 0; i < size; i++)
			{
				string k;
				V v;
				read(file, k);
				file.read((char*)(&v), sizeof(v));
				m[k] = v;
			}
		}
		return file;
	}
	static istream& read(istream& file, map<string, string>& m)
	{
		int i;
		int size;
		m.clear();
		if (file.eof());
		else
		{
			file.read((char*)(&size), sizeof(size));
			for (i = 0; i < size; i++)
			{
				string k, v;
				read(file, k);
				read(file, v);
				m[k] = v;
			}
		}
		return file;
	}
	//deseialize for map
	template<class K, class V>
	void deserialize(map<K, V>& m, std::string filename)
	{
		m = map<K, V>();
		std::ifstream file;
		file.open(filename, std::ios::in | std::ios::binary);
		read(file, m);
		file.clear();
	}

	//user_defined
	void userDefinedType(string file)
	{
		return;
	}
	template<class H,class ...Args>
	void userDefinedType(string file, H head, Args ...rest)
	{
		serialize(head, file);
		userDefinedType(file, rest...);
	}
	
}

#endif