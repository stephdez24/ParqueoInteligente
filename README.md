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

---

## Descripción del problema

El problema consiste en simular un sistema de parqueo inteligente con capacidad limitada, capaz de gestionar la entrada y salida de vehículos, asignar espacios disponibles y manejar una lista de espera cuando el parqueo se encuentra lleno.

El sistema permite:
- Registrar vehículos (placa, tipo y condición preferencial).
- Asignar espacios automáticamente según una estrategia.
- Gestionar una lista de espera cuando no hay disponibilidad.
- Consultar el estado del parqueo.
- Generar métricas para analizar el desempeño.

---

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

---

### Justificación

Las estructuras seleccionadas fueron elegidas considerando las operaciones principales del sistema: asignación de espacios, búsqueda de vehículos y gestión de la lista de espera.

- El uso de `vector` en la clase Parqueo responde a que la cantidad de espacios es fija desde la configuración inicial y no cambia durante la ejecución. Esto permite representar los espacios de forma simple y directa, facilitando su recorrido secuencial para operaciones como asignación y liberación. Además, el acceso a los elementos es eficiente y la estructura es fácil de implementar y mantener, lo cual es adecuado para el tipo de problema planteado.

- La `queue` en la clase ColaEspera permite modelar correctamente el comportamiento de una lista de espera real, donde los vehículos deben ser atendidos en el orden en que llegan. Esta estructura garantiza una política FIFO (First In, First Out), lo que aporta coherencia al sistema y evita inconsistencias en la atención de los vehículos. Además, sus operaciones principales (inserción y eliminación) tienen complejidad O(1), lo que la hace eficiente para este propósito.

- El uso de `unordered_map` en la clase BuscarVehiculo es clave para optimizar la búsqueda de vehículos por placa. En lugar de recorrer todos los espacios o la lista de espera, la tabla hash permite acceder directamente a la ubicación del vehículo en tiempo promedio O(1). Esto mejora significativamente el rendimiento del sistema, especialmente a medida que aumenta la cantidad de vehículos.

En resumen, estas estructuras permiten resolver el problema de manera eficiente, manteniendo un equilibrio entre simplicidad de implementación y buen desempeño en las operaciones principales del sistema.

---

### Alternativas consideradas

Se analizaron otras estructuras que podrían utilizarse en el sistema:

- **Lista enlazada:** podría utilizarse para representar los espacios del parqueo, permitiendo inserciones y eliminaciones dinámicas. Sin embargo, dado que la cantidad de espacios es fija y no cambia durante la ejecución, el vector resulta más eficiente y sencillo de manejar.

- **Árboles:** podrían utilizarse para mantener los datos ordenados o generar reportes más complejos. Sin embargo, el sistema no requiere mantener un orden específico ni realizar búsquedas por rango, por lo que su uso no aporta beneficios significativos y aumenta la complejidad de implementación.

---

### Impacto en la eficiencia

Las estructuras utilizadas permiten un desempeño adecuado en las operaciones principales del sistema.

- El uso de `vector` implica recorridos secuenciales para asignación y liberación de espacios, lo cual es eficiente dado el tamaño esperado del sistema.

- El `unordered_map` permite búsquedas rápidas por placa, evitando recorrer todas las estructuras del sistema.

- La `queue` permite gestionar la lista de espera de forma eficiente, manteniendo operaciones simples de inserción y eliminación.

En conjunto, estas estructuras permiten un sistema ágil y adecuado para los requerimientos planteados. Un análisis detallado de complejidad se presenta en la sección correspondiente.tes.
- Las operaciones de la cola (inserción y eliminación) se realizan en O(1), permitiendo una gestión eficiente de la lista de espera.

En conclusión, estas estructuras permiten un balance adecuado entre simplicidad de implementación y eficiencia en el sistema.

---

## Algoritmos implementados

El sistema implementa diferentes algoritmos para gestionar la asignación de espacios, la salida de vehículos, la búsqueda y la administración de la lista de espera.

### Asignación de espacios

Se implementaron dos estrategias principales:

