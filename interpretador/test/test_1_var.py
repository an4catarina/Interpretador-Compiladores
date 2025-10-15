from common import *

test_files = glob(f"{tests_path}/var/*.c")
test_files = sorted(list(test_files))
expected_return_code = [1, 1, 0, 0, 0, 0, 0, 0]
expected_output = [
    "Uso de variável desconhecida m na linha 2",
    "Uso de variável desconhecida string na linha",
    "",
    "",
    ["Variável: c", "Tipo: char", "Valor: 'A'"],
    ["Variável: d", "Tipo: double", "Valor: 3.141500"],
    ["Variável: f", "Tipo: float", "Valor: 2.5000"],
    ["Variável: i", "Tipo: int", "Valor: 10"],
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
