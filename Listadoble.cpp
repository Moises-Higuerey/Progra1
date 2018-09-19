
#include <iostream>
using namespace std;

class nodoD {
   public:
    nodoD(string v)
    {
       valor = v;
       siguiente = NULL;
       anterior =NULL;
    }
    string getValor(){
    	return valor;
	}
	nodoD * getSiguiente(){
		return siguiente;
	}	
	nodoD * getAnterior(){
		return anterior;
	}
nodoD(string v, nodoD * signodoD)
    {
       valor = v;
       siguiente = signodoD;
    }

   private:
    string valor;
    nodoD *siguiente;
    nodoD *anterior;
    
        
   friend class listaD;
};

typedef nodoD *pnodoD;

class listaD {
   public:
    listaD() { primero = actual = NULL; }
    ~listaD();
    
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
    pnodoD getPrimero(){
    	return primero;
	}
    int largoLista();
    
   private:
    pnodoD primero;
    pnodoD actual;
};

listaD::~listaD()
{
   pnodoD aux;
   
   while(primero) {
      aux = primero;
      primero = primero->siguiente;
      delete aux;
   }
   actual = NULL;
}

int listaD::largoLista(){
    int cont=0;

    pnodoD aux;
    aux = primero;
    if(ListaVacia()){
        return cont;
    }else{
        while(aux!=NULL){
        aux=aux->siguiente;
        cont++;
    }
    return cont;
    }
    
}

void listaD::InsertarInicio(string v)
{
   if (ListaVacia())
     primero = new nodoD(v);
   else
   {
     primero=new nodoD (v,primero);
     primero->siguiente->anterior=primero;
   }
}
 
void listaD::InsertarFinal(string v)
{
   if (ListaVacia())
     primero = new nodoD(v);
   else
     { pnodoD aux = primero;
        while ( aux->siguiente != NULL)
          aux= aux->siguiente;
        aux->siguiente=new nodoD(v);
        aux->siguiente->anterior=aux;       
      }    
}


void listaD::InsertarPos(string v,int pos)
{
   if (ListaVacia())
     primero = new nodoD(v);
   else{
        if(pos <=1)
          InsertarInicio(v);    
        else
        {
             pnodoD aux= primero;
             int i =2;
             while((i != pos )&&(aux->siguiente!= NULL)){
                   i++;
                   aux=aux->siguiente;
             }
             pnodoD nuevo= new nodoD(v);
             nuevo->siguiente=aux->siguiente;
             aux->siguiente=nuevo;
             aux->siguiente->anterior=aux;
             nuevo->siguiente->anterior=nuevo;                           
        }
        }
}
      
void listaD::BorrarFinal()
{
    if (ListaVacia()){
     cout << "No hay elementos en la lista:" << endl;
    
   }else{
        if (primero->siguiente == NULL) {
                primero= NULL;
            } else {

                pnodoD aux = primero;
                while (aux->siguiente->siguiente != NULL) 
                {
                    aux = aux->siguiente;
                }
                
              pnodoD temp = aux->siguiente;
              aux->siguiente= NULL;

                
                delete temp;
            }
        }
}

void listaD::BorrarInicio()
{
    if (ListaVacia()){
     cout << "No hay elementos en la lista:" << endl;
    
   }else{
        if (primero->siguiente == NULL) {
                primero= NULL;
            } else {

                pnodoD aux = primero;
                primero=primero->siguiente;                
                delete aux;
            }
        }
}



void listaD:: borrarPosicion(int pos)
{
     if(ListaVacia())
     {
              cout << "Lista vacia" <<endl;
     }
     else
     {
        if((pos>largoLista())||(pos<0))
        {
        cout << "Error en posicion" << endl;
        }
        else
        {
        if(pos==1)
           BorrarInicio();
        else
        {
          if (pos == largoLista())   
             BorrarFinal();
          else
          {   
            int cont=2;
            pnodoD aux=  primero;
            while(cont<pos)
            {
             aux=aux->siguiente;
             cont++;
            }
            pnodoD temp=aux->siguiente;
            aux->siguiente=aux->siguiente->siguiente;
            aux->siguiente->anterior=aux;
            delete temp;
          }//else
        }//else
      }//else
    }//else
}
 

void listaD::Mostrar()
{
   nodoD *aux;
   
   aux = primero;
   while(aux) {
      cout << aux->valor << "-> ";
      aux = aux->siguiente;
   }
   cout << endl;
}

void listaD::Siguiente()
{
   if(actual) actual = actual->siguiente;
}

void listaD::Primero()
{
   actual = primero;
}

void listaD::Ultimo()
{
   actual = primero;  
   if(!ListaVacia()) 
      while(actual->siguiente) Siguiente();
}

