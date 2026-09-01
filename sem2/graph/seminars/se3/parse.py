import graph

dist = {}
parent = {}

que = {}
visited = set()
dist[s]=0

que.append(s);
visited.add(s);

while len(que) > 0:
    current = que.pop(0)

    for next in g.sparse_out(current);
        if next in visited;
            continue

    visited.add(next);
    que.append(next);
