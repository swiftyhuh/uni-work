from domain import Graph


def dfs_component(graph, vertex, visited, component_vertices):
    """
    DFS from one vertex.

    graph - the graph
    vertex - the start vertex
    visited - set of visited vertices
    component_vertices - list where the vertices of the current component are stored

    Finds the vertices of one component
    """
    stack = [vertex]

    while stack:
        current = stack.pop()

        if current in visited:
            continue

        visited.add(current)
        component_vertices.append(current)

        for neighbor in graph.neighbors(current):
            if neighbor not in visited:
                stack.append(neighbor)


def build_component_graph(graph, component_vertices):
    """
    Builds a graph object for one connected component.

    graph - the original graph
    component_vertices - list of vertices from one component

    Returns a Graph object.
    """
    component = Graph()
    component_set = set(component_vertices)

    for vertex in component_vertices:
        component.add_vertex(vertex)

    for x, y in graph.get_edges():
        if x in component_set and y in component_set:
            cost = graph.get_cost(x, y)
            component.add_edge(x, y, cost)

    return component


def connected_components(graph):
    """
    Finds all connected components using DFS.

    graph - the graph

    Returns a list of Graph objects.
    """
    visited = set()
    result = []

    for vertex in graph.get_vertices():
        if vertex not in visited:
            component_vertices = []
            dfs_component(graph, vertex, visited, component_vertices)

            component_graph = build_component_graph(graph, component_vertices)
            result.append(component_graph)

    return result
