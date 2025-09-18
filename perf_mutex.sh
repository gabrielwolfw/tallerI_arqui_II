#!/bin/bash

EXEC="./histograma_mutex"
HILOS=(1 2 4 8 16)
CSV="resultados_perf_mutex.csv"

echo "variante,hilos,tiempo,cycles,instructions,cache_misses" > $CSV

for h in "${HILOS[@]}"; do
  echo "Ejecutando $EXEC $h..."
  PERF_OUT=$(perf stat -e cycles,instructions,cache-misses -x, $EXEC $h 2>&1)

  cycles=$(echo "$PERF_OUT" | awk -F, '/cycles/ {print $1}')
  instructions=$(echo "$PERF_OUT" | awk -F, '/instructions/ {print $1}')
  cache_misses=$(echo "$PERF_OUT" | awk -F, '/cache-misses/ {print $1}')
  tiempo=$(echo "$PERF_OUT" | grep "Tiempo de ejecución:" | awk '{print $4}')

  echo "mutex,$h,$tiempo,$cycles,$instructions,$cache_misses" >> $CSV
done