#include<string>
#include<locale.h>
#include<iostream>
#include<stdlib.h>
#include<windows.h>
 
using namespace std;
 
const int dFMAX = 500;                       //Declaro dimension fisica de los arreglo.
 
//----------------------------------------------------------------------------------------------------------------------------------------------------
                                                        // STRUCTS
 
struct categoria{ //Estructura de categoria.
      int codigoCategoria=0;
      string descripcion;
      //Esta estructura contendra 2 campos: código de la misma (tipo: entero) y su respectiva +descripcion (tipo: string).
};
 
struct prestatario{ //Estructura de prestatario.
     int codigoPrestatario=0;
     string nombre;
     string apellido;
    //Esta estructura contendra 3 campos: el codigo (tipo: entero), nombre/s del prestatario (tipo: string).
    //y apellido/s del mismo (tipo: string).
};
 
struct prestamo{ //Estructura de prestamo
     int codigosDeCategorias;
     int codigosDePrestatarios;
     string descripcion;
     bool estado;
    //Esta estructura contendra 4 campos: el código de la categoria en préstamo (tipo: entero),
    //codigo del prestatario del préstamo (tipo: entero), descripción del préstamo (tipo: string) y
    //estado del mismo (tipo: bool (true = préstamo vigente/false = préstamo devuelto)).
};
 
struct Nodo{
    prestamo adminPrestamo;
    Nodo *sig;
};
 
Nodo *lista = nullptr;
prestatario adminPrestatario[dFMAX];   //Arreglo de la struct prestatario.
categoria adminCategoria[dFMAX];       //Arreglo de la struct categoria.
//prestamo adminPrestamo[dFMAX];         //Arreglo de la struct prestamo.
int dlprestatario = 0;                 //Inicializo la dimension logica del arreglo prestatario en 0.
int dlcategoria = 0;                   //Inicializo la dimension logica del arreglo categoria en 0.
int dlprestamo = 0;                    //Inicializo la dimension logica del arreglo prestamo en 0.
 
//------------------------------------------------ Funciones adicionales  ------------------------------------------------------------------------
void volver(){
    cout<<"Se lo retornara al menu";
}
 
void incialesMayuscPrest(string & a){
    for(int i = 1; i < a.length(); i++){
        a[0]=toupper(a[0]);
        if(a[i] != ' '){
            a[i]=tolower(a[i]);
        }
        else{
            a[i]=toupper(a[i]+1);
        }
    }
}
 
    //Esta función incialesMayuscPrest cuyo parametro por referencia va a ser el nombre y apellido del prestatario,
    //transforma las inicales de nombre y apellido del prestatario a mayúsculas.
 
void ordenarPrestamo(Nodo *&lista,int codigo){
    int auxiliar1,auxiliar2;
    string descc;
    bool estadoss;
    for(Nodo *aux = lista; aux != NULL; aux = aux->sig){
        for(Nodo *aux2 = lista; aux2 != NULL; aux2 = aux2->sig){
            if(codigo == aux2->adminPrestamo.codigosDeCategorias){
                auxiliar1 = aux2->adminPrestamo.codigosDeCategorias;
                aux2->adminPrestamo.codigosDeCategorias = aux2->sig->adminPrestamo.codigosDeCategorias;
                aux2->sig->adminPrestamo.codigosDeCategorias = auxiliar1;
                auxiliar2 = aux2->adminPrestamo.codigosDePrestatarios;
                aux2->adminPrestamo.codigosDePrestatarios = aux2->sig->adminPrestamo.codigosDePrestatarios;
                aux2->sig->adminPrestamo.codigosDePrestatarios = auxiliar2;
                descc = aux2->adminPrestamo.descripcion;
                aux2->adminPrestamo.descripcion = aux2->sig->adminPrestamo.descripcion;
                aux2->sig->adminPrestamo.descripcion = descc;
                estadoss = aux2->adminPrestamo.estado;
                aux2->adminPrestamo.estado = aux2->sig->adminPrestamo.estado;
                aux2->sig->adminPrestamo.estado = estadoss;
            }
        }
    }
}
//Función que ordena a los prestamos de igual manera a partir de el primer codigo de la categoria que fue cambiada por otra que tenia la
//letra de la descripción más chica.
 
void ordenarPrestamosconDescIguales(Nodo *&lista, int codigo){
    int auxiliar,auxiliar2;
    string descc;
    bool estadoss;
    for(Nodo *aux = lista; aux != NULL; aux = aux->sig){
        for(Nodo *aux2 = lista; aux2 != NULL; aux2 = aux2->sig){
            if(codigo == aux2->adminPrestamo.codigosDeCategorias){
                auxiliar = aux2->adminPrestamo.codigosDeCategorias;
                aux2->adminPrestamo.codigosDeCategorias = aux2->sig->adminPrestamo.codigosDeCategorias;
                aux2->sig->adminPrestamo.codigosDeCategorias = auxiliar;
                auxiliar2 = aux2->adminPrestamo.codigosDePrestatarios;
                aux2->adminPrestamo.codigosDePrestatarios = aux2->sig->adminPrestamo.codigosDePrestatarios;
                aux2->sig->adminPrestamo.codigosDePrestatarios = auxiliar2;
                descc = aux2->adminPrestamo.descripcion;
                aux2->adminPrestamo.descripcion = aux2->sig->adminPrestamo.descripcion;
                aux2->sig->adminPrestamo.descripcion = descc;
                estadoss = aux2->adminPrestamo.estado;
                aux2->adminPrestamo.estado = aux2->sig->adminPrestamo.estado;
                aux2->sig->adminPrestamo.estado = estadoss;
            }
        }
    }
}
//Función que ordena a los prestamos de igual manera a partir de el primer codigo de la categoria que fue cambiada por otra que tenia la
//segunda letra de la descripción más chica.
 
void ordenarDescCatIguales(categoria adminCategoria[], int dlcategoria){
    string auxiliar;
    int codigo;
    for(int z = 0; z < dlcategoria; z++){
        if(lista->adminPrestamo.codigosDeCategorias == adminCategoria[z].codigoCategoria){
           for(int b = z; b < dlcategoria; b++){
               if(adminCategoria[z].descripcion[0] == adminCategoria[b].descripcion[0]){
                   if(adminCategoria[z].descripcion[1] > adminCategoria[b].descripcion[1]){
                       auxiliar = adminCategoria[z].descripcion;
                       codigo = adminCategoria[z].codigoCategoria;
                       adminCategoria[z].descripcion = adminCategoria[b].descripcion;
                       adminCategoria[b].descripcion = auxiliar;
                   }
 
               }
           }
        }
    }
    ordenarPrestamosconDescIguales(lista,codigo);
}
//Función que ordena alfabeticamente las descripciones de las categorias que tienen las primeras letras iguales de las descripciones, y despúes llama a una función
//ordenarPrestamoconDescIguale que ordena a los prestamos de igual manera a partir de el primer codigo de la categoria que fue cambiada por otra que tenia la
//segunda letra de la descripción más chica.
 
void ordenarDescCat(categoria adminCategoria[], int dlcategoria){
    string auxiliar;
    int codigo;
    for(int z = 0; z < dlcategoria; z++){
        if(lista->adminPrestamo.codigosDeCategorias == adminCategoria[z].codigoCategoria){
           for(int b = z; b < dlcategoria; b++){
               if(adminCategoria[z].descripcion[0] > adminCategoria[b].descripcion[0]){
                   auxiliar = adminCategoria[z].descripcion;
                   codigo = adminCategoria[z].codigoCategoria;
                   adminCategoria[z].descripcion = adminCategoria[b].descripcion;
                   adminCategoria[b].descripcion = auxiliar;
               }
               if(adminCategoria[z].descripcion[0] > adminCategoria[b].descripcion[0]){
                   ordenarDescCatIguales(adminCategoria, dlcategoria);
               }
           }
        }
    }
    ordenarPrestamo(lista,codigo);
}
//Función que ordena las descripciones de las categorias alfabeticamente, y despúes llama a una función ordenarPrestamo,
//que ordena a los prestamos de igual manera a partir de el primer codigo de la categoria que fue cambiada por otra que tenia la
//letra de la descripción más chica.
 
 
void ordenarPrestamoPrest(Nodo *&lista, int codigo){
    int auxiliar,auxiliar2;
    string descc;
    bool estadoss;
    for(Nodo *aux = lista; aux != NULL; aux = aux->sig){
        for(Nodo *aux2 = lista; aux2 != NULL; aux2 = aux2->sig){
            if(codigo == aux2->adminPrestamo.codigosDePrestatarios){
                auxiliar = aux2->adminPrestamo.codigosDeCategorias;
                aux2->adminPrestamo.codigosDeCategorias = aux2->sig->adminPrestamo.codigosDeCategorias;
                aux2->sig->adminPrestamo.codigosDeCategorias = auxiliar;
                auxiliar2 = aux2->adminPrestamo.codigosDePrestatarios;
                aux2->adminPrestamo.codigosDePrestatarios = aux2->sig->adminPrestamo.codigosDePrestatarios;
                aux2->sig->adminPrestamo.codigosDePrestatarios = auxiliar2;
                descc = aux2->adminPrestamo.descripcion;
                aux2->adminPrestamo.descripcion = aux2->sig->adminPrestamo.descripcion;
                aux2->sig->adminPrestamo.descripcion = descc;
                estadoss = aux2->adminPrestamo.estado;
                aux2->adminPrestamo.estado = aux2->sig->adminPrestamo.estado;
                aux2->sig->adminPrestamo.estado = estadoss;
            }
        }
    }
}
//Función que ordena a los prestamos de igual manera a partir de el primer codigo de prestatario que fue cambiado por otro que tenia la
//letra del nombre más chico.
 
