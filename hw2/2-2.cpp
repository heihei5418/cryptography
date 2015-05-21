#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;
int key[] = {2, 4, 6, 1, 8, 3, 5, 7};

void substituteBy8Bit(char* pass, char* ori) {
	int l = strlen(pass);
	int n = l / 8;
	int m = l % 8;
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < 8; j ++)
			ori[i * 8 + j] = pass[i * 8 + key[j] - 1];
	for(int i = 0; i < m; i ++)
		ori[n * 8 + i] = pass[n * 8 + key[i] - 1];
}

int main() {
	char pass[] = "TGEEMNELNNTDROEOAAHDOETCSHAEIRLM";
	char ori[] = "TGEEMNELNNTDROEOAAHDOETCSHAEIRLM";
	substituteBy8Bit(pass, ori);
	printf("%s\n", ori);
	return 0;
}