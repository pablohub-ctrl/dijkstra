#include <stdio.h>
#include <stdlib.h>


int** crearMatriz(int size){
	int** matriz = (int**)malloc(sizeof(int*)*size);
	int i,j;
	for(i = 0; i < size; i++){
		matriz[i] = (int*)malloc(sizeof(int)*size);
	}
	for(i=0; i<size; i++){
        for(j=0; j<size; j++){
            matriz[i][j]=0;
        }
}
	return matriz;
}


int** leerGrafo(FILE* f,int size){

	int** matrizAdyacencia = crearMatriz(size);
	//printMatriz(matrizAdyacencia, size);
	char aux;
	int auxCond = 1;
 	int i,indiceFila,indiceColumna,dist;
	for(i=0; i<size; i++){
        while(feof(f)==0){
            fscanf(f,"%d,%d%c",&indiceColumna,&dist,&aux);
            matrizAdyacencia[i][indiceColumna-1]=dist;          
            if(aux=='\n'){
                break;
            }
        }
        aux=0;
    }
    return matrizAdyacencia;
}

typedef struct grafo{
   int anterior;
   int visitado;
   int costo;
   struct grafo* siguiente;
}grafo;

grafo* crearNodoGrafo(int i){
		grafo *nuevoGrafo = (grafo*)malloc(sizeof(grafo));
	
	
		/* 			Habiendo la posibilidad de error en obtener reservas de memorias
							evaluamos a 'nuevoGrafo' en caso de ser un valor NULL*/
		if(nuevoGrafo==NULL){
				printf("No se puede obtener más espacio de memoria, GOTOwatch\n");
				return NULL;
			}
		/*			CASO CORRECTO DE LA FUNCIÓN		
						asigno valores por defecto a la variables inscritas*/
		
		nuevoGrafo -> anterior = -1;
		nuevoGrafo -> visitado = -1;
		nuevoGrafo -> costo = -1;
		
		nuevoGrafo -> siguiente = NULL;
		
		
			return nuevoGrafo;
	
}

grafo** crearGrafoStruc(int nVertices){
	grafo** enFilas = (grafo**)malloc(sizeof(grafo*)*nVertices);
		if(enFilas==NULL){
			printf("No se puede obtener más espacio en memoria... .\n");
				
				return NULL;
			}
	int j;
		for(j = 0 ;j < nVertices; j++){
			enFilas[j] = crearNodoGrafo(j+1);
		}
	 return enFilas;
	}


typedef struct arista{
   int desde;
   int hasta;
   int costo;
   struct arista* anterior;
   struct arista* siguiente;
}arista;


arista* crearArista(int desde, int hasta,int costo){
	
   	arista *nuevaArista = (arista*)malloc(sizeof(arista));
	/* 			Habiendo la posibilidad de error en obtener reservas de memorias
							evaluamos a 'nuevaArista' en caso de ser un valor NULL   */
		if(nuevaArista==NULL){
				printf("No se puede obtener más espacio de memoria, GOTOwatch\n");
				return NULL;
		}
	/*			CASO CORRECTO DE LA FUNCIÓN		
						asigno valores por defecto a la variables inscritas         */
		
		nuevaArista -> desde = desde;
		nuevaArista -> hasta = hasta;
		nuevaArista -> costo = costo;
      nuevaArista -> anterior = NULL;
		nuevaArista -> siguiente = NULL;
				
	return nuevaArista;
	
}

void initGrafo(grafo** grafoStruct, int i){
         grafoStruct[i]->costo = 0;
         grafoStruct[i]->anterior = -2;
         grafoStruct[i]->visitado = 1;
}

// recibe una pila y retorna su última posición como estructura
arista* trasladarClon_A_ultimaArista1(arista* pila){
   arista* clon = pila;
   while(clon -> siguiente != NULL){
      clon = clon -> siguiente;
   }
   return clon;
}