void ordenarPrestamosconNombrePrestIguales(Nodo *&lista, int codigo){
    int auxiliar,auxiliar2;
    string descc;
    bool estadoss;
    for(Nodo *aux = lista; aux != NULL; aux = aux->sig){
        for(Nodo *aux2 = lista; aux2 != NULL; aux2 = aux2->sig){
            if(codigo == aux2->adminPrestamo.codigosDePrestatarios){
                auxiliar = aux2->adminPrestamo.codigosDeCategorias;
                aux2->adminPrestamo.codigosDeCategorias = aux2->sig->adminPrestamo.codigosDeCategorias;
                aux2->sig->adminPrestamo.codigosDeCategorias = auxiliar;
                auxiliar2 = aux2->adminPrestamo.codigosDePrestatarios;
                aux2->adminPrestamo.codigosDePrestatarios = aux2->sig->adminPrestamo.codigosDePrestatarios;
                aux2->sig->adminPrestamo.codigosDePrestatarios = auxiliar2;
                descc = aux2->adminPrestamo.descripcion;
                aux2->adminPrestamo.descripcion = aux2->sig->adminPrestamo.descripcion;
                aux2->sig->adminPrestamo.descripcion = descc;
                estadoss = aux2->adminPrestamo.estado;
                aux2->adminPrestamo.estado = aux2->sig->adminPrestamo.estado;
                aux2->sig->adminPrestamo.estado = estadoss;
            }
        }
    }
}
//Función que ordena a los prestamos de igual manera a partir de el primer codigo del prestatario que fue cambiado por otra que tenia la segunda
//letra del nombre más chico.
 
void ordenarNombrePrestIguales(prestatario adminPrestatario[], int dlprestatario){
    string auxiliar;
    int codigo;
    for(int z = 0; z < dlprestatario; z++){
        if(lista->adminPrestamo.codigosDePrestatarios == adminPrestatario[z].codigoPrestatario){
           for(int b = z; b < dlprestatario; b++){
               if(adminPrestatario[z].nombre[0] == adminPrestatario[b].nombre[0]){
                   if(adminPrestatario[z].nombre[1] > adminPrestatario[b].nombre[1]){
                       auxiliar = adminPrestatario[z].nombre;
                       codigo = adminPrestatario[z].codigoPrestatario;
                       adminPrestatario[z].nombre = adminPrestatario[b].nombre;
                       adminPrestatario[b].nombre = auxiliar;
                   }
 
               }
           }
        }
    }
    ordenarPrestamosconNombrePrestIguales(lista,codigo);
}
//Función que ordena los nombres de las categorias que tienen la primer letra de los nombres iguales, y despúes llama a una función ordenarPrestamosconDescPrestIguales,
//que ordena a los prestamos de igual manera a partir de el primer codigo del prestatario que fue cambiado por otra que tenia la segunda
//letra del nombre más chico.
 
void ordenarNombrePrest(prestatario adminPrestatario[], int dlprestatario){
    string auxiliar;
    int codigo;
    for(int z = 0; z < dlprestatario; z++){
        if(lista->adminPrestamo.codigosDePrestatarios == adminPrestatario[z].codigoPrestatario){
           for(int b = z; b < dlprestatario; b++){
               if(adminPrestatario[z].nombre[0] > adminPrestatario[b].nombre[0]){
                   auxiliar = adminPrestatario[z].nombre;
                   codigo = adminPrestatario[z].codigoPrestatario;
                   adminPrestatario[z].nombre = adminPrestatario[b].nombre;
                   adminPrestatario[b].nombre = auxiliar;
               }
               if(adminPrestatario[z].nombre[0] > adminPrestatario[b].nombre[0]){
                   ordenarNombrePrestIguales(adminPrestatario, dlprestatario);
               }
           }
        }
    }
    ordenarPrestamoPrest(lista,codigo);
}
//Función que ordena los nombres de los prestatarios alfabeticamente, y despúes llama a una función ordenarPrestamoPrest,
//que ordena a los prestamos de igual manera a partir de el primer codigo de prestatario que fue cambiado por otro que tenia la
//letra del nombre más chico.
 
 
void insertarAlPrincipio(Nodo* &lista, Nodo* &nuevo){
    nuevo->sig = lista;
    lista = nuevo;
}
//Función que inserta elementos de una lista al principio
 
void listarCategorias(categoria adminCategoria[], int dlcategoria){
    if (dlcategoria != 0){
       cout<<" \n Lista de las categorias actuales: "<<"\n\n ";
       for(int x = 0; x < dlcategoria; x++){
              if (adminCategoria[x].descripcion != ""){
                  cout<< " Codigo: " << adminCategoria[x].codigoCategoria << "  -->  Categoria: " << adminCategoria[x].descripcion <<"\n\n ";
              }
       }
    }
 
    else{
        cout<<"\n Aun no hay categorias registradas por mostrar."<<"\n\n";
    }
    Sleep(1000);
}
    //Función que imprime por pantalla la lista de todas las categorias actuales.
 
void listarPrestatarios(prestatario adminPrestatario[], int dlprestatario){
 
    if (dlprestatario != 0){
        cout<<" \n Lista de los prestatarios actuales: "<<"\n\n ";
        for(int x = 0; x < dlprestatario; x++){
            if (adminPrestatario[x].nombre != "" && adminPrestatario[x].apellido != ""){
                cout<< " Codigo: " << adminPrestatario[x].codigoPrestatario << " --> Prestatario: " << adminPrestatario[x].nombre << " " << adminPrestatario[x].apellido <<"\n\n ";
            }
        }
    }
 
    else{
        cout<<"\n Aun no hay prestatarios registrados por mostrar."<<"\n\n";
    }
    Sleep(1000);
}
 
    //Función que imprime por pantalla la lista de todas los prestatarios actuales.
 
void listarPrestamos(Nodo *lista, int dlprestamo){
    int cont = 0;
    if (dlprestamo != 0){
        cout<<" \n Lista de los prestamos actuales: "<<"\n\n";
        for(Nodo *aux = lista; aux != NULL; aux = aux->sig){
           cont+=1;
           cout<< "  Codigo de prestamo nro: " << cont << endl;
           cout<< "  Codigo de categoria nro: " << aux->adminPrestamo.codigosDeCategorias <<"\n";
           cout<< "  Codigo de prestatario nro: " << aux->adminPrestamo.codigosDePrestatarios <<"\n";
           cout<< "  Descripcion: " << aux->adminPrestamo.descripcion <<"\n";
           if(aux->adminPrestamo.estado == true){
               cout<< "  El estado del prestamo es: " << aux->adminPrestamo.estado <<", vigente \n\n";
           }
           else{
               cout<< "  El estado del prestamo es: " << aux->adminPrestamo.estado <<", no vigente \n\n";
           }
        }
        Sleep(3000);
     }
}
    //Función que imprime por pantalla la lista de todos los prestamos actuales.
 
