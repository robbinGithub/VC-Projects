#include <curl/curl.h>
#include <stdlib.h>
#include <stdio.h>
#include "face.h"
#include "base/base64.h"
using namespace std;

int main(int argc, char* argv[])
{   

	CURL *curl = curl_easy_init();
	if (curl) printf("curl_easy_init() succeeded!\n");
	else fprintf(stderr, "Error calling curl_easy_init().\n");

	string appid = "11657163";
	string ak = "DQvVCL1VzQ809AL5Kfj7a5LW";
	string sk = "IWseUtCvRXqByn1lROcAGyZPMw70Fqvg";

	cout << "=================获取人脸列表=================\n";
	string user_id = "robbin";
	string group_id = "TestGroup01";
	map<std::string, std::string> options;

	aip::Face face(appid, ak, sk);
	Json::Value value = face.face_getlist(user_id, group_id, options);
	
	cout << "response [face_getlist]:" << value << endl;

	cout << "=================人脸检测=================\n";

	// C语言读取图片文件至char数组中

	//保存输入图像文件名和输出图像文件名
	char InImgName[10];

	//图像数据长度
	unsigned length;
	//文件指针
	FILE* fp;

	//输入要读取的图像名
	cout << "Enter Image name:";
	cin >> InImgName;
	//以二进制方式打开图像
	if ((fp = fopen(InImgName, "rb")) == NULL)
	{
		cout << "Open image failed!" << endl;
		exit(0);
	}
	//获取图像数据总长度
	fseek(fp, 0, SEEK_END);
	length = ftell(fp);
	rewind(fp);
	//根据图像数据长度分配内存buffer
	char* ImgBuffer = (char*)malloc(length * sizeof(char));
	//将图像数据读入buffer
	fread(ImgBuffer, length, 1, fp);
	fclose(fp);
	string image = aip::base64_encode(ImgBuffer, length);
	
	/*
	ifstream fin;
	ostringstream oss;

	fin.open("c:\\robbin2.png", ios_base::binary);
	if (!fin.is_open())
	{
		cout << "Error In Open..." << endl;
		return -1;
	}

	oss << fin.rdbuf();
	string image = oss.str().c_str();
	*/

	value = face.detect(image, "BASE64", options);
	cout << "response [face_detect]:" << value << endl;

	cout << "=================人脸搜索=================\n";
	value = face.search(image, "BASE64", "TestGroup01", options);
	cout << "response [face_search]:" << value << endl;

	system("pause");

	return 0;
		
}