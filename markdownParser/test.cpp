#include "markdown.h"

int main() {
	markdownParser mp("test.md");
	mp.transform();
	mp.generateHtml();
	cout << "����һ������" << endl;
	getchar();
	return 0;
}