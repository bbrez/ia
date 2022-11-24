use std::collections::HashMap;

#[allow(dead_code)]
#[derive(Clone, Debug)]
struct Aresta {
    origem: u32,
    peso: u32,
    destino: u32,
}

#[allow(dead_code)]
impl Aresta {
    pub fn new(origem: u32, peso: u32, destino: u32) -> Aresta {
        Aresta {
            origem,
            peso,
            destino,
        }
    }

    pub fn get_peso(self) -> u32 {
        self.peso
    }
}

#[allow(dead_code)]
#[derive(Clone, Debug)]
struct Vertice {
    id: u32,                       //Id do vertice, sua posição no vetor de vértices do grafo
    tag: String,                   //"nome" do vertice, usado para identificação pelo usuario
    arestas: HashMap<u32, Aresta>, //HashMap sendo utilizado como vetor esparso, Arestas são inseridas no indice do id de seu destino
}

#[allow(dead_code)]
impl Vertice {
    pub fn new(id: u32, tag: String) -> Vertice {
        Vertice {
            id,
            tag,
            arestas: HashMap::new(),
        }
    }

    pub fn set_aresta(&mut self, peso: u32, destino: u32) {
        self.arestas
            .entry(destino)
            .and_modify(|ar| ar.peso = peso)
            .or_insert(Aresta::new(self.id, peso, destino));
    }

    pub fn get_aresta(self, destino: u32) -> Option<Aresta> {
        self.arestas.get(&destino).cloned()
    }
}

#[allow(dead_code)]
#[derive(Clone, Debug)]
struct Grafo {
    vertices: Vec<Vertice>, //Vetor de vertices, sempre inseridos linearmente, o Id de um Vertice é sua posição no vetor
    orientado: bool, //Indica se o Grafo é orientado, se for, toda inserção de aresta chama a inserção de uma aresta em sentido oposto
}

#[allow(dead_code)]
impl Grafo {
    pub fn new(orientado: bool) -> Grafo {
        Grafo {
            vertices: Vec::new(),
            orientado,
        }
    }

    pub fn add_vertice(mut self, tag: String) {
        if self
            .vertices
            .iter()
            .find_map(|vert| if vert.tag == tag { Some(vert) } else { None })
            .is_none()
        {
            self.vertices
                .push(Vertice::new(self.vertices.len().try_into().unwrap(), tag));
        };
    }

    pub fn get_vertice(&self, tag: String) -> Option<&Vertice> {
        self.vertices
            .iter()
            .find_map(|vert| if vert.tag == tag { Some(vert) } else { None })
    }

    pub fn get_vertice_by_id(&mut self, id: u32) -> Option<&mut Vertice> {
        self.vertices
            .iter_mut()
            .find_map(|vert| if vert.id == id { Some(vert) } else { None })
    }

    pub fn add_aresta(mut self, origem: u32, peso: u32, destino: u32) {
        let vert = self
            .get_vertice_by_id(origem)
            .expect("O vertice deve existir");
        vert.set_aresta(peso, destino);
    }
}
