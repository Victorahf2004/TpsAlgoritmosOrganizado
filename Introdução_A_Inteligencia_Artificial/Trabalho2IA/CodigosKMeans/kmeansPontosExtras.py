import pandas as pd
from sklearn.cluster import KMeans
from sklearn.model_selection import train_test_split
from sklearn.metrics import confusion_matrix, accuracy_score
from sklearn import metrics

df_treino = pd.read_csv("nba_treino.csv")
df_teste = pd.read_csv("nba_teste.csv")

X_treino = df_treino.drop(columns="TARGET_5Yrs")
X_teste = df_teste.drop(columns="TARGET_5Yrs")

model = KMeans(n_clusters=3)

model.fit(X_treino)

labels_treino = model.labels_
labels_teste = model.predict(X_teste)

centroids_treino = model.cluster_centers_
centroids_teste = model.cluster_centers_

print("Resultados do treino:")
print(f"Centróides: {centroids_treino}")

print("Resultados do teste:")
print(f"Centróides: {centroids_teste}")