| Estrategia | Descripción | Ventaja | Desventaja |
|-----------|------------|--------|-----------|
| Estrategia A | Asigna el primer espacio libre disponible sin validar tipo de vehículo | Simple y rápida | Puede asignar espacios incorrectos |
| Estrategia B | Asigna según tipo de vehículo y tipo de espacio | Uso más eficiente del parqueo | Puede aumentar el tiempo de espera |

- **Estrategia A:** recorre el vector de espacios y asigna el primero que esté libre. No realiza validaciones adicionales, lo que la hace más rápida, pero puede generar un uso ineficiente de los espacios.

- **Estrategia B:** recorre el vector y valida si el espacio es adecuado utilizando el método `aceptaVehiculo`. Esto permite una asignación más correcta y realista.

---

### Registro de salida

Cuando un vehículo sale del parqueo, el sistema ejecuta los siguientes pasos:

| Paso | Acción |
|------|-------|
| 1 | Buscar el espacio ocupado por la placa |
| 2 | Liberar el espacio |
| 3 | Actualizar la tabla hash |
| 4 | Atender la lista de espera |

Posteriormente, si existen vehículos en espera:
- En la estrategia A se atiende el primero en la cola.
- En la estrategia B se busca el primer vehículo compatible con el tipo de espacio liberado.

---

### Búsqueda de vehículos

La búsqueda se realiza mediante una tabla hash (`unordered_map`):

| Elemento | Descripción |
|---------|------------|
| Clave   | Placa del vehículo |
| Valor   | ID del espacio |
| Acceso  | Directo (sin recorrido) |

Esto permite localizar vehículos de forma rápida y eficiente.

---

### Gestión de la lista de espera

La lista de espera se implementa mediante una cola (FIFO):

| Operación | Descripción |
|----------|------------|
| Inserción | Se agrega el vehículo al final de la cola |
| Extracción | Se atiende el primer vehículo en entrar |
| Compatibilidad | En estrategia B se busca un vehículo adecuado |

Esto garantiza un orden justo en la atención de los vehículos.

---

### Validación de datos

Se implementaron mecanismos de validación para asegurar la consistencia de los datos ingresados al sistema.

- **Validación de placas:** se utiliza una expresión regular para verificar que la placa cumpla con el formato establecido (tres letras seguidas de tres números). Esto evita el registro de placas inválidas.

- **Control de entradas numéricas:** se emplean verificaciones utilizando `cin.fail()`, junto con `cin.clear()` y `cin.ignore()`, para evitar errores cuando el usuario ingresa valores no válidos. Además, se valida que los números sean positivos.

Estas validaciones permiten evitar fallos en la ejecución del programa y garantizar que los datos utilizados sean correctos.


---

### Comparación de estrategias

El sistema permite comparar dos enfoques de asignación de espacios:

| Característica        | Estrategia A | Estrategia B |
|----------------------|-------------|-------------|
| Tipo de asignación   | Primer espacio libre | Según tipo de vehículo |
| Validación           | No realiza validación | Valida compatibilidad |
| Uso de espacios      | Menos eficiente | Más eficiente |
| Complejidad          | O(n)        | O(n)        |
| Tiempo de espera     | Menor       | Puede aumentar |

La estrategia A ofrece un comportamiento más simple y rápido, ya que no realiza validaciones adicionales. Sin embargo, puede provocar un uso ineficiente de los espacios.

Por otro lado, la estrategia B mejora la asignación al considerar el tipo de vehículo y del espacio, lo que permite un uso más adecuado del parqueo, aunque puede aumentar el tiempo de espera en algunos casos.

En resumen, estos algoritmos permiten que el sistema funcione de manera correcta y cumpla con los requerimientos planteados.

---

## Complejidad (Big-O)

En esta sección se analiza la complejidad temporal y espacial de las principales operaciones del sistema, considerando las estructuras de datos utilizadas y el comportamiento real de los algoritmos implementados.

### Complejidad de operaciones

| Operación            | Estructura utilizada | Complejidad | Descripción |
|---------------------|--------------------|------------|-------------|
| Registrar entrada   | vector             | O(n)       | Recorre los espacios hasta encontrar uno disponible |
| Registrar salida    | vector + hash      | O(n)       | Búsqueda rápida + recorrido para liberar el espacio |
| Asignar espacio     | vector             | O(n)       | Recorrido secuencial para encontrar un espacio válido |
| Buscar vehículo     | unordered_map      | O(1)       | Acceso directo mediante tabla hash |
| Cola (insertar)     | queue              | O(1)       | Inserción al final de la cola |
| Cola (extraer)      | queue              | O(1)       | Eliminación del primer elemento |
| Cola (compatible)   | queue              | O(n)       | Recorrido para encontrar un vehículo compatible |

