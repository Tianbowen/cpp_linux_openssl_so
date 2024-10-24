#include "common.h"

std::string read_file(string file_name) {
	/*ifstream ifs(LICENSE_KEY_FILE);
	if (!ifs.is_open())
	{
		cerr << "ifstream open file error!\n" ;
		return 9;
	}
	ifs.seekg(0, ios_base::end);
	int length = ifs.tellg();
	ifs.seekg(ios_base::beg);
	char* buff = new char[length + 1];
	ifs.read(buff,length + 1);
	cout << "读Key文件开始\n" << endl;
	string content(buff, length + 1);
	cout << content << endl;
	cout << "读Key文件结束\n" << endl;
	delete [] buff; // 该读文件存在一个屯字 */

	cout << "读Key文件开始:" << endl;
	std::ifstream t(file_name);
	std::stringstream buffer;
	buffer << t.rdbuf();
	std::string contents(buffer.str());
	cout << contents << endl;
	cout << "读Key文件结束\n" << endl;
	return contents;
}

time_t str_to_time_t(std::string str)
{
	char* cha = (char*)str.data();             // 将string转换成char*。
	tm tm_;                                    // 定义tm结构体。
	int year, month, day;// 定义时间的各个int临时变量。
	sscanf(cha, "%4d%2d%2d %d:%d:%d", &year, &month, &day, 0, 0, 0);// 将string存储的日期时间，转换为int临时变量。
	tm_.tm_year = year - 1900;                 // 年，由于tm结构体存储的是从1900年开始的时间，所以tm_year为int临时变量减去1900。
	tm_.tm_mon = month - 1;                    // 月，由于tm结构体的月份存储范围为0-11，所以tm_mon为int临时变量减去1。
	tm_.tm_mday = day;                         // 日。
	tm_.tm_hour = 0;                        // 时。
	tm_.tm_min = 0;                       // 分。
	tm_.tm_sec = 0;                       // 秒。
	tm_.tm_isdst = 0;                          // 非夏令时。
	time_t t_ = mktime(&tm_);                  // 将tm结构体转换成time_t格式。
	return t_;                                 // 返回值。
}

void Stringsplit(const string& str, const char split, std::vector<string>& res)
{
	if (str == "")		return;
	//在字符串末尾也加入分隔符，方便截取最后一段
	string strs = str + split;
	size_t pos = strs.find(split);

	// 若找不到内容则字符串搜索函数返回 npos
	while (pos != strs.npos)
	{
		string temp = strs.substr(0, pos);
		res.push_back(temp);
		//去掉已分割的字符串,在剩下的字符串中进行分割
		strs = strs.substr(pos + 1, strs.size());
		pos = strs.find(split);
	}
}

void Stringsplit(const string& str, const string& splits, std::vector<string>& res)
{
	if (str == "")		return;
	//在字符串末尾也加入分隔符，方便截取最后一段
	string strs = str + splits;
	size_t pos = strs.find(splits);
	int step = splits.size();

	// 若找不到内容则字符串搜索函数返回 npos
	while (pos != strs.npos)
	{
		string temp = strs.substr(0, pos);
		res.push_back(temp);
		//去掉已分割的字符串,在剩下的字符串中进行分割
		strs = strs.substr(pos + step, strs.size());
		pos = strs.find(splits);
	}
}

string& replace_all(string& src, const string& old_value, const string& new_value) {
	// 每次重新定位起始位置，防止上轮替换后的字符串形成新的old_value
	for (string::size_type pos(0); pos != string::npos; pos += new_value.length()) {
		if ((pos = src.find(old_value, pos)) != string::npos) {
			src.replace(pos, old_value.length(), new_value);
		}
		else break;
	}
	return src;
}