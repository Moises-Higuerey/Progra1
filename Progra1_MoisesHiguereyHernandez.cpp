#include <iostream>
#include <fstream>
#include <string>
#include "listaSimple.cpp"
#include "Listadoblecircular.cpp"
#include "Listadoble.cpp"
#include "Listadoblecircularclientes.cpp"
lista listaCiudades,listaU0,listaU1,listaU2,listaU3,carrito,ultimosProductosIngresados;
lista productosVendidos;//Nombre;Codigo;CodigoSuper;Cantidad
lista productosMenosVendidosPorSuper;//CodigoSuper;Cantidad
lista trabajoAdministradores;
lista comprasPorCliente;//Nombre;Cedula;Cantidad
lista visitasSuper;
listaD listaSuper;
listaD listaSolicitudes;
listaDC listaInventario;
listaDCC listaCliente;
ifstream archivoC;
ifstream archivoI;
ifstream archivoS;
ifstream archivoU;
string superCarrito = "";
string ultimoProductoModificado;
string ultimoProductoEliminado;
string productoMasVendido = "";
string clienteMasCompras;
string clienteMenosCompras;
string superMasVisitado;
string superMenosVisitado;
string administradorMasTrabajo;
int consecutivos=0;
using namespace std;  //Division de informacion
lista split(string cadena){
	lista Lista;
	string palabra;
	for(int i = 0; i < cadena.size(); ++i){
		if(cadena[i]==';'){
			Lista.InsertarFinal(palabra);
			palabra="";
		}
		else{
			palabra+=cadena[i];
		}
	}
	Lista.InsertarFinal(palabra);
	return Lista;
}

/*----------------Metodos de Verificacion-------------------*/
bool verificarCiudades(string codigo){
	pnodo aux = listaCiudades.getPrimero();
	string info;
	while(aux!=NULL){
		info = aux->getValor();
		aux=aux->getSiguiente();
		string codigoV = split(info).getPrimero()->getValor();
		if(codigo==codigoV){
			return true;
		}
	}
	return false;
}
bool verificarSupermercados(string codigo){
	pnodoD aux = listaSuper.getPrimero();
	string info;
	while(aux!=NULL){
		info = aux->getValor();
		aux=aux->getSiguiente();
		string codigoV = split(info).getPrimero()->getSiguiente()->getValor();
		if(codigo==codigoV){
			return true;
		}
	}
	return false;
}

bool verificarUsuarios(string codigo){
	pnodo aux = listaU0.getPrimero();
	string info;
	while(aux!=NULL){
		info = aux->getValor();
		aux=aux->getSiguiente();
		string codigoV = split(info).getPrimero()->getSiguiente()->getValor();
		if(codigo==codigoV){
			return true;
		}
	}
	aux = listaU1.getPrimero();
	while(aux!=NULL){
		info = aux->getValor();
		aux=aux->getSiguiente();
		string codigoV = split(info).getPrimero()->getSiguiente()->getValor();
		if(codigo==codigoV){
			return true;
		}
	}
	aux = listaU2.getPrimero();
	while(aux!=NULL){
		info = aux->getValor();
		aux=aux->getSiguiente();
		string codigoV = split(info).getPrimero()->getSiguiente()->getValor();
		if(codigo==codigoV){
			return true;
		}
	}
	aux = listaU3.getPrimero();
	while(aux!=NULL){
		info = aux->getValor();
		aux=aux->getSiguiente();
		string codigoV = split(info).getPrimero()->getSiguiente()->getValor();
		if(codigo==codigoV){
			return true;
		}
	}
	return false;
}


bool verificarTipo(string cedula, int usuario){
	bool resultado;
	pnodo aux;
	string tipo;
	string cedulaV;
	switch(usuario){
		case 0:
			aux = listaU0.getPrimero();
			while(aux!=NULL){
				cedulaV = split(aux->getValor()).getPrimero()->getSiguiente()->getValor();
				tipo = split(aux->getValor()).getPrimero()->getSiguiente()->getSiguiente()->getSiguiente()->getSiguiente()->getValor();
				aux = aux->getSiguiente();
				if(cedula == cedulaV && tipo=="0"){
					return true;
				}
			}
			break;
		case 1:
			aux = listaU1.getPrimero();
			while(aux!=NULL){
				cedulaV = split(aux->getValor()).getPrimero()->getSiguiente()->getValor();
				tipo = split(aux->getValor()).getPrimero()->getSiguiente()->getSiguiente()->getSiguiente()->getSiguiente()->getValor();
				aux = aux->getSiguiente();
				if(cedula == cedulaV && tipo=="1"){
					return true;
				}
			}
			break;
		case 2:
			aux = listaU2.getPrimero();
			while(aux!=NULL){
				cedulaV = split(aux->getValor()).getPrimero()->getSiguiente()->getValor();
				tipo = split(aux->getValor()).getPrimero()->getSiguiente()->getSiguiente()->getSiguiente()->getSiguiente()->getValor();
				aux = aux->getSiguiente();
				if(cedula == cedulaV && tipo=="2"){
					return true;
				}
			}
			break;
		case 3:
			aux = listaU3.getPrimero();
			while(aux!=NULL){
				cedulaV = split(aux->getValor()).getPrimero()->getSiguiente()->getValor();
				tipo = split(aux->getValor()).getPrimero()->getSiguiente()->getSiguiente()->getSiguiente()->getSiguiente()->getValor();
				aux = aux->getSiguiente();
				if(cedula == cedulaV && tipo=="3"){
					return true;
				}
			}
			break;
		default:
			break;
	}
	return false;
}