void listarPrestamospendientes(Nodo *lista, int dlprestamo, prestatario adminPrestatario[], int dlprestatario, int codCat){
    if (dlprestamo != 0){
        cout<<" \n Lista de los prestamos pendientes por categoria: "<<"\n\n";
        for(Nodo *aux = lista; aux != NULL; aux = aux->sig){
            if (aux->adminPrestamo.codigosDeCategorias == codCat){
                cout<< " Descripcion: " << aux->adminPrestamo.descripcion <<"\n";
                if (aux->adminPrestamo.estado == true){
                    cout<< " El estado del prestamo es: " << aux->adminPrestamo.estado << ", vigente \n";
                }
                else{
                    cout<<"  Ingreso el codigo de una categoria que no posee prestamos pendientes. \n ";
                    break;
                }
                for(int x=0; x<dlprestatario; x++){
                    if(aux->adminPrestamo.codigosDePrestatarios == adminPrestatario[x].codigoPrestatario){
                        cout<<" El nombre y apellido del prestatario es: "<<adminPrestatario[x].nombre<<" "<<adminPrestatario[x].apellido<< "\n\n";
                    }
                }
            }
            Sleep(6000);
        }
    }
 
    else{
        cout<<"\n Aun no hay prestamos registrados por mostrar."<<"\n\n";
    }
    Sleep(3000);
}
 
    //Función que lista los prestamos pendientes de una categoría (que es determinada por el usuario).
 
void prestamosporCat(Nodo *lista, int dlprestamo, categoria adminCategoria[], int dlcategoria, prestatario adminPrestatario[], int dlprestatario){
    string auxiliar;
    if (dlprestamo != 0){
        cout<<"\n Lista de prestamos por categoria: "<<"\n\n";
        for(Nodo *aux = lista; aux != NULL; aux = aux->sig){
             if(aux->adminPrestamo.estado == true){
                ordenarDescCat(adminCategoria, dlcategoria);
                for(Nodo *aux2 = lista; aux2 != NULL; aux2 = aux2->sig){
                    for(int i = 0; i<dlcategoria; i++){
                        if(aux2->adminPrestamo.codigosDeCategorias == adminCategoria[i].codigoCategoria){
                            cout<< " Categoria: " << adminCategoria[i].descripcion << "\n";
                            for(int x = 0; x<dlprestatario; x++){
                                if(aux2->adminPrestamo.codigosDePrestatarios == adminPrestatario[x].codigoPrestatario){
                                    cout<<" Prestatario: " << adminPrestatario[x].nombre << " " << adminPrestatario[x].apellido << "\n";
                                    cout<<" Descripcion: " << aux2->adminPrestamo.descripcion << "\n";
                                    if(aux2->adminPrestamo.estado == true){
                                        cout<<" Estado: " << aux2->adminPrestamo.estado << ", vigente."<< "\n\n";
                                    }
                                    else{
                                        cout<<" Estado: " << aux2->adminPrestamo.estado << ", no vigente."<< "\n\n";
                                    }
                                }
                            }
                        }
                    }
                    Sleep(5000);
                }
                break;
             }
 
            else{
                 if(aux->adminPrestamo.estado == false){
                     ordenarDescCat(adminCategoria, dlcategoria);
                     for(Nodo *aux3 = lista; aux3 != NULL; aux3 = aux3->sig){
                         for(int i = 0; i<dlcategoria; i++){
                             if(aux3->adminPrestamo.codigosDeCategorias == adminCategoria[i].codigoCategoria){
                                 cout<< " Categoria: " << adminCategoria[i].descripcion << "\n";
                                 for(int x = 0; x<dlprestatario; x++){
                                     if(aux3->adminPrestamo.codigosDePrestatarios == adminPrestatario[x].codigoPrestatario){
                                         cout<<" Prestatario: " << adminPrestatario[x].nombre << " " << adminPrestatario[x].apellido << "\n";
                                         cout<<" Descripcion: " << aux3->adminPrestamo.descripcion << "\n";
                                         if(aux3->adminPrestamo.estado == false){
                                            cout<<" Estado: " << aux3->adminPrestamo.estado <<", no vigente." <<"\n\n";
                                         }
                                         else{
                                            cout<<" Estado: " << aux3->adminPrestamo.estado <<", vigente." <<"\n\n";
                                         }
                                     }
                                 }
                             }
 
                         }
                        Sleep(5000);
                     }
                 break;
                 }
           }
 
        }
 
    }
 
    else{
        cout<<"\n No hay prestamos cargados. Se lo retornara al menu principal.";
        Sleep(3000);
    }
 
}
 
    //Función que lista los prestamos de una categoría (nombre de la categoría, nombre, apellido, descripción del prestamo y estado)
 
void prestamosporPrest(Nodo *lista, int dlprestamo, prestatario adminPrestatario[], int dlprestatario, categoria adminCategoria[], int dlcategoria){
    if(dlprestamo != 0){
        cout<<"\n Lista de prestamos por prestatario: "<<"\n\n";
        for(Nodo *aux = lista; aux != NULL; aux = aux->sig){
             if(aux->adminPrestamo.estado == true){
                ordenarNombrePrest(adminPrestatario, dlprestatario);
                for(Nodo *aux2 = lista; aux2 != NULL; aux2 = aux2->sig){
                        for(int z = 0; z < dlprestatario; z++){
                            if(aux2->adminPrestamo.codigosDePrestatarios == adminPrestatario[z].codigoPrestatario){
                                cout<<" Prestatario: "<<adminPrestatario[z].nombre<<" "<<adminPrestatario[z].apellido<<"\n";
                                for(int x = 0; x < dlcategoria; x++){
                                        if(aux2->adminPrestamo.codigosDeCategorias == adminCategoria[x].codigoCategoria){
                                            cout<<" Categoria: " << adminCategoria[x].descripcion << ",";
                                            cout<<" Descripcion prestamo: " << aux2->adminPrestamo.descripcion << ",";
                                            if(aux2->adminPrestamo.estado == true){
                                               cout<<" Estado: " << aux2->adminPrestamo.estado << ", vigente."<<"\n\n";
                                            }
                                            else{
                                            cout<<" Estado: " << aux2->adminPrestamo.estado << ", no vigente."<<"\n\n";
                                            }
                                        }
                                }
                             }
                        }
                       Sleep(5000);
                }
                break;
             }
 
             else{
                     if(aux->adminPrestamo.estado == false){
                        ordenarNombrePrest(adminPrestatario, dlprestatario);
                        for(Nodo *aux3 = lista; aux3 != NULL; aux3 = aux3->sig){
                                 for(int l = 0; l < dlprestatario; l++){
                                     if(aux3->adminPrestamo.codigosDePrestatarios == adminPrestatario[l].codigoPrestatario){
                                         cout<<" Prestatario: "<<adminPrestatario[l].nombre<<" "<<adminPrestatario[l].apellido<<"\n";
                                         for(int s = 0; s < dlcategoria; s++){
                                             if(aux3->adminPrestamo.codigosDeCategorias == adminCategoria[s].codigoCategoria){
                                                 cout<<" Categoria: " << adminCategoria[s].descripcion << ",";
                                                 cout<<" Descripcion prestamo: " << aux3->adminPrestamo.descripcion << ",";
                                                 if(aux3->adminPrestamo.estado == true){
                                                    cout<<" Estado: " << aux3->adminPrestamo.estado << ", vigente."<<"\n\n";
                                                 }
                                                 else{
                                                     cout<<" Estado: " << aux3->adminPrestamo.estado << ", no vigente."<<"\n\n";
                                                 }
                                             }
                                          }
                                      }
 
                                   }
                                Sleep(5000);
                      }
                   break;
                }
            }
        }
    }
    else{
        cout<<"\n No hay prestamos cargados. Se lo retornara al menu principal.";
        Sleep(3000);
    }
}
 
    //Función que lista los prestamos de un prestatario (nombre, apellido, categoría, descripción del prestamo y estado).
 
//------------------------------------------------------------------------------------------------------------------------------------------------------
                                                //	FUNCIONES : 1. Administrar y consultar CategorÃ­as y Prestatarios
 
