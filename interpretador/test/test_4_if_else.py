from common import *


test_files = glob(f"{tests_path}/if_else/*.c")
test_files = sorted(list(test_files))

# Retorno esperado (0 = sucesso, 1 = erro)
expected_return_code = [0, 0, 0, 1, 0, 0, 0]

# Saídas esperadas (stdout ou stderr)
expected_output = [
    ["Variável: a","Valor: 12"],
    ["Variável: x","Valor: 2"],
    ["Variável: x","Valor: -8"],
    "",
    ["Variável: x","Valor: 8"],
    ["Variável: x","Valor: -5"],
    ["Variável: x","Valor: 15"],
]


class TestIfElse:
    @pytest.mark.parametrize(
        "test_file, return_code, output",
        zip(test_files, expected_return_code, expected_output),
    )
    def test_all(self, test_file, return_code, output):
        with open(test_file) as f:
            result = subprocess.run(
                interpretador,
                stdin=f,
                capture_output=True,
            )

            assert result.returncode == return_code

            if isinstance(output, list):
                for o in output:
                    if return_code:
                        assert o in result.stderr.decode()
                    else:
                        assert o in result.stdout.decode()
            else:
                if return_code:
                    assert output in result.stderr.decode()
                else:
                    assert output in result.stdout.decode()
