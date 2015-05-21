#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

void incrShift(char* str) {
	int l = strlen(str);
	for(int i = 0; i < l; i ++) {
		str[i] -= 'A';
		str[i] += 1;
		str[i] %= 26;
		str[i] += 'A';
	}
}

int main() {
	char str[] = "BEEAKFYDJXUQYHYJIQRYHTYJIQFBQDUYJIIKFUHCQD";
	for(int i = 0; i < 26; i ++) {
		incrShift(str);
		printf("%s\n", str);
	}
	return 0;
}