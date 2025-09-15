# Taller 1 - Arquitectura de Computadores II

## Integrantes
- Gustavo Zamora Espinoza
- Kevin Lobo Juárez

---

## Compilación de los archivos

Para compilar los ejecutables después de realizar cambios en el código fuente, utilice los siguientes comandos:

```bash
make reduction
make mutex
```

Esto generará los binarios correspondientes para cada variante.

---

## Ejecución individual

Para ejecutar cada variante utilizando el **máximo de hilos disponibles** en el sistema:

```bash
make run_reduction
make run_mutex
```

Estos comandos ejecutan los programas con la máxima concurrencia detectada por el sistema.

---

## Obtención de datos de rendimiento

Para recolectar los resultados de las ejecuciones con diferentes cantidades de hilos (1, 2, 4, 8, 16), primero asegúrese de dar permisos de ejecución a los scripts:

```bash
chmod +x perf_reduction.sh
chmod +x perf_mutex.sh
```

Luego ejecute cada script:

```bash
./perf_reduction.sh
./perf_mutex.sh
```

Estos scripts realizarán las pruebas con diferentes cantidades de hilos y guardarán los resultados en archivos CSV (`resultados_perf_reduction.csv` y `resultados_perf_mutex.csv`), utilizando la herramienta **perf** para recolectar métricas como tiempo, ciclos, instrucciones y fallos de caché.

---

## Visualización de datos

Para comparar el rendimiento de las variantes, ejecute el script de visualización en Python:

```bash
python3 visualizar_datos.py
```

Este script generará gráficas comparativas de **tiempo de ejecución**, **speedup** y **eficiencia** para las variantes estudiadas en el taller, facilitando el análisis del impacto de la paralelización y la sincronización.

---

## Recomendaciones

- Asegúrese de tener instaladas las dependencias necesarias para ejecutar los scripts (por ejemplo, `pandas` y `matplotlib` para Python).
- Verifique que su sistema permita el uso de la herramienta `perf` (puede requerir permisos de superusuario).

---

## Estructura de archivos generados

- `resultados_perf_mutex.csv` : Resultados para la variante mutex.
- `resultados_perf_reduction.csv` : Resultados para la variante reduction.
- `resultados_comparacion.png` : Gráfica comparativa generada por el script Python.

---

## Contacto

Para consultas técnicas o soporte, contacte a los integrantes del equipo.