bool verificarProducto(string codigo){
	if(listaInventario.getPrimero()==NULL){
		return false;
	}
	else{
		string info;
		pnodoDC aux = listaInventario.getPrimero();
		pnodoDC aux2 = aux->getAnterior();
		info = split(aux->getValor()).getPrimero()->getSiguiente()->getValor();
		if(info==codigo){
			return true;
		}
		aux = aux->getSiguiente();
		while(aux!=listaInventario.getPrimero()){
			info = split(aux->getValor()).getPrimero()->getSiguiente()->getValor();
			if(info==codigo){
				return true;
			}
			aux = aux->getSiguiente();	
		}
		return false;
	}
}
bool verificarExistenciaArchivo(string nombre){
	ifstream prueba(nombre);
	return (bool)prueba;
}
/*--------------Metodos de la aplicacion----------------*/
string consultarPrecio(string producto){
	pnodoDC aux = listaInventario.getPrimero();
	string codigo = split(aux->getValor()).getPrimero()->getSiguiente()->getValor();
	if(codigo==producto){
		return aux->getValor();
	}
	aux=aux->getSiguiente();
	while(aux!=listaInventario.getPrimero()){
		string codigo = split(aux->getValor()).getPrimero()->getSiguiente()->getValor();
		if(codigo==producto){
			return aux->getValor();
		}	
		aux=aux->getSiguiente();
	}
	return "No se encontro el producto";
}
string consultarSuper(string super){
	if(!verificarSupermercados(super)){
		return "No existe el supermercado";
	}
	string resultado;
	pnodoDC aux = listaInventario.getPrimero();
	string info;
	info = split(aux->getValor()).getPrimero()->getValor();
	if(info==super){
		info = aux->getValor();
		resultado+=info+"\n";
	}
	aux = aux->getSiguiente();
	while(aux!=listaInventario.getPrimero()){
		info = split(aux->getValor()).getPrimero()->getValor();
		if(info==super){
			info = aux->getValor();
			resultado+=info+"\n";
		}
		aux = aux->getSiguiente();
	}
	return resultado;
}
string anadirAlCarrito(string producto,int cantidad){
	string compra = producto+";"+to_string(cantidad);
	pnodoDC aux = listaInventario.getPrimero();
	string info;
	info = split(aux->getValor()).getPrimero()->getSiguiente()->getValor();
	if(info==producto){
		producto = split(aux->getValor()).getPrimero()->getValor() + ";" + split(aux->getValor()).getPrimero()->getSiguiente()->getValor() + ";" + split(aux->getValor()).getPrimero()->getSiguiente()->getSiguiente()->getValor() + ";" + to_string(stoi(split(aux->getValor()).getPrimero()->getSiguiente()->getSiguiente()->getSiguiente()->getValor())-cantidad) + ";" + split(aux->getValor()).getPrimero()->getSiguiente()->getSiguiente()->getSiguiente()->getSiguiente()->getValor(); 
		aux->setValor(producto);
		return compra;		
	}
	aux = aux->getSiguiente();
	while(aux!=listaInventario.getPrimero()){
		info = split(aux->getValor()).getPrimero()->getSiguiente()->getValor();
		if(info==producto){
			producto = split(aux->getValor()).getPrimero()->getValor() + ";" + split(aux->getValor()).getPrimero()->getSiguiente()->getValor() + ";" + split(aux->getValor()).getPrimero()->getSiguiente()->getSiguiente()->getValor() + ";" + to_string(stoi(split(aux->getValor()).getPrimero()->getSiguiente()->getSiguiente()->getSiguiente()->getValor())-cantidad) + ";" + split(aux->getValor()).getPrimero()->getSiguiente()->getSiguiente()->getSiguiente()->getSiguiente()->getValor(); 
			aux->setValor(producto);
			return compra;
		}	
		aux = aux->getSiguiente();
	}
	return compra;
}
bool verificarSolicitud(string cedula){
	pnodoD aux = listaSolicitudes.getPrimero();
	string info;
	while(aux!=NULL){
		info = split(aux->getValor()).getPrimero()->getSiguiente()->getValor();
		if(info==cedula){
			return true;
		}
		aux = aux->getSiguiente();
	}
	return false;
}
void devolverProducto(string producto){
	string codigo = split(producto).getPrimero()->getValor();
	int cantidad = stoi(split(producto).getPrimero()->getSiguiente()->getValor());
	string info;
	pnodoDC aux = listaInventario.getPrimero();
	info = split(aux->getValor()).getPrimero()->getSiguiente()->getValor();
	if(info==codigo){
		producto = split(aux->getValor()).getPrimero()->getValor() + ";" + split(aux->getValor()).getPrimero()->getSiguiente()->getValor() + ";" + split(aux->getValor()).getPrimero()->getSiguiente()->getSiguiente()->getValor() + ";" + to_string(stoi(split(aux->getValor()).getPrimero()->getSiguiente()->getSiguiente()->getSiguiente()->getValor())+cantidad) + ";" + split(aux->getValor()).getPrimero()->getSiguiente()->getSiguiente()->getSiguiente()->getSiguiente()->getValor(); 
		aux->setValor(producto);
		return;
	}
	aux = aux->getSiguiente();
	while(aux->getValor()!=listaInventario.getPrimero()->getValor()){
		info = split(aux->getValor()).getPrimero()->getSiguiente()->getValor();
		if(info==codigo){
			producto = split(aux->getValor()).getPrimero()->getValor() + ";" + split(aux->getValor()).getPrimero()->getSiguiente()->getValor() + ";" + split(aux->getValor()).getPrimero()->getSiguiente()->getSiguiente()->getValor() + ";" + to_string(stoi(split(aux->getValor()).getPrimero()->getSiguiente()->getSiguiente()->getSiguiente()->getValor())+cantidad) + ";" + split(aux->getValor()).getPrimero()->getSiguiente()->getSiguiente()->getSiguiente()->getSiguiente()->getValor(); 
			aux->setValor(producto);
			return;
		}	
		aux = aux->getSiguiente();
	}
}
void insertarProducto(){
	string codigoS;
	string codigoP;
	string nombre;
	string cantidad;
	string precio;
	string producto;
	cout << "Indique el super" << endl;
	cin >> codigoS;
	if(!verificarSupermercados(codigoS)){
		cout << "Indique un supermercado valido" << endl;
		return insertarProducto();
	}
	cout << "Indique el codigo a asignar" << endl;
	cin >> codigoP;
	if(verificarProducto(codigoP)){
		cout << "El codigo esta en uso" << endl;
		return insertarProducto();
	}
	cout << "Indique el nombre a asignar" << endl;
	cin >> nombre;
	cout << "Indique la cantidad" << endl;
	cin >> cantidad;
	if(stoi(cantidad)<=0){
		cout << "Ingrese una cantidad mayor a cero" << endl;
		return insertarProducto();
	}
	cout << "Indique el precio" << endl;
	cin >> precio;
	if(stoi(precio)<=0){
		cout << "Ingrese un precio mayor a cero" << endl;
		return insertarProducto();
	}
	producto = codigoS+";"+codigoP+";"+nombre+";"+cantidad+";"+precio;
	listaInventario.InsertarFinal(producto);
	if(ultimosProductosIngresados.largoLista()<2){
		ultimosProductosIngresados.InsertarFinal(producto);
	}
	else{
		ultimosProductosIngresados.BorrarInicio();
		ultimosProductosIngresados.InsertarFinal(producto);
	}
	ofstream archivoIO;
	archivoIO.open("Inventario.txt",ios_base::app);
	archivoIO << producto << endl;
	archivoIO.close();
}
void eliminarProducto(string producto){
	string linea;
	int contador;
	contador = 1;
	producto = consultarPrecio(producto);
	pnodoDC aux = listaInventario.getPrimero();
	while(aux->getValor()!=producto){
		aux = aux->getSiguiente();
		contador++;
	}
	listaInventario.borrarPosicion(contador);
	ofstream archivoIO;
	archivoI.open("Inventario.txt");
	archivoIO.open("temp.txt");
	while(getline(archivoI,linea)){
		if(linea!=producto){
			archivoIO << linea << endl;
		}
	}
	ultimoProductoEliminado = producto;
	archivoI.close();
	archivoIO.close();
	remove("Inventario.txt");
	rename("temp.txt","Inventario.txt");
}
void modificarProducto(string producto){
	string linea;
	string codigoS;
	string codigoP;
	string nombre;
	string cantidad;
	string precio;
	string productoC = consultarPrecio(producto);
	pnodoDC aux = listaInventario.getPrimero();
	while(aux->getValor()!=productoC){
		aux = aux->getSiguiente();
	}
	cout << "La informacion del producto actual es: " << productoC << endl;
	cout << "Ingrese el codigo del super nuevo: "  << endl;
	cin >> codigoS;
	if(!verificarSupermercados(codigoS)){
		cout << "El supermercado no existe"	<< endl;
		return modificarProducto(producto);
	}
	cout << "Ingrese el nuevo codigo del producto: "  << endl;
	cin >> codigoP;
	if(verificarProducto(codigoP) && codigoP!=producto){
		cout << "El codigo ya esta en uso" << endl;
		return modificarProducto(producto);
	}
	cout << "Ingrese el nuevo nombre del producto: "  << endl;
	cin >> nombre;
	cout << "Ingrese la cantidad nueva: "  << endl;
	cin >> cantidad;
	if(stoi(cantidad)<=0){
		cout << "Ingrese una cantidad mayor a cero" << endl;
		return modificarProducto(producto);
	}
	cout << "Ingrese el precio nuevo: "  << endl;
	cin >> precio;
	if(stoi(cantidad)<=0){
		cout << "Ingrese un precio mayor a cero" << endl;
		return modificarProducto(producto);
	}
	producto = codigoS + ";"  + codigoP + ";"  + nombre + ";"  + cantidad + ";" + precio;
	aux->setValor(producto);
	ofstream archivoIO;
	archivoI.open("Inventario.txt");
	archivoIO.open("temp.txt");
	while(getline(archivoI,linea)){
		if(linea!=productoC){
			archivoIO << linea << endl;
		}
		else{
			archivoIO << producto << endl;
		}
	}
	ultimoProductoModificado = producto;
	archivoI.close();
	archivoIO.close();
	remove("Inventario.txt");
	rename("temp.txt","Inventario.txt");
}
void actualizarProductosVendidos(string infoP){
	pnodo aux = productosVendidos.getPrimero();
	int cantidad = stoi(split(infoP).getPrimero()->getSiguiente()->getSiguiente()->getSiguiente()->getValor());
	while(aux!=NULL){
		if(split(aux->getValor()).getPrimero()->getSiguiente()->getValor()==split(infoP).getPrimero()->getSiguiente()->getValor()){
			infoP = split(infoP).getPrimero()->getValor() + ";" + split(infoP).getPrimero()->getSiguiente()->getValor() + ";" + split(infoP).getPrimero()->getSiguiente()->getSiguiente()->getValor() + ";" + to_string(cantidad+stoi(split(infoP).getPrimero()->getSiguiente()->getSiguiente()->getSiguiente()->getValor()));
			aux->setValor(infoP);
			return;
		}
		aux = aux->getSiguiente();
	}
	productosVendidos.InsertarFinal(infoP);
}
void actualizarProductosPorSuper(){
	while(productosMenosVendidosPorSuper.getPrimero()!=NULL){
		productosMenosVendidosPorSuper.BorrarInicio();
	}
	string codigoSuper;
	string codigoSuperAux;
	string cantidadP;
	string cantidadPAux;
	pnodo aux;
	pnodo aux2;
	bool cambio=false;
	aux = productosVendidos.getPrimero();
	while(aux!=NULL){
		codigoSuper = split(aux->getValor()).getPrimero()->getSiguiente()->getSiguiente()->getValor();
		cantidadP = split(aux->getValor()).getPrimero()->getSiguiente()->getSiguiente()->getSiguiente()->getValor();
		aux2 = productosMenosVendidosPorSuper.getPrimero();
		while(aux2!=NULL){
			codigoSuperAux = split(aux2->getValor()).getPrimero()->getSiguiente()->getSiguiente()->getValor();
			cantidadPAux = split(aux2->getValor()).getPrimero()->getSiguiente()->getSiguiente()->getSiguiente()->getValor();
			if(codigoSuper==codigoSuperAux && stoi(cantidadP)<stoi(cantidadPAux)){
				aux2->setValor(aux->getValor());
				cambio=true;
				break;
			}
			aux2 = aux2->getSiguiente();
		}
		if(!cambio){
			productosMenosVendidosPorSuper.InsertarFinal(aux->getValor());
		}
		else{
			cambio = false;
		}
		aux = aux->getSiguiente();
	}
}
void actualizarComprasCliente(string nombre, string cedula, int cantidad){
	pnodo aux = comprasPorCliente.getPrimero();
	while(aux!=NULL){
		string cantidadActual = split(aux->getValor()).getPrimero()->getSiguiente()->getSiguiente()->getValor();
		if(split(aux->getValor()).getPrimero()->getSiguiente()->getValor()==cedula){
			aux->setValor(nombre+";"+cedula+";"+to_string(stoi(cantidadActual)+cantidad));
			return;
		}
		aux = aux->getSiguiente();
	}
	comprasPorCliente.InsertarFinal(nombre+";"+cedula+";"+to_string(cantidad));
}
void agregarVisitaSuper(string codigoSuper){
	pnodo aux = visitasSuper.getPrimero();
	while(aux!=NULL){
		if(split(aux->getValor()).getPrimero()->getValor()==codigoSuper){
			aux->setValor(codigoSuper+";"+to_string(stoi(split(aux->getValor()).getPrimero()->getSiguiente()->getValor())+1));
			return;
		}
		aux = aux->getSiguiente();
	}
	visitasSuper.InsertarFinal(codigoSuper+";"+"1");
}
void agregarTrabajoAdmin(string cedula){
	pnodo aux = trabajoAdministradores.getPrimero();
	while(aux!=NULL){
		if(split(aux->getValor()).getPrimero()->getValor()==cedula){
			aux->setValor(cedula+";"+to_string(stoi(split(aux->getValor()).getPrimero()->getSiguiente()->getValor())+1));
			return;
		}
		aux = aux->getSiguiente();
	}
	trabajoAdministradores.InsertarFinal(cedula+";"+"1");
}
void facturizar(string cedula, int descuento){
	pnodo aux;
	string telefono;
	string nombre;
	string super;
	string producto;
	string nombreP;
	int cantidad;
	float precioT;
	float precioU;
	float precioTT;
	ofstream factura;
	consecutivos++;
	if(descuento==5){
		aux = listaU0.getPrimero();
	}
	else{
		aux = listaU3.getPrimero();
	}
	while(split(aux->getValor()).getPrimero()->getSiguiente()->getValor()!=cedula){
		aux = aux->getSiguiente();
	}
	super=superCarrito;
	nombre = split(aux->getValor()).getPrimero()->getSiguiente()->getSiguiente()->getValor();
	telefono = split(aux->getValor()).getPrimero()->getSiguiente()->getSiguiente()->getSiguiente()->getValor();
	factura.open("Consecutivo"+to_string(consecutivos)+".txt");
	factura << "Cedula:\t\t" << cedula << endl;
	factura << "Nombre:\t\t" << nombre << endl;
	factura << "Telefono:\t" << telefono << endl;
	factura << "Codigo Super:\t" << super << endl;
	factura << "Producto\t" << "Cantidad\t" << "PrecioUnitario\t" << "PrecioTotalXProducto\t" << endl;
	while(carrito.getPrimero()!=NULL){
		aux = carrito.getPrimero();
		producto = consultarPrecio(split(aux->getValor()).getPrimero()->getValor());
		nombreP = split(producto).getPrimero()->getSiguiente()->getSiguiente()->getValor();
		precioU = stoi(split(producto).getPrimero()->getSiguiente()->getSiguiente()->getSiguiente()->getSiguiente()->getValor());
		cantidad = stoi(split(aux->getValor()).getPrimero()->getSiguiente()->getValor());
		precioT = cantidad*precioU;
		precioTT+=precioT;
		factura << nombreP+"\t\t" << to_string(cantidad)+"\t\t" << to_string((int)precioU)+"\t\t" << to_string((int)precioT)+"\t\t" << endl;
		actualizarProductosVendidos(nombreP+";"+split(producto).getPrimero()->getSiguiente()->getValor()+";"+super+";"+to_string(cantidad));
		actualizarComprasCliente(nombre,cedula,cantidad);
		carrito.BorrarInicio();
	}
	factura << "Total:\t\t" << to_string((int)precioTT) << endl;
	factura << "Descuento:\t" << to_string(descuento)+"%" << endl;
	factura << "Monto Final:\t" << to_string(precioTT-precioTT*((float)descuento/100)) << endl;
	factura.close();
}
/*--------------------Retorno de Informacion----------------------------*/
string getProducto(string producto){
	return consultarPrecio(producto);
}
/*--------------------------------------Menu----------------------------------------*/
void menu_cliente(string cedula, int descuento){
	string producto;
	string resultado;
	string super;
	pnodo aux;
	int cantidad;
	bool respuesta=false;
	cout << "------------MENU CLIENTE------------" << endl;
	cout << "1. Consultar Precio" << endl;
	cout << "2. Consultar Descuento" << endl;
	cout << "3. Consultar Productos" << endl;
	cout << "4. Comprar (Carrito)" << endl;
	cout << "5. Facturación" << endl;
	cout << "6. Salir" << endl;
	int opcion;
	cin >> opcion;
	switch(opcion){
		case 1:
			cout << "Ingrese el codigo del producto a buscar: " << endl;
			cin >> producto;
			resultado = consultarPrecio(producto);
			if(resultado!="No se encontro el producto"){
			resultado = "Nombre: "+split(resultado).getPrimero()->getSiguiente()->getSiguiente()->getValor()+"\nPrecio: "+split(resultado).getPrimero()->getSiguiente()->getSiguiente()->getSiguiente()->getSiguiente()->getValor();
			}
			cout << resultado << endl;
			return menu_cliente(cedula,descuento);	
		case 2:
			cout << "Su descuento es de: " << descuento <<"%" << endl;
			return menu_cliente(cedula,descuento);
		case 3:
			cout << "Indique el codigo del supermercado: " << endl;
			cin >> super;
			resultado = consultarSuper(super);
			cout << resultado << endl;
			return menu_cliente(cedula,descuento);
		case 4:
			if(superCarrito==""){
				cout << "Ingrese el codigo del supermercado: " << endl;
				cin >> super;	
				if(!verificarSupermercados(super)){
					cout << "El supermercado no existe" << endl;
					return menu_cliente(cedula,descuento);
				}
				superCarrito=super;
			}
			else{
				super=superCarrito;
			}
			cout << "Ingrese el codigo del producto a añadir al carrito: " << endl;
			cin >> producto;
			resultado = consultarPrecio(producto);
			if(resultado=="No se encontro el producto" || split(resultado).getPrimero()->getValor()!=super){
				cout << "No se encontro el producto, el codigo del producto es invalido o no se encuentra en el super" << endl;
				return menu_cliente(cedula,descuento);
			}
			else{
				cout << "Ingrese la cantidad a comprar: " << endl;
				cin >> cantidad;
				if(stoi(split(resultado).getPrimero()->getSiguiente()->getSiguiente()->getSiguiente()->getValor())<cantidad){
					cout << "No hay suficiente cantidad del producto" << endl;
					cantidad = stoi(split(resultado).getPrimero()->getSiguiente()->getSiguiente()->getSiguiente()->getValor());
					cout << "La cantidad disponible es " << cantidad << ", desea comprar esta cantidad? (y/n)" << endl;
					cin >> resultado;
					if(resultado=="y"){
						respuesta=true;
					}
					if(!respuesta){
					return menu_cliente(cedula,descuento);
					}
				}
				else{
					if(cantidad<=0){
						cout << "Ingrese una cantidad mayor a cero" << endl;
						return menu_cliente(cedula,descuento);
					}
					resultado = anadirAlCarrito(producto,cantidad);
					aux = carrito.getPrimero();
					while(aux!=NULL){
						if(split(aux->getValor()).getPrimero()->getValor()==split(resultado).getPrimero()->getValor()){
							resultado = split(aux->getValor()).getPrimero()->getValor() + ";" + to_string(stoi(split(aux->getValor()).getPrimero()->getSiguiente()->getValor())+stoi(split(resultado).getPrimero()->getSiguiente()->getValor()));
							aux->setValor(resultado);
							producto="Listo!";
						}
						aux = aux->getSiguiente();
					}
					if(producto!="Listo!"){
						carrito.InsertarFinal(resultado);
					}
					return menu_cliente(cedula,descuento);
				}
			}
			return menu_cliente(cedula,descuento);
		case 5:
			if(!carrito.ListaVacia()){
				facturizar(cedula,descuento);
				cout << "Se ha realizado la facturicacion exitosamente!" << endl;
				agregarVisitaSuper(superCarrito);
			}
			superCarrito="";
			return menu_cliente(cedula,descuento);
		case 6:
			if(superCarrito!=""){
				agregarVisitaSuper(superCarrito);
			}
			superCarrito="";
			while(carrito.getPrimero()!=NULL){
				devolverProducto(carrito.getPrimero()->getValor());
				carrito.BorrarInicio();
			}
			return;
		default:
			cout << "Opcion invalida" << endl;
			return menu_cliente(cedula,descuento);
	}
	
}
void menu_registro(string cedula){
	string ciudad;
	string nombre;
	string apellido;
	string telefono;
	string solicitud;
	cout << "Indique el codigo de ciudad: " << endl;
	cin >> ciudad;
	if(!verificarCiudades(ciudad)){
		cout << "Ciudad invalida" << endl;
	}
	else{
		if(verificarSolicitud(cedula)){
			cout << "La cedula ya esta en solicitud" << endl;
		}
		else{
			cout << "Indique su primer nombre: " << endl;
			cin >> nombre;
			cout << "Indique su apellido" << endl;
			cin >> apellido;
			cout << "Indique su telefono: " << endl;
			cin >> telefono;
			solicitud+=ciudad+";"+cedula+";"+nombre+" "+apellido + ";" +telefono+";"+"0";
			listaSolicitudes.InsertarFinal(solicitud);
		}
	}
}
void menu_clienteNoRegistradoAux(string cedula){
	string producto;
	string super;
	string resultado;
	cout << "------------MENU CLIENTE NO REGISTRADO------------" << endl;
	cout << "1. Consultar Precio" << endl;
	cout << "2. Consultar Descuento(deshabilitada)" << endl;
	cout << "3. Consultar Productos" << endl;
	cout << "4. Comprar (deshabilitada)" << endl;
	cout << "5. Facturación(deshabilitada)" << endl;
	cout << "6. Salir" << endl;
	int opcion;
	cin >> opcion;
	switch(opcion){
		case 1:
			cout << "Ingrese el codigo del producto a buscar: " << endl;
			cin >> producto;
			resultado = consultarPrecio(producto);
			if(resultado!="No se encontro el producto"){
			resultado = "Nombre: "+split(resultado).getPrimero()->getSiguiente()->getSiguiente()->getValor()+"\nPrecio: "+split(resultado).getPrimero()->getSiguiente()->getSiguiente()->getSiguiente()->getSiguiente()->getValor();
			}
			cout << resultado << endl;
			return menu_clienteNoRegistradoAux(cedula);	
			break;
		case 2:
			cout << "Opcion deshabilitada" << endl;
			return menu_clienteNoRegistradoAux(cedula);
			break;
		case 3:
			cout << "Indique el codigo del supermercado: " << endl;
			cin >> super;
			resultado = consultarSuper(super);
			cout << resultado << endl;
			return menu_clienteNoRegistradoAux(cedula);
			break;
		case 4:
			cout << "Opcion deshabilitada" << endl;
			return menu_clienteNoRegistradoAux(cedula);
			break;
		case 5:
			cout << "Opcion deshabilitada" << endl;
			return menu_clienteNoRegistradoAux(cedula);
			break;
		case 6:
			break;
		default:
			cout << "Opcion invalida" << endl;
			return menu_clienteNoRegistradoAux(cedula);
			break;
	}
}
void menu_clienteNoRegistrado(string cedula){
	int respuesta;
	cout << "No esta registrado, desea hacerlo?" << endl;
	cout << "1. Si" << endl;
	cout << "2. No" << endl;
	cin >> respuesta;
	switch(respuesta){
		case 1:
			menu_registro(cedula);
			return menu_clienteNoRegistradoAux(cedula);
		default:
			return menu_clienteNoRegistradoAux(cedula);
	}
}
void menu_reportes(string cedula){
	pnodo aux;
	string resultado;
	string nombre;
	string codigo;
	string cantidad;
	cout << "------------REPORTES------------" << endl;
	cout << "1. Ultimos dos productos ingresados al inventario" << endl;
	aux = ultimosProductosIngresados.getPrimero();
	if(aux!=NULL){
		while(aux!=NULL){
			nombre = split(aux->getValor()).getPrimero()->getSiguiente()->getSiguiente()->getValor();
			codigo = split(aux->getValor()).getPrimero()->getValor();
			cout << "Nombre: " << nombre << endl;
			cout << "Codigo Super: " << codigo << endl;
			aux = aux->getSiguiente();
		}
	}
	else{
		cout << "No se ha insertado ningun producto" << endl;
	}
	cout << "2. Ultimo Producto Modificado" << endl;
	
	if(ultimoProductoModificado!=""){
		nombre = split(ultimoProductoModificado).getPrimero()->getSiguiente()->getSiguiente()->getValor();
		codigo = split(ultimoProductoModificado).getPrimero()->getSiguiente()->getValor();
		cout << "Nombre: " << nombre << endl;
		cout << "Codigo: " << codigo << endl;
	}
	else{
		cout << "No se ha modificado un producto" << endl;
	}
	cout << "3. Ultimo Producto Eliminado" << endl;
	if(ultimoProductoEliminado!=""){
		nombre = split(ultimoProductoEliminado).getPrimero()->getSiguiente()->getSiguiente()->getValor();
		cout << nombre << endl;
	}
	else{
		cout << "No se ha eliminado un producto" << endl;
	}
	cout << "4. Producto mas vendido" << endl;
	aux = productosVendidos.getPrimero();
	if(aux!=NULL){
		while(aux!=NULL){
			if(productoMasVendido==""){
				productoMasVendido=aux->getValor();
			}
			else{
				string cantidadPActual = split(productoMasVendido).getPrimero()->getSiguiente()->getSiguiente()->getSiguiente()->getValor();
				cantidad = split(aux->getValor()).getPrimero()->getSiguiente()->getSiguiente()->getSiguiente()->getValor();
				if(cantidadPActual<cantidad){
					productoMasVendido = aux->getValor();
				}
			}
			aux = aux->getSiguiente();
		}
		nombre = split(productoMasVendido).getPrimero()->getValor();
		cantidad = split(productoMasVendido).getPrimero()->getSiguiente()->getSiguiente()->getSiguiente()->getValor();
		cout << "Nombre: " << nombre << endl;
		cout << "Cantidad: " << cantidad << endl;
	}
	else{
		cout << "No se ha vendido ningun producto" << endl;
	}
	cout << "5. Producto menos vendido por super" << endl;
	aux = productosVendidos.getPrimero();
	if(aux!=NULL){
		actualizarProductosPorSuper();
		aux = productosMenosVendidosPorSuper.getPrimero();
		while(aux!=NULL){
		nombre = split(aux->getValor()).getPrimero()->getValor();
		codigo = split(aux->getValor()).getPrimero()->getSiguiente()->getSiguiente()->getValor();
		cantidad = split(aux->getValor()).getPrimero()->getSiguiente()->getSiguiente()->getSiguiente()->getValor();
		cout << "Nombre: " << nombre << "\t";
		cout << "Super: " << codigo << "\t";
		cout << "Cantidad: " << cantidad << endl;
		aux = aux->getSiguiente();
		}
	}
	else{
		cout << "No se ha vendido ningun producto" << endl;
	}
	cout << "6. Cliente que mas compro" << endl;
	aux = comprasPorCliente.getPrimero();
	while(aux!=NULL){
		if(clienteMasCompras!=""){
			if(stoi(split(aux->getValor()).getPrimero()->getSiguiente()->getSiguiente()->getValor())>stoi(split(clienteMasCompras).getPrimero()->getSiguiente()->getSiguiente()->getValor())){
				clienteMasCompras=aux->getValor();
			}
		}
		else{
			clienteMasCompras=aux->getValor();
		}
		aux = aux->getSiguiente();
	}
	if(clienteMasCompras==""){
		cout << "No se ha vendido ningun producto" << endl;
	}
	else{
		nombre = split(clienteMasCompras).getPrimero()->getValor();
		codigo = split(clienteMasCompras).getPrimero()->getSiguiente()->getValor();
		cantidad = split(clienteMasCompras).getPrimero()->getSiguiente()->getSiguiente()->getValor();
		cout << "Nombre: " << nombre << endl;
		cout << "Cedula: " << codigo << endl;
		cout << "Cantidad: " << cantidad << endl;
	}
	cout << "7. Cliente que menos compro" << endl;
	aux = comprasPorCliente.getPrimero();
	while(aux!=NULL){
		if(clienteMenosCompras!=""){
			if(stoi(split(aux->getValor()).getPrimero()->getSiguiente()->getSiguiente()->getValor())<stoi(split(clienteMenosCompras).getPrimero()->getSiguiente()->getSiguiente()->getValor())){
				clienteMenosCompras=aux->getValor();
			}
		}
		else{
			clienteMenosCompras=aux->getValor();
		}
		aux = aux->getSiguiente();
	}
	if(clienteMenosCompras==""){
		cout << "No se ha vendido ningun producto" << endl;
	}
	else{
		nombre = split(clienteMenosCompras).getPrimero()->getValor();
		codigo = split(clienteMenosCompras).getPrimero()->getSiguiente()->getValor();
		cantidad = split(clienteMenosCompras).getPrimero()->getSiguiente()->getSiguiente()->getValor();
		cout << "Nombre: " << nombre << endl;
		cout << "Cedula: " << codigo << endl;
		cout << "Cantidad: " << cantidad << endl;
	}
	cout << "8. Cantidad de compras por cliente" << endl;
	aux = comprasPorCliente.getPrimero();
	if(aux!=NULL){
		while(aux!=NULL){
		nombre = split(aux->getValor()).getPrimero()->getValor();
		codigo = split(aux->getValor()).getPrimero()->getSiguiente()->getValor();
		cantidad = split(aux->getValor()).getPrimero()->getSiguiente()->getSiguiente()->getValor();
		cout << "Nombre: " << nombre << "\t";
		cout << "Cedula: " << codigo << "\t";
		cout << "Cantidad: " << cantidad << endl;
		aux = aux->getSiguiente();
		}
	}
	else{
		cout << "No se ha realizado ninguna compra" << endl;
	}
	cout << "9. Super mas visitado" << endl;
	superMasVisitado="";
	aux = visitasSuper.getPrimero();
	if(aux!=NULL){
		while(aux!=NULL){
			cantidad = split(aux->getValor()).getPrimero()->getSiguiente()->getValor();
			if(superMasVisitado!=""){
				if(stoi(cantidad)>stoi(split(superMasVisitado).getPrimero()->getSiguiente()->getValor())){
					superMasVisitado=aux->getValor();
				}
			}
			else{
				superMasVisitado=aux->getValor();
			}
			aux = aux->getSiguiente();
		}
		codigo = split(superMasVisitado).getPrimero()->getValor();
		cantidad = split(superMasVisitado).getPrimero()->getSiguiente()->getValor();
		cout << "Codigo del super: " << codigo << endl;
		cout << "Cantidad de visitas: " << cantidad << endl;
	}
	else{
		cout << "No se ha visitado ningun super" << endl;
	}
	cout << "10. Super menos visitado" << endl;
	superMenosVisitado="";
	aux = visitasSuper.getPrimero();
	if(aux!=NULL){
		while(aux!=NULL){
			cantidad = split(aux->getValor()).getPrimero()->getSiguiente()->getValor();
			if(superMenosVisitado!=""){
				if(stoi(cantidad)<stoi(split(superMenosVisitado).getPrimero()->getSiguiente()->getValor())){
					superMenosVisitado=aux->getValor();
				}
			}
			else{
				superMenosVisitado=aux->getValor();
			}
			aux = aux->getSiguiente();
		}
		codigo = split(superMenosVisitado).getPrimero()->getValor();
		cantidad = split(superMenosVisitado).getPrimero()->getSiguiente()->getValor();
		cout << "Codigo del super: " << codigo << endl;
		cout << "Cantidad de visitas: " << cantidad << endl;
	}
	else{
		cout << "No se ha visitado ningun super" << endl;
	}
	cout << "11. Administrador que mas trabajo" << endl;
	aux = trabajoAdministradores.getPrimero();
	if(aux!=NULL){
		while(aux!=NULL){
			cantidad = split(aux->getValor()).getPrimero()->getSiguiente()->getValor();
			if(administradorMasTrabajo!=""){
				if(stoi(cantidad)>stoi(split(administradorMasTrabajo).getPrimero()->getSiguiente()->getValor())){
					administradorMasTrabajo=aux->getValor();
				}
			}
			else{
				administradorMasTrabajo=aux->getValor();
			}
			aux = aux->getSiguiente();
		}
		codigo = split(administradorMasTrabajo).getPrimero()->getValor();
		cantidad = split(administradorMasTrabajo).getPrimero()->getSiguiente()->getValor();
		cout << "Administrador: " << codigo << endl;
		cout << "Cantidad de Trabajo: " << cantidad << endl;
	}
	else{
		cout << "Ningun administrador a trabajado" << endl;
	}
	cout << "12. Administradores que no trabajaron" << endl;
	aux = listaU1.getPrimero();
	bool comparar = false;
	while(aux!=NULL){
		codigo = split(aux->getValor()).getPrimero()->getSiguiente()->getValor();
		pnodo aux2 = trabajoAdministradores.getPrimero();
		while(aux2!=NULL){
			if(codigo==split(aux2->getValor()).getPrimero()->getValor()){
				comparar=true;
				break;
			}
			aux2 = aux2->getSiguiente();
		}
		if(!comparar){
			cout << "El administrador con cedula " << codigo << " no trabajo." << endl;
		}
		comparar = false;
		aux = aux->getSiguiente();
	}
	
}
void menu_admin(string cedula){
	string producto;
	string resultado;
	string super;
	cout << "------------MENU ADMINISTRADOR------------" << endl;
	cout << "1. Insertar Producto" << endl;
	cout << "2. Eliminar Producto" << endl;
	cout << "3. Modificar Producto" << endl;
	cout << "4. Consultar Precio" << endl;
	cout << "5. Consultar Descuentos" << endl;
	cout << "6. Consultar Productos de un Super" << endl;
	cout << "7. Registrar Clientes" << endl;
	cout << "8. Reportes" << endl;
	cout << "9. Salir" << endl;
	int opcion;
	cin >> opcion;
	switch(opcion){
		case 1:
			insertarProducto();
			agregarTrabajoAdmin(cedula);
			return menu_admin(cedula);
		case 2:
			cout << "Ingrese el codigo del producto a eliminar: " << endl;
			cin >> producto;
			if(!verificarProducto(producto)){
				cout << "No se encontro el producto" << endl;
				return menu_admin(cedula);
			}
			eliminarProducto(producto);
			agregarTrabajoAdmin(cedula);
			return menu_admin(cedula);
		case 3:
			cout << "Ingrese el codigo del producto a modificar: " << endl;
			cin >> producto;
			if(!verificarProducto(producto)){
				cout << "No se encontro el producto" << endl;
				return menu_admin(cedula);
			}
			modificarProducto(producto);
			agregarTrabajoAdmin(cedula);
			return menu_admin(cedula);
		case 4:
			cout << "Ingrese el codigo del producto a buscar: " << endl;
			cin >> producto;
			resultado = consultarPrecio(producto);
			if(resultado!="No se encontro el producto"){
			resultado = "Nombre: "+split(resultado).getPrimero()->getSiguiente()->getSiguiente()->getValor()+"\nPrecio: "+split(resultado).getPrimero()->getSiguiente()->getSiguiente()->getSiguiente()->getSiguiente()->getValor();
			}
			cout << resultado << endl;
			return menu_admin(cedula);
		case 5:
			cout << "5% para clientes" << endl;
			cout << "10% para clientes-funcionarios" << endl;
			return menu_admin(cedula);
		case 6:
			cout << "Indique el codigo del supermercado: " << endl;
			cin >> super;
			resultado = consultarSuper(super);
			cout << resultado << endl;
			return menu_admin(cedula);
		case 7:
			if(listaSolicitudes.ListaVacia()){
				return menu_admin(cedula);
			}
			cout << "Clientes registrados: " << endl;
			listaSolicitudes.Mostrar();
			while(!listaSolicitudes.ListaVacia()){
				listaU0.InsertarFinal(listaSolicitudes.getPrimero()->getValor());
				listaSolicitudes.BorrarInicio();
			}
			agregarTrabajoAdmin(cedula);
			return menu_admin(cedula);
		case 8:
			menu_reportes(cedula);
			return menu_admin(cedula);
		case 9:
			break;
		default:
			cout << "Opcion invalida" << endl;
			return menu_admin(cedula);
	}
}
void menu_vendedor(string cedula){
	string producto;
	string super;
	string resultado;
	cout << "------------MENU VENDEDOR------------" << endl;
	cout << "1. Consultar Precio" << endl;
	cout << "2. Consultar Descuento de un cliente" << endl;
	cout << "3. Consultar Productos de un Super" << endl;
	cout << "4. Salir" << endl;
	int opcion;
	cin >> opcion;
	switch(opcion){
		case 1:
			cout << "Ingrese el codigo del producto a buscar: " << endl;
			cin >> producto;
			resultado = consultarPrecio(producto);
			if(resultado!="No se encontro el producto"){
			resultado = "Nombre: "+split(resultado).getPrimero()->getSiguiente()->getSiguiente()->getValor()+"\nPrecio: "+split(resultado).getPrimero()->getSiguiente()->getSiguiente()->getSiguiente()->getSiguiente()->getValor();
			}
			cout << resultado << endl;
			return menu_vendedor(cedula);
		case 2:
			cout << "5% para clientes" << endl;
			cout << "10% para clientes-funcionarios" << endl;
			return menu_vendedor(cedula);
		case 3:
			cout << "Indique el codigo del supermercado: " << endl;
			cin >> super;
			resultado = consultarSuper(super);
			cout << resultado << endl;
			return menu_vendedor(cedula);
		case 4:
			break;
		default:
			cout << "Opcion invalida" << endl;
			return menu_vendedor(cedula);
	}
}
void menu(){
	cout << "Bienvenido" << endl;
	cout << "Indique su cedula: " << endl;
	string cedula;
	cin >> cedula;
	if(cedula=="Salir"){
		return;
	}
	cout << "Indique el tipo de usuario (0,1,2,3): " << endl;
	int usuario;
	cin >> usuario;
	if(!verificarUsuarios(cedula) && usuario==0){
		usuario = 4;
	}
	else{
		if(!verificarUsuarios(cedula)){
			usuario = 5;
		}
		if(!verificarTipo(cedula,usuario)){
			usuario = 5;
		}
	}
	
	switch(usuario){
		case 0:
			menu_cliente(cedula,5);
			return menu();
		case 1:
			menu_admin(cedula);
			return menu();
		case 2:
			menu_vendedor(cedula);
			return menu();
		case 3:
			menu_cliente(cedula,10);
			return menu();
		case 4:
			menu_clienteNoRegistrado(cedula);
			return menu();
		default:
			cout << "Cedula o tipo de usuario incorrecto/invalido" << endl;
			return menu();
	}
}

