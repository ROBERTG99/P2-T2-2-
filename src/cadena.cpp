#include "../include/cadena.h"
#include "../include/utils.h"
#include "../include/info.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct nodo
{
  TInfo dato;
  TLocalizador anterior;
  TLocalizador siguiente;
};

struct repCadena
{
  TLocalizador inicio;
  TLocalizador final;
};

/*
  Devuelve 'true' si y solo si 'loc' es un 'TLocalizador' válido.
  En cadenas enlazadas un 'TLocalizador' es válido si y solo si no es 'NULL'.
  El tiempo de ejecución en el peor caso es O(1).
*/
bool esLocalizador(TLocalizador loc) { return loc != NULL; }

/*
  Devuelve la 'TCadena' vacía (sin elementos).
  El tiempo de ejecución en el peor caso es O(1).
*/
TCadena crearCadena()
{
  TCadena res = new repCadena;
  res->inicio = res->final = NULL;
  return res;
}

/*
  Libera la memoria asignada a 'cad' y la de todos sus elementos.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en 'cad'.
*/
void liberarCadena(TCadena cad)
{
  TLocalizador a_borrar;
  while (cad->inicio != NULL)
  {
    a_borrar = cad->inicio;
    cad->inicio = cad->inicio->siguiente;
    liberarInfo(a_borrar->dato);
    delete a_borrar;
  }
  delete cad;
}

/*
  Devuelve 'true' si y solo si 'cad' es vacía (no tiene elementos).
  El tiempo de ejecución en el peor caso es O(1).
*/
bool esVaciaCadena(TCadena cad)
{
  assert(((cad->inicio == NULL) && (cad->final == NULL)) ||
         ((cad->inicio != NULL) && (cad->final != NULL)));
  return ((cad->inicio == NULL) && (cad->final == NULL));
}

/*
  Devuelve el 'TLocalizador' con el que se accede al inicio de 'cad'.
  Si esVaciaCadena(cad) devuelve un 'TLocalizador' no válido.
  El tiempo de ejecución en el peor caso es O(1).
*/
TLocalizador inicioCadena(TCadena cad)
{
  TLocalizador res;
  if (esVaciaCadena(cad))
  {
    res = NULL;
  }
  else
  {
    res = cad->inicio;
  }
  return res;
}

/*
  Devuelve el 'TLocalizador' con el que se accede al final de 'cad'.
  Si es_vacia_cadena(cad) devuelve un 'TLocalizador' no válido.
  El tiempo de ejecución en el peor caso es O(1).
*/
TLocalizador finalCadena(TCadena cad)
{
  TLocalizador res;
  if (esVaciaCadena(cad))
  {
    res = NULL;
  }
  else
  {
    res = cad->final;
  }
  return res;
}

/*
  Devuelve el elemento de 'cad' al que se accede con 'loc'.
  Precondición: localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(1).
*/
TInfo infoCadena(TLocalizador loc, TCadena cad)
{
  return loc->dato;
}

/*
  Devuelve el 'TLocalizador' con el que se accede al elemento de 'cad'
  inmediatamente siguiente a 'loc'.
  Si esFinalCadena(loc, cad) devuelve un 'TLocalizador' no válido.
  Precondición: localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(1).
*/
TLocalizador siguiente(TLocalizador loc, TCadena cad)
{
  assert(localizadorEnCadena(loc, cad));
  TLocalizador res;
  if (esFinalCadena(loc, cad))
  {
    res = NULL;
  }
  else
  {
    res = loc->siguiente;
  }
  return res;
}

/*
  Devuelve el 'TLocalizador' con el que se accede al elemento de 'cad'
  inmediatamente anterior a 'loc'.
  Si esInicioCadena(loc, cad) devuelve un 'TLocalizador' no válido.
  Precondición: localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(1).
*/
TLocalizador anterior(TLocalizador loc, TCadena cad)
{
  TLocalizador res;
  if (esInicioCadena(loc, cad))
  {
    res = NULL;
  }
  else
  {
    res = loc->anterior;
  }
  return res;
}

/*
  Devuelve 'true' si y solo si con 'loc' se accede al último elemento de 'cad'.
  Si esVaciaCadena (cad) devuelve 'false'.
  El tiempo de ejecución en el peor caso es O(1).
*/
bool esFinalCadena(TLocalizador loc, TCadena cad)
{
  bool aux;
  if (esVaciaCadena(cad))
  {
    aux = false;
  }
  else
  {
    aux = (loc == cad->final);
  }
  return aux;
}

