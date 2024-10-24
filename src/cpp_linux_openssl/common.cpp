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
	cout << "��Key�ļ���ʼ\n" << endl;
	string content(buff, length + 1);
	cout << content << endl;
	cout << "��Key�ļ�����\n" << endl;
	delete [] buff; // �ö��ļ�����һ������ */

	cout << "��Key�ļ���ʼ:" << endl;
	std::ifstream t(file_name);
	std::stringstream buffer;
	buffer << t.rdbuf();
	std::string contents(buffer.str());
	cout << contents << endl;
	cout << "��Key�ļ�����\n" << endl;
	return contents;
}

time_t str_to_time_t(std::string str)
{
	char* cha = (char*)str.data();             // ��stringת����char*��
	tm tm_;                                    // ����tm�ṹ�塣
	int year, month, day;// ����ʱ��ĸ���int��ʱ������
	sscanf(cha, "%4d%2d%2d %d:%d:%d", &year, &month, &day, 0, 0, 0);// ��string�洢������ʱ�䣬ת��Ϊint��ʱ������
	tm_.tm_year = year - 1900;                 // �꣬����tm�ṹ��洢���Ǵ�1900�꿪ʼ��ʱ�䣬����tm_yearΪint��ʱ������ȥ1900��
	tm_.tm_mon = month - 1;                    // �£�����tm�ṹ����·ݴ洢��ΧΪ0-11������tm_monΪint��ʱ������ȥ1��
	tm_.tm_mday = day;                         // �ա�
	tm_.tm_hour = 0;                        // ʱ��
	tm_.tm_min = 0;                       // �֡�
	tm_.tm_sec = 0;                       // �롣
	tm_.tm_isdst = 0;                          // ������ʱ��
	time_t t_ = mktime(&tm_);                  // ��tm�ṹ��ת����time_t��ʽ��
	return t_;                                 // ����ֵ��
}

void Stringsplit(const string& str, const char split, std::vector<string>& res)
{
	if (str == "")		return;
	//���ַ���ĩβҲ����ָ����������ȡ���һ��
	string strs = str + split;
	size_t pos = strs.find(split);

	// ���Ҳ����������ַ��������������� npos
	while (pos != strs.npos)
	{
		string temp = strs.substr(0, pos);
		res.push_back(temp);
		//ȥ���ѷָ���ַ���,��ʣ�µ��ַ����н��зָ�
		strs = strs.substr(pos + 1, strs.size());
		pos = strs.find(split);
	}
}

void Stringsplit(const string& str, const string& splits, std::vector<string>& res)
{
	if (str == "")		return;
	//���ַ���ĩβҲ����ָ����������ȡ���һ��
	string strs = str + splits;
	size_t pos = strs.find(splits);
	int step = splits.size();

	// ���Ҳ����������ַ��������������� npos
	while (pos != strs.npos)
	{
		string temp = strs.substr(0, pos);
		res.push_back(temp);
		//ȥ���ѷָ���ַ���,��ʣ�µ��ַ����н��зָ�
		strs = strs.substr(pos + step, strs.size());
		pos = strs.find(splits);
	}
}

string& replace_all(string& src, const string& old_value, const string& new_value) {
	// ÿ�����¶�λ��ʼλ�ã���ֹ�����滻����ַ����γ��µ�old_value
	for (string::size_type pos(0); pos != string::npos; pos += new_value.length()) {
		if ((pos = src.find(old_value, pos)) != string::npos) {
			src.replace(pos, old_value.length(), new_value);
		}
		else break;
	}
	return src;
}