int main(){
	listaCliente.InsertarFinal("0");
	listaCliente.InsertarFinal("1");
	listaCliente.InsertarFinal("2");
	listaCliente.InsertarFinal("3");
	archivoC.open("Ciudad.txt");
	if(archivoC.fail()){
		cout <<"Archivo de ciudades no encontrado" << endl;
	}
	archivoI.open("Inventario.txt");
	if(archivoI.fail()){
		cout <<"Archivo de inventario no encontrado" << endl;
	}
	archivoS.open("supermercado.txt");
	if(archivoS.fail()){
		cout <<"Archivo de supermercado no encontrado" << endl;
	}
	archivoU.open("Usuarios.txt");
	if(archivoU.fail()){
		cout <<"Archivo de usuarios no encontrado" << endl;
	}

	string informacion;
	while(getline(archivoC, informacion)){
		string codigo = split(informacion).getPrimero()->getValor();
		bool resultado = verificarCiudades(codigo);
		if(!resultado){
			listaCiudades.InsertarFinal(informacion);
		}
	}
	while(getline(archivoS, informacion)){
		string codigoC = split(informacion).getPrimero()->getValor();
		string codigo = split(informacion).getPrimero()->getSiguiente()->getValor();
		bool resultado = verificarCiudades(codigoC);
		bool resultadoS = verificarSupermercados(codigo);
		if(resultado && !resultadoS){
			listaSuper.InsertarFinal(informacion);
		}
	}
	while(getline(archivoI, informacion)){
		string codigo = split(informacion).getPrimero()->getValor();
		string codigoP = split(informacion).getPrimero()->getSiguiente()->getValor();
		bool resultado = verificarSupermercados(codigo);
		bool resultadoP = verificarProducto(codigoP);
		if(resultado && !resultadoP){
			listaInventario.InsertarFinal(informacion);
			
		}
	}
	while(getline(archivoU,informacion)){
		bool resultadoC;
		bool resultadoU;
		string codigoC=split(informacion).getPrimero()->getValor();
		string codigoU=split(informacion).getPrimero()->getSiguiente()->getValor();
		string codigoTipo=split(informacion).getPrimero()->getSiguiente()->getSiguiente()->getSiguiente()->getSiguiente()->getValor();
		resultadoC=verificarCiudades(codigoC);
		resultadoU=verificarUsuarios(codigoU);
		if(resultadoC && !resultadoU){
			if(codigoTipo=="0"){
				listaU0.InsertarFinal(informacion);
			}
			if(codigoTipo=="1"){
				listaU1.InsertarFinal(informacion);
			}
			if(codigoTipo=="2"){
				listaU2.InsertarFinal(informacion);
			}
			if(codigoTipo=="3"){
				listaU3.InsertarFinal(informacion);
			}
		}
	}
	archivoC.close();
	archivoI.close();
	archivoS.close();
	archivoU.close();
	string probarConsecutivos = "Consecutivo1.txt";
	while(verificarExistenciaArchivo(probarConsecutivos)){
		consecutivos++;
		probarConsecutivos = "Consecutivo" + to_string(consecutivos+1) + ".txt";
	}
	listaCliente.getPrimero()->getSiguiente()->setAbajo(listaU0.getPrimero());
	listaCliente.getPrimero()->getSiguiente()->getSiguiente()->setAbajo(listaU1.getPrimero());
	listaCliente.getPrimero()->getSiguiente()->getSiguiente()->getSiguiente()->setAbajo(listaU2.getPrimero());
	listaCliente.getPrimero()->getSiguiente()->getSiguiente()->getSiguiente()->getSiguiente()->setAbajo(listaU3.getPrimero());
	menu();
	cout << "--------Lista de Ciudades--------" << endl;
	listaCiudades.Mostrar();
	cout << "--------Lista de Supermercados--------" << endl;
	listaSuper.Mostrar();
	cout << "--------Lista de Productos--------" << endl;
	listaInventario.Mostrar();
	cout << "--------Lista de Clientes--------" << endl;
	listaCliente.Mostrar();
	cout << "--------Lista de Solicitudes--------" << endl;
	listaSolicitudes.Mostrar();
	cin.get();
	return 0;
}
