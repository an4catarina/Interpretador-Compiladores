from common import *
import subprocess
import pytest

test_files = [f"{tests_path}/funcs/printf_hello.c"]

expected_return_code = [0]

expected_output = [["Hello, world!"]]


class TestPrintf:
    @pytest.mark.parametrize(
        "test_file, return_code, output",
        zip(test_files, expected_return_code, expected_output),
    )
    def test_printf(self, test_file, return_code, output):
        result = subprocess.run(
            f"{interpretador} < {test_file}",
            shell=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
        )

        assert result.returncode == return_code

        stdout = result.stdout.decode()
        stderr = result.stderr.decode()

        if isinstance(output, list):
            if return_code:
                for o in output:
                    assert o in stderr
            else:
                for o in output:
                    assert o in stdout
        else:
            if return_code:
                assert output in stderr
            else:
                assert output in stdout
