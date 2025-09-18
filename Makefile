# Compila el histograma con reducción
reduction: histograma_reduction.cpp generator.cpp
	g++ histograma_reduction.cpp generator.cpp -o histograma_reduction -fopenmp

# Compila el histograma con mutex
mutex: histograma_mutex.cpp generator.cpp
	g++ histograma_mutex.cpp generator.cpp -o histograma_mutex

# Compila el histograma con atómicos
atomic: histograma_atomic.cpp generator.cpp
	g++ histograma_atomic.cpp generator.cpp -o histograma_atomic

# Ejecuta el histograma con reducción
run_reduction: reduction
	./histograma_reduction $(arg)

# Ejecuta el histograma con mutex
run_mutex: mutex
	./histograma_mutex $(arg)

# Ejecuta el histograma con atómicos
run_atomic: atomic
	./histograma_atomic $(arg)

# Argumento posicional (número de hilos)
arg = $(word 2, $(MAKECMDGOALS))

# Evita error si pones "make run_reduction 8"
%:
	@:

# Limpia los ejecutables
clean:
	rm -f histograma_reduction histograma_mutex histograma_atomic