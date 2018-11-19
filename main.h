void mostrarEspetaculosCadastrados();

void mostrarPoltronasDisponiveis();

Espetaculo *encontrarEspetaculoPorCodigo(int codigo);

int verificarSeExistePoltrona(char *poltrona);

int verificarSePoltronaEstaDisponivel(char *poltrona);

void adicionarVenda(Espetaculo *espetaculo, char *poltrona, float valorPago, int idadeComprador);

float calcularValorDesconto(float valorEspetaculo, float valorDesconto);