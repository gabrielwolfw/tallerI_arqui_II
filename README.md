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
make atomic
```

Esto generará los binarios correspondientes para cada variante.

---

## Ejecución individual

Para ejecutar cada variante utilizando el **máximo de hilos disponibles** en el sistema:

```bash
make run_reduction
make run_mutex
make run_atomic
```

Estos comandos ejecutan los programas con la máxima concurrencia detectada por el sistema.
Si deseas especificar explícitamente la cantidad de hilos a utilizar en cada variante, simplemente indica el número de hilos como argumento después del comando correspondiente. Por ejemplo:

```bash
make run_reduction 16 
make run_mutex 2
make run_atomic 1
```

---

## Obtención de datos de rendimiento

Para recolectar los resultados de las ejecuciones con diferentes cantidades de hilos (1, 2, 4, 8, 16), primero asegúrese de dar permisos de ejecución a los scripts:

```bash
chmod +x perf_reduction.sh
chmod +x perf_mutex.sh
chmod +x perf_atomic.sh
```
Antes de la ejecución de los scripts, es necesario que lea las recomendaciones al final. Debido a que es posible que necesite brindar permisos a perf para la obtención de datos.

Luego ejecute cada script:

```bash
./perf_reduction.sh
./perf_mutex.sh
./perf_atomic.sh
```

Estos scripts realizarán las pruebas con diferentes cantidades de hilos y guardarán los resultados en archivos CSV (`resultados_perf_reduction.csv`, `resultados_perf_mutex.csv`y `resultados_perf_atomic.csv`), utilizando la herramienta **perf** para recolectar métricas como ciclos, instrucciones y fallos de caché.

Para la recolección de los tiempo de ejecución se utilizó std::chrono.
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
- Verifique que su sistema permita el uso de la herramienta `perf` (puede requerir permisos de superusuario). En caso de no tener dichos permisos no se generarán los datos de los archivos .csv, para solucionarlo realice lo siguiente:

Para cambiar los permisos de forma temporal:
```bash
sudo sysctl -w kernel.perf_event_paranoid=1
```
Para cambiar los permisos de forma permanente:
1. Abre el archivo de configuración de sysctl para editarlo:
```bash
sudo nano /etc/sysctl.conf
```
2. Añade la siguiente línea al final del archivo:
```bash
kernel.perf_event_paranoid=1
```
3. Guarda y cierra el archivo.
4. Luego, aplica los cambios:
```bash
sudo sysctl -p
```
---

## Estructura de archivos generados

- `resultados_perf_mutex.csv` : Resultados para la variante mutex.
- `resultados_perf_reduction.csv` : Resultados para la variante reduction.
- `resultados_perf_atomic.csv` : Resultados para la variante atomic.
- `resultados_comparacion.png` : Gráfica comparativa generada por el script Python.

---

## Contacto

Para consultas técnicas o soporte, contacte a los integrantes del equipo.