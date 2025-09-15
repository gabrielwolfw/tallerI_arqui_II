import pandas as pd
import matplotlib.pyplot as plt

# Lee los datos
df_mutex = pd.read_csv("resultados_perf_mutex.csv")
df_reduction = pd.read_csv("resultados_perf_reduction.csv")

# Junta y ordena los datos
df = pd.concat([df_mutex, df_reduction], ignore_index=True)
df = df.sort_values(['variante', 'hilos'])

# Calcula speedup y eficiencia
for variante in df['variante'].unique():
    tiempo_base = df[(df['variante'] == variante) & (df['hilos'] == 1)]['tiempo'].values[0]
    df.loc[df['variante'] == variante, 'speedup'] = tiempo_base / df[df['variante'] == variante]['tiempo']
    df.loc[df['variante'] == variante, 'eficiencia'] = df.loc[df['variante'] == variante, 'speedup'] / df.loc[df['variante'] == variante, 'hilos']

# Define colores y estilos para cada variante
colores = {'mutex': 'royalblue', 'reduction': 'darkorange'}
marcadores = {'mutex': 'o', 'reduction': 's'}

fig, axs = plt.subplots(1, 3, figsize=(18, 6))

# Graficar cada variante
for variante in df['variante'].unique():
    datos = df[df['variante'] == variante]
    axs[0].plot(datos['hilos'], datos['tiempo'], marker=marcadores[variante], color=colores[variante], label=variante)
    axs[1].plot(datos['hilos'], datos['speedup'], marker=marcadores[variante], color=colores[variante], label=variante)
    axs[2].plot(datos['hilos'], datos['eficiencia'], marker=marcadores[variante], color=colores[variante], label=variante)

# Configuración de cada gráfica
axs[0].set_title("Tiempo de ejecución vs Hilos", fontsize=15)
axs[0].set_ylabel("Tiempo (segundos)")
axs[1].set_title("Speedup vs Hilos", fontsize=15)
axs[1].set_ylabel("Speedup")
axs[2].set_title("Eficiencia vs Hilos", fontsize=15)
axs[2].set_ylabel("Eficiencia")

for ax in axs:
    ax.set_xlabel("Cantidad de hilos", fontsize=12)
    ax.grid(True, linestyle='--', alpha=0.5)
    ax.legend(title="Variante", fontsize=12)

plt.suptitle("Comparación de variantes", fontsize=18)
plt.tight_layout(rect=[0, 0.03, 1, 0.95]) # para espacio del título
plt.savefig("resultados_comparacion.png", dpi=200)
plt.show()