Nombres:  
Juan Manuel Restrepo  
Fredy Hoyos Cardenas  
Dorian Garcia    
  
Estudiantes de la Universidad de Antioquia, ingenieria de sistemas.  
  
🧮 Laboratorio 3 – Programación Concurrente con Pthreads (C)  

Este proyecto forma parte del Laboratorio 3 del curso de Sistemas Operativos, enfocado en la programación paralela y concurrente utilizando la biblioteca POSIX Threads (pthread) en lenguaje C.  
  
📂 Contenido del Proyecto  

El laboratorio se divide en dos partes principales:  
  
🧠 Parte 1 – Cálculo Paralelo de π (Pi)  

Implementa una versión serial y paralela del cálculo del número π mediante el método del punto medio para integración numérica.  

- pi_s.c: versión serial (tiempo base Ts)  

- pi_p.c: versión paralela con hilos POSIX (pthread_create, pthread_join)  

- Se miden y comparan los tiempos de ejecución (Tp) con diferentes números de hilos (N = 1, 2, 4, 8, ...).  

- Se calcula y grafica el Speedup y la Eficiencia usando Python (analisis.ipynb).  
  
📈 Métricas calculadas:  

- Ts: Tiempo serial  

- Tp: Tiempo paralelo  

- Speedup = Ts / Tp  

- Eficiencia = Speedup / N  
  
🔢 Parte 2 – Generador de Secuencia de Fibonacci  

Implementa un programa concurrente donde un hilo trabajador genera los primeros N números de la secuencia de Fibonacci, mientras que el hilo principal espera la finalización del cálculo.  

- fibonacci.c:  
  
    - Usa memoria dinámica (malloc) para el arreglo compartido.  

    - El hilo principal crea un único hilo para generar la secuencia.  

    - Se sincroniza con pthread_join para garantizar la consistencia de los datos.  
  
🧩 Conceptos aplicados:  

- Paso de parámetros mediante estructuras (struct).  

- Sincronización entre hilos.  

- Comunicación a través de memoria compartida.    
  
⚙️ Compilación y Ejecución  
# Compilar programas
gcc -o pi_s pi_s.c -lm
gcc -o pi_p pi_p.c -lpthread -lm
gcc -o fibonacci fibonacci.c -lpthread

# Ejecutar
./pi_s
./pi_p 200000000 4
./fibonacci 15
