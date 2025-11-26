from common import *
import pytest
from glob import glob

test_files = sorted(glob(f"{tests_path}/while/*.c"))
expected_return_code = [0, 0, 0]  #  do_while_break_continue,while, do_while, no_block
expected_output = [
    "[DEBUG] Valor: 7",
    "[DEBUG] Valor: 3",
    "[DEBUG] Valor: 3",
    "[DEBUG] Break na linha 13",
    "[DEBUG] Valor: 3",

]


class TestWhile:
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