void agregar_categoria(categoria adminCategoria[], int & dlcategoria){
 
    system("CLS");
    string descripUsuario;
    int categoriaRepet = 0;
 
    while(dlcategoria < dFMAX){
 
        listarCategorias(adminCategoria,dlcategoria);
        cout<<" \n Este campo es obligatorio, no puede quedar vacio. No puede agregarse una categoria existente."<<"\n";
        cout<<" \n Ingrese la descripcion de la nueva categoria: "; getline(cin>>ws,descripUsuario);
 
        for(int i = 0; i < dlcategoria; i++){
            if (adminCategoria[i].descripcion == descripUsuario){
                categoriaRepet = 1;
                cout<<"\n Ingreso una categoria existente. Se lo retornara al menu principal.";
            }
        }
 
        if (categoriaRepet == 0){
            adminCategoria[dlcategoria].descripcion = descripUsuario;
            adminCategoria[dlcategoria].codigoCategoria = dlcategoria;
            dlcategoria++;
            cout<<"\n Categoria cargada exitosamente.";
        }
 
        break;
    }
 
    if (dlcategoria == dFMAX){
 
        cout<<"\n Se ha alcanzado el espacio maximo de carga. Por favor elimine una categoria.";
    }
 
    Sleep(2000);
}
    //Esta función será de tipo void ya que no tendrá valor de retorno; la misma tomará como parámetros
    //el arreglo adminCategoria y por referencia su dimensión lógica dlcategoria.
    //Se le pedirá al usuario la descripción de la categorÃ­a a agregar,
    //por ejemplo: videojuego,(este campo no debe quedar vacío), y
    //si esta última fue ingresada, se incrementará en 1 el código.
    //Caso contrario, se pedirá el reingreso de la descripción.
    //Luego se le almacenará el código de la categoría (que será autoincrementable y arrancará con el valor 0)
    // y cortará el programa (para que el proceso se realice una vez).
 
void modificar_categoria(categoria adminCategoria[], int dlcategoria){
 
    system("CLS");
    int codigoAmodificarleDesc, descripcionRepeat = 0, codigoVerificado = 0;
    string descripcionNueva;
 
    if (dlcategoria == 0){
        cout<<"\n Debido a la falta de categorias, se regresara al menu principal.";
        Sleep(2000);
    }
 
    //listo codigos de categorias
    else{
 
        listarCategorias(adminCategoria,dlcategoria);
        cout<<" \n Ingrese el codigo de la categoria a la que desea modificarle la descripcion: ";
        cin>>codigoAmodificarleDesc;
 
        while (descripcionRepeat == 0){
 
            for(int i = 0; i < dlcategoria; i++){
 
                if (adminCategoria[i].codigoCategoria == codigoAmodificarleDesc){
                    cout<<" \n Ingrese nueva descripcion (no puede ingresar una descripcion existente): ";
                    getline(cin>>ws, descripcionNueva);
                    codigoVerificado = 1;
                }
            }
 
            if (codigoVerificado == 1){
 
                for(int j = 0; j < dlcategoria; j++){
 
                    if (adminCategoria[j].descripcion == descripcionNueva){
                        descripcionRepeat = 1;
                    }
                }
            }
 
        break;
        }
 
        if (codigoVerificado == 0){
           cout<<" \n Codigo incorrecto. Reingrese el codigo de la categoria a la que desea modificarle la descripcion: ";cin>>codigoAmodificarleDesc;
        }
 
        if (descripcionRepeat == 1){
           cout<<"\n Ingreso una descripcion de categoria existente. Se lo retornara al menu principal.";
        }
 
        else{
             adminCategoria[codigoAmodificarleDesc].descripcion = descripcionNueva;
             cout<<"\n Descripcion modificada exitosamente.";
        }
 
        Sleep(2000);
   }
}
    //Esta función será de tipo void ya que no tendrá valor de retorno. Tomará como parámetros el arreglo adminCategoria
    //y su dimensión lógica.
    //Modificará la descripción de la categoría correspondiente. Se le pedirá al usuario
    //que ingrese el código de la categoría a la que desea modificarle la descripción.
    //Se verificará que el código de la categoria exista. Caso contrario se pedirá el reingreso del código.
    //Una vez que el código de la categoria sea verificado, se le pedirá al usuario que ingrese por teclado la descripción
    //y se reemplazará la existente.
 
 
void eliminar_categoria(categoria adminCategoria[], int &dlcategoria, Nodo *lista){
 
    system("CLS");
 
    listarCategorias(adminCategoria, dlcategoria);
    int categoriaAeliminar; int verificoCodigo = 0; int verificoCodigo2 = 0;
 
    cout<<" \n Ingrese el codigo de la categoria a eliminar: "; cin>>categoriaAeliminar;
 
    while(verificoCodigo == 0){
        for(int i = 0; i < dlcategoria; i++){
            if(adminCategoria[i].codigoCategoria == categoriaAeliminar){
                verificoCodigo = 1;
            }
        }
        if(verificoCodigo == 0){
            cout<<"\n El codigo ingresado no corresponde a una categoria existente, reingrese: "; cin>>categoriaAeliminar;
        }
    }
    for(Nodo *aux = lista; aux != NULL; aux = aux->sig){
        if(lista->adminPrestamo.codigosDeCategorias == categoriaAeliminar){
            verificoCodigo2 = 1;
        }
    }
    if(verificoCodigo2 == 0){
        cout<<"\n La categoria no tiene prestamos cargados, se lo retornara al menu principal. ";
        Sleep(2000);
        volver();
    }
    else{
        if(lista->adminPrestamo.estado == false){
            for(int l = categoriaAeliminar; l < dlcategoria; l++){
                adminCategoria[l].codigoCategoria =  adminCategoria[l+1].codigoCategoria;
                adminCategoria[l].descripcion = adminCategoria[l+1].descripcion;
            }
 
            dlcategoria--;
            cout<<"\n La categoria fue eliminada con exito.";
        }
        else{
            cout<<" \n La categoria no puede eliminarse debido a que hay prestamos pendientes.";
        }
        Sleep(2000);
    }
}
 
    //Esta función será de tipo void ya que no tendrá valor de retorno.
    //La eliminación de la categoría se realizará siempre y cuando no haya más de un objeto (pertenecientes a un prestamo vigente)
    //vinculado a la misma.
    //Caso contrario, se impedirá la eliminación.Luego de hacerlo, mostrará por pantalla el mensaje: La categoría
    //no puede eliminarse debido a que hay préstamos pendientes.
 
void agregar_prestatario(prestatario adminPrestatario[], int & dlprestatario){
    system("CLS");
 
    while(dlprestatario < dFMAX){
 
        cout<<" \n Ingrese el/los nombre/s del prestatario: ";
        getline(cin>>ws,adminPrestatario[dlprestatario].nombre);
        incialesMayuscPrest(adminPrestatario[dlprestatario].nombre);
 
        cout<<" \n Ingrese el/los apellido/s del prestatario: ";
        getline(cin>>ws,adminPrestatario[dlprestatario].apellido);
        incialesMayuscPrest(adminPrestatario[dlprestatario].apellido);
        adminPrestatario[dlprestatario].codigoPrestatario = dlprestatario;
 
        dlprestatario++;
        break;
 
        system("CLS");
    }
 
    cout<<"\n Carga de prestatario exitosa.";
 
    if (dlprestatario == dFMAX){
 
        cout<<"\n Se ha alcanzado el espacio maximo de carga. Por favor elimine un prestatario.";
    }
 
    Sleep(2000);
}
    //Esta función será de tipo void ya que no tendrá valor de retorno. Tomará como parámetros el arreglo adminPrestatario
    //y por referencia su dimensión lógica.
    //Se le pedirá al usuario el ingreso por teclado de los campos nombre/s y apellido/s (serán almacenados con la primera
    //letra en mayúscula).Luego del ingreso de los mismos, el código del prestatário(que será autoincrementable) se almacenará con el valor 0
    //y el programa cortará.
 
 
