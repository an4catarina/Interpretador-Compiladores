from common import *

test_files = glob(f"{tests_path}/expr/*.c")
test_files = sorted(list(test_files))
expected_return_code = [0, 0, 0, 0, 0, 0, 1, 1]
expected_output = [
    ["Valor: 12", "Valor: 47.000000"],
    ["Valor: 12", "Valor: 'B'", "Valor: 78.000000"],
    ["Valor: 0", "Valor: 10", "Valor: 20", "Valor: 31"],
    ["Valor: 1", "Valor: 11", "Valor: 21", "Valor: 31", "Valor: 40", "Valor: 50"],
    ["Valor: 0", "Valor: 11", "Valor: 21", "Valor: 31"],
    "Valor: 754.500000",
    "[ERRO] Símbolo ou operação desconhecidos",
    "[ERRO] Símbolo ou operação desconhecidos",
]


class TestVar:
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
