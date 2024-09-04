---
*Ejercicio:*

	Usuarios
1. ID(Serial)
2. Nombre (VarChar 30)
3. Apellido (VarChar 30)
4. Fecha de nacimiento. (Date)
5. Nombre de Usuario. (VarChar 30)
6. Banco



		Ofertas
- ID(Serial)
- Tipo de servicio
- Fecha de publicacion ( Date)
- Status
- Vendedor (VarChar 30)

			Ventas
- ID Usuario(Serial)
- ID oferta(Serial)
- ID Venta (Serial)
- Fecha de compra (Date)

				Banco
- ID
- Nombre (VarChar 30)


					Tipo_Cuenta
- Tipo_Cuenta (Varchar 20)

						Datos Bancarios
- ID Usuario
- ID Datos
- ID banco
- ID tipo
- Numero de Cuenta

						Servicio Streaming
- Nombre servivio
