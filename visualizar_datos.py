import pandas as pd
import matplotlib.pyplot as plt

# como instalo pandas y matplotlib?
# pip install pandas matplotlib sudo apt install matplotlib? así
# o con pip3?
# pip3 install pandas matplotlib

# Lee el archivo CSV
df = pd.read_csv("resultados.csv")
df.columns = df.columns.str.strip()

# Encuentra el tiempo secuencial (hilos=1) para cada variante
tiempo_secuencial = df[df['hilos'] == 1].set_index('variante')['tiempo'].to_dict()

# Calcula speedup y eficiencia
df['speedup'] = df.apply(lambda row: tiempo_secuencial[row['variante']] / row['tiempo'], axis=1)
df['eficiencia'] = df['speedup'] / df['hilos']

# Gráficas
fig, axs = plt.subplots(3, 1, figsize=(8, 15))

for variante in df['variante'].unique():
    sub_df = df[df['variante'] == variante]
    axs[0].plot(sub_df['hilos'], sub_df['tiempo'], marker='o', label=variante)
    axs[1].plot(sub_df['hilos'], sub_df['speedup'], marker='o', label=variante)
    axs[2].plot(sub_df['hilos'], sub_df['eficiencia'], marker='o', label=variante)

axs[0].set_title("Tiempo de ejecución vs Hilos")
axs[0].set_xlabel("Número de hilos")
axs[0].set_ylabel("Tiempo (s)")
axs[0].legend()

axs[1].set_title("Speedup vs Hilos")
axs[1].set_xlabel("Número de hilos")
axs[1].set_ylabel("Speedup")
axs[1].legend()

axs[2].set_title("Eficiencia vs Hilos")
axs[2].set_xlabel("Número de hilos")
axs[2].set_ylabel("Eficiencia")
axs[2].legend()

plt.tight_layout()
plt.savefig("escalado.png")
plt.show()