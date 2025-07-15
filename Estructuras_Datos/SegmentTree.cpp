/*
  Para construir un nuevo SegmentTree se tienen que tomar 
  en cuenta dos cosas: el valor que se almacenará en cada
  nodo y la operación encargada de fusionar los valores.
*/
void build(int a[], int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = a[tl];
    } else {
        int tm = (tl + tr) / 2;
        build(a, v*2, tl, tm);
        build(a, v*2+1, tm+1, tr);
        t[v] = t[v*2] + t[v*2+1];
    }
}
