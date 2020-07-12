#include "serial2bin.h"
#include "serial2xml.h"
using namespace serial2xml;
using namespace serial2bin;
using namespace std;

// user defined type for test.
struct UserDefinedType {
	int idx;
	std::string name;
	std::vector<double> data;
};

// test for serial2bin module.
void arithmetic_type_1();	// int
void arithmetic_type_2();	// double
void string_type();			//string
void pair_type();			//pair<int, double>
void vector_type_1();		//vector<int>
void vector_type_2();		//vector<double>
void vector_type_3();		//vector<string>
void vector_type_4();		//vector<pair<int, double>>
void vector_type_5();		//vector<vector<int>>
void list_type_1();			//list<int>
void list_type_2();			//list<double>
void list_type_3();			//list<string>
void set_type_1();			//set<int>
void set_type_2();			//set<double>
void set_type_3();			//set<string>
void map_type_1();			//map<int, string>
void map_type_2();			//map<double, string>
void map_type_3();			//map<int, double>


// test for xml module.
void xml_arithmetic_1(); // int
void xml_arithmetic_2(); // double
void xml_arithmetic_3(); // char
void xml_string(); // string
void xml_vector_int(); // vector<int>
void xml_vector_vector_int(); // vector<vector<int>>
void xml_vector_string(); // vector<string>
void xml_vector_pair(); // vector<pair<int, double>>
void xml_list_int(); // list<int>
void xml_pair_1(); // pair<int, float>
void xml_pair_2(); // pair<vector<int>, list<float>>
void xml_set_string(); // set<string>
void xml_map_1(); // map<double, string>
void xml_map_2(); // map<vector<int>, list<float>>

int main()
{
	int choice;
	while(true) {
		cout << "Test for Object Serialization" << endl;
		cout << "Here are the choices" << endl;
		cout << "1.Binary Module 2.XML Module 3.Exit" << endl;
		cin >> choice;
		switch (choice) {
			case 1: {
				//test for arithmetic types 
				//(1) int as sample	//(2) double
				arithmetic_type_1();arithmetic_type_2();
				//test for string 
				string_type();
				//test for pair
				pair_type();
				//test for vector
				//(1) vector<int> (2) vector<double> (3) vector<string> (4) vector<pair> (5) vector<vector<int>>
				vector_type_1();vector_type_2();vector_type_3();vector_type_4();vector_type_5();
				//test for list
				//(1) list<int> (2) list<double> (3) list<string>
				list_type_1();list_type_2();list_type_3();
				//test for set
				//(1) set<int> (2) set<double> (3) set<string>
				set_type_1();set_type_2();set_type_3();
				//test for map
				//(1) map<int ,string> (2) map<double, string> (3) map<int ,double>
				map_type_1();map_type_2();map_type_3();

				//userDefinedType serialization 1
				struct UserDefinedType u = { 5, "Tom", {1.2, 3.4, 7, 7} };
				struct UserDefinedType v;
				serial2bin::serialize(u.idx, "user_idx.data");
				serial2bin::serialize(u.name, "user_name.data");
				serial2bin::serialize(u.data, "user_data.data");
				serial2bin::deserialize(v.idx, "user_idx.data");
				serial2bin::deserialize(v.name, "user_name.data");
				serial2bin::deserialize(v.data, "user_data.data");
				if ((u.idx == v.idx) && (u.name == v.name) && (u.data == v.data))
					cout << "UserDefinedType is current!" << endl;
				else cout << "UserDefinedType is wrong!" << endl;

				//userDefinedType serialization 2
				struct UserDefinedType testStru = { 5, "Tom", {1.2, 3.4, 7, 7} };
				userDefinedType("user.data", testStru.idx, testStru.name, testStru.data);
				system("PAUSE");
				break;
			}
			case 2: {
				// test for arithmetic types 
				// (1) int //(2) double //(3) char
				xml_arithmetic_1();xml_arithmetic_2();xml_arithmetic_3();
				// string
				xml_string();
				// (1) vector<int> (2) vector<vector<int> (3) vector<string> (4) vector<pair<int,double>>
 				xml_vector_int();xml_vector_vector_int();xml_vector_string();xml_vector_pair();
				// (1) pair<int,double> (2) pair<vector<int>, list<float>>
				xml_pair_1();xml_pair_2();
				// list<int>
				xml_list_int();
				// set<string>
				xml_set_string();
				// (1) map<double, string> (2) map<vector<int>, list<float>>
				xml_map_1();xml_map_2();
				
				// Test User Defined Type
				struct UserDefinedType testStru = { 5, "Tom", {1.2, 3.4, 7, 7} };
				XMLSerializerBase<int> base;
				base.userDefinedTypeToXML("testStruct.xml", testStru.idx, testStru.name, testStru.data);
				cout << "Output a xml.file of USer-Defined-Type already!" << endl;
				system("PAUSE");
				break;
			}
			case 3: 
				exit(0);
			default:
				break;
		}
	};
	system("pause");
	return 0;
}

