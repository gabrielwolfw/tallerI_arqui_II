# Compila el histograma con reducción
reduction: histograma_reduction.cpp generator.cpp
	g++ histograma_reduction.cpp generator.cpp -o histograma_reduction

# Compila el histograma con mutex
mutex: histograma_mutex.cpp generator.cpp
	g++ histograma_mutex.cpp generator.cpp -o histograma_mutex

# Compila el histograma con atómicos
atomic: histograma_atomic.cpp generator.cpp
	g++ histograma_atomic.cpp generator.cpp -o histograma_atomic

# Ejecuta el histograma con reducción
run_reduction: reduction
	./histograma_reduction $h

# Ejecuta el histograma con mutex
run_mutex: mutex
	./histograma_mutex $h

# Ejecuta el histograma con atómicos
run_atomic: atomic
	./histograma_atomic $h

# Limpia los ejecutables
clean:
	rm -f histograma_reduction histograma_mutex histograma_atomic