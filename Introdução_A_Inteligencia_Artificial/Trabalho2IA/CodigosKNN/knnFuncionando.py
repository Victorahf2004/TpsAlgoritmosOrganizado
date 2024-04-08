import pandas as pd
import matplotlib.pyplot as plt
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score
from sklearn.model_selection import train_test_split
import numpy as np
from sklearn.metrics import confusion_matrix, accuracy_score
from collections import Counter
from matplotlib.colors import ListedColormap
from sklearn import metrics

df_treino = pd.read_csv("nba_treino.csv")
df_teste = pd.read_csv("nba_teste.csv")
X_treino = df_treino.drop(columns="TARGET_5Yrs")
y_treino = df_treino["TARGET_5Yrs"]
X_teste = df_teste.drop(columns="TARGET_5Yrs")
y_teste = df_teste["TARGET_5Yrs"]

def euclidean_distance(x1, x2):
    distance = np.sqrt(np.sum((x1 - x2) ** 2))
    return distance

class KNN:
    def __init__(self, k):
        self.k = k

    def fit(self, X, y):
        self.X_train = X
        self.y_train = y

    def predict(self, X):
        predictions = []
        for each in X:
            sublista = self._predict(each)
            predictions.append(sublista)
        return predictions

    def _predict(self, x):
        distances = []
        for elemento in self.X_train:
            distances.append(euclidean_distance(x, elemento))
        k_indices = np.argsort(distances)[:self.k]
        k_nearest_labels = [self.y_train[i] for i in k_indices]

        most_common = Counter(k_nearest_labels).most_common()
        return most_common[0][0]
X_treino2 = X_treino.values
y_treino2 = y_treino.values
X_teste2 = X_teste.values
y_teste2 = y_teste.values
teste = KNN(k=160)
teste.fit(X_treino2, y_treino2)
predictions = teste.predict(X_teste2)
matriz_de_confusao = confusion_matrix(y_teste2, predictions)
accuracy2 = accuracy_score(y_teste2, predictions)
precision, recall, f1, support = metrics.precision_recall_fscore_support(y_teste2, predictions)
print(f'A matriz de confusão é: {matriz_de_confusao}')
print(f'A acurácia é: {accuracy2}')
print(f'A precisão é: {precision}')
print(f'A revocação é: {recall}')
print(f'O F1 é: {f1}')