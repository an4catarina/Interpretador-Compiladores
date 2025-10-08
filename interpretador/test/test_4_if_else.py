from common import *


test_files = glob(f"{tests_path}/if_else/*.c")
test_files = sorted(list(test_files))

# Retorno esperado (0 = sucesso, 1 = erro)
expected_return_code = [0, 0, 0, 0, 0, 0, 1]

# Saídas esperadas (stdout ou stderr)
expected_output = [
    ["Variável: x", "Valor: 15"],  # 01_if_simples_verdadeiro
    ["Variável: x", "Valor: -5"],  # 02_if_simples_falso
    ["Variável: x", "Valor: -8"],  # 03_if_else
    ["Variável: x", "Valor: 2"],  # 04_else_if
    ["Variável: x", "Valor: 8"],  # 05_if_aninhado
    ["Variável: a", "Valor: 12"],  # 06_if_complexo
    "Sintaxe inválida",  # 07_if_invalido
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
