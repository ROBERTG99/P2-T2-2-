#include "../include/cadena.h"
#include "../include/utils.h"
#include "../include/info.h"
#include "../include/usoTads.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/*
  Devuelve 'true' si y solo si en 'cad' hay un elemento cuyo campo natural es
  'elem'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cad'.
*/
bool pertenece(nat elem, TCadena cad) {
  TLocalizador x = inicioCadena(cad);
  x = siguienteClave(elem, x, cad);
  return (x != NULL);
}
  /*x = cad->inicio;
  while ((x->siguiente != cad->final->siguiente) && (elem != natInfo())) {
    x = x->siguiente;
  }
  return (x->siguiente != cad->final->siguiente);
}
*/
/*
  Devuelve la cantidad de elementos de 'cad'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cad'.
*/
nat longitud(TCadena cad) {
  TLocalizador c = NULL;
  nat aux = 0;
  c = inicioCadena(cad);
  if (!esVaciaCadena(cad)) {
    while (c != NULL) {
      c = siguiente(c, cad);
      aux = aux + 1;
    }
  }
  return aux;
}

/*
  Devuelve 'true' si y solo si 'cad' está ordenada de forma no dereciente
  (creciente de manera no estricta) según las campos naturales de sus elementos.
  Si esVaciaVadena(cad) devuelve 'true'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cad'.
*/
bool estaOrdenadaPorNaturales(TCadena cad)  {
  bool res;
  if (esVaciaCadena(cad)) {
    res = true;
  } else {
    TLocalizador c, d;
    c = inicioCadena(cad);
    d = c;
    d = siguiente(d, cad);
    while ((d != nullptr) && (natInfo(infoCadena(d, cad)) >= natInfo(infoCadena(c, cad)))) {
      c = siguiente(c, cad);
      d = siguiente(d, cad);
    }
    res = (d == nullptr);
  }
  return res;
}

/*
  Devuelve 'true' si y solo si los componentes naturales de algún par de 
  elementos de 'cad' son iguales.  
*/
bool hayNatsRepetidos(TCadena cad) {
  bool res = false;
/* while ((aux != NULL) && (siguienteClave(natInfo(infoCadena(aux, cad)), aux, cad) == NULL)) {
    aux = siguiente(aux, cad);
  }
  return (aux != NULL);
}*/
  if (!esVaciaCadena(cad))  
  {
    TLocalizador aux;
    aux = inicioCadena(cad);
    if (aux != finalCadena(cad)) {
      TInfo info;
      nat n;
      info = infoCadena(aux, cad);
      n = natInfo(info);
      while ((aux != NULL)  && (!res))
      {
        aux = siguiente(aux, cad);
        if (aux != NULL){
          res = (siguienteClave( n, aux, cad) != NULL);
          info = infoCadena(aux, cad);
          n = natInfo(info);
        }
      }
    } else
    {
      res = false;
    } 
  }
  return res;
}

/*
  Devuelve 'true' si y solo si 'c1' y 'c2' son iguales (es decir, si los
  elementos son iguales y en el mismo orden).
  Si esVaciaCadena(c1) y esVaciaCadena(c2) devuelve 'true'.
  El tiempo de ejecución en el peor caso es O(n1 + n2), siendo 'n1' u 'n2' la
  cantidad de elementos de 'c1' y 'c2' respectivamente.
*/
bool sonIgualesCadena(TCadena c1, TCadena c2) {
  if ((esVaciaCadena(c1)) && (esVaciaCadena(c2))) {
    return true;
  } else if (((esVaciaCadena(c1)) && (!esVaciaCadena(c2))) || ((!esVaciaCadena(c1)) && (esVaciaCadena(c2)))) {
      return false;
  } else {
    if (longitud(c1) != longitud(c2))
    {
      return false;
    } else {
      TLocalizador i = inicioCadena(c1);
      TLocalizador j = inicioCadena(c2);
      while (((i != NULL) || (j != NULL)) && (sonIgualesInfo((infoCadena(i, c1)), (infoCadena(j, c2))))) {
        i = siguiente(i, c1);
        j = siguiente(j, c2);
      }
      return ((i == NULL) && (j == NULL));
    }
  }
}

