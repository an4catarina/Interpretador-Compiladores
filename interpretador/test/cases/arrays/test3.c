
int main() {
    int v[5];
    int i;
    int sum;

    i = 0;
    while (i < 5) {
        v[i] = i + 1;
        i = i + 1;
    }

    sum = 0;
    i = 0;

    while (i < 5) {
        sum = sum + v[i];
        i = i + 1;
    }

    sum;
}