//conecta dos estructuras 
//aristaStruc conecta su final con aristaNueva
arista* agregaArista(arista* aristaStruc, arista* aristaNueva){
         arista *clon = (arista*)malloc(sizeof(arista));
         
         clon = trasladarClon_A_ultimaArista1(aristaStruc);

			clon -> siguiente = aristaNueva;
         aristaNueva -> anterior = clon;
         
         return aristaNueva;
}


arista* crearPilaInical(int ** matriz, int size,int numero){
   	
      arista *nueva = (arista*)malloc(sizeof(arista));
      arista *clon = (arista*)malloc(sizeof(arista));
      arista *nueva3 = (arista*)malloc(sizeof(arista));
      arista *nueva2 = (arista*)malloc(sizeof(arista));
   
   
      int z=0;
      for(int i=0;i<size;i++){
         if(matriz[numero][i] != 0){
            if(z==0){
               //printf("%d ",matriz[numero][i]);
               nueva = crearArista(numero,i,matriz[numero][i]);   
               clon = nueva;
               z=z+1;
            }
            else if(z>1){
               //printf("%d ",matriz[numero][i]);
               nueva3 = crearArista(numero,i,matriz[numero][i]);
               agregaArista(clon, nueva3);
               //clon = trasladarClon_A_ultimaArista(clon);
            }
            else{
               arista* nueva2 = crearArista(numero,i,matriz[numero][i]);
               agregaArista(clon, nueva2);
               //printf("%d ",matriz[numero][i]);
               //clon = trasladarClon_A_ultimaArista(clon);
               z=z+1;
            }
            
         }
      }

   return nueva;   

}


int compruebaTermino(grafo** grafoStruct, int size){
	int total=0;
	int tamano=size;
	int i;
		for(i=0;i<size;i++){
			if(grafoStruct[i]->visitado == 1){
				total=total+1;
				
			}
		}
		//visualizarGrafo(grafoStruct,size);
		
		if(total == tamano){
			return 1;
		}
		return 0;

}


arista* aristaMenor(arista* pila){

   arista *arista1 = (arista*)malloc(sizeof(arista));
   arista *arista2 = (arista*)malloc(sizeof(arista));
   
   if(pila==NULL){
      //printf("grafoDesconexo777");
      return NULL;
   }
   else{
      arista1 = pila;
      arista2= pila -> siguiente;

      if(arista1 -> siguiente == NULL){
      return pila;
   }
   else{

      while(arista2 -> siguiente != NULL){

         if(arista1 -> costo < arista2 -> costo){
            arista2 = arista2 -> siguiente;
         }  
         else{
            arista1 = arista2;
            arista2 = arista2 -> siguiente;
         }
      }

      if(arista1 -> costo < arista2 -> costo){
            //arista1 -> siguiente = NULL;
            //arista1 -> anterior = NULL;
            return arista1;
      }  
      else{
         //arista2 -> siguiente = NULL;
         //arista2 -> anterior = NULL;
         return arista2;
      }   
   }
   }
}


arista* deletArist_pila(arista* pila, arista* valorMenor){
   arista *arista1;
   arista *arista2;
   arista *arista3;
   
    //= (arista*)malloc(sizeof(arista))
   
   if(pila!=NULL){

   int desde = valorMenor->desde;
   int hasta = valorMenor->hasta;
   int costo = valorMenor->costo;   
         
   if((pila->desde == desde) && (pila->hasta == hasta) && (pila->costo == costo)){

         if(pila -> siguiente == NULL){
            free(pila);
            return NULL;
         }
         arista1 = pila -> siguiente;
         arista1 -> anterior = NULL;
         free(pila);
         return arista1;
      }
   else{
         
         arista2 = pila;
         arista2 = arista2 -> siguiente;
            while(arista2->siguiente != NULL){
               
               if((arista2->desde == desde) && (arista2->hasta == hasta) && (arista2->costo == costo)){

                 
                  arista3 = arista2 -> siguiente;
                  arista1 = arista2 -> anterior;
                  arista1 -> siguiente = arista3;
                  
                  arista3 -> anterior = arista1;
                  

                  if(arista2->anterior == NULL){
                     printf("aparece null\n");
                  }
                  //free(arista3);
                  
                  //free(arista3);
                  //arista1 -> siguiente = arista2 -> siguiente;
                  return pila;

               }  
                  
                  arista2 = arista2 -> siguiente;
               
            }
            
            if((arista2->desde == desde) && (arista2->hasta == hasta) && (arista2->costo == costo)){

                   //arista3 = arista2 -> siguiente;
                  arista1 = arista2 -> anterior;

                  arista1 -> siguiente = NULL;
                  
                  //arista3 -> anterior = arista1;

                
                  
                  //arista3 -> siguiente = NULL;
                  free(arista2);
                  //arista1 -> siguiente = arista2 -> siguiente;
                  return pila;

               }
               printf("PilaVacia");
            return pila;  
      }
   }
   else{
      printf("PilaVacia");
   }
   
}