void modificar_prestatario(prestatario adminPrestatario[], int dlprestatario){
 
    system("CLS");
 
    int codigoAmodificarleDescPrest = 0; int seModificoDesc = 0;
 
    //listo los codigos de los prestatarios
    listarPrestatarios(adminPrestatario,dlprestatario);
    if(dlprestatario != 0){
        while(seModificoDesc == 0){
 
            cout<<"\n Ingrese el codigo del prestatario que desea modificar: ";
            cin>>codigoAmodificarleDescPrest;
 
            for(int i = 0; i < dlprestatario; i++){
                if(adminPrestatario[i].codigoPrestatario == codigoAmodificarleDescPrest){
 
                    cout<<"\n Ingrese el/los nuevos nombres: ";
                    getline(cin>>ws, adminPrestatario[i].nombre);
                    incialesMayuscPrest(adminPrestatario[i].nombre);
 
                    cout<<"\n Ingrese el/los nuevos apellidos: ";
                    getline(cin>>ws, adminPrestatario[i].apellido);
                    incialesMayuscPrest(adminPrestatario[i].apellido);
                    seModificoDesc = 1;
 
                    cout<<"\n El prestatario fue modificado exitosamente.";
                }
            }
        break;
        Sleep(2000);
        }
    }
    else{
        cout<<"\n Debido a la falta de prestatarios, se regresara al menu principal.";
        Sleep(2000);
    }
 
}
    //Esta función será de tipo void ya que no tendrá valor de retorno. Tomará como parámetros el arreglo adminPrestatario
    //y su dimensión lógica.
    //Modificará el campo nombre/s y apellido/s del prestatario correspondiente. Se le pedirá al usuario
    //que ingrese el código del prestatario al que desea modificarle estos campos.
    //Se verificará que el campo: código del prestatario, pertenezca a uno existente. Caso contrario, se pedirá el reingreso del mismo.
    //Una vez verificado el código del prestario, se le pedirá al usuario que ingrese por teclado los campos: nombre/s y apellido/s
    //y se reemplazarán los existentes.
 
void eliminar_prestatario(Nodo *lista, prestatario adminPrestatario[], int & dlprestatario){
 
    system("CLS");
 
    if (dlprestatario == 0){
 
        cout<<" \n No hay prestatarios cargados para mostrar, se retornara al menu";
        Sleep(2000);
    }
 
    else{
 
        int prestatarioAeliminar; int verificoCodigo2 = 0, verificoCodigo = 0;
        listarPrestatarios(adminPrestatario,dlprestatario);
 
        cout<<" \n Ingrese codigo del prestatario a eliminar: "; cin>>prestatarioAeliminar;
 
        while(verificoCodigo2 == 0){
            for(int i = 0; i < dlprestatario; i++){
                if(adminPrestatario[i].codigoPrestatario == prestatarioAeliminar){
                     verificoCodigo2 = 1;
                }
            }
            if(verificoCodigo2 == 0){
                cout<<" \n El codigo ingresado no corresponde a un prestatario existente, reingrese: ";cin>>prestatarioAeliminar;
            }
        }
        for(Nodo *aux = lista; aux != NULL; aux = aux->sig){
            if(lista->adminPrestamo.codigosDePrestatarios == prestatarioAeliminar){
                verificoCodigo = 1;
            }
        }
 
        if(verificoCodigo == 0){
            cout<<" \n El codigo ingresado no tiene prestamos cargados, se lo retornara al menu principal. ";
            Sleep(3000);
            volver();
        }
 
        else{
            if(lista->adminPrestamo.estado == false){
                for(int l = 0; l < dlprestatario; l++){
                    adminPrestatario[l].codigoPrestatario =  adminPrestatario[l+1].codigoPrestatario;
                    adminPrestatario[l].nombre = adminPrestatario[l+1].nombre;
                    adminPrestatario[l].apellido = adminPrestatario[l+1].apellido;
                }
                dlprestatario--;
                cout<<"\n El prestatario fue eliminado con exito.";
            }
            else{
                cout<<" \n El prestatario no puede eliminarse debido a que posee prestamos pendientes.";
            }
 
            Sleep(3000);
        }
        }
 
}
    //Esta función será de tipo void ya que no tendrá valor de retorno.
    //Se verificará que no haya objetos (préstamos pendientes) vinculados a ese prestatario. Para ello, se consultará el estado del préstamo
    //de dicho prestatario (valor booleano de la struct adminPrestamo). En caso de que el estado sea true, es decir, tenga un préstamo vigente,
    //se impedirá la eliminación y se informará por pantalla: El prestatario no puede eliminarse debido a que tiene préstamos pendientes.
 
//------------------------------------------------------------------------------------------------------------------------------------------------------
                                                // FUNCIONES : 2. Administrar PrÃ©stamos
 
 
void agregar_prestamo(Nodo *&lista, int & dlprestamo, categoria adminCategoria[], int dlcategoria, prestatario adminPrestatario[], int dlprestatario){
    int cont = 0;
    prestamo adminPrestamo;
    listarPrestamos(lista, dlprestamo);
 
    while(cont != -1){
        char respuestaCat; int codigoCat=0;
        cout<<" \n ¿Desea ver las actuales categorias (S/N)?: ";cin>>respuestaCat;
        respuestaCat = tolower(respuestaCat);
 
        while(respuestaCat == ' ' && respuestaCat != tolower('s') && respuestaCat != tolower('n')){
            cout<<" \n Respuesta incorrecta, reingrese: ";cin>>respuestaCat;
        }
 
        if(respuestaCat == 's'){
            //listó los codigos de los categorias
            listarCategorias(adminCategoria, dlcategoria);
            cout<<" \n Ingrese el codigo de la categoria: ";cin>>codigoCat;
        }
 
        if(respuestaCat == 'n'){
            cout<<" \n Ingrese el codigo de la categoria: ";cin>>codigoCat;
        }
 
        int verificar = 0;
        while(verificar == 0){
            for(int i=0; i<dlcategoria; i++){
                if(i == codigoCat){
                    verificar = 1;
                }
            }
            if(verificar == 0){
                cout<<" \n No existe una categoria registrada con ese codigo. Reingrese: ";cin>>codigoCat;
            }
            else{
                break;
            }
        }
        Sleep(2000);
        system("CLS");
 
        adminPrestamo.codigosDeCategorias = codigoCat;
 
        char respuestaPrest; int codigoPrest = 0;
 
        cout<<" \n ¿Desea ver los actuales prestatarios (S/N)?: ";cin>>respuestaPrest;
        respuestaPrest = tolower(respuestaPrest);
 
        while(respuestaPrest == ' ' && respuestaPrest != tolower('s') && respuestaPrest != tolower('n')){
            cout<<" \n Respuesta incorrecta, reingrese: ";cin>>respuestaPrest;
        }
 
        if(respuestaPrest == 's'){
            //listó los codigos de los prestatarios
            listarPrestatarios(adminPrestatario,dlprestatario);
            cout<<" \n Ingrese el codigo de prestatario: ";cin>>codigoPrest;
        }
 
        if(respuestaPrest == 'n'){
            cout<<" \n Ingrese el codigo de prestatario: ";cin>>codigoPrest;
        }
 
        int verificar2 = 0;
        while(verificar2 == 0){
            for(int z = 0; z<dlprestatario; z++){
                if(z == codigoPrest){
                    verificar2 = 1;
                }
            }
            if(verificar2 == 0){
                cout<<" \n No existe un prestatario registrado con ese codigo. Reingrese: ";cin>>codigoPrest;
            }
            else{
                break;
            }
        }
 
        Sleep(2000);
        system("CLS");
 
        adminPrestamo.codigosDePrestatarios = codigoPrest;
        adminPrestamo.estado = true;
 
        int descripcionRepeat = 0;
        string descripUsuario;
 
        cout<<" \n Este campo es obligatorio, no puede quedar vacio. No puede agregarse una descripcion de prestamo existente."<<"\n";
        cout<<" \n Ingrese la descripcion del nuevo prestamo: "; getline(cin>>ws, descripUsuario);//adminPrestamo.descripcion);
 
        for(Nodo *aux = lista; aux != NULL; aux = aux->sig){
            if(aux->adminPrestamo.codigosDeCategorias == codigoCat){
                    if(aux->adminPrestamo.descripcion == descripUsuario){
                        descripcionRepeat = 1;
                        cout<<"\n Ya existe un prestamo con la descripcion ingresada. Se lo retornara al menu principal.";
                    }
            }
        }
 
 
        if (descripcionRepeat == 0){
            adminPrestamo.descripcion = descripUsuario;
            dlprestamo++;
            cout<<"\n El prestamo se registro correctamente.";
        }
 
        Nodo *nuevo = new Nodo;
        nuevo->adminPrestamo = adminPrestamo;
        nuevo->sig = NULL;
 
        insertarAlPrincipio(lista, nuevo);
 
        Sleep(3000);
        break;
        system("CLS");
    }
}
 
     //Esta función será de tipo void ya que no tendrá valor de retorno.
     //Si el usuario desea agregar una categoría a los préstamos, se mostrará por pantalla el siguiente mensaje:
     //¿Desea ver las actuales categorías (S/N)?.Luego, se le pedirá que ingrese por teclado una respuesta (S/N).
     //Si el usuario ingresa "s/S", se listarán las categorías vigentes y se le pedirá el ingreso del código.
     //Si ingresa "n/N", se le pedirá el ingreso del código de la categoría a agregar sin mostrar la lista de las categorías vigentes. En ambos casos se verificará
     //que el código pertenezca a una categoría de las existentes. Caso contrario, se pedirá el reingreso del mismo hasta que
     //se ingrese un código vigente.
     //Si el usuario desea agregar un prestatario a los préstamos, se mostrará por pantalla el siguiente mensaje:
     //¿Desea ver los actuales prestatarios (S/N)?.Luego, se le pedirá que ingrese por teclado una respuesta (S/N).
     //Si el usuario ingresa "s/S", se listarán los prestatarios vigentes y se le pedirá el ingreso del código.
     //Si ingresa "n/N", se le pedirá el ingreso del código del prestatario a agregar. En ambos casos se verificará
     //que el código pertenezca a un prestatario existente. Caso contrario se pedirá el reingreso del mismo hasta que
     //se ingrese un código vigente.
     //La descripción del prestamo será pedida al usuario en caso de que el préstamo sea dado de alta.
     //Si el campo queda vacío, se solicitará el reingreso de la descripción.
     //El estado del préstamo al darse de alta, será inicializado con el valor booleano "true" y solo será "false" cuando
     //el objeto haya sido devuelto.
 
