from common import *
import pytest
from glob import glob

test_files = sorted(glob(f"{tests_path}/loops/*.c"))
expected_return_code = [0, 0, 1]  # while, do_while, no_block
expected_output = [
    ["[DEBUG] Valor: 3"],
    ["[DEBUG] Valor: 3"],
    "[ERRO] Sintaxe inválida",
]

@pytest.mark.parametrize("test_file, return_code, output", zip(test_files, expected_return_code, expected_output))
def test_loops(test_file, return_code, output):
    with open(test_file) as f:
        result = subprocess.run(
            interpretador,
            stdin=f,
            capture_output=True,
        )
    assert result.returncode == return_code
    out = result.stdout.decode()
    err = result.stderr.decode()

    if isinstance(output, list):
        for line in output:
            assert line in out
    else:
        assert output in err
