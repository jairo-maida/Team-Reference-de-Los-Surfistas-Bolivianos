// Cantidad de elementos en el arreglo original.
int n;

/*
 Vector que representa el arbol binario de forma implícita
 (Tener en cuenta que esta estructura debe manipularse con 
 indexación en 1).
*/

vector<int> t(4 * n, 0); 

/*
  Al momento de construir un SegmentTree hay que tomar en 
  cuenta dos cosas: el valor almacenado en cada nodo y la 
  operación encargada de fusionar los valores de los nodos.
*/

void build(vector<int> &a, int v, int tl, int tr){
  if(tl == tr){
    t[v] = a[tl];
  }else{
    int tm = (tl + tr) / 2;
    build(a, 2 * v, tl, tm);
    build(a, 2 * v + 1, tm + 1, tr);

    t[v] = t[2 * v] + t[2 * v + 1];
  }
}

int sum(int v, int tl, int tr, int l, int r) {
  int sum = 0;
  if(l > r){
    sum = 0;
  }else if(l == tl && r == tr){
    sum = t[v];
  }else{
    int tm = (tl + tr) / 2;
    sum = sum(v * 2, tl, tm, min(r, tm));
    sum += sum(v * 2 + 1, tm + 1, max(l, tm + 1), r);
  }
  return sum;
}

void update(int v, int tl, int tr, int pos, int new_val){
  if(tl == tr){
    t[v] = new_val;
  }else{
    int tm = (tl + tr) / 2;

    if(pos <= tm){
      update(2 * v, tl, tm, pos, new_val);
    }else{
      update(2 * v + 1, tm + 1, tr, pos, new_val);
    }

    t[v] = t[2 * v]  + t[2 * v + 1];
  }
}
