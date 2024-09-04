**Ejercicio:**

	A partir del siguiente enunciado se desea realizar el modelo entidad-relacion. "Con la llegada de la ley cholito se necesita saber de una mascota(Perros), de que criador proviene, en que veterinaria se atiende y quienes son sus familiares(Padre,Madre, Hermanos, Hermanas, Abuelos, Abuelas, Hijos e Hijas)"

	Considere que una mascota puede ser atendida por mas de una veterinaria, una veterinaria tiene Nombre, Direccion, Telefono, Veterinario encargado, un criadero contiene Nombre, Direccion, Telefono y por ultimo una mascota contiene los atributos Nombre, numero de chip, raza, color y fecha de nacimiento.


**Veterinario:**
1. Nombre
2. Dirección
3. Teléfono
4. Veterinario_Encargado

**Criadero:**
1. Nombre
2. Dirección
3. Teléfono
4. ID

**Mascota:**
1. Nombre
2. Chip
3. Raza
4. Color
5. Fecha_de_Nacimiento


#Importante 
Se resuelve con recursividad, en el nodo mascotas con padre id y madre id.
