
#include <iostream>
using namespace std;

class nodoDC {
   public:
    nodoDC(string v)
    {
       valor = v;
       siguiente = NULL;
       anterior =NULL;
    }
    string getValor(){
    	return valor;
	}
	nodoDC * getSiguiente(){
		return siguiente;
	}
	nodoDC * getAnterior(){
		return anterior;
	}
	void setValor(string v){
		valor = v;
	}
   nodoDC(string v, nodoDC * signodo)
    {
       valor = v;
       siguiente = signodo;
    }

 private:
    string valor;
    nodoDC *siguiente;
    nodoDC *anterior;
    
        
   friend class listaDC;
};
typedef nodoDC *pnodoDC;

class listaDC {
   public:
    listaDC() { primero = actual = NULL; }
    ~listaDC();
    
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
    pnodoDC getPrimero(){
    	return primero;
	}
	pnodoDC getActual(){
		return actual;
	}
    int largoLista();
    
   private:
    pnodoDC primero;
    pnodoDC actual;
};

listaDC::~listaDC()
{
   pnodoDC aux;
   
   while(primero) {
      aux = primero;
      primero = primero->siguiente;
      primero->anterior=aux->anterior;
      aux->anterior->siguiente=primero;
      delete aux;
   }
   actual = NULL;
}
bool listaDC::verificarActualConPrimero(){
	return actual==primero;
}
int listaDC::largoLista()
{
    int cont=0;

    pnodoDC aux = primero;
    if(ListaVacia())
    {
        return cont;
    }
    else
    {
    	cont++;
    	aux = aux->siguiente;
        while(aux!=primero)
        {
          aux=aux->siguiente;
          cont++;
        }
    return cont;
    }
    
}

void listaDC::InsertarInicio(string v)
{
  
   if (ListaVacia())
   {
     primero = new nodoDC(v);
     primero->anterior=primero;
     primero->siguiente=primero;
   }  
   else
   {
     pnodoDC nuevo=new nodoDC (v);
     nuevo->siguiente=primero;
     nuevo->anterior= primero->anterior;
     primero->anterior->siguiente=nuevo;
     nuevo->siguiente->anterior=nuevo;
     primero= nuevo;
   }
}
 
void listaDC::InsertarFinal(string v)
{
   if (ListaVacia())
     {
     primero = new nodoDC(v);
     primero->anterior=primero;
     primero->siguiente=primero;
   }  
   else
   { 
     pnodoDC nuevo = new nodoDC(v);
     nuevo->anterior = primero->anterior;
     nuevo->siguiente=primero->anterior->siguiente;
     primero->anterior->siguiente=nuevo;
     primero->anterior=nuevo;
    }    
}


void listaDC::InsertarPos(string v,int pos)
{
   if (ListaVacia())
   {
     primero = new nodoDC(v);
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
             pnodoDC aux= primero;
             int i =2;
             while((i != pos )&&(aux->siguiente!= primero))
             {
                   i++;
                   aux=aux->siguiente;
             }
             pnodoDC nuevo= new nodoDC(v);
             nuevo->siguiente=aux->siguiente;
             aux->siguiente=nuevo;
             aux->siguiente->anterior=aux;
             nuevo->siguiente->anterior=nuevo;                           
        }
       }
   }
}   

void listaDC::BorrarFinal()
{
    if (ListaVacia())
      cout << "No hay elementos en la lista:" << endl;
    else
    {
      if (primero->siguiente == primero)
      {
        pnodoDC temp= primero;
        primero= NULL;
        delete temp;
      }
      else 
      {
         pnodoDC aux = primero;
         while (aux->siguiente->siguiente != primero)
              aux = aux->siguiente;
         pnodoDC temp = aux->siguiente;
         aux->siguiente= primero;
         primero->anterior=aux;
         delete temp;
      }
    }
}

void listaDC::BorrarInicio()
{
    if (ListaVacia())
      cout << "No hay elementos en la lista:" << endl;
    else
    {
     if (primero->siguiente == primero)
     {
        pnodoDC temp= primero;
        primero= NULL;
        delete temp;
     }
     else
     {
        pnodoDC aux = primero->anterior;
        pnodoDC temp= primero;
        aux->siguiente=primero->siguiente;
        primero=primero->siguiente; 
        primero->anterior=aux;
        delete temp;
      }
    }
}

void listaDC:: borrarPosicion(int pos)
{
    
  if(ListaVacia())
    cout << "Lista vacia" <<endl;
  else
  {
   if((pos>largoLista())||(pos<0)){
   		pos = largoLista();
   		cout << pos << endl;
        cout << "Error en posicion" << endl;
    }
   else
   {
      if(pos==1)
        BorrarInicio();
      else
      {
       int cont=2;
       pnodoDC aux=  primero;
       while(cont<pos)
       {
         aux=aux->siguiente;
         cont++;
       }
       pnodoDC temp = aux->siguiente;
       aux->siguiente=aux->siguiente->siguiente;
       delete temp;
     }
    }
  }
}

void listaDC::Mostrar()
{
   pnodoDC aux=primero;
   while(aux->siguiente!=primero)
     {
                                
      cout << aux->valor << "-> ";
      aux = aux->siguiente;
     }
     cout<<aux->valor<<"->";
     cout<<endl;
}   



