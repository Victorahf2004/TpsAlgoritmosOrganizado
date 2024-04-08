import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import make_blobs
from sklearn.preprocessing import StandardScaler

def euclidean_distance(x1, x2):
    return np.sqrt(np.sum(x1 - x2)**2)
class KMeans:

    def __init__(self, K=5, max_iters=100, plot_steps=False):
        self.K = K
        self.max_iters = max_iters
        self.plot_steps = plot_steps
        self.clusters = [[] for _ in range(self.K)]
        self.centroids = []

    def predict(self, X):
        self.X = X
        self.n_samples, self.n_features = X.shape
        random_sample_idxs = np.random.choice(self.n_samples, self.K, replace=False)
        self.centroids = [self.X[idx] for idx in random_sample_idxs]
        for _ in range(self.max_iters):
            self.clusters = self._create_clusters(self.centroids)
            centroids_old = self.centroids
            self.centroids = self._get_centroids(self.clusters)

            if self._is_converged(centroids_old, self.centroids):
                break
        return self._get_clusters_labels(self.clusters)


    def _get_clusters_labels(self, clusters):
        labels = np.empty(self.n_samples)
        for cluster_idx, cluster in enumerate(clusters):
            for sample_idx in cluster:
                labels[sample_idx] = cluster_idx
        return labels
    
    def _create_clusters(self, centroids):
        clusters = [[] for _ in range(self.K)]
        for idx, sample in enumerate(self.X):
            centroid_idx = self._closest_centroid(sample, centroids)
            clusters[centroid_idx].append(idx)
        return clusters
    
    def _closest_centroid(self, sample, centroids):
        distances = [euclidean_distance(sample, point) for point in centroids]
        closest_idx = np.argmin(distances)
        return closest_idx
    
    def _get_centroids(self, clusters):
        centroids = np.zeros((self.K, self.n_features))
        for cluster_idx, cluster in enumerate(clusters):
            for sample_idx in cluster:
                centroids[cluster_idx] += self.X[sample_idx]
            centroids[cluster_idx] /= len(cluster)

        for cluster_idx, centroid in enumerate(centroids):
            print(f"Cluster {cluster_idx}: {centroid}")
        return centroids

    
    def _is_converged(self, centroids_old, centroids):
        distances = [euclidean_distance(centroids_old[i], centroids[i]) for i in range(self.K)]
        return sum(distances) == 0

np.random.seed(42)
df_treino = pd.read_csv("nba_treino.csv")
df_teste = pd.read_csv("nba_teste.csv")
X_treino = df_treino.drop(columns="TARGET_5Yrs")
scaler = StandardScaler()
X_treino = scaler.fit_transform(X_treino)
clusters = 3
max_iters = 150
plot_steps = True
k = KMeans(K=clusters, max_iters=max_iters, plot_steps=plot_steps)
y_pred = k.predict(X_treino)

X_treino = df_treino.drop(columns="TARGET_5Yrs")
y_treino = df_treino["TARGET_5Yrs"]
X_teste = df_teste.drop(columns="TARGET_5Yrs")
y_teste = df_teste["TARGET_5Yrs"]