import pandas as pd
from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import confusion_matrix, accuracy_score
from sklearn import metrics

df_treino = pd.read_csv("nba_treino.csv")
df_teste = pd.read_csv("nba_teste.csv")
X_treino = df_treino.drop(columns="TARGET_5Yrs")
y_treino = df_treino["TARGET_5Yrs"]
X_teste = df_teste.drop(columns="TARGET_5Yrs")
y_teste = df_teste["TARGET_5Yrs"] 

knn = KNeighborsClassifier(n_neighbors=160)

knn.fit(X_treino, y_treino)

predictions = knn.predict(X_teste)
matriz_de_confusao = confusion_matrix(y_teste, predictions)
accuracy2 = accuracy_score(y_teste, predictions)
precision, recall, f1, support = metrics.precision_recall_fscore_support(y_teste, predictions)
print(f'A matriz de confusão é: {matriz_de_confusao}')
print(f'A acurácia é: {accuracy2}')
print(f'A precisão é: {precision}')
print(f'A revocação é: {recall}')
print(f'O F1 é: {f1}')