void modGrafo(arista* aristaMenor, grafo** grafoStruct){
      if(grafoStruct[aristaMenor->hasta]->visitado==-1){
         grafoStruct[aristaMenor->hasta]->costo = aristaMenor->costo;
         grafoStruct[aristaMenor->hasta]->anterior = aristaMenor->desde;
         grafoStruct[aristaMenor->hasta]->visitado = 1;
      }
		/*
      else{
            if(grafoStruct[aristaMenor->hasta]->costo > aristaMenor->costo){
               grafoStruct[aristaMenor->hasta]->costo = aristaMenor->costo;   
               grafoStruct[aristaMenor->hasta]->anterior = aristaMenor->desde;
            }
            
            
      } 
		*/
}



arista* addPila(int ** matriz, int size, arista* AristaMenor, arista* pila ){
   	
      arista *nueva = (arista*)malloc(sizeof(arista));
      arista *clon = (arista*)malloc(sizeof(arista));
      arista *nueva3 = (arista*)malloc(sizeof(arista));
      arista *nueva2 = (arista*)malloc(sizeof(arista));
   
      if(AristaMenor==NULL){
         printf("llego una AristaMenor vacia");
      }  
      if(pila==NULL){
         printf("llego una pila vacia");
      }
    
      int z=0;
      for(int i=0;i<size;i++){
         if(matriz[i][AristaMenor -> hasta] != 0){
            if(z==0){
               //crearArista(int desde, int hasta,int costo)
               nueva = crearArista(AristaMenor -> hasta ,i,matriz[i][AristaMenor -> hasta] + AristaMenor -> costo);

               if(pila==NULL){
                  clon = nueva;
                  z=z+1;
               }
               else{
                 clon = agregaArista( pila, nueva);
                  //clon = trasladarClon_A_ultimaArista(pila);
               }
               
            }
            else if(z>1){
               //printf("%d ",matriz[numero][i]);
               nueva3 = crearArista(AristaMenor -> hasta,i,matriz[i][AristaMenor -> hasta] + AristaMenor -> costo);
               clon = agregaArista(clon, nueva3);
               //clon = trasladarClon_A_ultimaArista(clon);
            }
            else{
               arista* nueva2 = crearArista(AristaMenor -> hasta,i,matriz[i][AristaMenor -> hasta] + AristaMenor -> costo);
               clon = agregaArista(clon, nueva2);
               //clon = trasladarClon_A_ultimaArista(clon);
               z=z+1;
            }
            
         }
      }

   return pila;   

}


int sizeone(grafo** grafoVerticesDijkstra, int llegada){
	int contador=0;
	int visitado=llegada;
	

		while(visitado!=-2){
			//if(grafoVerticesDijkstra[visitado]->anterior!=-2){
				visitado=grafoVerticesDijkstra[visitado]->anterior;
				contador = contador + 1;
			//}
			
		}
	return contador;	
}		