/*
  Devuelve 'true' si y solo si con 'loc' se accede al primer elemento de 'cad'.
  Si esVaciaCadena (cad) devuelve 'false'.
  El tiempo de ejecución en el peor caso es O(1).
*/
bool esInicioCadena(TLocalizador loc, TCadena cad)
{
  bool aux;
  if (esVaciaCadena(cad))
  {
    aux = false;
  }
  else
  {
    aux = (loc == cad->inicio);
  }
  return aux;
}

/*
  Se inserta 'i' como último elemento de 'cad'.
  Devuelve 'cad'.
  Si esVaciaVadena (cad) 'i' se inserta como único elemento de 'cad'.
  El tiempo de ejecución en el peor caso es O(1).
*/
/* TLocalizador res = new nodo;
  res->dato = i;
  if (esVaciaCadena(cad)) {
    res->siguiente = NULL;
    res->anterior = NULL;
    cad->final = cad->inicio = res;
  } else {
    res->siguiente = NULL;
    res->anterior = cad->final;
    cad->final->siguiente = res;
    cad->final = res;
  }
  res = NULL;
  delete res;
  return cad;
}
*/
TCadena insertarAlFinal(TInfo i, TCadena cad)
{
  TLocalizador aux = new nodo;
  aux->dato = i;
  aux->siguiente = NULL;
  if (esVaciaCadena(cad))
  {
    aux->anterior = NULL;
    cad->inicio = cad->final = aux;
  }
  else
  {
    aux->anterior = cad->final;
    cad->final->siguiente = aux;
    cad->final = aux;
  }
  aux = NULL;
  delete aux;
  return cad;
}
/*
  Se inserta 'i' como un nuevo elemento inmediatamente antes de 'loc'.
  Devuelve 'cad'.
  Precondición: localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(1).
*/
TCadena insertarAntes(TInfo i, TLocalizador loc, TCadena cad)
{
  TLocalizador res = new nodo;
  res->dato = i;
  if (esInicioCadena(loc, cad))
  {
    res->anterior = NULL;
    res->siguiente = loc;
    cad->inicio = res;
    loc->anterior = res;
  }
  else 
  {
    loc->anterior->siguiente = res;
    res->anterior = loc->anterior;
    res->siguiente = loc;
    loc->anterior = res;
  }
  res = NULL;
  delete res;
  return cad;
}

/*
  Se remueve el elemento al que se accede desde 'loc' y se libera la memoria
  asignada al mismo y al nodo apuntado por el localizador.
  Devuelve 'cad'.
  El valor de 'loc' queda indeterminado.
  Precondición: localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(1).
*/
TCadena removerDeCadena(TLocalizador loc, TCadena cad)
{
  if (loc != NULL)
  {
    if (loc == cad->inicio)
    {
      if (loc == cad->final)
      {
        cad->final = cad->inicio = NULL;
        liberarInfo(loc->dato);
      }
      else
      {
        loc->siguiente->anterior = NULL;
        cad->inicio = loc->siguiente;
        loc->siguiente = NULL;
        liberarInfo(loc->dato);
      }
    }
    else if (loc == cad->final)
    {
      loc->anterior->siguiente = NULL;
      cad->final = loc->anterior;
      loc->anterior = NULL;
      liberarInfo(loc->dato);
    }
    else
    {
      loc->siguiente->anterior = loc->anterior;
      loc->anterior->siguiente = loc->siguiente;
      loc->anterior = NULL;
      loc->siguiente = NULL;
      liberarInfo(loc->dato);
    }
  }
  delete loc;
  return cad;
}

/*
  Imprime los elementos de 'cad' de la siguiente forma:
  (n de pos1,r de pos1)(n de pos2,r de pos2) ...
  donce 'n` es el componente natural y 'r' es el componente real.
  Antes de terminar, se debe imprimir un fin de linea.
  Si esVaciaCadena(cad) sólo se imprime el fin de línea.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en 'cad'.
*/
void imprimirCadena(TCadena cad)
{
  TLocalizador res;
  if (esVaciaCadena(cad))
  {
    printf("\n");
  }
  else
  {
    res = cad->inicio;
    while (res != NULL)
    {
      printf("(%i,%.2f)", natInfo(res->dato), realInfo(res->dato));
      res = res->siguiente;
    }
    printf("\n");
  }
  res = NULL;
  delete res;
}

