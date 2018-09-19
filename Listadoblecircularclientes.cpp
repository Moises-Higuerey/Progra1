#include <iostream>

using namespace std;

class nodoDCC {
   public:
    nodoDCC(string v)
    {
       valor = v;
       siguiente = NULL;
       anterior =NULL;
       abajo = NULL;
    }
    string getValor(){
    	return valor;
	}
	nodoDCC * getSiguiente(){
		return siguiente;
	}
	nodoDCC * getAnterior(){
		return anterior;
	}
	pnodo getAbajo(){
		return abajo;
	}
	void setAbajo(pnodo nuevo){
		if(abajo==NULL){
			abajo = nuevo;
		}
		else{
			pnodo aux = abajo->getSiguiente();
			while(aux->getSiguiente()!=NULL){
				aux=aux->getSiguiente();
			}
			aux->setSiguiente(nuevo);
		}
	}
	nodoDCC(string v, nodoDCC * signodo){
       valor = v;
       siguiente = signodo;
    }

 private:
    string valor;
    nodoDCC *siguiente;
    nodoDCC *anterior;
    pnodo abajo;
        
   friend class listaDCC;
};
typedef nodoDCC *pnodoDCC;

class listaDCC {
   public:
    listaDCC() { primero = actual = NULL; }
    ~listaDCC();
    
    void InsertarInicio(string v);
    void InsertarFinal(string v);
    void InsertarPos (string v, int pos);
    void EliminarInicio();
    void EliminarFinal();
    void EliminarPos(int pos);
    bool ListaVacia() { return primero == NULL; } 
    void Imprimir();
    void Borrar(int v);
    void Mostrar();
    void Siguiente();
    void Primero();
    void Ultimo();
    void BorrarFinal();
    void BorrarInicio();
    void borrarPosicion(int pos);
    bool verificarActualConPrimero();
    pnodoDCC getPrimero(){
    	return primero;
	}
	pnodoDCC getActual(){
		return actual;
	}
    int largoLista();
    
   private:
    pnodoDCC primero;
    pnodoDCC actual;
};

listaDCC::~listaDCC()
{
   pnodoDCC aux;
   
   while(primero) {
      aux = primero;
      primero = primero->siguiente;
      primero->anterior=aux->anterior;
      aux->anterior->siguiente=primero;
      delete aux;
   }
   actual = NULL;
}
bool listaDCC::verificarActualConPrimero(){
	return actual==primero;
}
int listaDCC::largoLista()
{
    int cont=0;

    pnodoDCC aux = primero;
    if(ListaVacia())
    {
        return cont;
    }
    else
    {
        while(aux!=primero)
        {
          aux=aux->siguiente;
          cont++;
        }
    return cont;
    }
    
}

void listaDCC::InsertarInicio(string v)
{
  
   if (ListaVacia())
   {
     primero = new nodoDCC(v);
     primero->anterior=primero;
     primero->siguiente=primero;
   }  
   else
   {
     pnodoDCC nuevo=new nodoDCC (v);
     nuevo->siguiente=primero;
     nuevo->anterior= primero->anterior;
     primero->anterior->siguiente=nuevo;
     nuevo->siguiente->anterior=nuevo;
     primero= nuevo;
   }
}
 
void listaDCC::InsertarFinal(string v)
{
   if (ListaVacia())
     {
     primero = new nodoDCC(v);
     primero->anterior=primero;
     primero->siguiente=primero;
   }  
   else
   { 
     pnodoDCC nuevo = new nodoDCC(v);
     nuevo->anterior = primero->anterior;
     nuevo->siguiente=primero->anterior->siguiente;
     primero->anterior->siguiente=nuevo;
     primero->anterior=nuevo;
    }    
}


void listaDCC::InsertarPos(string v,int pos)
{
   if (ListaVacia())
   {
     primero = new nodoDCC(v);
     primero->anterior=primero;
     primero->siguiente=primero;
   } 
   else
   {
      if(pos <=1)
        InsertarInicio(v);    
       else
       {
        if (pos==largoLista())
          InsertarFinal(v);
        else
        {     
             pnodoDCC aux= primero;
             int i =2;
             while((i != pos )&&(aux->siguiente!= primero))
             {
                   i++;
                   aux=aux->siguiente;
             }
             pnodoDCC nuevo= new nodoDCC(v);
             nuevo->siguiente=aux->siguiente;
             aux->siguiente=nuevo;
             aux->siguiente->anterior=aux;
             nuevo->siguiente->anterior=nuevo;                           
        }
       }
   }
}   

void listaDCC::BorrarFinal()
{
    if (ListaVacia())
      cout << "No hay elementos en la lista:" << endl;
    else
    {
      if (primero->siguiente == primero)
      {
        pnodoDCC temp= primero;
        primero= NULL;
        delete temp;
      }
      else 
      {
         pnodoDCC aux = primero;
         while (aux->siguiente->siguiente != primero)
              aux = aux->siguiente;
         pnodoDCC temp = aux->siguiente;
         aux->siguiente= primero;
         primero->anterior=aux;
         delete temp;
      }
    }
}

void listaDCC::BorrarInicio()
{
    if (ListaVacia())
      cout << "No hay elementos en la lista:" << endl;
    else
    {
     if (primero->siguiente == primero)
     {
        pnodoDCC temp= primero;
        primero= NULL;
        delete temp;
     }
     else
     {
        pnodoDCC aux = primero->anterior;
        pnodoDCC temp= primero;
        aux->siguiente=primero->siguiente;
        primero=primero->siguiente; 
        primero->anterior=aux;
        delete temp;
      }
    }
}

void listaDCC:: borrarPosicion(int pos)
{
    
  if(ListaVacia())
    cout << "Lista vacia" <<endl;
  else
  {
   if((pos>largoLista())||(pos<0))
        cout << "Error en posicion" << endl;
   else
   {
      if(pos==1)
        BorrarInicio();
      else
      {
       int cont=2;
       pnodoDCC aux=  primero;
       while(cont<pos)
       {
         aux=aux->siguiente;
         cont++;
       }
       pnodoDCC temp = aux->siguiente;
       aux->siguiente=aux->siguiente->siguiente;
       delete temp;
     }
    }
  }
}

void listaDCC::Mostrar()
{
   pnodoDCC aux=primero;
   	while(aux->siguiente!=primero){                            
      	cout << aux->valor << "-> ";
      	pnodo aux2 = aux->getAbajo();
      	while(aux2!=NULL){
	      	cout << aux2->getValor() << "-> ";
	      	aux2 = aux2->getSiguiente();
	  	}
	  	cout<<endl;
      	aux = aux->siguiente;
    }
    cout<<aux->valor<<"-> ";
    	pnodo aux2 = aux->getAbajo();
    	while(aux2!=NULL){
      		cout << aux2->getValor() << "-> ";
      		aux2 = aux2->getSiguiente();
	  }
    cout<<endl;
}   



