from glob import glob

import pytest
from common import *

test_files = sorted(glob(f"{tests_path}/funcs/*.c"))

expected_return_code = [1, 0, 1, 0, 0, 0, 0, 0]

expected_output = [
    "[ERRO] Função invocada incorretamente na linha 5",
    ["[DEBUG] Valor: 8", "[DEBUG] Valor: 65536"],
    "[ERRO] Número incorreto de argumentos em printf",
    ["n=5", "f=2.500000", "c=A"],
    ["linha1", "linha2", "X\\Y%"],
    ["Hello, world!"],
    ["a=10", "b=20"],
    ["[DEBUG] Valor: 3.000000", "[DEBUG] Valor: 3.464102"],
]

printf_test_files = [
    f"{tests_path}/funcs/printf_args_mismatch.c",
]

printf_expected_return_code = [
    1,
]

printf_expected_output = [
    "[ERRO] Número incorreto de argumentos em printf",
]


class TestFuncs:
    @pytest.mark.parametrize(
        "test_file, return_code, output",
        zip(test_files, expected_return_code, expected_output),
    )
    def test_all(self, test_file, return_code, output: str):
        with open(test_file) as f:
            result = subprocess.run(
                interpretador,
                stdin=f,
                capture_output=True,
            )

            assert result.returncode == return_code
            if isinstance(output, list):
                if return_code:
                    for o in output:
                        assert o in result.stderr.decode()
                else:
                    for o in output:
                        assert o in result.stdout.decode()
            else:
                if return_code:
                    assert output in result.stderr.decode()
                else:
                    assert output in result.stdout.decode()


class TestPrintf:
    @pytest.mark.parametrize(
        "test_file, return_code, output",
        zip(printf_test_files, printf_expected_return_code, printf_expected_output),
    )
    def test_printf(self, test_file, return_code, output: str):
        with open(test_file) as f:
            result = subprocess.run(
                interpretador,
                stdin=f,
                capture_output=True,
            )

            assert result.returncode == return_code
            if isinstance(output, list):
                if return_code:
                    for o in output:
                        assert o in result.stderr.decode()
                else:
                    for o in output:
                        assert o in result.stdout.decode()
            else:
                if return_code:
                    assert output in result.stderr.decode()
                else:
                    assert output in result.stdout.decode()