/*
  Devuelve el 'TLocalizador' con el que se accede al k-esimo elemento de 'cad'.
  Si 'k' es 0 o mayor a la cantidad de elementos de 'cad' devuelve un
  localizdor  no válido.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en 'cad'.
*/
TLocalizador kesimo(nat k, TCadena cad)
{
  TLocalizador res;
  nat i = 1;
  if (k == 0)
  {
    res = NULL;
  }
  else
  {
    res = inicioCadena(cad);
    while ((res != NULL) && (i < k))
    {
      i++;
      res = siguiente(res, cad);
    }
  }
  return res;
}

/*
  Devuelve 'true' si y solo si con 'loc' se accede a un elemento de 'cad',
  (o sea, si apunta a un nodo de 'cad').
  Si esVaciaCadena (cad) devuelve 'false'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en 'cad'.
*/
bool localizadorEnCadena(TLocalizador loc, TCadena cad)
{
  TLocalizador cursor = inicioCadena(cad);
  while (esLocalizador(cursor) && (cursor != loc))
    cursor = siguiente(cursor, cad);
  return esLocalizador(cursor);
}

/*
  Devuelve 'true' si y solo si 'loc1' es igual o precede a 'loc2' en 'cad'.
  Si esVaciaCadena (cad) devuelve 'false'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en 'cad'.
*/
bool precedeEnCadena(TLocalizador loc1, TLocalizador loc2, TCadena cad)
{
  bool res;
  res = localizadorEnCadena(loc1, cad);
  if (res)
  {
    TLocalizador cursor = loc1;
    while (esLocalizador(cursor) && (cursor != loc2))
      cursor = siguiente(cursor, cad);
    res = esLocalizador(cursor);
    assert(!res || localizadorEnCadena(loc2, cad));
  }
  return res;
}

/*
  Se inserta en 'cad' la 'TCadena' 'sgm' inmediatamente después de 'loc',
  manteniendo los elementos originales y el orden relativo entre ellos.
  Devuelve 'cad'.
  No se debe obtener memoria (los nodos de 'sgm' pasan a ser parte de 'cad').
  Se libera la memoria asignada al resto de las estructuras de 'sgm'.
  El valor de 'sgm' queda indeterminado.
  Si esVaciaCadena(cad) 'loc' es ignorado y el segmento queda insertado.
  Precondición: esVaciaCadena(cad) o localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(1).
*/
TCadena insertarSegmentoDespues(TCadena sgm, TLocalizador loc, TCadena cad)
{
  if (!esVaciaCadena(sgm)) {
    if (esVaciaCadena(cad))
    {
      cad->inicio = sgm->inicio;
      cad->final = sgm->final;
    } else if (esFinalCadena(loc,cad))
    {
      loc->siguiente = sgm->inicio;
      sgm->inicio->anterior = cad->final;
      cad->final = sgm->final;
    } else 
    {
      loc->siguiente->anterior = sgm->final;
      sgm->final->siguiente = loc->siguiente;
      loc->siguiente = sgm->inicio;
      sgm->inicio->anterior = loc;
    }
  }
  sgm->inicio = sgm->final = NULL;
  liberarCadena(sgm);
  return cad;
}

/*
  Devuelve una 'TCadena' con los elementos de 'cad' que se encuentran entre
  'desde' y 'hasta', incluidos.
  La 'TCadena' resultado no comparte memoria con 'cad'.
  Si esVaciaCadena(cad) devuelve la 'TCadena' vacia.
  Precondición: esVaciaCadena(cad) o precedeEnCadena(desde, hasta, cad).
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en la cadena resultado.
*/
TCadena copiarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad)
{
  TCadena x;
  x = crearCadena();
  if (esVaciaCadena(cad))
  {
    return x;
  }
  else
  {
    TInfo aux;
    while (precedeEnCadena(desde, hasta, cad))
    {
      aux = copiaInfo(desde->dato);
      insertarAlFinal(aux, x);
      desde = desde->siguiente;
    }
  }
  return x;
}

