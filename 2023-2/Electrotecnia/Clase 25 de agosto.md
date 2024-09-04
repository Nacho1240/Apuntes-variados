*Método de nodos:*


	A diferencia del metodo de malla del cual obtenemos corriente, el metodo de nodos nos entrega voltaje.

- Primero Identificar la cantidad mínima de nodos
- El circuito necesita una referencia, el cual es 0 Volteos.
- Ademas, para cada voltaje de nodo necesito su propio sistema de referencia


$$Ia2 = \frac{Va-Vc}{R2}$$
- De manera simplificada seria el nodo - la tierra dividido en la resistencia.

Lo anterior se demuestra de la siguiente manera
-
#formula_de_origen
- $Epa = \Delta Ep2 + \Delta Epc$
- $Va =Ia · R2 + Vc$


$$Ia3 = \frac{Va-Vb}{R3}$$
$$Ia1 = \frac{Va -Vt -Vc}{R1}$$
---

	Segun Kirtchnoff la suma de las energias salientes es igual a 0
#Esto_es_solo_el_nodo_A
$$Ia1 + Ia2+Ia3=0$$

$$\frac{Va-Vt-Vc}{R1}+\frac{Va-Vc}{R2}+\frac{Va-VB}{R3}=0$$

$$Va[\frac{1}{R1}+\frac{1}{R2}+\frac{1}{R3}]+Vb[\frac{-1}{R3}]=\frac{Vt}{R1}$$




