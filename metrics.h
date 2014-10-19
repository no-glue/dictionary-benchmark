template<class Adapter>class Metrics {
public:
    Metrics() {}
    Metrics(Adapter * & adapter): adapter(adapter) {}
    void collect_nodes() {
        // add nodes to results
        collect_nodes(adapter);
    }
    int nodes() {
        // get number of nodes
        return nodes(adapter);
    }
    void collect_edges() {
        // add edges to results
        collect_edges(adapter);
    }
    int edges() {
        // get number of edges
        return edges(adapter);
    }
    void collect_density() {
        // add density to results
        collect_density(adapter);
    }
    double density() {
        // get density
        return density(adapter);
    }
    void collect_average_degree() {
        // add average degree to results
        collect_average_degree(adapter);
    }
    double average_degree() {
        // average degree
        return average_degree(adapter);
    }
    void breadth_first_search() {
        // breadth first search
        breadth_first_search(adapter);
    }
private:
    Adapter * adapter;
    void collect_nodes(Adapter * & adapter) {
        // add nodes to results
        adapter->collect_nodes();
    }
    int nodes(Adapter * & adapter) {
        // get number of nodes
        return adapter->nodes();
    }
    void collect_edges(Adapter * & adapter) {
        // add edges to results
        adapter->collect_edges();
    }
    int edges(Adapter * & adapter) {
        // get number of edges
        return adapter->edges();
    }
    void collect_density(Adapter * & adapter) {
        // add density to results
        adapter->collect_density();
    }
    double density(Adapter * & adapter) {
        // get density
        return adapter->density();
    }
    void collect_average_degree(Adapter * & adapter) {
        // add average degree to results
        adapter->collect_average_degree();
    }
    double average_degree(Adapter * & adapter) {
        // average degree
        return adapter->average_degree();
    }
    void breadth_first_search(Adapter * & adapter) {
        // breadth first search
        adapter->breadth_first_search();
    }
};