// Falha
int main() {
  {
    int n = 10;
    {
      float m = n / 3;
      m;
    }
    m;
  }
}