void modificar_prestamo(Nodo *&lista, int dlprestamo){
 
    system("CLS");
 
    int codigoAmodificarleDesc, descripcionRepeat = 0, codigoVerificado = 0;
    string descripcionNueva;
 
    if (dlprestamo == 0){
 
        cout<<"\n Debido a la falta de prestamos, se regresara al menu principal.";
    }
 
    else{
        listarPrestamos(lista, dlprestamo); //listo prestamos
 
        cout<<" \n Ingrese el codigo del prestamo al que desea modificarle la descripcion: ";
        cin>>codigoAmodificarleDesc;
 
        while (descripcionRepeat == 0){
 
            for(int a = 0; a < dlprestamo; a++){
 
                if (a == codigoAmodificarleDesc){
                    codigoVerificado = 1;
                    cout<<" \n Ingrese nueva descripcion: ";
                    getline(cin>>ws, descripcionNueva);
 
                }
            }
            if (codigoVerificado == 0){
                cout<<" \n Codigo incorrecto. Se lo retornara al menu principal.";
                break;
            }
 
            if (codigoVerificado == 1){
 
                for(Nodo *aux = lista; aux != NULL; aux = aux->sig){
 
                    if (aux->adminPrestamo.descripcion != descripcionNueva){
                        aux->adminPrestamo.descripcion = descripcionNueva;
                        descripcionRepeat = 1;
                        cout<<"\n Descripcion modificada exitosamente.";
                        break;
                    }
                }
                if (descripcionRepeat == 0){
                    cout<<"\n Ingreso una descripcion de prestamo existente. Se lo retornara al menu principal.";
                    break;
                }
            }
        }
 
        Sleep(2000);
   }
}
    //Esta función será de tipo void ya que no tendrá valor de retorno.
    //Le permitirá al usuario modificar la descripción del préstamo deseado siempre y cuando, el préstamo están vigente (exista).
 
void eliminar_prestamo(Nodo *&lista, int & dlprestamo){
 
    system("CLS");
 
    listarPrestamos(lista, dlprestamo);
 
    int codigoDePrestamoEliminar; int verificarPrestamoAeliminar = 0;
 
    cout<<" \n Ingrese el codigo del prestamo que desea eliminar: "; cin>> codigoDePrestamoEliminar;
 
    while(verificarPrestamoAeliminar == 0){
 
        for(int i = 0; i <= dlprestamo; i++){
            if(i == codigoDePrestamoEliminar){
                verificarPrestamoAeliminar = 1;
            }
        }
 
        if(verificarPrestamoAeliminar == 0){
            cout<<" \n Reingrese el codigo del prestamo: "; cin>> codigoDePrestamoEliminar;
        }
    }
    int seElimino = 0;
    Nodo *aEliminar;
    Nodo *aux = lista;
    while(aux != nullptr){
        for(Nodo *aux = lista; aux != NULL; aux = aux->sig){
            if(aux->adminPrestamo.estado == false && dlprestamo == codigoDePrestamoEliminar){
                if(aux->sig == nullptr){
                    aEliminar = lista;
                    //lista = lista->sig;
                    aux = aux->sig;
                    seElimino = 1;
                    delete aEliminar;
                 }
 
                 if(aux->sig != nullptr){
                    aEliminar = aux->sig;
                    aux->sig = aux->sig->sig;
                    seElimino = 1;
                    delete aEliminar;
                 }
            }
            dlprestamo--;
        }
        if(seElimino == 0){
            cout<<"\n El prestamo no se puede eliminar ya que hay prestamos pendientes.";
            Sleep(2000);
        }
        else{
           cout<<" \n El prestamo ha sido eliminado con exito.";
           Sleep(2000);
        }
    }
}
    //Esta función será de tipo void ya que no tendrá valor de retorno.
    //Le permitirá al usuario eliminar un préstamo cuando lo requiera, siempre y cuando, el estado del
    //préstamo a eliminar sea "false" es decir, no haya objetos pendientes de devolución en el mismo.
 
 
void devolver_prestamo(Nodo *&lista, int dlprestamo, prestatario adminPrestatario[], int dlprestatario){
 
    system("CLS");
 
    listarPrestatarios(adminPrestatario, dlprestatario);
 
    int codigoDePrest, verificarPrestamo = 0,verificarDevPrestamo = 1 , opcionDevolucion = 0, numeroPrestamo = 1;
 
    cout<<" \n Ingrese el codigo de prestatario que desea devolver objeto: "; cin>>codigoDePrest;
 
    while(verificarPrestamo == 0){
       for(Nodo *aux = lista; aux != NULL; aux = aux->sig){
           if(aux->adminPrestamo.codigosDePrestatarios == codigoDePrest){
               if (aux->adminPrestamo.estado == true){
                   cout<< "\n  Prestamo nro: " << numeroPrestamo++ <<"\n";
                   cout<< "  Codigo de categoria nro: " << aux->adminPrestamo.codigosDeCategorias <<"\n";
                   cout<< "  Codigo de prestatario nro: " << aux->adminPrestamo.codigosDePrestatarios <<"\n";
                   cout<< "  Descripcion: " << aux->adminPrestamo.descripcion <<"\n";
                   cout<< "  El estado del prestamo es: " << aux->adminPrestamo.estado <<", vigente \n";
               }
            verificarPrestamo = 1;
           }
       }
       if(verificarPrestamo == 0){
         cout<<" \n Codigo de prestatario incorrecto, reingrese: ";
         cin>>codigoDePrest;
       }
 
   }
       cout<<" \n Ingrese numero de prestamo a devolver: "; cin>>opcionDevolucion;
       while(dlprestamo != 0){
           if(opcionDevolucion == dlprestamo){
             for(Nodo *aux2 = lista; aux2 != NULL; aux2 = aux2->sig){
                if(codigoDePrest == aux2->adminPrestamo.codigosDePrestatarios){
                   if(aux2->adminPrestamo.estado == true){
                       aux2->adminPrestamo.estado = false;
                       cout<<"\n El prestamo se devolvio exitosamente.";
                       verificarDevPrestamo = 0;
                       break;
                   }
                }
             }
          }
          dlprestamo--;
       }
 
      if(verificarDevPrestamo == 1){
         cout<<"\n El numero de prestamo a devolver es incorrecto, se lo retornara al menu.";
      }
        Sleep(2000);
}
 
    //Esta función será de tipo void ya que no tendrá valor de retorno.
    //Le permitirá al usuario buscar un prestatario correspondiente cuando este haya hecho una devolución.
    //Se le mostrará por pantalla el listado de los prestatarios existentes con sus códigos y se le permitirá
    //realizar la entrada del código de prestatario deseado. Una vez verificado el código, se mostrarán los
    //préstamos pendientes del mismo y se le permitirá elegir entre ellos el préstamo a modificar su estado.
    //Una vez verificada la existencia del préstamo ingresado, se colocará el estado del préstamo elegido en "false".
 
//------------------------------------------------------------------------------------------------------------------------------------------------------
                                                // FUNCIONES :	3. Consultar PrÃ©stamos