---

### Análisis temporal

Las operaciones relacionadas con el parqueo utilizan un `vector`, lo que implica recorridos secuenciales para encontrar espacios disponibles o liberar uno ocupado. Por esta razón, estas operaciones presentan una complejidad O(n), donde n es la cantidad de espacios.

La búsqueda de vehículos se realiza mediante `unordered_map`, lo que permite acceder directamente a la información en tiempo promedio O(1), evitando recorridos innecesarios.

La lista de espera, implementada con una `queue`, permite operaciones eficientes de inserción y eliminación en O(1). Sin embargo, cuando se requiere buscar un vehículo compatible (en la estrategia B), es necesario recorrer la cola, lo que introduce una complejidad O(n).

---

### Complejidad espacial

El sistema utiliza memoria proporcional a la cantidad de elementos almacenados:

- El `vector` ocupa espacio O(n), donde n es la cantidad de espacios del parqueo.
- La `queue` puede crecer hasta O(n) en el peor caso, cuando todos los vehículos están en espera.
- El `unordered_map` almacena un registro por vehículo, con complejidad O(n).

En general, el sistema mantiene una complejidad espacial O(n).

---

### Justificación

Las decisiones de diseño reflejan un equilibrio entre simplicidad, claridad y eficiencia.

El uso de un `vector` permite una implementación directa y fácil de entender, ya que los espacios del parqueo se recorren de forma secuencial. Aunque esto implica una complejidad O(n), resulta adecuado dado que el número de espacios es limitado y conocido desde el inicio.

La incorporación de un `unordered_map` optimiza significativamente la búsqueda de vehículos, reduciendo el tiempo de acceso de O(n) a O(1) en promedio. Esto es especialmente importante para operaciones frecuentes como la consulta por placa o la verificación de duplicados.

La `queue` permite una gestión eficiente de la lista de espera con operaciones constantes, lo que asegura un buen desempeño en inserciones y eliminaciones. Aunque la búsqueda de un vehículo compatible introduce un costo adicional O(n), este comportamiento es necesario para garantizar una asignación correcta en la estrategia B.

En resumen, el sistema prioriza una implementación clara y funcional, incorporando optimizaciones clave donde más impacto tienen, lo que permite un desempeño adecuado para los requerimientos del problema.

---

## Métricas

El sistema incluye un módulo de métricas que permite analizar el desempeño del parqueo durante su ejecución. Estas métricas se obtuvieron a partir de pruebas reales ejecutando el programa.

### Métricas implementadas

| Métrica                  | Descripción |
|--------------------------|------------|
| Ocupación del parqueo    | Promedio de ocupación calculado a partir de múltiples mediciones durante la ejecución |
| Tiempo promedio de espera | Promedio de tiempo que los vehículos permanecen en la lista de espera |
| Tiempo máximo de espera  | Mayor tiempo registrado en la lista de espera |
| Espacio más utilizado    | Espacio con mayor cantidad de asignaciones |

---

### Prueba realizada

Se ejecutó el sistema utilizando la estrategia B (asignación por tipo de espacio) con la siguiente configuración:

- Espacios normales: 2  
- Espacios para motos: 2  
- Espacios preferenciales: 2  
- Total de espacios: 6  

Durante la prueba se realizaron múltiples acciones, incluyendo:

- Registro de vehículos de distintos tipos.
- Llenado completo del parqueo.
- Envío de vehículos a la lista de espera.
- Salida de vehículos y reasignación automática desde la cola.
- Consulta del estado del parqueo y de la lista de espera.

---

### Resultados obtenidos

- Ocupación promedio del parqueo: **84.375%**  
- Tiempo promedio de espera: **3.67 ticks**  
- Tiempo máximo de espera: **8 ticks**  
- Espacio más utilizado: **#1 con 3 usos**

---

### Observaciones

- El sistema logró mantener el parqueo lleno durante gran parte de la ejecución, lo que se refleja en una alta ocupación promedio.

