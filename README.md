# ParqueoInteligente

## Información del Proyecto

- Universidad: Universidad Técnica Nacional  
- Curso: Estructuras de Datos  
- Periodo: I Cuatrimestre 2026  
- Proyecto: Sistema de Parqueo Inteligente  
- Profesor: Jose Carlos González González  

### Integrantes
- Rachel Cristina Oviedo Carvajal  
- Stephany del Carmen Hernández Tercero

## Descripción del problema

El problema consiste en simular un sistema de parqueo inteligente con capacidad limitada, capaz de gestionar la entrada y salida de vehículos, asignar espacios disponibles y manejar una lista de espera cuando el parqueo se encuentra lleno.

El sistema permite:
- Registrar vehículos (placa, tipo y condición preferencial).
- Asignar espacios automáticamente según una estrategia.
- Gestionar una lista de espera cuando no hay disponibilidad.
- Consultar el estado del parqueo.
- Generar métricas para analizar el desempeño.

## Estructuras de datos utilizadas

En el desarrollo del sistema se utilizaron tanto estructuras lineales como no lineales, seleccionadas en función de las operaciones principales del sistema, como asignación de espacios, búsqueda de vehículos y gestión de la lista de espera.

### Estructuras utilizadas

| Estructura        | Tipo        | Uso en el sistema |
|------------------|------------|------------------|
| vector           | Lineal     | Almacenar los espacios del parqueo |
| queue            | Lineal     | Gestionar la lista de espera (FIFO) |
| unordered_map    | No lineal  | Buscar vehículos por placa |

### Estructuras lineales

- **vector (Parqueo):** se utiliza para almacenar los espacios del parqueo. Esta estructura permite recorrer los espacios de forma secuencial para realizar operaciones como asignación y liberación. Dado que la cantidad de espacios es fija desde la configuración inicial, el uso de un vector resulta adecuado y eficiente.

- **queue (ColaEspera):** se utiliza para gestionar los vehículos en lista de espera siguiendo una política FIFO (First In, First Out). Esto asegura que los vehículos sean atendidos en el mismo orden en que llegan, lo cual representa un comportamiento realista del sistema.

### Estructuras no lineales

- **unordered_map (BuscarVehiculo):** se utiliza para almacenar la relación entre la placa del vehículo y el espacio asignado. Esta estructura permite realizar búsquedas en tiempo promedio O(1), lo que evita recorrer todos los espacios del parqueo o la lista de espera.

### Justificación

Las estructuras seleccionadas fueron elegidas considerando las operaciones principales del sistema: asignación de espacios, búsqueda de vehículos y gestión de la lista de espera.

- El uso de `vector` en la clase Parqueo responde a que la cantidad de espacios es fija desde la configuración inicial y no cambia durante la ejecución. Esto permite representar los espacios de forma simple y directa, facilitando su recorrido secuencial para operaciones como asignación y liberación. Además, el acceso a los elementos es eficiente y la estructura es fácil de implementar y mantener, lo cual es adecuado para el tipo de problema planteado.

- La `queue` en la clase ColaEspera permite modelar correctamente el comportamiento de una lista de espera real, donde los vehículos deben ser atendidos en el orden en que llegan. Esta estructura garantiza una política FIFO (First In, First Out), lo que aporta coherencia al sistema y evita inconsistencias en la atención de los vehículos. Además, sus operaciones principales (inserción y eliminación) tienen complejidad O(1), lo que la hace eficiente para este propósito.

- El uso de `unordered_map` en la clase BuscarVehiculo es clave para optimizar la búsqueda de vehículos por placa. En lugar de recorrer todos los espacios o la lista de espera, la tabla hash permite acceder directamente a la ubicación del vehículo en tiempo promedio O(1). Esto mejora significativamente el rendimiento del sistema, especialmente a medida que aumenta la cantidad de vehículos.

En conjunto, estas estructuras permiten resolver el problema de manera eficiente, manteniendo un equilibrio entre simplicidad de implementación y buen desempeño en las operaciones principales del sistema.

### Alternativas consideradas

Se analizaron otras estructuras que podrían utilizarse en el sistema:

- **Lista enlazada:** podría utilizarse para representar los espacios del parqueo, permitiendo inserciones y eliminaciones dinámicas. Sin embargo, dado que la cantidad de espacios es fija y no cambia durante la ejecución, el vector resulta más eficiente y sencillo de manejar.

- **Árboles:** podrían utilizarse para mantener los datos ordenados o generar reportes más complejos. Sin embargo, el sistema no requiere mantener un orden específico ni realizar búsquedas por rango, por lo que su uso no aporta beneficios significativos y aumenta la complejidad de implementación.

### Impacto en la eficiencia

Las estructuras utilizadas permiten un desempeño adecuado en las operaciones principales del sistema.

- El uso de `vector` implica recorridos secuenciales para asignación y liberación de espacios, lo cual es eficiente dado el tamaño esperado del sistema.

- El `unordered_map` permite búsquedas rápidas por placa, evitando recorrer todas las estructuras del sistema.

- La `queue` permite gestionar la lista de espera de forma eficiente, manteniendo operaciones simples de inserción y eliminación.

En conjunto, estas estructuras permiten un sistema ágil y adecuado para los requerimientos planteados. Un análisis detallado de complejidad se presenta en la sección correspondiente.tes.
- Las operaciones de la cola (inserción y eliminación) se realizan en O(1), permitiendo una gestión eficiente de la lista de espera.

En conjunto, estas estructuras permiten un balance adecuado entre simplicidad de implementación y eficiencia en el sistema.

---
