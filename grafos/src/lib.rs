use std::collections::HashMap;

#[allow(dead_code)]
struct Aresta {
    origem: u32,
    peso: u32,
    destino: u32,
}

impl Aresta {
    pub fn new(origem: u32, peso: u32, destino: u32) -> Aresta {
        Aresta {
            origem,
            peso,
            destino,
        }
    }
}

#[allow(dead_code)]
struct Vertice {
    id: u32,
    arestas: HashMap<u32, Aresta>,
}

impl Vertice {
    pub fn new(id: u32) -> Vertice {
        Vertice {
            id,
            arestas: HashMap::new(),
        }
    }
}

#[allow(dead_code)]
struct Grafo {
    vertices: HashMap<u32, Vertice>,
    orientado: bool,
}

impl Grafo {
    pub fn new(orientado: bool) -> Grafo {
        Grafo {
            vertices: HashMap::new(),
            orientado,
        }
    }

    pub fn set_aresta(mut self, origem: u32, peso: u32, destino: u32) {
        let vert = self.vertices.entry(origem).or_insert(Vertice::new(origem));
        vert.arestas
            .entry(destino)
            .and_modify(|ar| ar.peso = peso)
            .or_insert(Aresta::new(origem, peso, destino));
    }
}
