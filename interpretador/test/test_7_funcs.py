from glob import glob

import pytest
from common import *

test_files = sorted(glob(f"{tests_path}/funcs/*.c"))

expected_return_code = [1, 0, 0, 0, 0]

expected_output = [
    "[ERRO] Função invocada incorretamente na linha 5",
    ["[DEBUG] Valor: 8", "[DEBUG] Valor: 65536"],
    "",
    ["[DEBUG] Valor: 3.000000", "[DEBUG] Valor: 3.464102"],
    "",
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
