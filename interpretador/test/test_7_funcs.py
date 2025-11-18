from glob import glob

import pytest
from common import *

test_files = sorted(glob(f"{tests_path}/funcs/*.c"))

expected_return_code = [0] * len(test_files)

expected_output = [""] * len(test_files)


class TestFuncs:
    @pytest.mark.parametrize(
        "test_file, return_code, output",
        zip(test_files, expected_return_code, expected_output),
    )
    def test_funcs(self, test_file, return_code, output):
        result = subprocess.run(
            f"{interpretador} < {test_file}",
            shell=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
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
