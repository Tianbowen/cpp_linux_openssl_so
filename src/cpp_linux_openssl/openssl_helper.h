#pragma once

#include <vector>
#include <string.h>
#include <fstream>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/des.h>




std::string HexToBin(const std::string& strHex);

std::string RsaPubDecrypt(const std::string& cipher_text, const std::string& pub_key);

std::string base64_decode(const std::string& encoded_string);

std::string des_cbc_pkcs5_decrypt(const std::string& cipherText, const std::string& key);