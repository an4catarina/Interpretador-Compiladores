from glob import glob

import pytest
from common import *

test_files = sorted(glob(f"{tests_path}/for/*.c"))
expected_return_code = [0, 0]  # for , double_for , for_break_continue
expected_output = [
    "[DEBUG] Valor: 5",
    "[DEBUG] Valor: 4",
    "[DEBUG] Break na linha 10",
]


class TestFor:
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