void arithmetic_type_1()
{
	cout << "test for arithmetic types (1) int" << endl;
	int n0 = 256, n1;
	serialize(n0, "arith_1.data");
	deserialize(n1, "arith_1.data");
	cout << "n0 = " << n0 << endl;
	cout << "n1 = " << n1 << endl;
	cout << "Is equal:" << (n0 == n1) << endl;
	cout << endl;
}
void arithmetic_type_2()
{
	cout << "test for arithmetic types (2) double" << endl;
	double n0 = 12.12, n1;
	serialize(n0, "arith_2.data");
	deserialize(n1, "arith_2.data");
	cout << "n0 = " << n0 << endl;
	cout << "n1 = " << n1 << endl;
	cout << "Is equal:" << (n0 == n1) << endl;
	cout << endl;
}
void string_type()
{
	cout << "test for string" << endl;
	string str0 = "test", str1;
	serialize(str0, "string.data");
	deserialize(str1, "string.data");
	cout << "str0 = " << str0 << endl;
	cout << "str1 = " << str1 << endl;
	cout << "Is equal:" << (str0 == str1) << endl;
	cout << endl;
}
void pair_type()
{
	cout << "test for pair" << endl;
	pair<int, double> p0 = { 256,12.12 }, p1;
	serialize(p0, "pair.data");
	deserialize(p1, "pair.data");
	cout << "p0 = " << " <" << p0.first << "," << p0.second << ">" << endl;
	cout << "p1 = " << " <" << p1.first << "," << p1.second << ">" << endl;
	cout << "Is equal:" << (p0 == p1) << endl;
	cout << endl;
}
void vector_type_1()
{
	cout << "test for vector (1) vector<int>" << endl;
	vector<int> v0 = { 12,13,14 }, v1;
	serialize(v0, "vec1.data");
	deserialize(v1, "vec1.data");
	cout << "v0 = " << " {" << v0[0] << "," << v0[1] << "," << v0[2] << "}" << endl;
	cout << "v1 = " << " {" << v1[0] << "," << v1[1] << "," << v1[2] << "}" << endl;
	cout << "Is equal:" << (v0 == v1) << endl;
	cout << endl;
}
void vector_type_2()
{
	cout << "test for vector (2) vector<double>" << endl;
	vector<double> v0 = { 12.12,13.13,14.14 }, v1;
	serialize(v0, "vec2.data");
	deserialize(v1, "vec2.data");
	cout << "v0 = " << " {" << v0[0] << "," << v0[1] << "," << v0[2] << "}" << endl;
	cout << "v1 = " << " {" << v1[0] << "," << v1[1] << "," << v1[2] << "}" << endl;
	cout << "Is equal:" << (v0 == v1) << endl;
	cout << endl;
}
void vector_type_3()
{
	vector<string> v0, v1;
	cout << "test for vector (3) vector<string>" << endl;
	v0 = { "string1","string2","string3" };
	v1 = { "1","2","3" };
	serialize(v0, "vec3.data");
	deserialize(v1, "vec3.data");
	cout << "v0 = " << " {" << v0[0] << "," << v0[1] << "," << v0[2] << "}" << endl;
	cout << "v1 = " << " {" << v1[0] << "," << v1[1] << "," << v1[2] << "}" << endl;
	cout << "Is equal:" << (v0 == v1) << endl;
	cout << endl;
}
void vector_type_4()
{
	cout << "test for vector (4) vector<pair>" << endl;
	pair<int, double>p0, p1, p2;
	p0 = { 12,12.12 };p1 = { 13,13.13 };p2 = { 14,14.14 };
	vector<pair<int, double>> v0, v1;
	v0.push_back(p0);
	v0.push_back(p1);
	v0.push_back(p2);

	serialize(v0, "vec4.data");
	deserialize(v1, "vec4.data");
	cout << "v0 = " << " {" << " <" << v0[0].first << "," << v0[0].second << ">" << "," << " <" << v0[1].first << "," << v0[1].second << ">" << " <" << v0[2].first << "," << v0[2].second << ">" << "}" << endl;
	cout << "v1 = " << " {" << " <" << v1[0].first << "," << v1[0].second << ">" << "," << " <" << v1[1].first << "," << v1[1].second << ">" << " <" << v1[2].first << "," << v1[2].second << ">" << "}" << endl;
	cout << "Is equal:" << (v0 == v1) << endl;
	cout << endl;
}
void vector_type_5()
{
	cout << "test for vector (5) vector<vector<int>>" << endl;
	vector<vector<int>> v0 = { {1,2,3,4,5,6,7}, {2,3,4,5,6}, {1,2,3,4} }, v1;
	serialize(v0, "vec5.data");
	deserialize(v1, "vec5.data");
	cout << "v0 =: {";
	for (auto i : v0)
	{
		cout << "{ ";
		for (auto j : i) cout << j << " ";
		cout << "}";
	}
	cout <<"}"<< endl;
	cout << "v1 =: {";
	for (auto i : v1)
	{
		cout << "{ ";
		for (auto j : i) cout << j << " ";
		cout << "}";
	}
	cout << "}" << endl;
	cout << "Is equal:" << (v0 == v1) << endl;
	cout << endl;
}
void list_type_1()
{
	cout << "test for list (1) list<int>" << endl;
	list<int> l0, l1;
	l0.push_back(12);
	l0.push_back(13);
	l0.push_back(14);
	l0.push_back(256);
	serialize(l0, "list1.data");
	deserialize(l1, "list1.data");
	list<int> ::iterator it0 = l0.begin();
	list<int> ::iterator it1 = l1.begin();
	cout << "l0 : ";
	for (it0 = l0.begin();it0 != l0.end();it0++)
		cout << *it0 << " ";
	cout << endl;
	cout << "l1 : ";
	for (it1 = l1.begin();it1 != l1.end();it1++)
		cout << *it1 << " ";
	cout << endl;
	cout << "Is equal:" << (l0 == l1) << endl;
	cout << endl;
}
void list_type_2()
{
	cout << "test for list (2) list<double>" << endl;
	list<double> l0, l1;
	l0.push_back(12.12);
	l0.push_back(13.13);
	l0.push_back(14.14);
	l0.push_back(256.256);
	serialize(l0, "list2.data");
	deserialize(l1, "list2.data");
	list<double> ::iterator it0 = l0.begin();
	list<double> ::iterator it1 = l1.begin();
	cout << "l0 : ";
	for (it0 = l0.begin();it0 != l0.end();it0++)
		cout << *it0 << " ";
	cout << endl;
	cout << "l1 : ";
	for (it1 = l1.begin();it1 != l1.end();it1++)
		cout << *it1 << " ";
	cout << endl;
	cout << "Is equal:" << (l0 == l1) << endl;
	cout << endl;
}
void list_type_3()
{
	cout << "test for list (3) list<string>" << endl;
	list<string> l0, l1;
	l0.push_back("string1");
	l0.push_back("string2");
	l0.push_back("string3");
	serialize(l0, "list3.data");
	deserialize(l1, "list3.data");
	list<string> ::iterator it0 = l0.begin();
	list<string> ::iterator it1 = l1.begin();
	cout << "l0 : ";
	for (it0 = l0.begin();it0 != l0.end();it0++)
		cout << *it0 << " ";
	cout << endl;
	cout << "l1 : ";
	for (it1 = l1.begin();it1 != l1.end();it1++)
		cout << *it1 << " ";
	cout << endl;
	cout << "Is equal:" << (l0 == l1) << endl;
	cout << endl;
}
void set_type_1()
{
	cout << "test for set (1) set<int>" << endl;
	std::set<int> s0, s1;
	s0.insert(256);
	s0.insert(12);
	s0.insert(13);
	s0.insert(14);
	serialize(s0, "set1.data");
	deserialize(s1, "set1.data");
	set<int> ::iterator it0 = s0.begin();
	set<int> ::iterator it1 = s1.begin();
	cout << "s0 : ";
	for (it0 = s0.begin();it0 != s0.end();it0++)
		cout << *it0 << " ";
	cout << endl;
	cout << "s1 : ";
	for (it1 = s1.begin();it1 != s1.end();it1++)
		cout << *it1 << " ";
	cout << endl;
	cout << "Is equal:" << (s0 == s1) << endl;
	cout << endl;
}
void set_type_2()
{
	cout << "test for set (2) set<double>" << endl;
	std::set<double> s0, s1;
	s0.insert(12.12);
	s0.insert(13.13);
	s0.insert(14.14);
	s0.insert(156.156);
	serialize(s0, "set2.data");
	deserialize(s1, "set2.data");
	set<double> ::iterator it0 = s0.begin();
	set<double> ::iterator it1 = s1.begin();
	cout << "s0 : ";
	for (it0 = s0.begin();it0 != s0.end();it0++)
		cout << *it0 << " ";
	cout << endl;
	cout << "s1 : ";
	for (it1 = s1.begin();it1 != s1.end();it1++)
		cout << *it1 << " ";
	cout << endl;
	cout << "Is equal:" << (s0 == s1) << endl;
	cout << endl;
}
void set_type_3()
{
	cout << "test for set (3) set<string>" << endl;
	std::set<string> s0, s1;
	s0.insert("string1");
	s0.insert("string2");
	s0.insert("string3");
	serialize(s0, "set3.data");
	deserialize(s1, "set3.data");
	set<string> ::iterator it0 = s0.begin();
	set<string> ::iterator it1 = s1.begin();
	cout << "s0 : ";
	for (it0 = s0.begin();it0 != s0.end();it0++)
		cout << *it0 << " ";
	cout << endl;
	cout << "s1 : ";
	for (it1 = s1.begin();it1 != s1.end();it1++)
		cout << *it1 << " ";
	cout << endl;
	cout << "Is equal:" << (s0 == s1) << endl;
	cout << endl;
}
void map_type_1()
{
	cout << "test for map (1) map<int, string>" << endl;
	map<int, string> m0, m1;
	m0.insert(pair<int, string>(12, "string1"));
	m0.insert(pair<int, string>(13, "string2"));
	m0.insert(pair<int, string>(14, "string3"));
	m0.insert(pair<int, string>(256, "string4"));
	serialize(m0, "map1.data");
	deserialize(m1, "map1.data");
	map<int, string> ::iterator it0 = m0.begin();
	map<int, string> ::iterator it1 = m1.begin();
	cout << "m0 : ";
	for (it0 = m0.begin();it0 != m0.end();it0++)
		cout << "<" << it0->first << "," << it0->second << ">" << " ";
	cout << endl;
	cout << "m1 : ";
	for (it1 = m1.begin();it1 != m1.end();it1++)
		cout << "<" << it1->first << "," << it1->second << ">" << " ";
	cout << endl;
	cout << "Is equal:" << (m0 == m1) << endl;
	cout << endl;
}
void map_type_2()
{
	cout << "test for map (2) map<double, string>" << endl;
	map<double, string> m0, m1;
	m0.insert(pair<double, string>(12.12, "string1"));
	m0.insert(pair<double, string>(13.13, "string2"));
	m0.insert(pair<double, string>(14.14, "string3"));
	m0.insert(pair<double, string>(256.256, "string4"));
	serialize(m0, "map2.data");
	deserialize(m1, "map2.data");
	map<double, string> ::iterator it0 = m0.begin();
	map<double, string> ::iterator it1 = m1.begin();
	cout << "m0 : ";
	for (it0 = m0.begin();it0 != m0.end();it0++)
		cout << "<" << it0->first << "," << it0->second << ">" << " ";
	cout << endl;
	cout << "m1 : ";
	for (it1 = m1.begin();it1 != m1.end();it1++)
		cout << "<" << it1->first << "," << it1->second << ">" << " ";
	cout << endl;
	cout << "Is equal:" << (m0 == m1) << endl;
	cout << endl;
}
void map_type_3()
{
	cout << "test for map (3) map<int, double>" << endl;
	map<int, double> m0, m1;
	m0.insert(pair<int, double>(12, 12.12));
	m0.insert(pair<int, double>(13, 13.13));
	m0.insert(pair<int, double>(14, 14.14));
	m0.insert(pair<int, double>(256, 256.256));
	serialize(m0, "map3.data");
	deserialize(m1, "map3.data");
	map<int, double> ::iterator it0 = m0.begin();
	map<int, double> ::iterator it1 = m1.begin();
	cout << "m0 : ";
	for (it0 = m0.begin();it0 != m0.end();it0++)
		cout << "<" << it0->first << "," << it0->second << ">" << " ";
	cout << endl;
	cout << "m1 : ";
	for (it1 = m1.begin();it1 != m1.end();it1++)
		cout << "<" << it1->first << "," << it1->second << ">" << " ";
	cout << endl;
	cout << "Is equal:" << (m0 == m1) << endl;
	cout << endl;
}
void xml_arithmetic_1()
{
	XMLSerializerBase<int> baseInt;
	int a = 57, b;
	baseInt.serialize_xml(a, "std_int", "arith1.xml");
	baseInt.deserialize_xml(b, "std_int", "arith1.xml");
	cout << "a = " << a << " " << "b = " << b << endl;
	cout << "Is equal:" << (a == b) << endl;
	cout << endl;
}
void xml_arithmetic_2()
{
	XMLSerializerBase<double> baseDouble;
	double a = -6.66666, b;
	baseDouble.serialize_xml(a, "std_double", "arith2.xml");
	baseDouble.deserialize_xml(b, "std_double", "arith2.xml");
	cout << "a = " << a << " " << "b = " << b << endl;
	cout << "Is equal:" << (a == b) << endl;
	cout << endl;
}
void xml_arithmetic_3()
{
	XMLSerializerBase<char> baseChar;
	char a = '+', b;
	baseChar.serialize_xml(a, "std_char", "arith3.xml");
	baseChar.deserialize_xml(b, "std_char", "arith3.xml");
	cout << "a = " << a << " " << "b = " << b << endl;
	cout << "Is equal:" << (a == b) << endl;
	cout << endl;
}
void xml_string()
{
	XMLSerializerBase<string> baseStr;
	string a = "HelloMyLove!", b;
	baseStr.serialize_xml(a, "std_string", "string.xml");
	baseStr.deserialize_xml(b, "std_string", "string.xml");
	cout << "a = " << a << " " << "b = " << b << endl;
	cout << "Is equal:" << (a == b) << endl;
	cout << endl;
}
void xml_vector_int()
{
	XMLSerializerBase<vector<int>> baseVec;
	vector<int> a = {1,2,3,4,5,6,7}, b;
	baseVec.serialize_xml(a, "std_vector", "vec1.xml");
	baseVec.deserialize_xml(b, "std_vector", "vec1.xml");
	for(auto i:a) cout << i << " ";
	cout << endl;
	for(auto i:b) cout << i << " ";
	cout << endl;
	cout << "Is equal:" << (a == b) << endl;
	cout << endl;
}
void xml_vector_vector_int()
{
	XMLSerializerBase<vector<vector<int>>> baseVec;
	vector<vector<int>> a = {{1,2,3,4,5,6,7}, {2,3,4,5,6}, {1,2,3,4}}, b;
	baseVec.serialize_xml(a, "std_vector", "vec2.xml");
	baseVec.deserialize_xml(b, "std_vector", "vec2.xml");
	for(auto i:a) for(auto j:i) cout << j << " ";
	cout << endl;
	for(auto i:b) for(auto j:i) cout << j << " ";
	cout << endl;
	cout << (a == b) << endl;
	cout << endl;
}
void xml_vector_string()
{
	XMLSerializerBase<vector<string>> baseVec;
	vector<string> a = { "Hello","My","Love","!" }, b;
	baseVec.serialize_xml(a, "std_vector", "vec3.xml");
	baseVec.deserialize_xml(b, "std_vector", "vec3.xml");
	for (auto i : a) cout << i << " ";
	cout << endl;
	for (auto i : b) cout << i << " ";
	cout << endl;
	cout << "Is equal:" << (a == b) << endl;
	cout << endl;
}
void xml_vector_pair()
{
	XMLSerializerBase<vector<string>> baseVec;
	pair<int, double>p0, p1, p2;
	p0 = { 12,12.12 };p1 = { 13,13.13 };p2 = { 14,14.14 };
	vector<pair<int, double>> a, b;
	a.push_back(p0);
	a.push_back(p1);
	a.push_back(p2);
	baseVec.serialize_xml(a, "std_vector", "vec4.xml");
	baseVec.deserialize_xml(b, "std_vector", "vec4.xml");
	for (auto i : a) cout << "<" << i.first << "," << i.second << ">" << " ";
	cout << endl;
	for (auto i : b) cout << "<" << i.first << "," << i.second << ">" << " ";
	cout << endl;
	cout << "Is equal:" << (a == b) << endl;
	cout << endl;
}
void xml_list_int()
{
	XMLSerializerBase<list<int>> baseListInt;
	list<int> vec1 = { 1,2,3,4,5 };
	baseListInt.serialize_xml(vec1, "std_list", "list.xml");
	list<int> vec2;
	baseListInt.deserialize_xml(vec2, "std_list", "list.xml");
	for (auto i : vec1)
		cout << i << " ";
	cout << endl;
	for (auto i : vec2)
		cout << i << " ";
	cout << endl;
	cout << "Is equal:" << (vec1 ==vec2) << endl;
	cout << endl;	
}
void xml_pair_1()
{
	XMLSerializerBase<pair<int,double>> basePair;
	pair<int,double> a = {1,-2.267};
	pair<int,double> b;
	basePair.serialize_xml(a, "std_pair", "pair1.xml");
	basePair.deserialize_xml(b, "std_pair", "pair1.xml");
	cout << a.first << " " << a.second << endl;
	cout << b.first << " " << b.second << endl;
	cout << "Is equal:" << (a==b) << endl;
	cout << endl;
}
void xml_pair_2()
{
	XMLSerializerBase<pair<int,double>> basePair;
	pair<vector<int>, list<float>> a = {{1,2,3,4,5},{2.2,3.3,4.4}};
	pair<vector<int>, list<float>> b;
	basePair.serialize_xml(a, "std_pair", "pair2.xml");
	basePair.deserialize_xml(b, "std_pair", "pair2.xml");
	for(auto i : a.first)
		cout << i << " ";
	cout << endl;
	for(auto i : a.second)
		cout << i << " ";	
	cout << endl;	
	for(auto i : b.first)
		cout << i << " ";
	cout << endl;
	for(auto i : b.second)
		cout << i << " ";	
	cout << endl;		
	cout << "Is equal:" << (a==b) << endl;
	cout << endl;	

}
void xml_set_string()
{
	XMLSerializerBase<list<int>> baseSet;
	set<string> vec1 = { "I", "Love", "ZJU", "HangZhou", "China" };
	baseSet.serialize_xml(vec1, "std_set", "set.xml");
	set<string> vec2;
	baseSet.deserialize_xml(vec2, "std_set", "set.xml");
	for (auto i : vec1)
		cout << i << " ";
	cout << endl;
	for (auto i : vec2)
		cout << i << " ";
	cout << endl;
	cout << "Is equal:" << (vec1 == vec2) << endl;
	cout << endl;	
}
void xml_map_1()
{
	XMLSerializerBase<map<double, string>> base_map;
	map<double, string> student, s2;
	student.insert(pair<double, string>(2.2, "li"));
	student.insert(pair<double, string>(1.1, "wang"));
	student.insert(pair<double, string>(3.3, "sun"));
	base_map.serialize_xml(student, "std_map", "map1.xml");
	base_map.deserialize_xml(s2, "std_map", "map1.xml");
	for (auto i : student)
		cout << "<" << i.first << "," << i.second << ">" << endl;
	for (auto i : s2)
		cout << "<" << i.first << "," << i.second << ">" << endl;
	cout << "Is equal:" << (student == s2) << endl;
	cout << endl;
}
void xml_map_2()
{
	XMLSerializerBase<map<vector<int>, list<float>>> base_map;
	map<vector<int>, list<float>> s1, s2;
	s1.insert(pair<vector<int>, list<float>>({1,2,3}, {1.1,2.2,3.3}));
	s1.insert(pair<vector<int>, list<float>>({4,5,6}, {4.4,5.5,6.6}));
	s1.insert(pair<vector<int>, list<float>>({7,8,9}, {7,7,8.8,9.9}));
	base_map.serialize_xml(s1, "std_map", "map2.xml");
	base_map.deserialize_xml(s2, "std_map", "map2.xml");
	for (auto i : s1) {
		cout << "<";
		for (auto j: i.first) cout << j << " ";
		cout << ",";
		for (auto j: i.second) cout << j << " ";
		cout << ">" << endl;
	}
	for (auto i : s2) {
		cout << "<";
		for (auto j: i.first) cout << j << " ";
		cout << ",";
		for (auto j: i.second) cout << j << " ";
		cout << ">" << endl;
	}
	cout << "Is equal:" << (s1 == s2) << endl;
	cout << endl;
}