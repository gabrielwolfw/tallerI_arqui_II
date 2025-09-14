# Compila el histograma con reducción
reduction: histograma_reduction.cpp generator.cpp
	g++ histograma_reduction.cpp generator.cpp -o histograma_reduction

# Compila el histograma con mutex
mutex: histograma_mutex.cpp generator.cpp
	g++ histograma_mutex.cpp generator.cpp -o histograma_mutex

# Ejecuta el histograma con reducción
run_reduction: reduction
	./histograma_reduction

# Ejecuta el histograma con mutex
run_mutex: mutex
	./histograma_mutex

# Limpia los ejecutables
clean:
	rm -f histograma_reduction histograma_mutex