Ejemplo de ejercicio tipo solemne

	A partir del siguiente enunciado se desea realizar el modelo de entidad-relacion.
	"Una empresa vende productos a varios clientes. Se necesita conocer los datos personales de los clientes, (nombre, apellido, rut, direccion y fecha de nacimiento), cada producto tiene nombre y un codigo, así como un precio unitario. Un cliente puede comprar varios productosa la empresa, y un mismo producto puede ser comprado por varios clientes."


	Los productos son suministrados por proovedores diferentes. Se debe tener en cuenta que un producti sólo puede ser suministrado por un proovedor, y un proovedor puede sumnistrar diferentes productos, De cada proveedor se debe saber: el rut, nombre y direccion.

*Respondiendo a esto, se debe generar la siguiente tabla por ejemplo.*

	clientes
1. ID (Serial)
 2. Nombre (VarChar(30))
3. Apellido ( VarChar(30))
4. Rut (INT)
5. DV (VarChar(1))
6. Dirección (VarChar(30))
7. Fecha_Nacimiento (Date)
8. Dirección_numero ( VarChar(15))
---


		productos
1. ID (Serial)
2. Nombre (VarChar(30))
3. Código (Varchar(30))
4. Precio (INT)
5. Provedor ID (INT)


----
	Provedores
1. ID (Serial)
2. RUT (INT)
3. NOMBRE (VarChar(30))
4. DIRECCION (VarChar(30))
5. DV (VarCHar(1))
---
**Todo esto Corresponde a la Empresa**
-




*Ejercicio N°2*

	Camioneros
- Nombre (VarChar(30))
- RUT (Int)
- Telefono (Int)
- Direccion (VarChar (20))
- Salario (Int)
- DV (VarChar(1))
---
	Paquetes
- Codigo (Serial)
- Descripcion (VarChar(40))
- Destinatario (VarChar(30))
- Direccion de destinatario(Varchar(20))

---
	Provincia
- Codigo (Serial)
- Nombre (VarChar(30))
---
	Camiones
- Matricula (Serial)
- Modelo (VarChar(20))
- Tipo (VarChar(1))
- Potencia (Int)
#METATABLA
