"""
Classificação de Seres Humanos vs. Máquinas usando Aprendizado de Máquina Supervisionado

Este programa utiliza um algoritmo de árvore de decisão para classificar objetos como seres humanos ou máquinas
com base em características como altura e largura. O algoritmo é treinado com dados de treinamento e avaliado
com dados de teste para medir sua precisão.

Dados de Treinamento:
- Cada entrada consiste em duas características (altura e largura) e um rótulo (0 para máquina, 1 para ser humano).
- Exemplo: [1.80, 0.20, 1] representa um ser humano com altura 1.80, largura 0.20.

O programa inclui as seguintes etapas:
1. Importa as bibliotecas necessárias do scikit-learn.
2. Define os dados de treinamento, com mais exemplos incluídos.
3. Separa as características e rótulos dos dados de treinamento.
4. Divide os dados em conjuntos de treinamento e teste.
5. Cria um modelo de árvore de decisão.
6. Treina o modelo com os dados de treinamento.
7. Faz previsões nos dados de teste.
8. Avalia a precisão do modelo.
9. Demonstra uma previsão para um novo objeto.

"""

# Importando as bibliotecas necessárias
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier
from sklearn.metrics import accuracy_score

# Dados de treinamento: características (features) e rótulos (labels)
dados_treinamento = [
    [1.80, 0.20, 1],  # Ser humano
    [0.15, 0.80, 0],  # Máquina
    [1.60, 0.30, 1],  # Ser humano
    [0.25, 0.90, 0],  # Máquina
    [1.75, 0.25, 1],  # Ser humano
    [0.20, 0.85, 0],  # Máquina
    [1.65, 0.28, 1],  # Ser humano
    [0.18, 0.88, 0],  # Máquina
    [1.70, 0.23, 1],  # Ser humano
    [0.22, 0.92, 0],  # Máquina
    [1.68, 0.26, 1],  # Ser humano
    [0.21, 0.86, 0],  # Máquina
    [1.78, 0.24, 1],  # Ser humano
    [0.19, 0.89, 0],  # Máquina
]

# Separando características e rótulos
caracteristicas = [item[:2] for item in dados_treinamento]
rotulos = [item[2] for item in dados_treinamento]

# Dividindo os dados em conjuntos de treinamento e teste
caracteristicas_treino, caracteristicas_teste, rotulos_treino, rotulos_teste = train_test_split(caracteristicas, rotulos, test_size=0.2, random_state=42)

# Criando o modelo de árvore de decisão
modelo = DecisionTreeClassifier()

# Treinando o modelo
modelo.fit(caracteristicas_treino, rotulos_treino)

# Fazendo previsões no conjunto de teste
previsoes = modelo.predict(caracteristicas_teste)

# Avaliando a precisão do modelo
precisao = accuracy_score(rotulos_teste, previsoes)
print(f'A precisao do modelo eh: {precisao * 100:.2f}%')

# Exemplo de previsão para um novo objeto
novo_objeto = [[1.70, 0.22]]  # pode  se ajustar esses valores
resultado = modelo.predict(novo_objeto)

# Exibindo o resultado da previsão
if resultado[0] == 1:
    print("O objeto eh um ser humano.")
else:
    print("O objeto eh uma máquina.")
