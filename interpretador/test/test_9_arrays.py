import os
import subprocess

interpretador = "interpretador/build/interpretador"
tests_path = "interpretador/test/cases/arrays"

def run_case(path):
    """Executa um caso de teste e retorna o código de saída"""
    with open(path) as f:
        result = subprocess.run(
            interpretador,
            stdin=f,
            capture_output=True,
        )
    return result.returncode

def test_array_set_get():
    code = """
int main() {
    int v[3];
    v[0] = 10;
    v[1] = 20;
    v[2] = 30;

    v[0];
}
"""
    path = f"{tests_path}/test1.c"
    os.makedirs(tests_path, exist_ok=True)
    open(path, "w").write(code)

    assert run_case(path) == 0


def test_array_in_loop():
    code = """
int main() {
    int v[10];
    int i;
    i = 0;

    while (i < 10) {
        v[i] = i * 2;
        i = i + 1;
    }

    v[4];
}
"""
    path = f"{tests_path}/test2.c"
    open(path, "w").write(code)

    assert run_case(path) == 0


def test_array_sum():
    """
    Soma simples de array
    v = [1,2,3,4,5]
    """
    code = """
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
"""
    path = f"{tests_path}/test3.c"
    open(path, "w").write(code)

    assert run_case(path) == 0


def test_array_index_expr():
    code = """
int main() {
    int v[4];
    v[1+1] = 50;
    v[2];
}
"""
    path = f"{tests_path}/test4.c"
    open(path, "w").write(code)

    assert run_case(path) == 0


def test_array_nested_expression():
    code = """
int main() {
    int v[2];
    v[0] = 5;
    v[1] = 7;
    v[0];
}
"""
    path = f"{tests_path}/test5.c"
    open(path, "w").write(code)

    assert run_case(path) == 0