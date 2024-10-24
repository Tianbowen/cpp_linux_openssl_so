#include "openssl_helper.h"

// �ο� https://blog.csdn.net/zyy29182918/article/details/130405807

static const std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";



std::string RsaPubDecrypt(const std::string& cipher_text, const std::string& pub_key)
{
	std::string decrypt_text;
	BIO* keybio = BIO_new_mem_buf((unsigned char*)pub_key.c_str(), -1);
	RSA* rsa = RSA_new();

	// ע��--------ʹ�õ�1�ָ�ʽ�Ĺ�Կ���н���
	//rsa = PEM_read_bio_RSAPublicKey(keybio, &rsa, NULL, NULL);
	// ע��--------ʹ�õ�2�ָ�ʽ�Ĺ�Կ���н��ܣ�����ʹ�����ָ�ʽ��Ϊʾ����
	rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa, NULL, NULL);
	if (!rsa)
	{
		unsigned long err = ERR_get_error(); //��ȡ�����
		char err_msg[1024] = { 0 };
		ERR_error_string(err, err_msg); // ��ʽ��error:errId:��:����:ԭ��
		printf("err msg: err:%ld, msg:%s\n", err, err_msg);
		BIO_free_all(keybio);
		return decrypt_text;
	}

	int len = RSA_size(rsa);
	char* text = new char[len + 1];
	memset(text, 0, len + 1);
	// �����Ľ��н���
	int ret = RSA_public_decrypt(cipher_text.length(), (const unsigned char*)cipher_text.c_str(), (unsigned char*)text, rsa, RSA_PKCS1_PADDING);
	if (ret >= 0) {
		decrypt_text.append(std::string(text, ret));
	}

	// �ͷ��ڴ�  
	delete text;
	BIO_free_all(keybio);
	RSA_free(rsa);

	return decrypt_text;

}


static inline bool is_base64(unsigned char c) {
	return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string base64_decode(const std::string& encoded_string) {
	size_t in_len = encoded_string.size();
	int i = 0;
	int j = 0;
	int in_ = 0;
	unsigned char char_array_4[4], char_array_3[3];
	std::string ret;

	while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
		char_array_4[i++] = encoded_string[in_]; in_++;
		if (i == 4) {
			for (i = 0; i < 4; i++)
				char_array_4[i] = base64_chars.find(char_array_4[i]) & 0xff;

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (i = 0; (i < 3); i++)
				ret += char_array_3[i];
			i = 0;
		}
	}

	if (i) {
		for (j = 0; j < i; j++)
			char_array_4[j] = base64_chars.find(char_array_4[j]) & 0xff;

		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);

		for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
	}

	return ret;
}

std::string des_cbc_pkcs5_decrypt(const std::string& cipherText, const std::string& key)
{
	//��ʼ��IV���� 
	std::string clearText;
	DES_cblock keyEncrypt, ivec;
	memset(keyEncrypt, 0, 8);

	if (key.length() <= 8)
		memcpy(keyEncrypt, key.c_str(), key.length());
	else
		memcpy(keyEncrypt, key.c_str(), 8);

	DES_key_schedule keySchedule;  //��Կ��
	DES_set_key_unchecked(&keyEncrypt, &keySchedule);   //������Կ���Ҳ������Կ��ż��  

	//memcpy(ivec, cbc_iv, sizeof(cbc_iv));
	if (key.length() <= 8)
		memcpy(ivec, key.c_str(), key.length());
	else
		memcpy(ivec, key.c_str(), 8);

	// ѭ�����ܣ�ÿ8�ֽ�һ��    
	const_DES_cblock inputText;
	DES_cblock outputText;
	std::vector<unsigned char> vecCleartext;
	unsigned char tmp[8];

	for (int i = 0; i < cipherText.length() / 8; i++)
	{
		memcpy(inputText, cipherText.c_str() + i * 8, 8);
		DES_ncbc_encrypt(inputText, outputText, 8, &keySchedule, &ivec, DES_DECRYPT);  //����
		memcpy(tmp, outputText, 8);

		for (int j = 0; j < 8; j++)
			vecCleartext.push_back(tmp[j]);

		//����ivec
		//memcpy(ivec, outputText, 8);  //���ܹ��̲���Ҫ��ǰһ��Ľ����Ϊ��һ���IV
	}

	if (clearText.length() % 8 != 0)
	{
		int tmp1 = clearText.length() / 8 * 8;
		int tmp2 = clearText.length() - tmp1;
		memset(inputText, 0, tmp2);
		memcpy(inputText, cipherText.c_str() + tmp1, tmp2);
		DES_ncbc_encrypt(inputText, outputText, tmp2, &keySchedule, &ivec, DES_DECRYPT);  //����
		memcpy(tmp, outputText, tmp2);
		for (int j = 0; j < 8; j++)
			vecCleartext.push_back(tmp[j]);
	}
	clearText.clear();
	clearText.assign(vecCleartext.begin(), vecCleartext.end());
	return clearText;
}

std::string HexToBin(const std::string& strHex)
{
	if (strHex.size() % 2 != 0)
	{
		return "";
	}

	std::string strBin;
	strBin.resize(strHex.size() / 2);
	for (size_t i = 0; i < strBin.size(); i++)
	{
		uint8_t cTemp = 0;
		for (size_t j = 0; j < 2; j++)
		{
			char cCur = strHex[2 * i + j];
			if (cCur >= '0' && cCur <= '9')
			{
				cTemp = (cTemp << 4) + (cCur - '0');
			}
			else if (cCur >= 'a' && cCur <= 'f')
			{
				cTemp = (cTemp << 4) + (cCur - 'a' + 10);
			}
			else if (cCur >= 'A' && cCur <= 'F')
			{
				cTemp = (cTemp << 4) + (cCur - 'A' + 10);
			}
			else
			{
				return "";
			}
		}
		strBin[i] = cTemp;
	}

	return strBin;
}