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

	cout << "=================��ȡ�����б�=================\n";
	string user_id = "robbin";
	string group_id = "TestGroup01";
	map<std::string, std::string> options;

	aip::Face face(appid, ak, sk);
	Json::Value value = face.face_getlist(user_id, group_id, options);
	
	cout << "response [face_getlist]:" << value << endl;

	cout << "=================�������=================\n";

	// C���Զ�ȡͼƬ�ļ���char������

	//��������ͼ���ļ��������ͼ���ļ���
	char InImgName[10];

	//ͼ�����ݳ���
	unsigned length;
	//�ļ�ָ��
	FILE* fp;

	//����Ҫ��ȡ��ͼ����
	cout << "Enter Image name:";
	cin >> InImgName;
	//�Զ����Ʒ�ʽ��ͼ��
	if ((fp = fopen(InImgName, "rb")) == NULL)
	{
		cout << "Open image failed!" << endl;
		exit(0);
	}
	//��ȡͼ�������ܳ���
	fseek(fp, 0, SEEK_END);
	length = ftell(fp);
	rewind(fp);
	//����ͼ�����ݳ��ȷ����ڴ�buffer
	char* ImgBuffer = (char*)malloc(length * sizeof(char));
	//��ͼ�����ݶ���buffer
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

	cout << "=================��������=================\n";
	value = face.search(image, "BASE64", "TestGroup01", options);
	cout << "response [face_search]:" << value << endl;

	system("pause");

	return 0;
		
}