- La lista de espera funcionó correctamente, almacenando vehículos cuando no había espacios disponibles.

- Al liberar un espacio, el sistema reasignó automáticamente vehículos desde la cola, respetando la estrategia seleccionada.

- Se observó que algunos vehículos permanecieron más tiempo en espera debido a la necesidad de encontrar un espacio compatible, lo cual incrementó el tiempo máximo de espera.

- La métrica de uso de espacios muestra que ciertos espacios son utilizados con mayor frecuencia, lo que puede deberse al orden de asignación.

---

### Importancia de las métricas

Las métricas permiten:

- Evaluar el comportamiento del sistema en condiciones de alta demanda.
- Analizar el impacto de la estrategia de asignación utilizada.
- Verificar el correcto funcionamiento de la lista de espera.
- Identificar patrones de uso dentro del parqueo.

En conjunto, estas métricas permiten validar el funcionamiento del sistema y respaldar el análisis realizado en el proyecto.

---

## Comparación de enfoques

El sistema implementa dos estrategias de asignación de espacios, lo que permite comparar su comportamiento y evaluar su impacto en el funcionamiento del parqueo.

### Estrategias implementadas

| Característica        | Estrategia A | Estrategia B |
|----------------------|-------------|-------------|
| Tipo de asignación   | Primer espacio libre | Según tipo de vehículo |
| Validación           | No realiza validación | Valida compatibilidad |
| Complejidad          | O(n)        | O(n)        |
| Uso de espacios      | Menos eficiente | Más eficiente |
| Tiempo de espera     | Menor       | Puede aumentar |
| Realismo             | Bajo        | Alto |

---

### Análisis comparativo

La **Estrategia A** presenta un enfoque directo, donde el sistema asigna el primer espacio disponible sin considerar el tipo de vehículo. Esto permite una respuesta rápida ante la llegada de vehículos y reduce el tiempo de espera en la lista. Sin embargo, este comportamiento puede provocar una asignación inadecuada de espacios, por ejemplo, utilizando espacios preferenciales para vehículos que no lo requieren o asignando espacios no óptimos según el tipo.

Por otro lado, la **Estrategia B** incorpora validaciones que permiten asignar cada vehículo a un espacio compatible con sus características. Esto mejora significativamente el uso de los recursos del parqueo, ya que cada tipo de espacio se utiliza de manera más adecuada. No obstante, esta restricción introduce un costo en términos de tiempo de espera, especialmente en escenarios donde hay pocos espacios disponibles del tipo requerido.

En la prueba realizada, se observó que la estrategia B mantiene el parqueo en niveles altos de ocupación durante la mayor parte de la ejecución, lo que indica un uso eficiente de los espacios. Sin embargo, también se evidenció que algunos vehículos permanecen más tiempo en la lista de espera, ya que no siempre hay espacios compatibles disponibles de inmediato.

Además, la gestión de la lista de espera mostró un comportamiento correcto, manteniendo el orden de llegada y realizando reasignaciones automáticas cuando se liberaban espacios, lo cual refuerza la validez del modelo implementado.

---

### Resultados observados en la prueba

A partir de la ejecución del sistema:

- El parqueo se mantuvo lleno durante gran parte del tiempo, lo que demuestra un uso eficiente de los espacios con la estrategia B.

- La lista de espera se utilizó constantemente, lo que evidencia que la estrategia B puede generar mayor permanencia en la cola debido a las restricciones de asignación.

- La reasignación automática desde la lista de espera funcionó correctamente, respetando la compatibilidad entre vehículo y espacio.

- Se observó que algunos vehículos permanecieron más tiempo en espera, lo cual incrementó el tiempo máximo registrado.

---

### Conclusión

Ambas estrategias cumplen con el objetivo de asignar espacios dentro del parqueo, pero presentan diferencias importantes en su comportamiento.

La estrategia A es más eficiente en términos de rapidez, ya que permite una asignación inmediata sin restricciones. Esto la hace adecuada para escenarios donde se prioriza la velocidad de atención sobre la precisión en la asignación.

En contraste, la estrategia B prioriza la correcta asignación de los espacios, logrando un uso más eficiente y realista del parqueo. Aunque puede aumentar el tiempo de espera en algunos casos, ofrece un comportamiento más acorde a un sistema real.

