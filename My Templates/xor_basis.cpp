const int N = 1e5 + 10, LOG_A = 20;

int basis[LOG_A];

int sz;

void insertVector(int mask) {
	for (int i = 0; i < LOG_A; i++) {
		if ((mask & 1 << i) == 0) continue;

		if (!basis[i]) {
			basis[i] = mask;
			++sz;
			
			return;
		}

		mask ^= basis[i];
	}
}

int main() {
	int n;
	cin >> n;

	while (n--) {
		int a;
		scanf("%d", &a);

		insertVector(a);
	}

	cout << (1 << sz) << endl;

	return 0;
}