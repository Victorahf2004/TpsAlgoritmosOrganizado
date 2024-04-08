import pandas as pd
import matplotlib.pyplot as plt

# Dados brutos
dados_brutos = """
Algoritmo A*:
    Os tempos são: [0.0001010894775390625, 0.00013184547424316406, 0.0001780986785888672, 0.0004897117614746094, 0.0006477832794189453, 0.0010561943054199219, 0.0008878707885742188, 0.0032165050506591797, 0.00834798812866211, 0.010363578796386719, 0.024087190628051758]
    Os tamanhos são: [0, 6, 19, 45, 85, 130, 140, 408, 641, 916, 1525]

Algoritmo Bfs:
    Os tempos são: [0.00010132789611816406, 0.00010013580322265625, 0.00010895729064941406, 0.0001361370086669922, 0.00023126602172851562, 0.0003323554992675781, 0.00045418739318847656, 0.0011067390441894531, 0.0015521049499511719, 0.0022687911987304688, 0.006044626235961914]
    Os tamanhos são: [0, 4, 11, 17, 29, 45, 67, 181, 256, 359, 676]

Algoritmo Greedy:
    Os tempos são: [0.00010061264038085938, 0.00010228157043457031, 0.000141143798828125, 0.00012302398681640625, 0.00013566017150878906, 0.00010776519775390625, 0.00011610984802246094, 0.002976655960083008, 0.00014519691467285156, 0.0018689632415771484, 0.007439851760864258]
    Os tamanhos são: [0, 4, 8, 11, 13, 16, 18, 543, 23, 351, 1241]

Algoritmo Hill Climbing:
    Os tempos são: [9.322166442871094e-05, 0.00015163421630859375, 0.0002155303955078125, 0.0002923011779785156, 0.0004596710205078125, 0.0010039806365966797, 0.00011610984802246094, 0.0002892017364501953, 0.00048160552978515625, 0.00030612945556640625, 0.0008533000946044922]
    Os tamanhos são: [0, 2, 4, 6, 16, 34, 1, 19, 9, 7, 13]
Algoritmo Ids:
    Os tempos são: [9.608268737792969e-05, 5.53131103515625e-05, 0.00011396408081054688, 0.000171661376953125, 0.0005612373352050781, 0.0011518001556396484, 0.0024671554565429688, 0.00407719612121582, 0.00961160659790039, 0.04265260696411133, 0.12145614624023438]
    Os tamanhos são: [0, 4, 16, 32, 124, 293, 677, 1118, 2504, 11923, 37221]

Algoritmo Ucs:
    Os tempos são: [0.00011706352233886719, 0.00011086463928222656, 0.00017571449279785156, 0.0001933574676513672, 0.0004253387451171875, 0.0005047321319580078, 0.0008218288421630859, 0.0014841556549072266, 0.0021750926971435547, 0.006318092346191406, 0.012326717376708984]
    Os tamanhos são: [0, 10, 29, 33, 89, 105, 173, 305, 523, 1260, 2478]
"""

# Dividir os dados brutos em linhas
linhas = dados_brutos.split("\n")

# Inicializar listas para armazenar os dados
algoritmos = []
tempos = []
tamanhos = []

# Processar cada linha
for linha in linhas:
    if "Algoritmo" in linha:
        # Esta é uma linha de nome de algoritmo
        algoritmo = linha.split(" ")[1][:-1]  # Remover o ':' do final
    elif "Os tempos são" in linha:
        # Esta é uma linha de tempos
        tempo = list(map(float, linha.split(":")[1].strip()[1:-1].split(", ")))
    elif "Os tamanhos são" in linha:
        # Esta é uma linha de tamanhos
        tamanho = list(map(int, linha.split(":")[1].strip()[1:-1].split(", ")))
        
        # Adicionar os dados às listas
        algoritmos.extend([algoritmo]*len(tempo))
        tempos.extend(tempo)
        tamanhos.extend(tamanho)

# Criar o DataFrame
df = pd.DataFrame({
    "Algoritmo": algoritmos,
    "Tempo de execução": tempos,
    "Nós Expandidos": tamanhos
})

print(df)
# Criar uma figura com dois subplots
fig, axs = plt.subplots(2)

# Criar o primeiro gráfico (Tempo de execução)
axs[0].bar(df['Algoritmo'], df['Tempo de execução'])
axs[0].set_title('Tempo de execução por algoritmo')
axs[0].set_xlabel('Algoritmo')
axs[0].set_ylabel('Tempo de execução')

# Criar o segundo gráfico (Nós Expandidos)
axs[1].bar(df['Algoritmo'], df['Nós Expandidos'])
axs[1].set_title('Nós Expandidos por algoritmo')
axs[1].set_xlabel('Algoritmo')
axs[1].set_ylabel('Nós Expandidos')

# Ajustar o layout
fig.tight_layout()

# Mostrar os gráficos
plt.show()