En el contexto de este proyecto, la estrategia B resulta más adecuada, ya que permite modelar de forma más precisa el funcionamiento de un parqueo inteligente, equilibrando la eficiencia en el uso de los espacios con la gestión de la lista de espera.

---

## Análisis de resultados

A partir de las pruebas realizadas y las métricas obtenidas, es posible analizar el comportamiento general del sistema y evaluar la efectividad de las decisiones de diseño implementadas.

### Interpretación de métricas

Los resultados obtenidos muestran que el sistema mantiene un alto nivel de ocupación del parqueo, lo cual indica un uso eficiente de los espacios disponibles. La ocupación promedio refleja que, durante la ejecución, la mayoría de los espacios estuvieron en uso, especialmente en escenarios de alta demanda.

El tiempo promedio de espera y el tiempo máximo de espera evidencian el impacto de la lista de espera en el sistema. Aunque algunos vehículos fueron atendidos rápidamente, otros debieron esperar más tiempo debido a la disponibilidad limitada de espacios compatibles.

La métrica del espacio más utilizado permite identificar patrones en la asignación, mostrando que ciertos espacios tienden a ser utilizados con mayor frecuencia, lo cual está relacionado con el orden en que se recorren los espacios durante la asignación.

---

### Comportamiento del sistema

Durante la ejecución se observó que el sistema responde correctamente ante diferentes situaciones:

- Cuando el parqueo se llena, los vehículos adicionales son enviados a la lista de espera sin perder información.
- Al liberar un espacio, el sistema reasigna automáticamente un vehículo desde la cola, manteniendo la continuidad del flujo.
- La lista de espera respeta el orden de llegada, garantizando un comportamiento justo.
- La estrategia de asignación influye directamente en la distribución de los vehículos y en los tiempos de espera.

---

### Impacto de las estrategias

El uso de la estrategia B permitió una asignación más adecuada de los espacios, asegurando que cada vehículo ocupe un lugar compatible con sus características. Esto contribuyó a un uso más eficiente del parqueo, manteniendo altos niveles de ocupación durante la ejecución.

Sin embargo, esta misma restricción provocó que algunos vehículos permanecieran más tiempo en la lista de espera, lo cual se refleja en el aumento del tiempo máximo de espera.

En contraste, la estrategia A, permite una asignación más rápida al no aplicar validaciones. Esto reduciría el tiempo de espera en la lista, pero podría generar un uso ineficiente de los espacios, asignando vehículos a lugares no adecuados.

Esto demuestra que existe un balance entre rapidez y eficiencia en la asignación, dependiendo de la estrategia seleccionada.

---

### Evaluación general

El sistema cumple con los objetivos planteados, permitiendo gestionar la entrada y salida de vehículos, asignar espacios correctamente y manejar una lista de espera de forma eficiente.

Las métricas obtenidas respaldan el funcionamiento del sistema y permiten comprender su comportamiento bajo condiciones de alta demanda.

En general, el sistema presenta un buen desempeño, combinando estructuras de datos adecuadas con algoritmos eficientes, lo que permite una simulación realista del funcionamiento de un parqueo inteligente.

---

## Conclusiones

El desarrollo del sistema de parqueo inteligente permitió aplicar conceptos fundamentales de estructuras de datos y algoritmos en un contexto práctico, simulando un problema real de gestión de espacios.

A través de la implementación, se logró modelar correctamente el funcionamiento de un parqueo, incluyendo la asignación de espacios, la gestión de la lista de espera y la búsqueda eficiente de vehículos. El uso de estructuras como `vector`, `queue` y `unordered_map` permitió mantener un equilibrio entre simplicidad y eficiencia.

Las pruebas realizadas demostraron que el sistema responde adecuadamente ante escenarios de alta demanda, manteniendo una alta ocupación y gestionando correctamente los vehículos en espera. Las métricas obtenidas permitieron analizar el comportamiento del sistema y evidenciar el impacto de las decisiones de diseño.

Se observó que la estrategia de asignación influye directamente en el desempeño del sistema. La estrategia A prioriza la rapidez en la asignación, mientras que la estrategia B mejora la utilización de los espacios al considerar las características de los vehículos. Esto refleja un compromiso entre eficiencia operativa y realismo en la simulación.

