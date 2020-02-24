# dijkstra
Uso de dijkstra en estructuras en lenguaje C

El algoritmo Dijkstra permite por medio de grafos conexos encontrar la ruta más corta de nodo a otro nodo. 
Esto gracias al indicar el nodo de partida y destino. 
Su resultado son la ruta traza para llegar a destino y el costo que se genera para llegar a destino. 
El programa lee el archivo grafo.in y crea una matriz de adyacencia n*n, 
siendo el este valor indicado por la primera línea del archivo “grafo.in”. 
funcionalmente se trabaja con listas enlazadas o bien con estructuras para así ser posible ingresar cualquier tamaño y 
cantidad de conexiones que tenga un grafo conexo. 
Si bien la primera línea indica la cantidad de nodos que contiene el grafo conexo, 
las siguientes líneas corresponde de la siguiente forma: 
2,8 3,4
...
..
.
En el archivo grafo.in la segunda línea comienza a significar el nodo,
donde a este a de restar un 1, en este caso el nodo es: 2-1=1. Nodo 1.
El nodo 1 tiene conexión con nodo 2 y 3. El costo para llegar a nodo 2 es 8 y el costo para llegar a nodo 3 es 4. 
Esto funciona de igual manera para las líneas siguiente.