int* arrayRuta(grafo** grafoVerticesDijkstra, int size,int inicio, int llegada){
	int contador=0;
	int visitado=llegada;
	

		while(visitado!=-2){
			//if(grafoVerticesDijkstra[visitado]->anterior!=-2){
				visitado=grafoVerticesDijkstra[visitado]->anterior;
				contador = contador + 1;
			//}
			
		}
		int* arregloprintf=(int*)malloc(sizeof(int*)*contador);
		int contadorInmutable=contador;
		contador=contador-1;
		
		visitado=llegada;
		arregloprintf[contador]=visitado;
		while(visitado!=-2){
			//if(grafoVerticesDijkstra[visitado]->anterior!=-2){
				contador = contador - 1;
				visitado=grafoVerticesDijkstra[visitado]->anterior;
				arregloprintf[contador]=visitado;
				//contador = contador + 1;
			//}
			
		}
		arregloprintf[0]=inicio;
	//printf("contador llego a %d\n", contadorInmutable);
	/*
			printf("Ruta: ");
			for(int e=0;e<contadorInmutable; e++){
				printf("%d ",arregloprintf[e]);
			}
			printf("\nmenor costo total de ruta: %d", grafoVerticesDijkstra[llegada]->costo);
			*/
	return arregloprintf;

}


int dijkstra(int** matriz, int size, int inicio, int destino){

    arista *AristaMenor = (arista*)malloc(sizeof(arista));
    arista *pila = (arista*)malloc(sizeof(arista));
    grafo** grafoStruct =  (grafo**)malloc(sizeof(grafo**)*size);
    arista *modificado = (arista*)malloc(sizeof(arista));
    int retorno=1;
   
    grafoStruct = crearGrafoStruc(size);   

    initGrafo(grafoStruct, inicio);

    pila = crearPilaInical(matriz, size, inicio);
    
    int saltaAutomatico=1;
    while(compruebaTermino(grafoStruct, size)==0 && saltaAutomatico==1){
    
        AristaMenor = aristaMenor(pila);
        if(AristaMenor==NULL){
            printf("Grafo desconexo");
            saltaAutomatico=0;
            retorno=0;
        }
        else{
                //printf(" %d",AristaMenor->desde);
                if(grafoStruct[AristaMenor -> hasta]->visitado == 1){
                    modificado = deletArist_pila(pila, AristaMenor);
                    pila = modificado;
                }
                else{
                        
                        //printf("Llego hasta acá?");
                        modGrafo(AristaMenor,grafoStruct);

                        pila = addPila( matriz,  size, AristaMenor, pila );
                        modificado = deletArist_pila(pila, AristaMenor);
                        pila = modificado;
                }   
        }
        
    
    }
    //if(contadorconexto==0){
    //    printf("Grafo desconexo");
    //}
    //visualizarGrafo(grafoStruct,size);
    if(saltaAutomatico!=0){
            int largo=sizeone(grafoStruct,  destino);
            int* ruta=(int*)malloc(sizeof(int*)*largo);
            ruta=arrayRuta(grafoStruct,  size,inicio,  destino);
            //printf("\n Tamano: %d",largo);

            printf("Ruta mas corta: ");
                    for(int e=0;e<largo; e++){
                        if(e<largo-1){
                            printf("%d-",ruta[e]+1);
                        }
                        else{
                            printf("%d",ruta[e]+1);
                        }
                        
                    }
                    printf("\nDistancia: %d", grafoStruct[destino]->costo);
        
        

        
        }
/*
    free(grafoStruct);
    //liberargrafo(grafoStruct, size);
    free(AristaMenor);
    free(pila);
    free(modificado);
*/
    return retorno;


}


int main(){

   
   FILE* f = fopen("grafo.in","r");
	int size;
	fscanf(f,"%d",&size);
   int salida=1;
           
	int** matriz = leerGrafo(f,size);
   int inicio=0;
   int destino=0;
    //int salida=1;
   printf("Ingrese punto de inicio: ");
   scanf("%d",&inicio);
   inicio=inicio-1;
   printf("Ingrese punto de destino: ");
   scanf("%d",&destino);
   destino=destino-1;

    
    
   int validacion = dijkstra(matriz, size, inicio, destino);

   if(validacion==1){
      printf("\nExiste La ruta\n");   
   }
   

    
    


}