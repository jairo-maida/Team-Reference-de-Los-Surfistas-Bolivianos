/**
 * Autor: Simon Lindholm
 * Fecha: 2015-02-18
 * Licencia: CC0
 * Código: marian's (TC) code
 * Descripción: Autómata de Aho-Corasick, utilizado para
 * búsqueda de múltiples patrones.
 * Se inicializa con AhoCorasick ac(patterns); el nodo inicial
 * del autómata estará en el índice 0.
 * find(word) devuelve, para cada posición, el índice de la palabra
 * más larga que termina ahí, o -1 si no hay ninguna.
 * findAll($-$, word) encuentra todas las palabras
 * (hasta $N \sqrt N$ si no hay patrones duplicados) que comienzan en
 * cada posición (las más cortas primero).
 * Se permiten patrones duplicados; no se permiten patrones vacíos.
 * Para encontrar las palabras más largas que comienzan en cada posición,
 * invierte todas las entradas.
 * Para alfabetos grandes, divide cada símbolo en partes, con
 * bits centinela para marcar los límites de los símbolos.
 * Tiempo: la construcción toma $O(26N)$, donde $N =$ suma de
 * las longitudes de los patrones.
 * find(x) es $O(N)$, donde N = longitud de x. findAll es $O(NM)$.
 */
#pragma once

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
typedef long long ll;

// Estructura principal del autómata de Aho-Corasick
struct AhoCorasick {
    // Tamaño del alfabeto (por defecto 26 letras mayúsculas)
    // Caracter base es 'A' pero puede ser otro, cambiar de ser necesario
    enum { alpha = 26,
           first = 'A' };

    // Estructura de cada nodo en el trie
    struct Node {
        int back;          // Enlace de fallo, a dónde debo saltar (fail link)
        int next[alpha];   // Enlaces a hijos (para cada letra del alfabeto)
        int start = -1;    // Índice del primer patrón que
                           // termina en este nodo
        int end = -1;      // Último patrón que termina en este nodo
        int nMatches = 0;  // Cantidad de patrones que terminan aquí
                           // (incluyendo por fail links)

        // Inicializa hijos con valor `v`
        Node(int v) { memset(next, v, sizeof(next)); }
    };

    vector<Node> N;     // Lista de nodos del trie
    vector<int> backp;  // Enlaces hacia patrones anteriores
                        // (para patrones duplicados)

    // Inserta un patrón en el trie
    void insert(string& s, int j) {
        assert(!s.empty());
        int n = 0;  // Empezar en el nodo raíz

        for (char c : s) {
            // Referencia al hijo correspondiente al carácter actual
            int& m = N[n].next[c - first];
            if (m == -1) {
                // Si no existe el nodo hijo, lo creamos
                n = m = N.size();
                N.emplace_back(-1);
            } else
                n = m;  // Continuamos al hijo existente
        }

        // Si es la primera vez que se alcanza
        // este nodo como final de un patrón
        if (N[n].end == -1) N[n].start = j;

        // Mantenemos enlace a patrón anterior si hay duplicados
        backp.push_back(N[n].end);
        N[n].end = j;     // Marcamos que este patrón termina aquí
        N[n].nMatches++;  // Aumentamos la cantidad de coincidencias
    }

    // Constructor: recibe un conjunto de patrones y construye el autómata
    AhoCorasick(vector<string>& pat) : N(1, -1) {
        // Insertar todos los patrones en el trie
        rep(i, 0, pat.size()) insert(pat[i], i);

        // Inicializar nodo raíz con enlace a un nodo dummy adicional
        N[0].back = N.size();
        N.emplace_back(0);

        // Construcción de los enlaces de fallo (fail links)
        queue<int> q;
        for (q.push(0); !q.empty(); q.pop()) {
            int n = q.front(), prev = N[n].back;
            rep(i, 0, alpha) {
                int& ed = N[n].next[i];   // Hijo actual
                int y = N[prev].next[i];  // Hijo del nodo de fallo

                if (ed == -1) {
                    // Si no hay hijo, redirigir a hijo del nodo de fallo
                    ed = y;
                } else {
                    // Si sí hay hijo, se construye su fail link
                    // y se actualizan coincidencias
                    N[ed].back = y;

                    // Actualizar enlaces de patrones duplicados (si los hay)
                    (N[ed].end == -1 ? N[ed].end : backp[N[ed].start]) =
                        N[y].end;

                    // Acumular cantidad de coincidencias desde el fail link
                    N[ed].nMatches += N[y].nMatches;

                    // Añadir hijo a la cola para procesar sus hijos
                    q.push(ed);
                }
            }
        }
    }

    // Búsqueda de patrones en un texto. Devuelve un vector con el
    // índice del patrón más largo que termina en cada posición
    // del texto, o -1 si no hay ninguno.
    vector<int> find(string word) {
        int n = 0;  // Comenzar desde la raíz
        vector<int> res;
        // ll count = 0;

        for (char c : word) {
            // Avanzar al siguiente nodo
            n = N[n].next[c - first];
            // Guardar el patrón (si hay alguno que termina aquí)
            res.push_back(N[n].end);

            // count += N[n].nMatches;
        }
        return res;
    }

    // Búsqueda de **todos** los patrones que
    // terminan en cada posición del texto.
    vector<vector<int>> findAll(vector<string>& pat, string word) {
        vector<int> r = find(word);
        vector<vector<int>> res(word.size());

        rep(i, 0, word.size()) {
            int ind = r[i];
            // Seguir los enlaces hacia atrás (backp) para
            // encontrar patrones anteriores
            while (ind != -1) {
                // Marcar la posición donde inicia el patrón
                res[i - pat[ind].size() + 1].push_back(ind);
                // Saltar a un patrón duplicado anterior (si lo hay)
                ind = backp[ind];
            }
        }
        return res;
    }
};

int main() {
    // Lista de patrones a buscar
    vector<string> patrones = {"HOLA", "MUNDO", "LO", "NO"};

    // Crear el autómata
    AhoCorasick ac(patrones);

    // Texto donde se van a buscar los patrones
    string texto = "HOLAMUNDONOMUNDO";

    // Buscar todas las ocurrencias de los patrones en el texto
    vector<vector<int>> resultados = ac.findAll(patrones, texto);

    // Mostrar resultados
    for (int i = 0; i < resultados.size(); ++i) {
        for (int id : resultados[i]) {
            cout << "Patron " << patrones[id]
                 << " encontrado en posicion " << i << '\n';
        }
    }

    /** Impresión
     * Patron HOLA encontrado en posicion 0
     * Patron MUNDO encontrado en posicion 4
     * Patron NO encontrado en posicion 9
     * Patron MUNDO encontrado en posicion 11
     * */

    return 0;
}