/*
 * a)print categorias= num de prestasmos
 
b)= ingresar categoria
print objeto, nombre completo, estado
 
 c)= listar por categoria o por user: ej (categoria)
print:
libros:
juan perez , libro, true
juegos:
juana perez, juego, estado
 ej por prest:
print: juana perez:
libros, "soledad", true
videojuegos, "hades", true
 
d) importante ver el "estado del préstamo" si no esta en true, no imprimir
print: prestatarios con prestamos
 
*/
 
void cantidad_de_objetos_prestados_por_categoria(Nodo *lista, int dlprestamo, categoria adminCategoria[], int dlcategoria){
    system("CLS");
    int contObjCat = 0; int ocurrencias[5000] = {};
    int dlocurrencias = 0;
    int contExit=0;
    if(dlprestamo != 0){
        for(Nodo *aux = lista; aux != NULL; aux = aux->sig){
            if(aux->adminPrestamo.estado == true){
                 for(Nodo *aux2 = lista; aux2 != NULL; aux2 = aux2->sig){
                     if(aux->adminPrestamo.codigosDeCategorias == aux2->adminPrestamo.codigosDeCategorias){
                         contObjCat+=1;
                     }
                 }
                 for(int y=0; y<dlocurrencias; y++){
                     if(ocurrencias[y] == aux->adminPrestamo.codigosDeCategorias){
                             contExit = 1;
                     }
                 }
 
                 if(contObjCat > 1){
                     ocurrencias[dlocurrencias] = aux->adminPrestamo.codigosDeCategorias;
                     dlocurrencias++;
                 }
            if(contExit == 1){
                 contExit = 0;
                 continue;
            }
                 for(int i=0; i<dlcategoria; i++){
                     if(aux->adminPrestamo.codigosDeCategorias == adminCategoria[i].codigoCategoria){
                         cout<< " \n La categoria " << adminCategoria[i].descripcion << " tiene: " << contObjCat << " prestamos." << "\n ";
                         contObjCat = 0;
                         Sleep(3000);
                     }
                 }
            }
 
            Sleep(3000);
        }
    }
    else{
        cout<<"No hay prestamos cargados. Se lo retornara al menu principal.";
        Sleep(3000);
    }
}
    //Esta función será de tipo int ya que retornará la cantidad de préstamos por categoría y el total
    //de préstamos pendientes (ambos valores numéricos).
    //Tendrá como parámetros el arreglo de los préstamos y su dimensión lógica.
 
void lista_prestamos_por_categoria(Nodo *lista, int dlprestamo, categoria adminCategoria[], int dlcategoria, prestatario adminPrestatario[], int dlprestatario){
    system("CLS");
    int codigoCategoria, verificaCat;
    listarCategorias(adminCategoria, dlcategoria);
    if(dlcategoria != 0){
        cout<<" Ingrese el codigo de una de las categorias existentes a consultar prestamos pendientes: ";cin>>codigoCategoria;
        for(int i=0; i<dlcategoria; i++){
            if(adminCategoria[i].codigoCategoria == codigoCategoria){
                listarPrestamospendientes(lista, dlprestamo, adminPrestatario, dlprestatario,codigoCategoria);
                verificaCat = 1;
            }
        }
        if(verificaCat == 0){
            cout<<" Ingreso una categoria inexistente. Se lo devolvera al menu principal.";
            Sleep(3000);
        }
    }
 
    //Esta función será de tipo void ya que no tendrá valor de retorno. Solo mostrará por pantalla información
    //necesaria/solicitada para el usuario.
    //Dada una categoría por el usuario, se le mostrará un listado con la descripción de los préstamos pendientes
    //y datos del prestatario.
}
 
 
void lista_prestamos_catoprest(Nodo *lista, int dlprestamo, categoria adminCategoria[], int dlcategoria, prestatario adminPrestatario[], int dlprestatario){
    system("CLS");
    char respuesta;
    cout<<"\n Indicar como desea listar los prestamos C(para categorias) o P(prestatarios): ";cin>>respuesta;
    respuesta = toupper(respuesta);
 
    if(respuesta != 'C' && respuesta != 'P'){
        cout<<"\n\n Ingreso una respuesta incorrecta, se lo devolvera al menu principal."<<"\n";
        Sleep(3000);
    }
 
    if(respuesta == 'C'){
        prestamosporCat(lista, dlprestamo, adminCategoria, dlcategoria, adminPrestatario, dlprestatario);
    }
 
    if(respuesta == 'P'){
        prestamosporPrest(lista, dlprestamo, adminPrestatario, dlprestatario, adminCategoria, dlcategoria);
    }
 
    //Esta función será de tipo void ya que no tendrá valor de retorno. Solo mostrará por pantalla información
    //necesaria/solicitada para el usuario.
    //Tendrá como parámetros todos los arreglos con sus respectivas dimensiones lógicas.
    //Le permitirá al usuario elegir el listado de los préstamos por categoría o prestatarios. Una vez ingresada
    //la opción, se le mostrará por pantalla el listado de la forma elegida de manera ascendente, conteniendo
    //cada préstamo la categoría, descripción y datos del prestatario.
}
 
void prestatarios_con_prestamos_activos(Nodo *lista, int dlprestamo, prestatario adminPrestatario[], int dlprestatario){
    system("CLS");
    int contPrestAct; int ocurrenciasPrestamos[5000] = {};
    int dlocurrenciasPres = 0; int contSalir = 0;
    if(dlprestamo != 0){
        cout<<"\n  Lista de prestamos pendientes por prestatario: "<<"\n\n";
        for(Nodo *aux = lista; aux != NULL; aux = aux->sig){
            if(aux->adminPrestamo.estado == true){
               for(Nodo *aux2 = lista; aux2 != NULL; aux2 = aux2->sig){
                    if(aux->adminPrestamo.codigosDePrestatarios == aux2->adminPrestamo.codigosDePrestatarios){
                        contPrestAct += 1;
                    }
                }
                for(int y=0; y<dlocurrenciasPres; y++){
                    if(ocurrenciasPrestamos[y] == aux->adminPrestamo.codigosDePrestatarios){
                        contSalir = 1;
                    }
                }
 
                if(contPrestAct > 1){
                    ocurrenciasPrestamos[dlocurrenciasPres] = aux->adminPrestamo.codigosDePrestatarios;
                    dlocurrenciasPres++;
                }
                if(contSalir == 1){
                    contSalir = 0;
                    continue;
 
                }
                for(int z = 0; z < dlprestatario; z++){
                    if(aux->adminPrestamo.codigosDePrestatarios == adminPrestatario[z].codigoPrestatario){
                       cout<<" Prestatario: "<<adminPrestatario[z].nombre<<" "<<adminPrestatario[z].apellido<<". Prestamos activos: "<<contPrestAct<< "\n";
                       contPrestAct = 0;
                    }
                }
            }
        }
        Sleep(5000);
    }
    else{
        cout<<"\n No hay prestamos cargados. Se lo retornara al menu principal.";
        Sleep(3000);
    }
 
    //Esta función será de tipo void ya que no tendrá valor de retorno. Solo mostrará por pantalla información
    //necesaria/solicitada para el usuario.
    //Tendra como parametros el arreglo de los prestamos,su dimensión lógica, y el arreglo de prestatarios con su dimensión lógica.
    //Listará todos los prestatarios con préstamos pendientes.
}
 
