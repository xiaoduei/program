/* 
	�򵥵�markdown������
	�������markdown�ĵ�ת��Ϊhtml�ĵ�
	�����﷨�����䣬���⣬ͼƬ�����ӣ�����飬���ڴ��룬���ã��б�(��������)�����壬б��
*/

#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// nul:��ʾ���ı��ڵ�
enum Token {
	nul = 0, paragraph = 1, href = 2, ul = 3,
	ol = 4, li = 5, em = 6, strong = 7,
	hr = 8, image = 9, quote = 10, h1 = 11,
	h2 = 12, h3 = 13, h4 = 14, h5 = 15,
	h6 = 16, blockcode = 17, code = 18,
};

// HTMLǰ�ñ�ǩ 
const std::string frontTag[] = {"", "<p>", "", "<ul>", "<ol>", "<li>",
								"<em>", "<strong>", "<hr color=#CCCCCC size=1 />",
								"", "<blockquote>", "<h1>", "<h2>", "<h3>", "<h4>",
								"<h5>", "<h6>","<pre><code>", "<code>" };
// HTML ���ñ�ǩ 
const std::string backTag[] = { "", "</p>", "", "</ul>", "</ol>", "</li>",
								"</em>", "</strong>", "", "", "</blockquote>",
								"</h1>", "</h2>", "</h3>", "</h4>", "</h5>",
								"</h6>", "</code></pre>", "</code>" };

class Node {
public:
	int _type;					//�﷨����
	vector<Node*> _child;		//���ӽڵ�
	string elem[2];				//elem[1]:������Ҫ��ʾ�����ݣ� elem[2]:������ַ��·��

	Node(int type)
		:_type(type)
	{}
};

class markdownParser {
private:
	Node* _root;				//�﷨�����ڵ�
	string _filename;			//�ļ���
	string _content;			//���html�ĵ�����

public:
	markdownParser(const string& filename);
	void transform();
	// ���﷨��ת����html�ĵ�(�������)
	void dfs(Node* _root);
	void insert(Node* curNode, const char* str);
	// ���������﷨
	// ����ֵ���﷨���� + �﷨��Ӧ��������ʼλ��
	pair<int, const char*> parseType(const char* str);
	// �ж��Ƿ���ˮƽ�ָ���
	bool isCutLine(const char* str);
	// ȥ�����׵Ŀո�
	const char* processStr(const char* str);

	string getContent() const;
	// ����html�ļ�
	void generateHtml();
	void destory(Node* root);
	~markdownParser();
};