/*
  Devuelve el resultado de concatenar 'c2' después de 'c1'.
  La 'TCadena' resultado no comparte memoria ni con 'c1' ni con 'c2'.
  El tiempo de ejecución en el peor caso es O(n1 + n2), siendo 'n1' u 'n2' la
  cantidad de elementos de 'c1' y 'c2' respectivamente.
*/
TCadena concatenar(TCadena c1, TCadena c2){
  TCadena i,j;
  i = copiarSegmento(inicioCadena(c1),finalCadena(c1),c1);
  j = copiarSegmento(inicioCadena(c2),finalCadena(c2),c2);
  i = insertarSegmentoDespues(j,finalCadena(i), i);
  return i;
}
/*
  Se ordena 'cad' de manera creciente según los componentes naturales de sus
  elementos.
  Devuelve 'cad'
  Precondición: ! hayNatsRepetidos(cad)
  No se debe obtener ni devolver memoria de manera dinámica.
  Se debe mantener las relaciones de precedencia entre localizadores.
  Si esVaciaCadena(cad) no hace nada.
  El tiempo de ejecución en el peor caso es O(n^2), siendo 'n' la cantidad de
  elementos de 'cad'.
*/
TCadena ordenar(TCadena cad){
  if ((!esVaciaCadena(cad)) && (longitud(cad) > 1)) {
    TLocalizador loc1, loc2, loc3;
    loc1 = loc3 = finalCadena(cad);
    loc2 = anterior(loc1, cad);
    while (loc3 != NULL){
      loc1 = loc3;
      while (loc2 != NULL) {
        nat n1, n2;
        n1 = natInfo(infoCadena(loc1, cad));
        n2 = natInfo(infoCadena(loc2, cad));
        if (n2 > n1)  {
          intercambiar(loc1,loc2,cad);
        }
        loc1 = anterior(loc1, cad);
        loc2 = anterior(loc2, cad);
      }
      loc3 = anterior(loc3, cad);
    }
  } while (!estaOrdenadaPorNaturales(cad)){
    ordenar(cad);
  }
  return cad;
}

/*
  Cambia todas las ocurrencias de 'original' por 'nuevo' en los elementos
  de 'cad'.
  Devuelve 'cad'
  No debe quedar memoria inaccesible.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cad'.
*/
TCadena cambiarTodos(nat original, nat nuevo, TCadena cad)  {
  TLocalizador aux;
  aux = inicioCadena(cad);;
  if (original != nuevo) 
  {
    while (aux != NULL)   {
      if (natInfo(infoCadena(aux, cad)) != original) 
      {
        aux = siguienteClave(original,aux,cad);
      }
      if (aux != NULL) {
        TInfo i =  NULL;
        TInfo x = infoCadena(aux,cad);
        double j = realInfo(infoCadena(aux, cad));
        i = crearInfo(nuevo, j);
        cad = cambiarEnCadena(i,aux,cad);
        aux = siguienteClave(original,aux,cad);
        i = NULL;
        liberarInfo(x);
      }
    }
  }
  return cad;
}
/*
  Devuelve la 'TCadena' de elementos de 'cad' que cumplen
  "menor <= natInfo (elemento) <= mayor".
  El orden relativo de los elementos en la 'TCadena' resultado debe ser el mismo
  que en 'cad'.
  Precondición: estaOrdenadaPorNaturales (cad), 'menor' <= 'mayor',
  pertenece (menor, cad), pertenece (mayor, cad).
  La 'TCadena' resultado no comparte memoria con 'cad'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cad'.
*/
TCadena subCadena(nat menor, nat mayor, TCadena cad)  {
  TLocalizador i, j;
  TCadena res;
  i = inicioCadena(cad);
  j = finalCadena(cad);
  if (natInfo(infoCadena(i,cad)) != menor)  {
    i = siguienteClave(menor,i,cad);
  }
  if (natInfo(infoCadena(j,cad)) != mayor) { 
    j = anteriorClave(mayor,j,cad);
  }
  res = copiarSegmento(i,j,cad);
  return res;
}