Además, la implementación de métricas como la ocupación promedio, el tiempo de espera y el uso de los espacios permitió evaluar el sistema de manera más objetiva, proporcionando información útil para su análisis.

Como posible mejora, se podría implementar un sistema de prioridades en la lista de espera, así como un cálculo más detallado de métricas en tiempo real. También se podría optimizar la asignación de espacios utilizando estructuras más avanzadas si el sistema creciera en tamaño.

En general, el proyecto cumple con los objetivos planteados, logrando una simulación funcional, clara y eficiente de un sistema de parqueo inteligente.

---

## Uso de Inteligencia Artificial

### Herramienta utilizada
Claude (Anthropic) – https://claude.ai  

---

### 1. Uso de `unordered_map` (tabla hash)

**Objetivo:** Comprender el funcionamiento y eficiencia de una tabla hash en C++.

**Prompt empleado:**  
"¿Qué es un unordered_map en C++ y cómo se diferencia de un map normal?"

**Resumen de la respuesta:**  
Se explicó que `unordered_map` utiliza una función hash para almacenar elementos, permitiendo búsquedas en tiempo promedio O(1), mientras que `map` utiliza un árbol binario balanceado con complejidad O(log n).

**Cómo ayudó:**  
Permitió seleccionar una estructura eficiente para la búsqueda de vehículos por placa, evitando recorridos lineales.

**Modificaciones realizadas:**  
Se implementó la clase `BuscarVehiculo` utilizando `unordered_map`, con métodos adaptados al sistema:
- `registrarUbicacion`
- `buscarEspacio`
- `eliminarPlaca`
- `existe`

---

### 2. Expresiones regulares (`regex`)

**Objetivo:** Validar el formato de placas vehiculares.

**Prompt empleado:**  
"¿Cómo valido que un string tenga exactamente 3 letras seguidas de 3 números en C++?"

**Resumen de la respuesta:**  
Se explicó el uso del patrón `^[A-Za-z]{3}[0-9]{3}$` para validar el formato de la placa.

**Cómo ayudó:**  
Permitió implementar una validación eficiente sin recorrer manualmente el string.

**Modificaciones realizadas:**  
Se implementó la función `placaValida()` adaptada al formato de placas tipo `ABC123`.

---

### 3. Conversión de mayúsculas y minúsculas

**Objetivo:** Normalizar la entrada de datos del usuario.

**Prompt empleado:**  
"¿Cómo convierto un string completo a mayúsculas en C++ y un char a minúscula?"

**Resumen de la respuesta:**  
Se explicó el uso de `transform` junto con `toupper` para strings y `tolower` para caracteres individuales.

**Cómo ayudó:**  
Permitió evitar inconsistencias en los datos ingresados.

**Modificaciones realizadas:**  
Se aplicó `transform` para normalizar las placas y `tolower` para validar respuestas tipo 's'/'n'.

---

### 4. Validación de entrada de datos

**Objetivo:** Evitar errores de ejecución por entradas inválidas.

**Prompt empleado:**  
"¿Cómo evito que mi programa en C++ falle cuando el usuario ingresa texto en lugar de números?"

**Resumen de la respuesta:**  
Se explicó el uso de:
- `cin.fail()` para detectar errores  
- `cin.clear()` para limpiar el estado  
- `cin.ignore()` para limpiar el buffer  

**Cómo ayudó:**  
Permitió implementar una lectura robusta de datos, evitando bloqueos del programa.

**Modificaciones realizadas:**  
Se implementaron las funciones:
- `leerOpcion()`
- `leerEnteroPositivo()`

Incluyendo validación de valores negativos y entradas incorrectas.

---

### Conclusión

La inteligencia artificial fue utilizada como una herramienta de apoyo para comprender conceptos y mejorar la implementación del sistema.

Las respuestas obtenidas permitieron reforzar el uso de estructuras de datos, validaciones y manejo de entradas en C++. El código final no fue generado automáticamente, sino adaptado, comprendido y modificado según los requerimientos del proyecto.

En conjunto, el uso de IA contribuyó al aprendizaje y a la correcta implementación de las funcionalidades del sistema.