/*
  Remueve de 'cad' los elementos que se encuentran  entre 'desde' y 'hasta',
  incluidos y libera la memoria que tenían asignada y la de sus nodos.
  Devuelve 'cad'.
  Si esVaciaCadena(cad) devuelve la 'TCadena' vacía.
  Precondición: esVaciaCadena(cad) o precedeEnCadena(desde, hasta, cad).
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en la cadena resultado.
*/
TCadena borrarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad)
{
  TLocalizador a_borrar;
  if (esInicioCadena(desde, cad))
  {
    while (cad->inicio != hasta)
    {
      a_borrar = cad->inicio;
      cad->inicio = cad->inicio->siguiente;
      liberarInfo(a_borrar->dato);
    }
  }
  else
  {
    while (desde != hasta->siguiente)
    {
      a_borrar = desde;
      desde = desde->siguiente;
      liberarInfo(a_borrar->dato);
    }
  }
  delete a_borrar;
  return cad;
}

/*
  Sustituye con 'i' el elemento de 'cad' al que se accede con 'loc'.
  Devuelve 'cad'.
  No destruye el elemento al que antes se accedía con 'loc'.
  Precondición: localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(1).
*/
TCadena cambiarEnCadena(TInfo i, TLocalizador loc, TCadena cad)
{
  loc->dato = i;
  return cad;
}

/*
  Intercambia los elementos a los que se accede con 'loc1' y 'loc2'.
  'loc1' y 'loc2' mantienen su relación de precedencia.
  Devuelve 'cad'.
  Precondición:
  localizadorEnCadena (loc1, cad)
  y localizadorEnCadena (loc2, cad).
  El tiempo de ejecución en el peor caso es O(1).
*/
TCadena intercambiar(TLocalizador loc1, TLocalizador loc2, TCadena cad)
{
  TInfo aux;
  aux = loc1->dato;
  loc1->dato = loc2->dato;
  loc2->dato = aux;
  liberarInfo(aux);
  return cad;
}

/*
  Devuelve el primer 'TLocalizador' con el que se accede a un elemento cuyo
  componente natural es igual a 'clave', buscando desde 'loc' (inclusive) hacia
  el final de 'cad'. Si no se encuentra o 'cad' es vacía devuelve un
  'TLocalizador' no válido.
  Precondición: esVaciaCadena(cad) o localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en 'cad'.
*/
TLocalizador siguienteClave(nat clave, TLocalizador loc, TCadena cad)
{
  TLocalizador res;
  if (localizadorEnCadena(loc, cad) == false)
  {
    res = NULL;
  }
  else
  {
    while ((loc->siguiente != cad->final->siguiente) && (clave != natInfo(loc->dato)))
    {
      loc = loc->siguiente;
    }
    if (clave == natInfo(loc->dato))
    {
      res = loc;
    }
    else
    {
      res = NULL;
    }
  }
  return res;
}

/*
  Devuelve el primer 'TLocalizador' con el que se accede a un elemento cuyo
  componente natural es igual a 'clave', buscando desde 'loc' (inclusive) hacia
  el inicio de 'cad'. Si no se encuentra o 'cad' es vacía devuelve un
  'TLocalizador' no válido.
  Precondición: esVaciaCadena(cad) o localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en 'cad'.
*/
TLocalizador anteriorClave(nat clave, TLocalizador loc, TCadena cad)
{
  TLocalizador res;
  if (localizadorEnCadena(loc, cad) == false)
  {
    res = NULL;
  }
  else
  {
    while ((loc->anterior != cad->inicio->anterior) && (clave != natInfo(loc->dato)))
    {
      loc = loc->anterior;
    }
    if (clave == natInfo(loc->dato))
    {
      res = loc;
    }
    else
    {
      res = NULL;
    }
  }
  return res;
}

/*
  Devuelve el 'TLocalizador' con el que se accede al elemento cuyo componente
  natural es el menor en el segmento que va desde 'loc' hasta finalCadena(cad).
  Si hay más de un elemento cuyo valor es el menor el resultado accede al que
  precede a los otros.
  Precondición: localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en 'cad'.
*/
TLocalizador menorEnCadena(TLocalizador loc, TCadena cad)
{
  TLocalizador res;
  nat x = 0;
  while (loc->siguiente != cad->final->siguiente)
  {
    if (natInfo(loc->dato) > x)
    {
      x = natInfo(loc->dato);
      res = loc;
    }
    loc = loc->siguiente;
  }
  return res;
}

/*MAL*/