//-------------------------------------------------MENU PRINCIPAL-----------------------------------------------------------------
 void menuPrincipal(){
     int opcion = 0;
     do{
 
        // MENU PRINCIPAL
        system("CLS");
        cout<<
 
        "\n   Menu\n"
 
        "\n 1. Administrar y consultar Categorias y Prestatarios\n"
 
        "\n 2. Administrar Prestamos\n"
 
        "\n 3. Consultar Prestamos\n"
 
        "\n 4. Salir\n\n"
 
        "   Digitar opcion: ";cin>>opcion;
 
          //While para evitar que el usuario ingrese una opcion incorrecta
          while (opcion != 1 && opcion != 2 && opcion != 3 && opcion != 4){
            system("CLS");
 
            cout<<
 
            "\n   Menu\n"
 
            "\n 1. Administrar y consultar Categorias y Prestatarios\n"
 
            "\n 2. Administrar Prestamos\n"
 
            "\n 3. Consultar Prestamos\n"
 
            "\n 4. Salir\n\n"
 
            "   Ingresar una de las opciones de arriba: ";cin>>opcion;
          }
 
        system("CLS");
 
        // PRIMER OPCION - ADMINISTRAR Y CONSULTAR CATEGORIAS Y PRESTATARIOS
 
        if (opcion == 1){
 
            char opcion_actual = 0;
 
            cout<<"\n 1. Administrar y consultar Categorias y Prestatarios\n"
 
            "\n A) Agregar categoria\n"
 
            "\n B) Modificar categoria\n"
 
            "\n C) Eliminar categoria\n"
 
            "\n D) Agregar prestatario\n"
 
            "\n E) Modificar prestatario\n"
 
            "\n F) Eliminar prestatario\n"
 
            "\n G) Regresar al menu principal\n\n"
 
            "   Digitar opcion: ";cin>>opcion_actual;
 
        //While para evitar que el usuario ingrese una opcion incorrecta
        while (   toupper(opcion_actual) != 65
                & toupper(opcion_actual) != 66
                & toupper(opcion_actual) != 67
                & toupper(opcion_actual) != 68
                & toupper(opcion_actual) != 69
                & toupper(opcion_actual) != 70
                & toupper(opcion_actual) != 71
              ){
 
                system("CLS");
 
 
                cout<<"\n 1. Administrar y consultar Categorias y Prestatarios\n"
 
                "\n A) Agregar categoria\n"
 
                "\n B) Modificar categoria\n"
 
                "\n C) Eliminar categoria\n"
 
                "\n D) Agregar prestatario\n"
 
                "\n E) Modificar prestatario\n"
 
                "\n F) Eliminar prestatario\n"
 
                "\n G) Regresar al menu principal\n\n"
 
                "   Ingresar una de las opciones de arriba: ";cin>>opcion_actual;
            }
 
            system("CLS");
 
 
 
            switch(toupper(opcion_actual)){
 
                case 'A':  // Agregar categoria
 
                    agregar_categoria(adminCategoria, dlcategoria); //Llamado a la función que agregará una categoria.
 
                    break;
 
                case 'B':  // Modificar categoria
 
                    modificar_categoria(adminCategoria, dlcategoria); //Llamado a la función que modificará la descripción de una categoria.
 
                    break;
 
                case 'C':  // Eliminar categoria
 
                    eliminar_categoria(adminCategoria, dlcategoria, lista); //Llamado a la función que eliminará una categoria.
 
                    break;
 
                case 'D':  // Agregar prestatario
 
                    agregar_prestatario(adminPrestatario, dlprestatario); 	//Llamado a la función que agregará un prestatario.
 
                    break;
 
 
                case 'E':  // Modificar prestatario
 
                    modificar_prestatario(adminPrestatario, dlprestatario); //Llamado a la función que modificará el nombre/s y apellido/s de un prestatario.
 
                    break;
 
                case 'F':  // Eliminar prestatario
 
                    eliminar_prestatario(lista, adminPrestatario, dlprestatario); //Llamado a la función que eliminará un prestatario.
 
                    break;
 
                default:   // Regresar al menu principal
 
                    volver();
                    break;
            }
 
 
        }
 
        // SEGUNDA OPCION - ADMINISTRAR PRESTAMOS
 
        if (opcion == 2){
 
            char opcion_actual = 0;
 
            cout<<
 
            "\n 2. Administrar prestamos\n"
 
            "\n A) Agregar prestamo\n"
 
            "\n B) Modificar prestamo\n"
 
            "\n C) Eliminar prestamo\n"
 
            "\n D) Devolver prestamo\n"
 
            "\n G) Regresar al menu principal\n\n"
 
            "   Digitar opcion: ";cin>>opcion_actual;
 
 
 
        //While para evitar que el usuario ingrese una opcion incorrecta
        while (toupper(opcion_actual) != 65 && toupper(opcion_actual) != 66 && toupper(opcion_actual) != 67 && toupper(opcion_actual) != 68 && toupper(opcion_actual) != 71){
 
                system("CLS");
                cout<<
 
                "\n 2. Administrar prestamos\n"
 
                "\n A) Agregar prestamo\n"
 
                "\n B) Modificar prestamo\n"
 
                "\n C) Eliminar prestamo\n"
 
                "\n D) Devolver prestamo\n"
 
                "\n G) Regresar al menu principal\n\n"
 
                "   Ingresar una de las opciones de arriba: ";cin>>opcion_actual;
            }
 
            system("CLS");
 
            switch(toupper(opcion_actual)){
 
                case 'A': // Agregar prestamo
 
                    agregar_prestamo(lista, dlprestamo, adminCategoria, dlcategoria, adminPrestatario, dlprestatario); //Llamado a la función que agrega un prestamo.
 
                    break;
 
                case 'B': // Modificar prestamo
 
                    modificar_prestamo(lista, dlprestamo); //Llamado a la función que modificará la descripción de un prestamo.
 
                    break;
 
                case 'C': // Eliminar prestamo
 
                    eliminar_prestamo(lista, dlprestamo); //Llamado a la función que eliminará un prestamo.
 
                    break;
 
                case 'D': // Delvolver prestamo
 
                   devolver_prestamo(lista, dlprestamo, adminPrestatario, dlprestatario); //Llamado a la función que da de baja un prestamo, cambiando el estado del mismo.
 
                    break;
 
                 default:   // Regresar al menu principal
 
                    break;
                }
 
        }
 
        // TERCER OPCION - CONSULTAR PRESTAMOS
 
        if (opcion==3){
 
            char opcion_actual = 0;
 
            cout<<
 
            "\n 3. Consultar Prestamos\n"
 
            "\n A) Cantidad de objetos prestados por categoria\n"
 
            "\n B) Listado de prestamos por categoria\n"
 
            "\n C) Listado de prestamos ordenados por categoria o prestatario\n"
 
            "\n D) Listar todos los prestatarios que tienen al menos un objeto prestado\n"
 
            "\n G) Regresar al menu principal\n\n"
 
            "   Digitar opcion: ";cin>>opcion_actual;
 
        //While para evitar que el usuario ingrese una opcion incorrecta
        while (toupper(opcion_actual) != 65 && toupper(opcion_actual) != 66 && toupper(opcion_actual) != 67 && toupper(opcion_actual) != 68 && toupper(opcion_actual) != 71){
 
                system("CLS");
                cout<<
 
                "\n 3. Consultar Prestamos\n"
 
                "\n A) Cantidad de objetos prestados por categoria\n"
 
                "\n B) Listado de prestamos por categoria\n"
 
                "\n C) Listado de prestamos ordenados por categoria o prestatario\n"
 
                "\n D) Listar todos los prestatarios que tienen al menos un objeto prestado\n"
 
                "\n G) Regresar al menu principal\n\n"
 
                "   Ingresar una de las opciones de arriba: ";cin>>opcion_actual;
            }
 
            system("CLS");
 
            switch(toupper(opcion_actual)){
 
                case 'A': // Cantidad de objetos prestados por categoria.
 
                    cantidad_de_objetos_prestados_por_categoria(lista, dlprestamo, adminCategoria, dlcategoria);
                    //Llamado a la función que devuelve la cantidad de préstamos por categoría y el total de préstamos pendientes.
 
                    break;
 
                case 'B': // Listado de prestamos por categoria.
 
                    lista_prestamos_por_categoria(lista, dlprestamo, adminCategoria, dlcategoria, adminPrestatario, dlprestatario);
                    //Llamado a función que lista la descripción de los préstamos pendientes y datos del prestatario.
 
                    break;
 
                case 'C': // Listado de prestamos ordenados por categoria o prestatario.
 
                    lista_prestamos_catoprest(lista, dlprestamo,adminCategoria, dlcategoria,adminPrestatario, dlprestatario);
                    // Llamado a función que lista los préstamos pendientes, ordenados y agrupados por categoría o por prestatario,
                    // según la elección del usuario.
 
                    break;
 
                case 'D': // Listar todos los prestatarios que tienen al menos un objeto prestado.
 
                    prestatarios_con_prestamos_activos(lista, dlprestamo, adminPrestatario, dlprestatario);
                    // Llamado a función que lista los prestatarios con prestamos pendientes.
 
                    break;
 
                default: // Regresar al menú principal
 
                    break;
            }
        }
 
 
    }while(opcion!=4);
 
    cout<< "\n\n   A finalizado el menu \n\n";
 }
 
//------------------------------------------------------------------------------------------------------------------------------------------------------
 
int main(){
    setlocale(LC_CTYPE,"Spanish");
    menuPrincipal();
    return 0;
}